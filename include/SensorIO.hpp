/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  SensorIO.hpp
 * @brief SensorIO Class implementation
 * @author Pratik Acharya and Sumedh Koppula
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

/**
 * Adding members from std and cv namespaces into current scope
 */

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::endl;
using cv::CommandLineParser;
using cv::VideoCapture;
using cv::Mat;

/**
 * @class SensorIO
 * @brief A class to interact with sensor to receive data for processing by other classes
 */

class SensorIO {
 private:
  /**
   * @brief private variable for Image Path.
   */
  string imagePath;
  /**
   * @brief private variable for Video Path.
   */
  string videoPath;
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
   * @fn void setImagePath(string)
   * @brief It sets the value of imagePath attribute
   * @param[in] path value to set for imagePath
   * @return None
   */
  void setImagePath(string path);
  /**
   * @fn void setVideoPath(string)
   * @brief It sets the value of videoPath attribute
   * @param[in] path value to set for videoPath
   * @return None
   */
  void setVideoPath(string path);
  /**
   * @fn string getImagePath()
   * @brief It gets the value of imagePath attribute
   * @param None
   * @return Value of imagePath attribute
   */

  string getImagePath();
  /**
   * @fn string getVideoPath()
   * @brief It gets the value of videoPath attribute
   * @param None
   * @return Value of videoPath attribute
   */
  string getVideoPath();
  /**
   * @fn string getDataType(const CommandLineParser)
   * @brief Function to tell if the input is an image or video
   * @param[in] parser to get the parser from opencv
   * @return "image", "video" or "error"
   */
  string getDataType(const CommandLineParser parser);
  /**
   * @fn string getDataPath(const CommandLineParser&, const string&)
   * @brief Fucntion to get input data path
   * @param[in] parser to get parser from opencv
   * @param[in] dataType param to indicate if the input is image or video
   * @return input Path
   */
  string getDataPath(const CommandLineParser &parser, const string &dataType);
  /**
   * @fn VideoCapture imageProcessor(const string&, Mat)
   * @brief Function to process image
   * @param[in] rwoperation to indicate if the operation to be performed is read/write
   * @param[frame] input frame
   * @return Opens a video file or a capturing device to receive input
   */
  VideoCapture imageProcessor(const string &rwoperation, Mat frame);
  /**
   * @fn VideoCapture videoProcessor(const string&, Mat, VideoWriter)
   * @brief Function to process video
   * @param[in] rwoperation to indicate if the operation to be performed is read/write
   * @param[in] frame input frame
   * @param[in] video file to write the frame to
   * @return Opens a video file or a capturing device to receive input
   */
  VideoCapture videoProcessor(const string &rwoperation, Mat frame,
                              VideoWriter video)
};
