#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <librealsense2/rs.hpp> // Include RealSense Cross Platform API
#include <opencv2/core.hpp> // OpenCV libraries

class PCLUse{
    public:
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr pointsToPcl(rs2::points& _points, rs2::video_frame& _colored_frame);
    private:
        std::tuple<uint8_t, uint8_t, uint8_t> getTexcolor(rs2::video_frame& _texture, rs2::texture_coordinate _texcoords);
};