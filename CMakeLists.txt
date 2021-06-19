cmake_minimum_required(VERSION 2.8)
project( DroneVision )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( BlueFilter blueFilter/blueFilter.cpp )
target_link_libraries( BlueFilter ${OpenCV_LIBS} )

add_executable( RedFinder redFinder/redTracker.cpp )
target_link_libraries( RedFinder ${OpenCV_LIBS} )