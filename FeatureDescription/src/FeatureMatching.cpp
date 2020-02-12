#include <FeatureMatching.h>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
//#include "opencv2/xfeatures2d.hpp"

//using namespace cv::xfeatures2d;
FeatureMatching::FeatureMatching(std::string _argv){
    templ_ = cv::imread(_argv, CV_LOAD_IMAGE_GRAYSCALE);
    detector = cv::ORB::create( minHessian );
    detection(templ_, keypoints_templ_, descriptors_templ_);
    // //-- Draw keypoints
    // cv::Mat img_keypoints;
    // drawKeypoints( templ_, keypoints_templ_, img_keypoints );
    // //-- Show detected (drawn) keypoints
    // imshow("ORB Keypoints", img_keypoints );

    //Matcher without filter
    matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    //Matcher with filter
    //matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
}


void FeatureMatching::detection(cv::Mat &_input,std::vector<cv::KeyPoint> &_keypoints, cv::Mat &_descriptors)
{
    //-- Step 1: Detect the keypoints using ORB Detector
    detector->detectAndCompute(_input, cv::noArray(), _keypoints, _descriptors);

    // //-- Draw keypoints
    // cv::Mat img_keypoints;
    // drawKeypoints( _input, _keypoints, img_keypoints );
    // //-- Show detected (drawn) keypoints
    // imshow("ORB Keypoints", img_keypoints );
    // return;
}

void FeatureMatching::matching(cv::Mat &_descrip_img,std::vector<cv::KeyPoint> &_keyp_img, cv::Mat &_img){
    // Matches without filter
    // //-- Step 2: Matching descriptor vectors with a brute force matcher
    // std::vector< cv::DMatch > matches;
    // matcher->match(descriptors_templ_, _descrip_img, matches );
    // //-- Draw matches
    // cv::Mat img_matches;
    // drawMatches(templ_, keypoints_templ_, _img, _keyp_img, matches, img_matches );
    // //-- Show detected matches
    // imshow("Matches", img_matches );

    //Matches with filter
    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // ORB uses Hamming distance to determine features
    if (_descrip_img.rows>12){
        std::vector< std::vector<cv::DMatch> > knn_matches;
        matcher->knnMatch(descriptors_templ_,_descrip_img, knn_matches, 2 );
        //-- Filter matches using the Lowe's ratio test
        const float ratio_thresh = 0.77f;
        std::vector<cv::DMatch> good_matches;
        for (size_t i = 0; i < knn_matches.size(); i++)
        {
            if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
            {
                good_matches.push_back(knn_matches[i][0]);
            }
        }
        //-- Draw matches
        cv::Mat img_matches;
        drawMatches( templ_, keypoints_templ_, _img, _keyp_img, good_matches, img_matches, cv::Scalar::all(-1),
                    cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        //-- Show detected matches
        imshow("Resultado", img_matches );
    }
    else{
        imshow("Resultado", _img);
    }
}