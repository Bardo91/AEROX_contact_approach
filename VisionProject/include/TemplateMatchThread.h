#include <opencv2/core.hpp> // OpenCV libraries

class TemplateMatchThread{
    public:
    cv::Mat templ;
    TemplateMatchThread(std::string);
    void matchThread(cv::Mat &_input);
    private:
    std::vector<cv::Mat> templ_resize;
};