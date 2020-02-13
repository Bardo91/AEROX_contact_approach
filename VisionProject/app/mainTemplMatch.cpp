#include <opencv2/highgui.hpp>
#include <iostream>

#include <TemplateMatching.h>
#include <RealSenseCamera.h>

int main(int _argc, char **_argv){

    RealSenseCamera realSenseCamera;
    TemplateMatching templateMatching(_argv[1]);

    if(templateMatching.templ.rows == 0 ) { // Check for invalid template
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    while(true){
        realSenseCamera.setImage();
        templateMatching.matchingMethod(realSenseCamera.img);
        cv::waitKey(3);
    }
    return 0;
}