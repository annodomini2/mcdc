cmake_minimum_required(VERSION 3.25)
project(function
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "Only the original author knows why this is a separate component")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 
    PRIVATE ${PROJECT_NAME}.c
    PUBLIC FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES ${PROJECT_NAME}.h
)