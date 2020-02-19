#include <opencv2/core.hpp> // OpenCV libraries
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <PCLUse.h>


class RealSenseCamera{
    public:
        RealSenseCamera();
        cv::Mat img;
        void setImage();
        RealSenseCamera &operator>> (cv::Mat &_giveframe);
        RealSenseCamera &operator<< (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &_givecloud);
    private:
        rs2::pipeline pipe;
        cv::Mat getImage();
        PCLUse cloudVision;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPointCloud();

};