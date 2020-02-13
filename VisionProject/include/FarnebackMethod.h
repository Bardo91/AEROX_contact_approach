#include <opencv2/core.hpp>
class FarnebackMethod{
    public:
        FarnebackMethod(cv::Mat &_input);
        void method(cv::Mat &_input);
    private:
        cv::Mat prvs;
};