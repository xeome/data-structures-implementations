cmake_minimum_required(VERSION 3.25)
project(data_structures C)

set(CMAKE_C_STANDARD 23)

# Add -mavx flag to the compiler
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mavx -mavx2")


add_executable(vector vector.c)
add_executable(linked_list linked_list.c)
add_executable(queue queue.c)
add_executable(heap_tree heap_tree.c)
add_executable(huffman huffman.c)
add_executable(hashmap hashmap.c)
