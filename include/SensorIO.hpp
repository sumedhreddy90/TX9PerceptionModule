/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  SensorIO.hpp
 * @brief SensorIO Class implementation
 * @author Pratik Acharya and Sumedh Koppula
 */

#pragma once

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

/**
 * @class SensorIO
 * @brief A class to interact with sensor to receive data for processing by other classes
 */

class SensorIO {
 private:
  /**
   * @brief private variable for Image Path.
   */
  std::string imagePath;
  /**
   * @brief private variable for Video Path.
   */
  std::string videoPath;
  /**
   * @brief private variable for output frame width.
   */
  int outputWidth;
  /**
   * @brief private variable for output frame height.
   */
  int outputHeight;

 public:
  /**
   * @fn  SensorIO()
   * @brief constructor for SensorIO class with no parameters.
   * @param None
   * @return None
   */
  SensorIO();
  /**
   * @fn void setOutputWidth(int)
   * @brief It sets the value for outputWidth attribute
   * @param[in] width value to set outputWidth
   * @return None
   */
  void setOutputWidth(int width);
  /**
   * @fn void setOutputHeight(int)
   * @brief It sets the value for outputHeight attribute
   * @param[in] height value to set outputWidth
   * @return None
   */
  void setOutputHeight(int height);
  /**
   * @fn int getOutputWidth()
   * @brief It gets the value of outputWidth attribute
   * @param None
   * @return The value of outputWidth
   */
  int getOutputWidth();
  /**
   * @fn int getOutputHeight()
   * @brief It gets the value of outputHeight attribute
   * @param None
   * @return The value of outputHeight
   */
  int getOutputHeight();
  /**
   * @fn void setImagePath(std::string)
   * @brief It sets the value of imagePath attribute
   * @param[in] path value to set for imagePath
   * @return None
   */
  void setImagePath(std::string path);
  /**
   * @fn void setVideoPath(std::string)
   * @brief It sets the value of videoPath attribute
   * @param[in] path value to set for videoPath
   * @return None
   */
  void setVideoPath(std::string path);
  /**
   * @fn std::string getImagePath()
   * @brief It gets the value of imagePath attribute
   * @param None
   * @return Value of imagePath attribute
   */

  std::string getImagePath();
  /**
   * @fn std::string getVideoPath()
   * @brief It gets the value of videoPath attribute
   * @param None
   * @return Value of videoPath attribute
   */
  std::string getVideoPath();
  /**
   * @fn std::string getDataType(const cv::CommandLineParser)
   * @brief Function to tell if the input is an image or video
   * @param[in] parser to get the parser from opencv
   * @return "image", "video" or "error"
   */
  std::string getDataType(const cv::CommandLineParser parser);
  /**
   * @fn std::string getDataPath(const cv::CommandLineParser&, const std::string&)
   * @brief Fucntion to get input data path
   * @param[in] parser to get parser from opencv
   * @param[in] dataType param to indicate if the input is image or video
   * @return input Path
   */
  std::string getDataPath(const cv::CommandLineParser &parser,
                          const std::string &dataType);
  /**
   * @fn cv::VideoCapture imageProcessor(const std::string&, cv::Mat)
   * @brief Function to process image
   * @param[in] rwoperation to indicate if the operation to be performed is read/write
   * @param[frame] input frame
   * @return Opens a video file or a capturing device to receive input
   */
  cv::VideoCapture imageProcessor(const std::string &rwoperation,
                                  cv::Mat frame);
  /**
   * @fn cv::VideoCapture videoProcessor(const std::string&, cv::Mat, VideoWriter)
   * @brief Function to process video
   * @param[in] rwoperation to indicate if the operation to be performed is read/write
   * @param[in] frame input frame
   * @param[in] video file to write the frame to
   * @return Opens a video file or a capturing device to receive input
   */
  cv::VideoCapture videoProcessor(const std::string &rwoperation, cv::Mat frame,
                                  cv::VideoWriter video);
  /**
   * @fn  ~SensorIO()
   * @brief Destructor for SensorIO class
   */
  ~SensorIO();
};
