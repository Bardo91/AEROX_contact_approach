cmake_minimum_required(VERSION 3.10)
project(contact_approach)
include_directories(include)

########################################################
add_executable(lucas	)
find_package(OpenCV REQUIRED)
target_link_libraries(lucas LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(lucas PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(lucas LINK_PUBLIC ${realsense2_LIBRARY})

########################################################
add_executable(farneback	)
find_package(OpenCV REQUIRED)
target_link_libraries(farneback LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(farneback PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(farneback LINK_PUBLIC ${realsense2_LIBRARY})