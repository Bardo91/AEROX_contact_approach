#include <LucasMethod.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>

LucasMethod::LucasMethod(cv::Mat &_input){
    //Create some random colors
    cv::RNG rng;
    for(int i = 0; i < 100; i++){
        int r = rng.uniform(0, 256);
        int g = rng.uniform(0, 256);
        int b = rng.uniform(0, 256);
        colors.push_back(cv::Scalar(r,g,b));
    }
    // Take first frame and find corners in it
    old_frame=_input;
    cvtColor(old_frame, old_gray, CV_BGR2GRAY);
    goodFeaturesToTrack(old_gray, p0, 100, 0.3, 7, cv::Mat(), 7, false, 0.04);
    // Create a mask image for drawing purposes
    mask = cv::Mat::zeros(old_frame.size(), old_frame.type());
    criteria = cv::TermCriteria((cv::TermCriteria::COUNT) + (cv::TermCriteria::EPS), 10, 0.03);
}

void LucasMethod::method(cv::Mat &_input){
    cv::Mat frame, frame_gray;
    frame=_input;
    cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
    // calculate optical flow
    std::vector<uchar> status;
    std::vector<float> err;
    cv::calcOpticalFlowPyrLK(old_gray, frame_gray, p0, p1, status, err, cv::Size(15,15), 2, criteria);
    std::vector<cv::Point2f> good_new;
    for(uint i = 0; i < p0.size(); i++)
    {
        // Select good points
        if(status[i] == 1) {
            good_new.push_back(p1[i]);
            // draw the tracks
            line(mask,p1[i], p0[i], colors[i], 2);
            circle(frame, p1[i], 5, colors[i], -1);
        }
    }
    cv::Mat img;
    add(frame, mask, img);
    imshow("Frame", img);
    // Now update the previous frame and previous points
    old_gray = frame_gray.clone();
    p0 = good_new;
}