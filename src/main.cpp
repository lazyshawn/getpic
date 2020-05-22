#include <librealsense2/rs.hpp>
#include<librealsense2/rsutil.h>
#include <librealsense2/hpp/rs_processing.hpp>
#include <librealsense2/hpp/rs_types.hpp>
#include <librealsense2/hpp/rs_sensor.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace cv;

int main()
{
  //Contruct a pipeline which abstracts the device
	rs2::pipeline pipe;    // 声明Realsense管道
  rs2::frameset frames;  // 创建一个rs2::frameset对象, 包含一组帧和访问它们的接口
  rs2::colorizer color_map;    // 声明彩色图
  
  //Create a configuration for configuring the pipeline with a non default profile
  // 配置数据流信息
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
	cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

  // 启动设备的管道配置文件, 开始传送数据流
	rs2::pipeline_profile selection = pipe.start(cfg);

	while (waitKey(10)<0)
	{
		frames = pipe.wait_for_frames();    // 等待下一帧

		// Get each frame
    rs2::frame color_frame = frames.get_color_frame();  // 获取彩色图
    // 获取深度图, 加颜色滤镜
    rs2::frame depth_frame = frames.get_depth_frame().apply_filter(color_map);

		// 创建Opencv类,并传入数据
		Mat color(Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), Mat::AUTO_STEP);
		Mat depth(Size(640, 480), CV_8UC3, (void*)depth_frame.get_data(), Mat::AUTO_STEP);
		imshow("Display color Image", color);
		imshow("Display depth Image", depth);
	}
	return 0;
}

