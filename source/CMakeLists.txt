cmake_minimum_required(VERSION 3.22.1)
project(bot)
# Local header files here ONLY
SET(TARGET_H
    mouseMover.h  
   )

# Local source files here
SET(TARGET_SRC
    mouseMover.cpp
    )
    
add_executable(bot main.cpp)