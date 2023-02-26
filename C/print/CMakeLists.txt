cmake_minimum_required(VERSION 3.25)
project(print
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "heart of the system, but another poorly named library")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} 
    PRIVATE ${PROJECT_NAME}.c
    PUBLIC FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES ${PROJECT_NAME}.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE binary)