#include <opencv2/core.hpp>
class LucasMethod{
    public:
        LucasMethod(cv::Mat &_input);
        void method(cv::Mat &_input);
    private:
        std::vector<cv::Scalar> colors;
        cv::Mat old_frame, old_gray;
        std::vector<cv::Point2f> p0, p1;
        cv::Mat mask;
};