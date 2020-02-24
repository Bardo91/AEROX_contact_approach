#include <RealSenseCamera.h>
#include <iostream>
#include <iomanip>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

#include <Eigen/Geometry>
#include <Eigen/Dense>

#include <math.h>
#define PI 3.14159265


int main (int _argc, char **_argv){
    RealSenseCamera realSenseCamera(1);
    pcl::visualization::PCLVisualizer::Ptr viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
    Eigen::Matrix4f pose_mat;

    // Eigen::Matrix4f Rz;
    // Rz << cos(PI/2), -sin(PI/2), 0, 0,
    //       sin(PI/2), cos(PI/2), 0, 0,
    //       0, 0, 1, 0,
    //       0, 0, 0, 1;

    viewer->addCoordinateSystem (1.0, "cloud");
    int flag=1;
    viewer->addCoordinateSystem (1.0, "origin");
    viewer->addCoordinateSystem (1.0, "drone");

    while(true){
        realSenseCamera = pose_mat;
        // std::cout << "\r" << "Pose Matrix:" << endl;
        // std::cout << "\r" << std::setprecision(3) << std::fixed << pose_mat << endl;
        Eigen::Matrix3f R = pose_mat.block(0,0,3,3);
        Eigen::Vector3f T = pose_mat.block(0,3,3,1);
        // std::cout << "\r" << "Rotation:" << endl;
        // std::cout << "\r" << std::setprecision(3) << std::fixed << R << endl;
        // std::cout << "\r" << "Translation:" << endl 
        // std::cout << std::setprecision(3) << std::fixed << T << endl
        Eigen::Affine3f t;
        t.fromPositionOrientationScale(T, R, Eigen::Vector3f::Ones());

        Eigen::Affine3f d;
        Eigen::Vector3f w; // rotation axis
        z << 0, 0, 1;

        Eigen::AngleAxisf(PI/2, Vector3f::UnitZ());

        d.fromPositionOrientationScale(T, Rd, Eigen::Vector3f::Ones());

        //x=red axis, y=green axis, z=blue axis
        if (flag==1){
            viewer->updateCoordinateSystemPose("origin", t);
            flag=0;
        }
        viewer->updateCoordinateSystemPose("cloud", t);
        viewer->updateCoordinateSystemPose("drone", d);
        viewer->spinOnce(30);
    }

    return 0;
}