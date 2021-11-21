cmake_minimum_required(VERSION 2.8)
project( DroneVision )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
include_directories(${ltesseract_INCLUDE_DIRS})

add_executable( BlueFilter blueFilter/blueFilter.cpp )
target_link_libraries( BlueFilter ${OpenCV_LIBS} )

add_executable( RedFinder redFinder/redTracker.cpp )
target_link_libraries( RedFinder ${OpenCV_LIBS} )

add_executable( text_recognition textRecognition/tesseract_opencv.cpp )
target_link_libraries( text_recognition ${OpenCV_LIBS} -ltesseract -llept )

#add_executable( RealsenseViewer realsenseExample.cpp )
#target_link_libraries( RealsenseViewer ${DEPENDENCIES} )
#set_property(TARGET RealsenseViewer PROPERTY CXX_STANDARD 11)

#set_target_properties (RealsenseViewer PROPERTIES
#	FOLDER "Examples/OpenCV"
#)

#install(
#	TARGETS
#
#	RealsenseViewer
#
#	RUNTIME DESTINATION
#	${CMAKE_INSTALL_PREFIX}/bin
#)