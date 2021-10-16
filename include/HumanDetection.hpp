/**
 * @copyright  MIT License (c) 2021 Sumedh Koppula and Pratik Acharya
 * @file  HumanDetection.hpp
 * @brief Declaration of HumanDetection class, In order to implement
 *  detection algorithm for input video stream/ Image Frames
 * It also helps in storing video and displays output with Bounding Boxes.
 * @author Sumedh Koppula and Pratik Acharya
 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "YoloConfig.hpp"

/**
 * @brief HumanDetection class runs object detection on input image or video.
 */
class HumanDetection {
 private:
  /**
  * @brief private variable for inputWidth.
  */
  int inputWidth{0};
  /**
  * @brief private variable for inputHeight.
  */
  int inputHeight{0};
  /**
   * @brief private variable for averageHeight.
   * 
   */
  int averageHeight{0};
  /**
  * @brief private variable for configurationThreshold.
  */
  float confidenceThreshold{0};
  /**
  * @brief private variable for nmsThreshold.
  */
  float nmsThreshold{0};

 public:
  /**
  * @brief  constructor for HumanDetection class with no parameters.
  */
  HumanDetection();
  /**
  * @brief set the inputWidth value.
  * @param width
  * @return type void.
  */
  void setInputWidth(int width);
  /**
  * @brief set the inputHeight value.
  * @param height
  * @return type void.
  */
  void setInputHeight(int height);
  /**
   * @brief Set the Average Height object
   * 
   */
  void setConfidenceThreshold(float configThres);
  /**
  * @brief set the nmsThreshold value.
  * @param nmsThres
  * @return type void.
  */
  void setNmsThreshold(float nmsThres);
  /**
  * @brief returns the inputWidth value.
  * @param None
  * @return type int.
  */
  int getInputWidth();
  /**
  * @brief returns the inputHeight value.
  * @param None
  * @return type int.
  */
  int getInputHeight();
  /**
  * @brief returns the configurationThreshold value.
  * @param None
  * @return type float.
  */
  float getConfidenceThreshold();
  /*
  * @brief returns the nmsThreshold value.
  * @param None
  * @return type float.
  */
  float getNmsThreshold();
  /*
   * @brief This method predicts the best bounding box
   for each detection and eliminates the redundant/ overlapping box 
   * @param frame
   * @param outs
   * @param confThreshold
   * @param classes
   * @return None.
   */
  void eliminateBox(cv::Mat& frame, const std::vector<cv::Mat>& outs ,
  float confThreshold, const std::vector<std::string>& classes);
  /*
   * @brief This Method helps in drawing the bounding box
    for detected object with its label/ class ID
   * @param classId
   * @param conf
   * @param left
   * @param right
   * @param bottom
   * @param &frame
   * @param classes
   * @return None
   */
  static void drawBox(int classId, float conf, int left,
  int top, int right, int bottom, cv::Mat &frame,
  std::vector<std::string> classes);
  /* @brief This method returns the label
   * names of the detected objects
   * @param net
   * @return type std::vector<std::string>
   */
  static std::vector<std::string> getOutputNames(const cv::dnn::Net& net);
  /*
   * @brief Our Human Detection algorithm is implemented in 
   this method. This performs detection of input stream.
   It also stores video and displays output with Bounding Boxes.
   * @param parser
   * @param SensorIO
   * @param HumanDetection
   * @param YoloConfig
   */
  void humanDetection(cv::CommandLineParser parser, SensorIO io,
  HumanDetection human_detection, YoloConfig config);
};
