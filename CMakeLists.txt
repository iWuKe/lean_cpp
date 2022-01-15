cmake_minimum_required(VERSION 3.0.2)
project(pthread_lean)

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