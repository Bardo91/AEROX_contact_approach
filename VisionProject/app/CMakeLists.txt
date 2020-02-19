cmake_minimum_required(VERSION 3.10)
project(contact_approach)
include_directories(include)

########################################################
add_executable(template_match	mainTemplMatch.cpp)

target_link_libraries(template_match PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(features	mainFeatureDescript.cpp)

target_link_libraries(features PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(sparseOF	mainLucas.cpp)

target_link_libraries(sparseOF PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(denseOF	mainFanerback.cpp)

target_link_libraries(denseOF PUBLIC VisionFauli_LIBRARY)

########################################################
add_executable(pointsviewer	mainApproachPCL.cpp)

target_link_libraries(pointsviewer LINK_PUBLIC VisionFauli_LIBRARY)


