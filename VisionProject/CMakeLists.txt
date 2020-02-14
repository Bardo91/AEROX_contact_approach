cmake_minimum_required(VERSION 3.10)
project(contact_approach)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)


########################################################
include_directories(include)
add_subdirectory(app)

########################################################
find_package(OpenCV REQUIRED)

########################################################
find_package(realsense2 REQUIRED)

########################################################
add_library(VisionFauli_LIBRARY SHARED src/RealSenseCamera.cpp   include/RealSenseCamera.h 
                                       src/TemplateMatching.cpp  include/TemplateMatching.h
                                       src/FeatureMatching.cpp   include/FeatureMatching.h
                                       src/LucasMethod.cpp       include/LucasMethod.h
                                       src/FarnebackMethod.cpp   include/FarnebackMethod.h)

target_link_libraries(VisionFauli_LIBRARY LINK_PUBLIC ${OpenCV_LIBRARIES})
target_include_directories(VisionFauli_LIBRARY PUBLIC ${OpenCV_INCLUDE_DIR})
            
target_link_libraries(VisionFauli_LIBRARY LINK_PUBLIC ${realsense2_LIBRARY})