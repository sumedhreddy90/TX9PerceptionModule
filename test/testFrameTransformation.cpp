/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  testFrameTransformation.cpp
 * @brief Tests for FrameTransformation class
 * @author Pratik Acharya and Sumedh Koppula
 */

#pragma once
#include <gtest/gtest.h>
#include <FrameTransformation.hpp>

FrameTransformation frameTransformation;
std::vector<std::vector<double>> testMatrix { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0,
    1 } };
std::vector<double> testVector { 1, 2, 3 };

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
  EXPECT_EQ(frameTransformation.transformFrame(testVector), testMatrix);
}
