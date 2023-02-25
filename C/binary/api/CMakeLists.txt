cmake_minimum_required(VERSION 3.25)
project(binary_if
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "Decimal to Binary Converter interface")

add_library(${PROJECT_NAME} INTERFACE)

target_sources(${PROJECT_NAME} PUBLIC binary.h)