#include <TemplateMatchingThread.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>

#include <unistd.h>
#include <iostream>

TemplateMatching::TemplateMatching(std::string _argv){
    int i;
    templ = cv::imread(_argv, CV_LOAD_IMAGE_COLOR);


    for (i=0; i<3;i++){
        cv::Mat scaledTemplate;
        resize(templ, scaledTemplate, cv::Size(), (1-i*0.5), (1-i*0.5));
        templ_resize.push_back(scaledTemplate);
    }
}

void TemplateMatching::matchingMethod(cv::Mat &_input){
    std::vector<std::thread> vt(templ_resize.size());
    std::vector<double> maxScore(templ_resize.size());
    std::vector<double> minScore(templ_resize.size());
    std::vector<cv::Point> maxScoreLoc(templ_resize.size());
    std::vector<cv::Point> minScoreLoc(templ_resize.size());
    std::vector<int> col(templ_resize.size());
    std::vector<int> row(templ_resize.size());

    cv::Mat img_display;
    _input.copyTo(img_display);
    double minVal_act=800;
    double maxVal_act=0;
    cv::Point matchLoc;
    int cols, rows;

    //uncomment matching method preferred
    //int match_method=cv::TM_SQDIFF_NORMED;
    //int match_method=cv::TM_CCORR;
    //int match_method=cv::TM_CCOEFF;
    int match_method=cv::TM_CCOEFF_NORMED;


    for (int i=0;i<templ_resize.size();i++){
        vt[i]=std::thread([&](int _id){
            cv::Mat eval;            
            eval=templ_resize[i];

            cv::Mat result;
            double minVal;
            double maxVal;       
            cv::Point minLoc;
            cv::Point maxLoc;

            int result_cols = _input.cols - eval.cols + 1;
            int result_rows = _input.rows - eval.rows + 1;
            result.create(result_rows, result_cols, CV_32FC1);

            //function where the template is matched with the camera image
            matchTemplate(_input, eval, result, match_method);
            normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

            maxScore[i]=maxVal; maxScoreLoc[i]=maxLoc;
            minScore[i]=minVal; minScoreLoc[i]=minLoc;
            col[i]=eval.col; row[i]=eval.row;
        }, i);
    }
    
    const char *image_window = "Source Image";
    for(int i=0;i<templ_resize.size();i++){
        if(match_method==cv::TM_SQDIFF_NORMED){
            if (minScore[i]<minVal_act) {
                minVal_act=minScore[i];
                matchLoc = minScoreLoc[i]; 
                cols=col[i];
                rows=row[i];
            }
        }
        else{
            if (maxScore[i]>maxVal_act) {
                maxVal_act=maxScore[i];
                matchLoc = maxScoreLoc[i]; 
                cols=col[i];
                rows=row[i];
            }
        }
    }
    
    rectangle(img_display, matchLoc, cv::Point(matchLoc.x + cols, matchLoc.y + rows), cv::Scalar::all(0), 2, 8, 0);
    imshow(image_window, img_display);
}