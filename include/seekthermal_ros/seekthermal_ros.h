#pragma once

// libseekthermal
#include <seekthermal/seekthermal.h>
#include <seekthermal/command/application.h>
#include <seekthermal/usb/context.h>

// ros
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <camera_info_manager/camera_info_manager.h>
#include <image_geometry/pinhole_camera_model.h>

// opencv
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/photo/photo.hpp>

// boost
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/thread/condition_variable.hpp>

#include <queue>

#include <cv_bridge/cv_bridge.h>
// thermal image msg
#include <seekthermal_ros/ThermalImage.h>

using namespace cv;
using namespace SeekThermal;

namespace seekthermal_ros {

class SeekthermalRos
{
public:
  /*!
   * Constructor.
   */
  SeekthermalRos(ros::NodeHandle nh);

  /*!
   * Destructor.
   */
  virtual ~SeekthermalRos();

private:
  void captureThermalImages(const Pointer<Device>& device);
  void publishingThermalImages();
  Mat convertFromGrayToColor(Mat &image);

  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::CameraPublisher thermal_image_publisher_;
  image_transport::Publisher colored_thermal_image_publisher_;
  ros::Publisher thermal_image_raw_publisher_;

  boost::shared_ptr<camera_info_manager::CameraInfoManager> cinfo_;

  std::string device_adress_;

  std::string thermal_image_topic_name_;
  std::string thermal_image_raw_topic_name_;
  std::string colored_thermal_image_topic_name_;

  std::string camera_name_;
  std::string camera_frame_id_;
  std::string camera_info_url_;

  std::string package_path_, package_path_name;

  Pointer<Device> device_;

  Frame last_calibration_frame_;
  bool use_inpaint_;
  bool calibrate_dead_pixels_;
  bool mean_compensation_;
  bool calibrate_mean_compensation_;
  bool denoise_;
  bool show_debug_images_;

  enum State {CALIBRATE_DEAD_PIXEL, LOAD_DEAD_PIXEL, CALIBRATE_MEAN, LOAD_MEAN, RUN};
  State state_;

  cv::Mat inpaint_mask_;
  cv::Mat mean_compensation_image_;
  
  std::unique_ptr<cv_bridge::CvImage> cv_ptr_colored;
  std::unique_ptr<cv_bridge::CvImage> cv_ptr;

  std::queue<Pointer<Frame>> frame_queue_;
  mutable boost::mutex mutex_;
  boost::condition_variable condition_variable_;

};

} /* namespace */
