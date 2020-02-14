#include <RealSenseCamera.h>
#include <opencv2/imgproc.hpp>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API

RealSenseCamera::RealSenseCamera(){
    // Start streaming with default recommended configuration
    pipe.start();
}

void RealSenseCamera::setImage(){
    rs2::frameset data = pipe.wait_for_frames(); // Wait for next set of frames from the camera
    color = data.get_color_frame(); //Get color image only

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
    color = data.get_color_frame(); //Get color image only

    rs2::pointcloud pc;
    pc.map_to(color);//where the pointcloud has to map
    auto depth = data.get_depth_frame();
    points = pc.calculate(depth); //generate pointcloud

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

RealSenseCamera& RealSenseCamera::operator>>(cv::Mat &giveframe){
    giveframe=getImage();
}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr RealSenseCamera::getPointCloud(){
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud = cloudVision.pcl(points, color);
    return cloud;
}