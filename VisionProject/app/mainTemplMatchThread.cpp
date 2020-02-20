#include <opencv2/highgui.hpp>
#include <iostream>
#include <gperftools/profiler.h>

#include <TemplateMatchingThread.h>
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

    RealSenseCamera realSenseCamera;
    TemplateMatching templateMatching(_argv[1]);

    if(templateMatching.templ.rows == 0 ) { // Check for invalid template
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    std::string fileName = "template_"+std::to_string(time(NULL));
    ProfilerStart(fileName.c_str());
    while(run){
        realSenseCamera.setImage();
        templateMatching.matchingMethod(realSenseCamera.img);
        cv::waitKey(3);
    }
    cv::destroyAllWindows();
    ProfilerStop();
    
    return 0;
}