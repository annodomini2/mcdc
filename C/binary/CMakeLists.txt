cmake_minimum_required(VERSION 3.25)
project(binary 
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "Decimal to Binary Converter")

add_subdirectory(api)
add_subdirectory(src)