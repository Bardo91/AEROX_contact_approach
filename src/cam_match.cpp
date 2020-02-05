#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/opencv.hpp>   // Include OpenCV API
#include <unistd.h>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using namespace std;
using namespace cv;
//bool use_mask;
Mat img;
Mat templ;
Mat mask;
Mat result;
const char *image_window = "Source Image";
const char *result_window = "Result window";
int match_method=TM_SQDIFF_NORMED;
void MatchingMethod();
int main(int argc, char **argv)
{
    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;
    // Start streaming with default recommended configuration
    pipe.start();

    templ = imread(argv[0], IMREAD_COLOR);

    if (templ.empty())
    {
        cout << "Template missing" << endl;
        return EXIT_FAILURE;
    }

    while (true)
    {
        rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
        rs2::frame color = data.get_color_frame();


        // Query frame size (width and height)
        const int w = color.as<rs2::video_frame>().get_width();
        const int h = color.as<rs2::video_frame>().get_height();

        // Create OpenCV matrix of size (w,h) from the colorized depth data
        Mat img(Size(w, h), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
        MatchingMethod();
    }
    return EXIT_SUCCESS;
}

void MatchingMethod()
{
    Mat img_display;
    img.copyTo(img_display);
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1);

    matchTemplate(img, templ, result, match_method);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
    double minVal;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    matchLoc = minLoc;
    rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
    rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
    imshow(image_window, img_display);
    imshow(result_window, result);
    return;
}
// void MatchingMethod()
// {
//     Mat img_display;
//     img.copyTo(img_display);
//     int result_cols = img.cols - templ.cols + 1;
//     int result_rows = img.rows - templ.rows + 1;
//     result.create(result_rows, result_cols, CV_32FC1);
//     bool method_accepts_mask = (TM_SQDIFF == match_method || match_method == TM_CCORR_NORMED);
//     if (use_mask && method_accepts_mask)
//     {
//         matchTemplate(img, templ, result, match_method, mask);
//     }
//     else
//     {
//         matchTemplate(img, templ, result, match_method);
//     }
//     normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
//     double minVal;
//     double maxVal;
//     Point minLoc;
//     Point maxLoc;
//     Point matchLoc;
//     minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
//     if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
//     {
//         matchLoc = minLoc;
//     }
//     else
//     {
//         matchLoc = maxLoc;
//     }
//     rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
//     rectangle(result, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
//     imshow(image_window, img_display);
//     imshow(result_window, result);
//     return;
// }