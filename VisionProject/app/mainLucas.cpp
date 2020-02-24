#include <opencv2/highgui.hpp>
#include <iostream>
#include <gperftools/profiler.h>

#include <LucasMethod.h>
#include <RealSenseCamera.h>

#include <signal.h>

bool run = true;
void signal_callback_handler(int signum) {
   // Terminate program
//    exit(signum);
    run = false;
}

int main(int _argc, char **_argv){

    signal(SIGINT, signal_callback_handler);

    cv::Mat image;
    RealSenseCamera realSenseCamera(0);
    realSenseCamera>>image;
    LucasMethod lucas(image);

    std::string fileName = "lucas_"+std::to_string(time(NULL));
    ProfilerStart(fileName.c_str());
    while(run){
        realSenseCamera>>image;
        lucas.method(image);
        cv::waitKey(3);
    }
    cv::destroyAllWindows();
    ProfilerStop();
    return 0;
}