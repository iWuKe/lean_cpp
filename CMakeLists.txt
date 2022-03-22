cmake_minimum_required(VERSION 3.0.2)
project(lean_thread)

#c++11
add_compile_options(-std=c++11)

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
)

add_executable(mt_tcp
                src/mt_tcp.cpp)
target_link_libraries(mt_tcp
pthread
)

add_executable(thread
                src/thread.cpp)
target_link_libraries(thread
)

# add_executable(atomic
#                 src/atomic.cpp)
# target_link_libraries(atomic
#     -latomic
# )

add_executable(lambda
                src/lambda.cpp)
target_link_libraries(lambda
)

add_executable(bind
                src/bind.cpp)
target_link_libraries(bind
)

add_executable(sort
                src/sort.cpp)
target_link_libraries(sort
)

add_executable(ucontext
                src/ucontext.cpp)
target_link_libraries(ucontext
)

#
add_executable(shared_ptr1
                src/shared_ptr1.cpp)
target_link_libraries(shared_ptr1
)

add_executable(search
  src/data_structure/graph.cpp
  src/data_structure/search.cpp
  src/data_structure/main.cpp
  src/data_structure/digraph.cpp
)
target_link_libraries(search
)

add_executable(digraph
  src/data_structure/digraph_main.cpp
  src/data_structure/digraph.cpp
  src/data_structure/directedcycle.cpp
  src/data_structure/disearch.cpp
)
target_link_libraries(digraph
)

add_executable(test1
  src/c++11/test.cpp
  )
target_link_libraries(test1
)

add_executable(vector
  src/data_structure/vector.cpp
)
target_link_libraries(vector
)