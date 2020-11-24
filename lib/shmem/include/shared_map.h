#pragma once

#include <map>
#include <sys/mman.h>
#include "shmem_exception.h"
#include "allocator.h"
#include "sem_wrapper.h"

namespace shmem
{
template<typename Key, typename Value, typename Compare = std::less<Key>>
class SharedMap
{
    using SharedString = std::basic_string<char, std::char_traits<char>, ShAlloc<char>>;

    using Key_ = std::conditional_t<std::is_pod_v<Key>, Key, SharedString>;
    using Value_ = std::conditional_t<std::is_pod_v<Value>, Value, SharedString>;

    using Pair = std::pair<Key_, Value_>;
    using PairAllocator = ShAlloc<Pair>;
    using Map = std::map<Key_, Value_, Compare, PairAllocator>;
    using pMmap = std::unique_ptr<char, std::function<void(char*)>>;
    using pSemaphore = std::unique_ptr<Semaphore, std::function<void(Semaphore*)>>;

    pMmap mmap_;
    pSemaphore semaphore_;
    Map *map_;

public:
    SharedMap(size_t blockSize, size_t blockCount)
    {
        size_t shmemSize = sizeof(Semaphore) + sizeof(Map) + sizeof(ShMemState) + blockCount + blockCount * blockSize;
        void* mmap = ::mmap(0, shmemSize,
                            PROT_READ | PROT_WRITE,
                            MAP_ANONYMOUS | MAP_SHARED,
                            -1, 0);

        if(mmap == MAP_FAILED)
            throw ShmemException("Failed to create shared map");

        mmap_ = pMmap(static_cast<char*>(mmap), [shmemSize](char* shmem) { ::munmap(shmem, shmemSize); } );

        semaphore_ = pSemaphore(new (mmap_.get()) Semaphore{},
                                [](Semaphore *semaphore) { semaphore->~Semaphore(); });

        ShMemState* state = new(mmap_.get() + sizeof(Semaphore) + sizeof(Map)) ShMemState{};

        state->block_size = blockSize;
        state->blocks_count = blockCount;
        state->used_blocks_table = mmap_.get() + sizeof(Semaphore) + sizeof(Map) + sizeof(ShMemState);
        state->first_block = state->used_blocks_table + state->blocks_count;
        ::memset(state->used_blocks_table, FREE_BLOCK, state->blocks_count);

        map_ = new (mmap_.get() + sizeof(Semaphore)) Map(ShAlloc<PairAllocator>{state});
    }

    void update(const Key &key, const Value &value)
    {
        SemaphoreLock semaphoreLock{*semaphore_};
        if (map_->find(transformKey(key)) == map_->end())
            throw SharedMapException("key does not exist");

        map_->insert({transformKey(key), transformValue(value)});
    }

    void insert(const Key &key, const Value &value)
    {
        SemaphoreLock semaphoreLock{*semaphore_};
        if (map_->find(transformKey(key)) != map_->end())
            throw SharedMapException("key exists");

        map_->insert({transformKey(key), transformValue(value)});
    }

    Value get(const Key &key)
    {
        SemaphoreLock semaphoreLock{*semaphore_};
        if (map_->find(transformKey(key)) == map_->end())
            throw SharedMapException("key does not exist");

        return Value{ map_->at(transformKey(key)) };
    }

    void remove(const Key &key)
    {
        SemaphoreLock semaphoreLock{*semaphore_};
        if (map_->find(transformKey(key)) == map_->end())
            throw SharedMapException("key does not exist");

        map_->erase(transformKey(key));
    }

private:

    Key_ transformKey(const Key &key)
    {
        if constexpr (std::is_same_v<Key, Key_>)
            return key;
        else
            return Key_{ key, map_->get_allocator() } ;
    }

    Value_ transformValue(const Value &value)
    {
        if constexpr (std::is_same_v<Value, Value_>)
            return value;
        else
            return Value_{ value, map_->get_allocator() };
    }
};

}