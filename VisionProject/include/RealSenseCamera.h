#include <opencv2/core.hpp> // OpenCV libraries
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <PCLUse.h>

class RealSenseCamera{
    public:
        RealSenseCamera();
        cv::Mat img;
        void setImage();
        RealSenseCamera &operator>> (cv::Mat &giveframe);
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPointCloud();

    private:
        rs2::pipeline pipe;
        rs2::video_frame color;
        //rs2::pointcloud pc;
        rs2::points points;//points object to be persistent to display the last cloud when frame drops
        cv::Mat getImage();
        PCLUse cloudVision;
};