#include <RealSenseCamera.h>
#include <opencv2/imgproc.hpp>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <Eigen/Geometry>

RealSenseCamera::RealSenseCamera(bool newCam){
    if (newCam){
        cfg.enable_stream(RS2_STREAM_POSE, RS2_FORMAT_6DOF);
        //stream with config
        pipe.start(cfg);
    }
    else{
        // Start streaming with default recommended configuration
        pipe.start();
    }
}

void RealSenseCamera::setImage(){ // eliminar para libreria buena
    rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    rs2::video_frame color = data.get_color_frame(); //Get color image only

    // Query frame size (width and height)
    const int w = color.as<rs2::video_frame>().get_width();
    const int h = color.as<rs2::video_frame>().get_height();

    // Create OpenCV matrix of size (w,h) from the color data
    cv::Mat img_prev(cv::Size(w, h), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);
    //Realsense camera is in BGR so we need to change it to RGB
    cvtColor(img_prev, img, CV_RGB2BGR);
    return;
}

cv::Mat RealSenseCamera::getImage(){
    rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    rs2::video_frame color = data.get_color_frame(); //Get color image only

    // Query frame size (width and height)
    const int w = color.as<rs2::video_frame>().get_width();
    const int h = color.as<rs2::video_frame>().get_height();

    // Create OpenCV matrix of size (w,h) from the color data
    cv::Mat img_prev(cv::Size(w, h), CV_8UC3, (void*)color.get_data(), cv::Mat::AUTO_STEP);
    //Realsense camera is in BGR so we need to change it to RGB
    cv::Mat frame;
    cvtColor(img_prev, frame, CV_RGB2BGR);
    return frame;
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr RealSenseCamera::getPointCloud(){
    rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    rs2::video_frame color = data.get_color_frame(); //Get color image only

    rs2::points points;//points object to be persistent to display the last cloud when frame drops
    rs2::pointcloud pc;
    pc.map_to(color);//where the pointcloud has to map
    rs2::video_frame depth = data.get_depth_frame();
    points = pc.calculate(depth); //generate pointcloud
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud = cloudVision.pointsToPcl(points, color);
    return cloud;
}

rs2_pose RealSenseCamera::getPose(){
    // Wait for the next set of frames from the camera
    rs2::frameset frames = pipe.wait_for_frames();
    // Get a frame from the pose stream
    rs2::pose_frame f = frames.first_or_default(RS2_STREAM_POSE);
    // Cast the frame to pose_frame and get its data
    rs2_pose pose_data = f.as<rs2::pose_frame>().get_pose_data();
    return pose_data;
}

Eigen::Matrix4f RealSenseCamera::getPoseMatrix(){
    rs2_pose pose=getPose();

    Eigen::Quaternionf q(pose.rotation.w, pose.rotation.x, pose.rotation.y, pose.rotation.z); 

    Eigen::Matrix3f R = q.toRotationMatrix();
    Eigen::Vector3f T (pose.translation.x, pose.translation.y, pose.translation.z);
    Eigen::Vector4f D (0, 0, 0, 1);

    Eigen::Matrix4f mat;
    mat<< R, T, D.transpose();
    
    return mat;
}

RealSenseCamera& RealSenseCamera::operator>>(cv::Mat &_giveframe){
    _giveframe=getImage();
}

RealSenseCamera& RealSenseCamera::operator>>(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &_givecloud){
    _givecloud=getPointCloud();
}

RealSenseCamera& RealSenseCamera::operator>>(Eigen::Matrix4f &_pose){//rs2_pose &_pose){
    _pose=getPoseMatrix();
}