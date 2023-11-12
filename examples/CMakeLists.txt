cmake_minimum_required(VERSION 3.26)
project(examples C)

set(CMAKE_C_STANDARD 11)


add_executable(log log.c)
target_link_libraries(log megalib)
target_include_directories(log PRIVATE ../megalib)

add_executable(logger logger.c)
target_link_libraries(logger megalib)
target_include_directories(logger PRIVATE ../megalib)
