#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>

typedef pcl::PointXYZRGB P_pcl;
typedef pcl::PointCloud<P_pcl> point_cloud;
typedef point_cloud::Ptr ptr_cloud;

using namespace cv;


// Get RGB values based on normals - texcoords, normals value [u v]
std::tuple<uint8_t, uint8_t, uint8_t> get_texcolor(rs2::video_frame texture, rs2::texture_coordinate texcoords)
{
    const int w = texture.get_width(), h = texture.get_height();
    
    // convert normals [u v] to basic coords [x y]
    int x = std::min(std::max(int(texcoords.u*w + .5f), 0), w - 1);
    int y = std::min(std::max(int(texcoords.v*h + .5f), 0), h - 1);

    int idx = x * texture.get_bytes_per_pixel() + y * texture.get_stride_in_bytes();
    const auto texture_data = reinterpret_cast<const uint8_t*>(texture.get_data());
    return std::tuple<uint8_t, uint8_t, uint8_t>(texture_data[idx], texture_data[idx+1], texture_data[idx+2]);
}

ptr_cloud points_to_pcl(const rs2::points& points, const rs2::video_frame& color){

    // OpenCV Mat for showing the rgb color image, just as part of processing
    Mat colorr(Size(640, 480), CV_8UC3, (void*)color.get_data(), Mat::AUTO_STEP);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", colorr);
        
    auto sp = points.get_profile().as<rs2::video_stream_profile>();
    ptr_cloud cloud(new point_cloud);
    
    // Config of PCL Cloud object
    cloud->width = static_cast<uint32_t>(sp.width());
    cloud->height = static_cast<uint32_t>(sp.height());
    cloud->is_dense = false;
    cloud->points.resize(points.size());

    auto tex_coords = points.get_texture_coordinates();
    auto vertices = points.get_vertices();

    // Iterating through all points and setting XYZ coordinates
    // and RGB values
    for (int i = 0; i < points.size(); ++i)
    {
        cloud->points[i].x = vertices[i].x;
        cloud->points[i].y = vertices[i].y;
        cloud->points[i].z = vertices[i].z;

        std::tuple<uint8_t, uint8_t, uint8_t> current_color;
        current_color = get_texcolor(color, tex_coords[i]);

        cloud->points[i].r = std::get<0>(current_color);
        cloud->points[i].g = std::get<1>(current_color);
        cloud->points[i].b = std::get<2>(current_color);

    }
   return cloud;
}


