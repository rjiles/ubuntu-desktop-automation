cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 11)
project(ubuntuDesktopBot)
# Local header files here ONLY
SET(TARGET_H
    mouseMover.h  
   )

# Local source files here
SET(TARGET_SRC
    mouseMover.cpp
    )

add_executable(ubuntuDesktopBot main.cpp mouseMover.cpp)