#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <PCLUse.h>

int main ()
 {
   pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud= getPointCloud();
   //... populate cloud
   pcl::visualization::CloudViewer viewer ("Simple Cloud Viewer");
   viewer.showCloud (cloud);
   while (!viewer.wasStopped ())
   {
   }
 }