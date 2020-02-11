#include <FeatureMatching.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
//#include "opencv2/xfeatures2d.hpp"

//using namespace cv::xfeatures2d;
FeatureMatching::FeatureMatching(std::string _argv){
    templ_ = cv::imread(_argv, CV_LOAD_IMAGE_GRAYSCALE);
    detection(templ_, keypoints_templ_, descriptors_templ_);
    // //-- Draw keypoints
    // cv::Mat img_keypoints;
    // drawKeypoints( templ_, keypoints_templ_, img_keypoints );
    // //-- Show detected (drawn) keypoints
    // imshow("ORB Keypoints", img_keypoints );
}


void FeatureMatching::detection(cv::Mat &_input,std::vector<cv::KeyPoint> &_keypoints, cv::Mat &_descriptors)
{
    //-- Step 1: Detect the keypoints using ORB Detector
    cv::Ptr<cv::ORB> detector = cv::ORB::create( minHessian );
    detector->detectAndCompute(_input, cv::noArray(), _keypoints, _descriptors);

    // //-- Draw keypoints
    // cv::Mat img_keypoints;
    // drawKeypoints( _input, _keypoints, img_keypoints );
    // //-- Show detected (drawn) keypoints
    // imshow("ORB Keypoints", img_keypoints );
    // return;
}

void FeatureMatching::matching(cv::Mat &_descrip_img,std::vector<cv::KeyPoint> &_keyp_img, cv::Mat &_img){
    //-- Step 2: Matching descriptor vectors with a brute force matcher
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector< cv::DMatch > matches;
    matcher->match(descriptors_templ_, _descrip_img, matches );
    //-- Draw matches
    cv::Mat img_matches;
    drawMatches(templ_, keypoints_templ_, _img, _keyp_img, matches, img_matches );
    //-- Show detected matches
    imshow("Matches", img_matches );
}