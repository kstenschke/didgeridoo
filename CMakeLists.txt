cmake_minimum_required(VERSION 3.14)
project(quietschbox C CXX)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Use the package PkgConfig to detect GTK+ headers/library files
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

# Add an executable compiled from hello.c
#ADD_EXECUTABLE(hello main.c)

include_directories("${CMAKE_SOURCE_DIR}/quietschbox")

add_executable(quietschbox
        quietschbox/main.cc
        quietschbox/main.h
        quietschbox/struct/pitch.h
        quietschbox/helper/helper_gtk.cc
        quietschbox/helper/helper_gtk.h
        quietschbox/helper/helper_system.cc
        quietschbox/helper/helper_system.h
        quietschbox/model/WaveGenerator.cc
        quietschbox/model/WaveGenerator.h
        quietschbox/model/ToneSequencer.cc
        quietschbox/model/ToneSequencer.h
)

# Link the target to the GTK+ libraries
TARGET_LINK_LIBRARIES(quietschbox ${GTK3_LIBRARIES})
