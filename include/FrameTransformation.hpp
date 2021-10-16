/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  FrameTransformation.hpp
 * @brief FrameTransformation Class implementation
 * @author Pratik Acharya and Sumedh Koppula
 */

#pragma once

#include <vector>

/**
 * @class FrameTransformation
 * @brief A class to transform the position of detected humans from \
 * camera's frame of reference to robot's frame of reference
 *
 */
class FrameTransformation {
 private:
  /**
   * @brief private variable for transformation matrix
   */
  vector<vector<double>> transformationMatrix;

 public:
  /**
   * @fn  FrameTransformation()
   * @brief Constructor for FrameTransformation class
   * @param None
   * @return None
   */
  FrameTransformation();
  /**
   * @fn void setTransformationMatrix(vector<vector<double>>)
   * @brief Function to set the transformation matrix
   * @param[in] matrix the transformation matrix
   * @return None
   */
  void setTransformationMatrix(vector<vector<double>> matrix);
  /**
   * @fn vector<double> transformFrame(vector<double>)
   * @brief function to get the input from YOLO and transform
   * the position of detected humans into robot's frame
   * @param[in] position vector containing positions of detected humans
   * @return
   */
  vector<double> transformFrame(vector<double> position);
  /**
   * @fn  ~FrameTransformation()
   * @brief Destructor for FrameTransformation class
   * @param None
   * @return None
   */
  ~FrameTransformation();

};
