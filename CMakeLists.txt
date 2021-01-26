cmake_minimum_required(VERSION 3.14)
project(didgeridoo C CXX)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include_directories("${CMAKE_SOURCE_DIR}/didgeridoo")

add_executable(didgeridoo
        didgeridoo/main.cc
        didgeridoo/main.h
        didgeridoo/struct/pitch.h
        didgeridoo/helper/helper_system.cc
        didgeridoo/helper/helper_system.h
        didgeridoo/model/Generator.cc
        didgeridoo/model/Generator.h
        didgeridoo/model/Didgeridoo.cc
        didgeridoo/model/Didgeridoo.h
)
