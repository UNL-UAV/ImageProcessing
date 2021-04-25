cmake_minimum_required(VERSION 2.8)
project( RedTracker )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( RedTracker redTracker.cpp )
target_link_libraries( RedTracker ${OpenCV_LIBS} )

