cmake_minimum_required(VERSION 3.10)
project(contact_approach)

########################################################
include_directories(include)
add_executable(features	src/main.cpp include/FeatureMatching.h include/RealSenseCamera.h src/FeatureMatching.cpp src/RealSenseCamera.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(features LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(features PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(features LINK_PUBLIC ${realsense2_LIBRARY})
