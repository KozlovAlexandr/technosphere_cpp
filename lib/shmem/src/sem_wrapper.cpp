#include "sem_wrapper.h"
#include "shmem_exception.h"

namespace shmem
{

Semaphore::Semaphore()
{
    if (sem_init(&sem_, 1, 1) < 0)
    {
        throw ShmemException("cannot init semaphore");
    }
}

Semaphore::~Semaphore()
{
    sem_destroy(&sem_);
}

void Semaphore::post()
{
    if (sem_post(&sem_) < 0)
    {
        throw ShmemException("semaphore post error");
    }
}

void Semaphore::wait()
{
    if (sem_wait(&sem_) < 0)
    {
        throw ShmemException("semaphore wait error");
    }
}

SemaphoreLock::SemaphoreLock(Semaphore &semaphore) : semaphore_(semaphore)
{
    semaphore_.wait();
}

SemaphoreLock::~SemaphoreLock()
{
    semaphore_.post();
}

}