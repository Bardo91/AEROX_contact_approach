#include <opencv2/core.hpp> // OpenCV libraries
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <PCLUse.h>
#include <Eigen/Geometry>

class RealSenseCamera{
    public:
        RealSenseCamera(bool newCam);
        cv::Mat img;
        void setImage();
        RealSenseCamera &operator>> (cv::Mat &_giveframe);
        RealSenseCamera &operator<< (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &_givecloud);
        RealSenseCamera &operator>> (Eigen::Matrix4f &_pose);//rs2_pose &_pose);
    private:
        rs2::pipeline pipe;
        rs2::config cfg;
        cv::Mat getImage();
        PCLUse cloudVision;
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPointCloud();
        rs2_pose getPose();
        Eigen::Matrix4f getPoseMatrix();
};