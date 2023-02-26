cmake_minimum_required(VERSION 3.25)
project(mcdc 
        LANGUAGES C
        VERSION 0.1.0
        DESCRIPTION "MCDC Code Coverage Analyzer")
        
add_subdirectory(C)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)