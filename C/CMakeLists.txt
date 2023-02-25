cmake_minimum_required(VERSION 3.25)
project(mcdc 
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "MCDC Code Coverage Analyzer")

add_executable(${CMAKE_PROJECT_NAME})
#add_subdirectory(lib)
#add_subdirectory(src)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        src/binary.c
        src/bubblesort.c
        src/function.c
        src/mcdc.c
        src/print.c
        src/solve.c
        src/threads.c
        lib/binary.h
        lib/bubblesort.h
        lib/function.h
        lib/mcdc.h
        lib/print.h
        lib/solve.h
        lib/threads.h

)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC lib)