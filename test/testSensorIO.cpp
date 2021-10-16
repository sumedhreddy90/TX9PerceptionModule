/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  testSensorIO.cpp
 * @brief Tests for SensorIO class
 * @author Pratik Acharya and Sumedh Koppula
 */

#pragma once
#include <gtest/gtest.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <SensorIO.hpp>

SensorIO sensor;
int testInt = 416;
std::string testString = "test";

const char *testImageKey = "{image i        |path/to/image.jpg| input image   }"
    "{video v       |<none>| input video   }"
    "{showOutput       |<none>| show output   }";

const char *testVideoKey = "{image i        |<none>| input image   }"
    "{video v       |path/to/video.mp4| input video   }"
    "{showOutput       |<none>| show output   }";

const char *testNoneKey = "{image i        |<none>| input image   }"
    "{video v       |<none>| input video   }"
    "{showOutput       |<none>| show output   }";

/**
 * @brief test for getOutputWidth() and setOutputWidth() methods
 */
TEST_F(testGetSet, testOutputWidth) {
  sensor.setOutputWidth(testInt);
  EXPECT_EQ(sensor.getOutputWidth(), testInt);
}
/**
 * @brief test for getOutputHeight() and setOutputHeight() methods
 */
TEST_F(testGetSet, testOutputHeight) {
  sensor.setOutputHeight(testInt);
  EXPECT_EQ(sensor.getOutputHeight(), testInt);
}
/**
 * @brief test for getImagePath() and setImagePath() methods
 */
TEST_F(testGetSet, testImagePath) {
  sensor.setImagePath(testString);
  EXPECT_EQ(sensor.getImagePath(), testString);
}
/**
 * @brief test for getVideoPath() and setVideoPath() methods
 */
TEST_F(testGetSet, testVideoPath) {
  sensor.setVideoPath(testString);
  EXPECT_EQ(sensor.getVideoPath(), testString);
}
/**
 * @brief test for getDataType() method using image as input
 */
TEST_F(testGetSet, testDataTypeImage) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, testImageKey);
  EXPECT_EQ(sensor.getDataType(parser), "image");
}
/**
 * @brief test for getDataType() method using video as input
 */
TEST_F(testGetSet, testDataTypeVideo) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, testVideoKey);
  EXPECT_EQ(sensor.getDataType(parser), "video");
}
/**
 * @brief test for getDataType() method with no input
 */
TEST_F(testGetSet, testDataTypeNone) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, testNoneKey);
  EXPECT_EQ(sensor.getDataType(parser), "Error");
}
/**
 * @brief test for getDataPath() method using image as input
 */
TEST_F(testGetSet, testDataPathImage) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, testImageKey);
  EXPECT_EQ(sensor.getDataPath(parser, "val"), "path/to/image.jpg");
}
/**
 * @brief test for getDataPath() method using video as input
 */
TEST_F(testGetSet, testDataPathVideo) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, testVideoKey);
  EXPECT_EQ(sensor.getDataPath(parser, "val"), "path/to/video.jpg");
}
/**
 * @brief test for getDataPath() method with no input
 */
TEST_F(testGetSet, testDataPathNone) {
  int argc = 0;
  const char *argv = "";
  cv::CommandLineParser parser(argc, &argv, testNoneKey);
  EXPECT_EQ(sensor.getDataPath(parser, "val"), "Error");
}
/**
 * @brief test for imageProcessor() method for read operation
 */
TEST_F(testProcessor, testImageProcessor) {
  cv::Mat frame;
  cv::VideoCapture cap;
  cap.open("image.jpg");
  user.setImagePath("img.jpg");
  cv::VideoCapture capture = sensor.imageProcessor("read", frame);
  EXPECT_EQ(capture.get(cv::CAP_PROP_FRAME_HEIGHT),
            cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}
/**
 * @brief test for videoProcessor() method for read operation
 */
TEST_F(testProcessor, testVideoProcessor) {
  cv::Mat frame;
  cv::VideoCapture cap;
  cv::VideoWriter video;
  cap.open("video.mp4");
  user.setImagePath("video.mp4");
  cv::VideoCapture capture = sensor.videoProcessor("read", frame, video);
  EXPECT_EQ(capture.get(cv::CAP_PROP_FRAME_HEIGHT),
            cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}
/**
 * @brief test for imageProcessor() method for write operation
 */
TEST_F(testProcessor, testImageProcessorWrite) {
  cv::Mat frame = cv::imread("image.jpg");
  EXPECT_NO_FATAL_FAILURE(sensor.imageProcessor("write", frame));
}
/**
 * @brief test for videoProcessor() method for write operation
 */
TEST_F(testProcessor, testVideoProcessorWrite) {
  cv::Mat frame;
  cv::VideoCapture cap
  cv::VideoWriter video;
  cv::Mat frame = cv::imread("image.jpg");
  EXPECT_NO_FATAL_FAILURE(sensor.videoProcessor("write", frame, video));
}
