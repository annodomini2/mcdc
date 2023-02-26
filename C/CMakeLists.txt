cmake_minimum_required(VERSION 3.25)
project(mcdc 
        LANGUAGES C
        VERSION 0.1
        DESCRIPTION "MCDC Code Coverage Analyzer")

add_executable(${CMAKE_PROJECT_NAME})
add_subdirectory(binary)
add_subdirectory(bubblesort)
add_subdirectory(function)
add_subdirectory(main)
add_subdirectory(print)
add_subdirectory(solve)
add_subdirectory(threads)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC lib "${PROJECT_SOURCE_DIR}")

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC binary bubblesort function print solve threads)