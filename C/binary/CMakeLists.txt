cmake_minimum_required(VERSION 3.25)
project(binary
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "Decimal to Binary Converter")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 
    PRIVATE binary.c
    PUBLIC FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES binary.h
)