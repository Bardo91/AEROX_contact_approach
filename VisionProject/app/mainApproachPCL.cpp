#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <gperftools/profiler.h>

#include <RealSenseCamera.h>

int main (int _argc, char **_argv){

  RealSenseCamera realSenseCamera(0);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
  pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");

  std::string fileName = "PCL_"+std::to_string(time(NULL));
  ProfilerStart(fileName.c_str());
  while(!viewer.wasStopped ()){
    realSenseCamera>>cloud;
    viewer.showCloud (cloud);
  }
  ProfilerStop();
  return 0;
}