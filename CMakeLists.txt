cmake_minimum_required(VERSION 3.0.2)
project(ImageProcessing)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  image_transport
  cv_bridge
  sensor_msgs
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES trajectory_provider
#  CATKIN_DEPENDS mavROS roscpp std_msg
#  DEPENDS system_lib
)

include_directories(include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(image_pub src/image_pub.cpp)
target_link_libraries(image_pub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

add_executable(image_sub src/image_sub.cpp)
target_link_libraries(image_sub ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})