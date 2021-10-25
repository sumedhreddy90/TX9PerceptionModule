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
  std::vector<std::vector<double>> transformationMatrix = { { 1, 0, 0, 0 }, { 0,
      1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

 public:
  /**
   * @fn  FrameTransformation()
   * @brief Constructor for FrameTransformation class
   * @param None
   * @return None
   */
  FrameTransformation();
  /**
   * @fn void setTransformationMatrix(std::vector<std::vector<double>>)
   * @brief Function to set the transformation matrix
   * @param[in] matrix the transformation matrix
   * @return None
   */
  void setTransformationMatrix(const std::vector<std::vector<double>> &matrix);
  /**
   * @fn std::vector<std::vector<double>> getTransformationMatrix()
   * @brief Function to get the transformation matrix
   * @param None
   * @return Transformation Matrix in 2D vector form
   */
  std::vector<std::vector<double>> getTransformationMatrix();
  /**
   * @fn std::vector<double> transformFrame(std::vector<double>)
   * @brief function to get the input from YOLO and transform
   * the position of detected humans into robot's frame
   * @param[in] position vector containing positions of detected humans
   * @return
   */
  std::vector<double> transformFrame(const std::vector<double> &position);
  /**
   * @fn  ~FrameTransformation()
   * @brief Destructor for FrameTransformation class
   * @param None
   * @return None
   */
  ~FrameTransformation();

};
