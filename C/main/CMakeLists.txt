cmake_minimum_required(VERSION 3.25)
project(main
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "main")

target_sources(${CMAKE_PROJECT_NAME} 
    PRIVATE ${PROJECT_NAME}.c
    PUBLIC FILE_SET HEADERS 
    BASE_DIRS ${PROJECT_SOURCE_DIR}
    FILES ${PROJECT_NAME}.h
)