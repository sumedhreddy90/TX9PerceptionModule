/**
 * @copyright  MIT License (c) 2021 Sumedh Koppula and Pratik Acharya
 * @file  testHumanDetection.hpp
 * @brief Unit tests for HumanDetection Class. Unit tests for testing Human detection
 * Algorithm, drawBox() and other required getter setter tests for thresholds
 * @author Sumedh Koppula and Pratik Acharya
 */

#include <gtest/gtest.h>
#include<SensorIO.hpp>
#include<YoloConfig.hpp>
#include<HumanDetection.hpp>

SensorIO sensor;
YoloConfig config;
HumanDetection detection;
double test = 10;
/**
 * @brief Test case for setNmsThreshold method of HumanDetection class.
 * This verifies whether value set for nmsThreshold is same as the value input
 * by the getNmsThreshold method.
 */
TEST(DetectionGetterSetter, verifynmsThreshold) {
    detection.setNmsThreshold(test);
    EXPECT_EQ(detection.getNmsThreshold(), test);
}
/**
 * @brief Test case for setConfidenceThreshold method of HumanDetection class. 
 * This test verifies whether value set for confidence is same as the value input
 * by the getConfidenceThreshold method.
 */
TEST(DetectionGetterSetter, verifyConfThreshold) {
    detection.setConfidenceThreshold(test);
    EXPECT_EQ(detection.getConfidenceThreshold(), test);
}
/**
 * @brief Test case for setInputHeight method of HumanDetection class. 
 * This test checks whether value set for InputHeight is same as the value input
 * by the getInputHeight method.
 */
TEST(DetectionGetterSetter, verifyInputHeight) {
    detection.setInputHeight(test);
    EXPECT_EQ(detection.getInputHeight(), test);
}
/**
 * @brief Test case for setInputWidth method of HumanDetection class. The
 * test checks whether value set for InputWidth is same as the value input
 * by the getInputWidth method.
 */
TEST(DetectionGetterSetter, verifyInputWidth) {
    detection.setInputWidth(test);
    EXPECT_EQ(detection.getInputWidth(), test);
}

