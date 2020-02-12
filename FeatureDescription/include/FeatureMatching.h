#include <opencv2/core.hpp>
#include <opencv2/features2d.hpp>

class FeatureMatching{
    public:
    cv::Mat templ_;
    FeatureMatching(std::string _argv);
    void detection(cv::Mat &_input, std::vector<cv::KeyPoint> &_keypoints, cv::Mat &_descriptors);
    void matching(cv::Mat &_descrip_img,std::vector<cv::KeyPoint> &_keyp_img, cv::Mat &_img);
    private:
    int minHessian = 400;
    std::vector<cv::KeyPoint> keypoints_templ_;
    cv::Mat descriptors_templ_;
    cv::Ptr<cv::ORB> detector;
    cv::Ptr<cv::DescriptorMatcher> matcher;
};