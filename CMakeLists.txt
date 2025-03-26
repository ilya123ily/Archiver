cmake_minimum_required(VERSION 3.12)

project(Archivery)

if (NOT CMAKE_BUILD_TYPE) 
        set(CMAKE_BUILD_TYPE Debug) 
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        archiver 
        main.cpp 
        cmd_line_args_parser.cpp 
        cmd_line_args_parser.h 
        application.cpp 
        application.h 
        modified_iostream.cpp 
        modified_iostream.h 
        haffman.cpp 
        haffman.h 
        encode.cpp 
        encode.h 
        decode.cpp 
        decode.h 
        help.h
        exceptions.h 
        utilities.h
)
