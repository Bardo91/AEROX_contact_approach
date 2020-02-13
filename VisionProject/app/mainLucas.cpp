#include <opencv2/highgui.hpp>
#include <iostream>

#include <LucasMethod.h>
#include <RealSenseCamera.h>

int main(int _argc, char **_argv){

    cv::Mat image;
    RealSenseCamera realSenseCamera;
    realSenseCamera>>image;
    LucasMethod lucas(image);

    while(true){
        realSenseCamera>>image;
        lucas.method(image);
        cv::waitKey(3);
    }
    return 0;
}