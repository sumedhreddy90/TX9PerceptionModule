/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  FrameTransformation.cpp
 * @brief FrameTransformation Class implementation
 * @author Pratik Acharya and Sumedh Koppula
 */

#pragma once

#include <vector>

/**
 * @fn  FrameTransformation()
 * @brief Constructor for FrameTransformation class
 * @param None
 * @return None
 */
FrameTransformation::FrameTransformation() = default;
/**
 * @fn void setTransformationMatrix(vector<vector<double>>)
 * @brief Function to set the transformation matrix
 * @param[in] matrix the transformation matrix
 * @return None
 */
void FrameTransformation::setTransformationMatrix(
    vector<vector<double>> matrix) {
}
/**
 * @fn vector<double> transformFrame(vector<double>)
 * @brief function to get the input from YOLO and transform
 * the position of detected humans into robot's frame
 * @param[in] position vector containing positions of detected humans
 * @return
 */
vector<double> FrameTransformation::transformFrame(vector<double> position) {
}
/**
 * @fn  ~FrameTransformation()
 * @brief Destructor for FrameTransformation class
 * @param None
 * @return None
 */
~FrameTransformation::FrameTransformation() {}

};
