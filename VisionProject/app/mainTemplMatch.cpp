#include <opencv2/highgui.hpp>
#include <iostream>
#include <gperftools/profiler.h>
#include <chrono>

#include <TemplateMatching.h>
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
        auto start = std::chrono::system_clock::now();
        templateMatching.matchingMethod(realSenseCamera.img);
        auto end = std::chrono::system_clock::now();
        cv::waitKey(3);
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << elapsed.count() << '\n';
    }
    cv::destroyAllWindows();
    ProfilerStop();
    return 0;
}