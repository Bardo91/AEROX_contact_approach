#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>

#include <FeatureMatching.h>
#include <RealSenseCamera.h>

int main(int _argc, char **_argv){

    RealSenseCamera realSenseCamera;
    FeatureMatching featureDetection(_argv[1]);

   if (featureDetection.templ_.empty() )
    {
        std::cout << "Could not open or find the image!\n" << std::endl;
        std::cout << "Usage: " << _argv[0] << " <Input image>" << std::endl;
        return -1;
    }

    std::vector<cv::KeyPoint> keypoints_img;
    cv::Mat descriptors_img;

    while(true){
        realSenseCamera.setImage();
        featureDetection.detection(realSenseCamera.img, keypoints_img, descriptors_img);
        // //-- Draw keypoints
        // cv::Mat img_keypoints;
        // drawKeypoints(realSenseCamera.img, keypoints_img, img_keypoints);
        // //-- Show detected (drawn) keypoints
        // imshow("ORB Keypoints", img_keypoints );


        featureDetection.matching(descriptors_img, keypoints_img, realSenseCamera.img);
        cv::waitKey(3);
    }
    return 0;
}