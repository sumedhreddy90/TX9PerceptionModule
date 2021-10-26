/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  FrameTransformation.cpp
 * @brief FrameTransformation Class implementation
 * @author Pratik Acharya and Sumedh Koppula
 */

#include <FrameTransformation.hpp>
#include <vector>

/**
 * @fn  FrameTransformation()
 * @brief Constructor for FrameTransformation class
 * @param None
 * @return None
 */
FrameTransformation::FrameTransformation() = default;
/**
 * @fn void setTransformationMatrix(std::vector<std::vector<double>>)
 * @brief Function to set the transformation matrix
 * @param[in] matrix the transformation matrix
 * @return None
 */
void FrameTransformation::setTransformationMatrix(
    const std::vector<std::vector<double>> &matrix) {
}
/**
 * @fn std::vector<std::vector<double>> getTransformationMatrix()
 * @brief Function to get the transformation matrix
 * @param None
 * @return Transformation Matrix in 2D vector form
 */
std::vector<std::vector<double>>
FrameTransformation::getTransformationMatrix() {
  return transformationMatrix;
}
/**
 * @fn std::vector<double> transformFrame(std::vector<double>)
 * @brief function to get the input from YOLO and transform
 * the position of detected humans into robot's frame
 * @param[in] position vector containing positions of detected humans
 * @return
 */
std::vector<double> FrameTransformation::transformFrame(
    const std::vector<double> &position) {
    double mult_sum = 0;
    std::vector<double> finalPosition;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        mult_sum += transformationMatrix[i][j]*position[j];
      }
      finalPosition.push_back(mult_sum);
      mult_sum = 0;
    }
  return finalPosition;
}
/**
 * @fn  ~FrameTransformation()
 * @brief Destructor for FrameTransformation class
 * @param None
 * @return None
 */
FrameTransformation::~FrameTransformation() {
}
