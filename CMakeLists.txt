cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
file(GLOB SRC RELATIVE "${CMAKE_SOURCE_DIR}" "*.c")

foreach( target_file ${SRC} )
    string ( REPLACE ".c" "" target ${target_file} )
    message ("Added new executable ${target} ${target_file}")
    add_executable(${target} ${target_file})
endforeach()

