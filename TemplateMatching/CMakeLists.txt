cmake_minimum_required(VERSION 3.10)
project(contact_approach)

########################################################
include_directories(include)
add_executable(template_match	src/main.cpp include/TemplateMatching.h include/RealSenseCamera.h src/RealSenseCamera.cpp src/TemplateMatching.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(template_match LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(template_match PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(template_match LINK_PUBLIC ${realsense2_LIBRARY})
