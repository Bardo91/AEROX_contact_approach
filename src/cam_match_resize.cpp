#include "opencv2/imgcodecs.hpp" // OpenCV libraries
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
//#include <opencv2/opencv.hpp>   // Include OpenCV API
#include <unistd.h>
//#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using namespace std;
using namespace cv;

void MatchingMethod(Mat &_input, std::vector<cv::Mat>&_temp);

int main(int argc, char **argv) {
    int i;
    std::vector<Mat> templ_resize;
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;
    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();
    
    Mat templ = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cout << argv[1] << endl;

    if( templ.rows == 0 ) { // Check for invalid template
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    for (i=1; i<3;i++){
        cv::Mat scaledTemplate;
        resize(templ, scaledTemplate, cv::Size(), (1-i*0.25), (1-i*0.25));

        templ_resize.push_back(scaledTemplate);
    }

    while (true) {
        rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
        auto color = data.get_color_frame(); //Get color image only
        
        // Query frame size (width and height)
        const int w = color.as<rs2::video_frame>().get_width();
        const int h = color.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (w,h) from the color data
        Mat img(Size(w, h), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
        //Realsense camera is in BGR so we need to change it to RGB
        cvtColor(img, img, CV_RGB2BGR);

        MatchingMethod(img, templ_resize);
        waitKey(3);
    }
    return EXIT_SUCCESS;
}

void MatchingMethod(Mat &_input, std::vector<cv::Mat> &_temp){
    Mat final_result;
    Mat result;
    Mat eval;

    int i;
    int cols, rows;
    double minVal;
    double minVal_act=800;
    double maxVal;
    double maxVal_act=0;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    const char *image_window = "Source Image";
    const char *result_window = "Result window";

    //uncomment matching method preferred
    //int match_method=TM_SQDIFF_NORMED;
    //int match_method=TM_CCORR;
    //int match_method=TM_CCOEFF;
    int match_method=TM_CCOEFF_NORMED;

    Mat img_display;
    _input.copyTo(img_display);

    for(i=0;i<_temp.size();i++){
        eval=_temp[i];
        int result_cols = _input.cols - eval.cols + 1;
        int result_rows = _input.rows - eval.rows + 1;
        result.create(result_rows, result_cols, CV_32FC1);

        //function where the template is matched with the camera image
        matchTemplate(_input, eval, result, match_method);
        normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

        //only TM_SQDIFF_NORMED method uses min values. 
        if(match_method==TM_SQDIFF_NORMED){
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
    /*We have two images displayed: the actual camera image and a gray scale 
    image(result) that represents the amount of matching made by the template 
    in each point (more white=more matching)*/
    rectangle(img_display, matchLoc, Point(matchLoc.x + cols, matchLoc.y + rows), Scalar::all(0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + cols, matchLoc.y + rows), Scalar::all(0), 2, 8, 0);
    imshow(image_window, img_display);
    imshow(result_window, result);
    return;
}