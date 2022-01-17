cmake_minimum_required(VERSION 3.0.2)
project(pthread_lean)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(pthread_lean1
                src/main.cpp)
target_link_libraries(pthread_lean1
 pthread
)

add_executable(pthread_exit
                src/pthread_exit.cpp)
target_link_libraries(pthread_exit
 pthread
)

add_executable(pthread_join
                src/pthread_join.cpp)
target_link_libraries(pthread_join
 pthread
)

add_executable(pthread_synchronize
                src/pthread_synchronize.cpp)
target_link_libraries(pthread_synchronize
 pthread
)

add_executable(pthread_deadlock
                src/pthread_deadlock.cpp)
target_link_libraries(pthread_deadlock
 pthread
)

add_executable(pthread_deadlock1
src/pthread_deadlock1.cpp)
target_link_libraries(pthread_deadlock1
pthread
)

add_executable(producer_and_consumer
                src/producer_and_consumer.cpp)
target_link_libraries(producer_and_consumer
pthread
)

add_executable(producer_and_consumer_sem
                src/producer_and_consumer_sem.cpp)
target_link_libraries(producer_and_consumer_sem
pthread
)


add_executable(mp_tcp
                src/mp_tcp.cpp)
target_link_libraries(mp_tcp
pthread
)