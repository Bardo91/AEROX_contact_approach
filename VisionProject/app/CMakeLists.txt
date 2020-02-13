cmake_minimum_required(VERSION 3.10)
project(contact_approach)
include_directories(include)

########################################################
add_executable(template_match	mainTemplMatch.cpp)
target_link_libraries(template_match LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(template_match PUBLIC ${OpenCV_INCLUDE_DIR})

target_link_libraries(template_match LINK_PUBLIC ${realsense2_LIBRARY})

target_link_libraries(template_match PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(features	mainFeatureDescript.cpp)
target_link_libraries(features LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(features PUBLIC ${OpenCV_INCLUDE_DIR})

target_link_libraries(features LINK_PUBLIC ${realsense2_LIBRARY})

target_link_libraries(features PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(sparseOF	mainLucas.cpp)

target_link_libraries(sparseOF PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(denseOF	mainFanerback.cpp)

target_link_libraries(denseOF PUBLIC VisionFauli_LIBRARY)


