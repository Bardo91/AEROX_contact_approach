#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <RealSenseCamera.h>

int main (int _argc, char **_argv){

  RealSenseCamera realSenseCamera;
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
  pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");

  while(true){
    realSenseCamera<<cloud;
    viewer.showCloud (cloud);
  }
   
}