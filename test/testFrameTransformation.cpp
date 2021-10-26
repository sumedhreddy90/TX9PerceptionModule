/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  testFrameTransformation.cpp
 * @brief Tests for FrameTransformation class
 * @author Pratik Acharya and Sumedh Koppula
 */

#include <gtest/gtest.h>
#include <FrameTransformation.hpp>

FrameTransformation frameTransformation;
std::vector<std::vector<double>> testMatrix { { 1, 0, 0, 1 }, { 0, 1, 0, 1 }, {
    0, 0, 1, -2 }, { 0, 0, 0, 1 } };
std::vector<double> testVector { 1, 2, 3, 4 };
std::vector<double> eqVector { 5, 6, -5, 4};

/**
 * @brief test for getTransformationMatrix() and setTransformationMatrix() methods
 */
TEST(testGetSet, testTransformationMatrix) {
  frameTransformation.setTransformationMatrix(testMatrix);
  EXPECT_EQ(frameTransformation.getTransformationMatrix(), testMatrix);
}

/**
 * @brief test for transformFrame() method
 */
TEST(testTransformation, testTransformFrame) {
  EXPECT_EQ(frameTransformation.transformFrame(testVector), eqVector);
}
