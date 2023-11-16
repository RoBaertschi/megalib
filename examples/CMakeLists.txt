cmake_minimum_required(VERSION 3.26)
project(examples C)

set(CMAKE_C_STANDARD 11)


add_executable(log log.c)
target_link_libraries(log megalib)

add_executable(logger logger.c)
target_link_libraries(logger megalib)

add_executable(argvparse argvparse.c)
target_link_libraries(argvparse megalib)

add_executable(vector vector.c)
target_link_libraries(vector megalib)

add_executable(window window.c)
target_link_libraries(window megalib)

