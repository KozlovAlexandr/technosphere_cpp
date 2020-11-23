add_library(shmem STATIC src/sem_wrapper.cpp)
target_include_directories(shmem PUBLIC include)

add_executable(shmem_example example/shmem_example.cpp)
target_link_libraries(shmem_example shmem pthread)