#pragma once

#include <semaphore.h>

namespace shmem
{

class Semaphore
{
public:
    Semaphore();
    ~Semaphore();
    void post();
    void wait();

private:
    sem_t sem_;
};

class SemaphoreLock
{
public:
    explicit SemaphoreLock(Semaphore &semaphore);
    ~SemaphoreLock();

private:
    Semaphore &semaphore_;
};

} // namespace shmem