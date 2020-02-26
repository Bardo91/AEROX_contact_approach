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
        void setImage(); //eliminar para libreria buena
        RealSenseCamera &operator>> (cv::Mat &_giveframe); //image
        RealSenseCamera &operator>> (pcl::PointCloud<pcl::PointXYZRGB>::Ptr &_givecloud); //pointcloud
        RealSenseCamera &operator>> (Eigen::Matrix4f &_pose); //pose matrix
    private:
        rs2::pipeline pipe;
        rs2::config cfg;
        PCLUse cloudVision;
        cv::Mat getImage();
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr getPointCloud();
        rs2_pose getPose();
        Eigen::Matrix4f getPoseMatrix();
};