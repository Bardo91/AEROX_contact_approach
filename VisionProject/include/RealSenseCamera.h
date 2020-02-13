#include <opencv2/core.hpp> // OpenCV libraries
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API

class RealSenseCamera{
    public:
        RealSenseCamera();
        cv::Mat img;
        void setImage();
        RealSenseCamera &operator>> (cv::Mat &giveframe);
    private:
        rs2::pipeline pipe;
        rs2::colorizer color_map;
        cv::Mat getImage();
};