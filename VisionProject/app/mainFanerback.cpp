#include <opencv2/highgui.hpp>
#include <iostream>

#include <FarnebackMethod.h>
#include <RealSenseCamera.h>

int main(int _argc, char **_argv){

    cv::Mat image;
    RealSenseCamera realSenseCamera;
    realSenseCamera>>image;
    FarnebackMethod farneback(image);

    while(true){
        realSenseCamera>>image;
        farneback.method(image);
        cv::waitKey(3);
    }
    return 0;
}