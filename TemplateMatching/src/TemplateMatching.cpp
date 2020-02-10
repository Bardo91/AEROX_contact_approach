#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <unistd.h>
#include <iostream>

class TemplateMatching{
    public:
    cv::Mat templ;
    TemplateMatching(std::string);
    void matchingMethod(cv::Mat &_input);
    private:
    std::vector<cv::Mat> templ_resize;

};

TemplateMatching::TemplateMatching(std::string _argv){
    int i;
    templ = cv::imread(_argv, CV_LOAD_IMAGE_COLOR);

    for (i=0; i<2;i++){
        cv::Mat scaledTemplate;
        resize(templ, scaledTemplate, cv::Size(), (1-i*0.5), (1-i*0.5));
        templ_resize.push_back(scaledTemplate);
    }
}

void TemplateMatching::matchingMethod(cv::Mat &_input){
    cv::Mat final_result;
    cv::Mat result;
    cv::Mat eval;

    int i;
    int cols, rows;
    double minVal;
    double minVal_act=800;
    double maxVal;
    double maxVal_act=0;
    cv::Point minLoc;
    cv::Point maxLoc;
    cv::Point matchLoc;

    const char *image_window = "Source Image";
    const char *result_window = "Result window";

    //uncomment matching method preferred
    //int match_method=cv::TM_SQDIFF_NORMED;
    //int match_method=cv::TM_CCORR;
    //int match_method=cv::TM_CCOEFF;
    int match_method=cv::TM_CCOEFF_NORMED;

    cv::Mat img_display;
    _input.copyTo(img_display);

    for(i=0;i<templ_resize.size();i++){
        eval=templ_resize[i];
        int result_cols = _input.cols - eval.cols + 1;
        int result_rows = _input.rows - eval.rows + 1;
        result.create(result_rows, result_cols, CV_32FC1);

        //function where the template is matched with the camera image
        matchTemplate(_input, eval, result, match_method);
        normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

        //only TM_SQDIFF_NORMED method uses min values. 
        if(match_method==cv::TM_SQDIFF_NORMED){
            if (minVal<minVal_act) {
                minVal_act=minVal;
                matchLoc = minLoc; 
                cols=eval.cols;
                rows=eval.rows;
            }
        }
        else{
            if (maxVal>maxVal_act) {
                maxVal_act=maxVal;
                matchLoc = maxLoc; 
                cols=eval.cols;
                rows=eval.rows;
            }
        }
        
    }
    //We have two images displayed: the actual camera image and a gray scale 
    //image(result) that represents the amount of matching made by the template 
    //in each point (more white=more matching)
    rectangle(img_display, matchLoc, cv::Point(matchLoc.x + cols, matchLoc.y + rows), cv::Scalar::all(0), 2, 8, 0);
    rectangle(result, matchLoc, cv::Point(matchLoc.x + cols, matchLoc.y + rows), cv::Scalar::all(0), 2, 8, 0);
    imshow(image_window, img_display);
    imshow(result_window, result);
    return;
}