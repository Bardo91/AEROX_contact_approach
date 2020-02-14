#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

class PCLUse{
    public:
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr points_to_pcl(points, colored_frame);
    private:
        std::tuple<uint8_t, uint8_t, uint8_t> get_texcolor(rs2::video_frame texture, rs2::texture_coordinate texcoords)


}