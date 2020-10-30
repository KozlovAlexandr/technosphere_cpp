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

    pMmap mmap_;
    Map *map_;
    Semaphore *semaphore_;

public:
    SharedMap(size_t blockSize, size_t blockCount)
    {
        size_t shmemSize = blockCount * blockSize;
        void* mmap = ::mmap(0, shmemSize,
                            PROT_READ | PROT_WRITE,
                            MAP_ANONYMOUS | MAP_SHARED,
                            -1, 0);

        if(mmap == MAP_FAILED)
            throw ShmemException("Failed to create shared map");

        mmap_ = pMmap(static_cast<char*>(mmap), [shmemSize](char* shmem) { ::munmap(shmem, shmemSize); } );

        ShMemState* state = new(mmap_.get()) ShMemState{};

        float header_size = (sizeof(ShMemState) + blockCount) / static_cast<float>(blockSize);

        state->block_size = blockSize;
        state->blocks_count = blockCount - std::floor(header_size);
        state->used_blocks_table = mmap_.get() + sizeof(ShMemState);
        state->first_block = state->used_blocks_table + state->blocks_count;
        ::memset(state->used_blocks_table, FREE_BLOCK, state->blocks_count);

        map_ = new (ShAlloc<Map>{state}.allocate(1)) Map(ShAlloc<PairAllocator>{state});
        semaphore_ = new (ShAlloc<Semaphore>{state}.allocate(1)) Semaphore;
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

    Value remove(const Key &key)
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