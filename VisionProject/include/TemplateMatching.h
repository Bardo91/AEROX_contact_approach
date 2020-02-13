#include <opencv2/core.hpp> // OpenCV libraries

class TemplateMatching{
    public:
    cv::Mat templ;
    TemplateMatching(std::string);
    void matchingMethod(cv::Mat &_input);
    private:
    std::vector<cv::Mat> templ_resize;
};