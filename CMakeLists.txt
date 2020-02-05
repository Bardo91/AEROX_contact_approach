cmake_minimum_required(VERSION 3.10)
project(contact_approach)

########################################################
add_executable(imshow_test 	src/imshow_test.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(imshow_test LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(imshow_test PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(imshow_test LINK_PUBLIC ${realsense2_LIBRARY})

########################################################
add_executable(image_try src/image_try.cpp)
find_package(OpenCV REQUIRED)
target_link_libraries(image_try LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(image_try PUBLIC ${OpenCV_INCLUDE_DIR})


########################################################

add_executable(temp_mask 	src/temp_mask.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(temp_mask LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(temp_mask PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(temp_mask LINK_PUBLIC ${realsense2_LIBRARY})

########################################################

add_executable(cam_match	src/cam_match.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(cam_match LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(cam_match PUBLIC ${OpenCV_INCLUDE_DIR})

find_package(realsense2 REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
target_link_libraries(cam_match LINK_PUBLIC ${realsense2_LIBRARY})


