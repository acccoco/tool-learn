set(PRE ${PRE}sync.)

add_executable(${PRE}thread thread.cpp)
add_executable(${PRE}mutex mutex.cpp)
add_executable(${PRE}atomic atomic.cpp)
add_executable(${PRE}yield yield.cpp)
add_executable(${PRE}condition-variable condition_variable.cpp)
add_executable(${PRE}semaphore semaphore.cpp)
add_executable(${PRE}future future.cpp)