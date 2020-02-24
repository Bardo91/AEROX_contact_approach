#include <opencv2/highgui.hpp>
#include <iostream>
#include <chrono>
#include <gperftools/profiler.h>

#include <TemplateMatchThread.h>
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

    RealSenseCamera realSenseCamera(0);
    TemplateMatchThread templateMatchThread(_argv[1]);

    if(templateMatchThread.templ.rows == 0 ) { // Check for invalid template
        std::cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    std::string fileName = "tmthread_"+std::to_string(time(NULL));
    ProfilerStart(fileName.c_str());
    while(run){
        realSenseCamera.setImage();
        auto start = std::chrono::system_clock::now();
        templateMatchThread.matchThread(realSenseCamera.img);
        auto end = std::chrono::system_clock::now();
        cv::waitKey(3);
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << elapsed.count() << '\n';
    }

    cv::destroyAllWindows();
    ProfilerStop();
    
    return 0;
}