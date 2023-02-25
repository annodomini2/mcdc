cmake_minimum_required(VERSION 3.25)
project(binary
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "Decimal to Binary Converter")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE binary.c)

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_NAME}_if)