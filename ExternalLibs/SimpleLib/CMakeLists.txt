cmake_minimum_required (VERSION 3.1.0)
project (SimpleLib VERSION 1.0.0 DESCRIPTION "Simple library for integration with Qt based project")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(SimpleLib SHARED
    SimpleLib.cpp
)

# set project version
set_target_properties(SimpleLib PROPERTIES VERSION ${PROJECT_VERSION})

# set SOVERSION number
set_target_properties(SimpleLib PROPERTIES SOVERSION 1)

# declare public API
set_target_properties(SimpleLib PROPERTIES PUBLIC_HEADER SimpleLib.h)

