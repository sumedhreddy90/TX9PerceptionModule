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

SensorIO sensorIO;
YoloConfig config;
HumanDetection detection;
double test = 10;
const char* keys =
    "{image img        |<none>| input image   }"
    "{video vid       |../dog.jpg| input video   }"
    "{show_output       |<none>| show output   }";
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
/**
 * @brief Test case for drawBox method of HumanDetection class.
 */
TEST(verifyDetection, verifyDrawBox) {
    config.setYoloClassesLocation("../coco.names");
    std::vector<std::string> cocoClasses = config.getYoloClasses();
    cv::Mat frame = cv::imread("", 0);
    int rows = frame.rows;
    int cols = frame.cols;
    detection.drawBox(0, 95.0, 5, 5, 10, 10, frame, cocoClasses);
    EXPECT_EQ(frame.rows, rows);
    EXPECT_EQ(frame.cols, cols);
}
/**
 * @brief Test case for humanDetection method of HumanDetection class.
 */
TEST(verifyDetection, DetectionAlgo) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, keys);
  detection.setConfidenceThreshold(0.8);
  detection.setInputHeight(320);
  detection.setInputWidth(320);
  detection.setNmsThreshold(0.5);
//   EXPECT_NO_FATAL_FAILURE(detection.humanDetection(parser,
//   sensor, detection, config));
}
/**
 * @brief Test case for humanDetection Algorithm of HumanDetection class.
 */
TEST(checkYolo, checkEliminateBox) {
  cv::Mat blob;
  config.setYoloClasses();
  std::vector<std::string> cocoClasses = config.getYoloClasses();
  // Load the neural network
  cv::dnn::Net net = cv::dnn::readNetFromDarknet(
  config.getYoloConfigurationFile(), config.getYoloWeightsFile());
  cv::Mat frame = cv::imread("../image.jpg");
  cv::dnn::blobFromImage(frame,  blob, 1/255.0,
  cv::Size(320, 320), cv::Scalar(0, 0, 0), true, false);
  net.setInput(blob);
  std::vector<cv::Mat> outs;
  net.forward(outs, detection.getOutputNames(net));
  EXPECT_NO_FATAL_FAILURE(detection.eliminateBox(frame,
  outs, 0.5, cocoClasses));
}
