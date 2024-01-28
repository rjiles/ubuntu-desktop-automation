cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 11)
project(ubuntuDesktopBot)

# Local header files here ONLY
SET(TARGET_H
    mouseMover.h  
    entityFinder.h  
   )

# Local source files here
SET(TARGET_SRC
    mouseMover.cpp
    entityFinder.cpp
    )


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(X11 REQUIRED)
IF (X11_FOUND)
    INCLUDE_DIRECTORIES(${X11_INCLUDE_DIR})
    LINK_LIBRARIES(${X11_LIBRARIES})
ENDIF ( X11_FOUND )
add_executable(ubuntuDesktopBot main.cpp mouseMover.h mouseMover.cpp entityFinder.h entityFinder.cpp)
target_link_libraries(ubuntuDesktopBot ${OpenCV_LIBS})