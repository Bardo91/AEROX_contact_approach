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

void MatchingMethod(Mat _input, Mat _temp);

int main(int argc, char **argv) {
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;
    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();

    Mat templ = imread("/home/ana/programming/AEROX_contact_approach/TestTemplateMatching/botella4.jpg", CV_LOAD_IMAGE_COLOR);

    if( templ.rows == 0 ) { // Check for invalid template
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
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

        MatchingMethod(img, templ);
        waitKey(3);
    }
    return EXIT_SUCCESS;
}

void MatchingMethod(Mat _input, Mat _temp){
    Mat result;

    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    const char *image_window = "Source Image";
    const char *result_window = "Result window";
    int match_method=TM_SQDIFF_NORMED;

    Mat img_display;
    _input.copyTo(img_display);
    int result_cols = _input.cols - _temp.cols + 1;
    int result_rows = _input.rows - _temp.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1);

    //function where the template is matched with the camera image
    matchTemplate(_input, _temp, result, match_method);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = minLoc; //we use this because it corresponds to the method I chose

    /*We have two images displayed: the actual camera image and a gray scale 
    image(result) that represents the amount of matching made by the template 
    in each point (more white=more matching)*/
    rectangle(img_display, matchLoc, Point(matchLoc.x + _temp.cols, matchLoc.y + _temp.rows), Scalar::all(0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + _temp.cols, matchLoc.y + _temp.rows), Scalar::all(0), 2, 8, 0);
    imshow(image_window, img_display);
    //imwrite("result.jpg",img_display);
    imshow(result_window, result);
    return;
}