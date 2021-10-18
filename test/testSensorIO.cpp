/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  testSensorIO.cpp
 * @brief Tests for SensorIO class
 * @author Pratik Acharya and Sumedh Koppula
 */

#include <gtest/gtest.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <SensorIO.hpp>

SensorIO sensor;
int testInt = 416;

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
TEST(testGetSet, testOutputWidth) {
  sensor.setOutputWidth(testInt);
  EXPECT_EQ(sensor.getOutputWidth(), testInt);
}
/**
 * @brief test for getOutputHeight() and setOutputHeight() methods
 */
TEST(testGetSet, testOutputHeight) {
  sensor.setOutputHeight(testInt);
  EXPECT_EQ(sensor.getOutputHeight(), testInt);
}
/**
 * @brief test for getImagePath() and setImagePath() methods
 */
TEST(testGetSet, testImagePath) {
sensor.setImagePath("test";);
EXPECT_EQ(sensor.getImagePath(), "test";);
}
/**
 * @brief test for getVideoPath() and setVideoPath() methods
 */
TEST(testGetSet, testVideoPath) {
sensor.setVideoPath("test";);
EXPECT_EQ(sensor.getVideoPath(), "test";);
}
/**
 * @brief test for getDataType() method using image as input
 */
TEST(testGetSet, testDataTypeImage) {
int argc = 0;
const char *argv = "";
cv::CommandLineParser parser(argc, &argv, testImageKey);
EXPECT_EQ(sensor.getDataType(parser), "image");
}
/**
 * @brief test for getDataType() method using video as input
 */
TEST(testGetSet, testDataTypeVideo) {
int argc = 0;
const char *argv = "";
cv::CommandLineParser parser(argc, &argv, testVideoKey);
EXPECT_EQ(sensor.getDataType(parser), "video");
}
/**
 * @brief test for getDataType() method with no input
 */
TEST(testGetSet, testDataTypeNone) {
int argc = 0;
const char *argv = "";
cv::CommandLineParser parser(argc, &argv, testNoneKey);
EXPECT_EQ(sensor.getDataType(parser), "Error");
}
/**
 * @brief test for getDataPath() method using image as input
 */
TEST(testGetSet, testDataPathImage) {
int argc = 0;
const char *argv = "";
cv::CommandLineParser parser(argc, &argv, testImageKey);
EXPECT_EQ(sensor.getDataPath(parser, "val"), "path/to/image.jpg");
}
/**
 * @brief test for getDataPath() method using video as input
 */
TEST(testGetSet, testDataPathVideo) {
int argc = 0;
const char *argv = "";
cv::CommandLineParser parser(argc, &argv, testVideoKey);
EXPECT_EQ(sensor.getDataPath(parser, "val"), "path/to/video.jpg");
}
/**
 * @brief test for getDataPath() method with no input
 */
TEST(testGetSet, testDataPathNone) {
int argc = 0;
const char *argv = "";
cv::CommandLineParser parser(argc, &argv, testNoneKey);
EXPECT_EQ(sensor.getDataPath(parser, "val"), "Error");
}
/**
 * @brief test for imageProcessor() method for read operation
 */
TEST(testProcessor, testImageProcessor) {
cv::Mat frame;
cv::VideoCapture cap;
cap.open("image.jpg");
sensor.setImagePath("img.jpg");
cv::VideoCapture capture = sensor.imageProcessor("read", frame);
EXPECT_EQ(capture.get(cv::CAP_PROP_FRAME_HEIGHT),
          cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}
/**
 * @brief test for videoProcessor() method for read operation
 */
TEST(testProcessor, testVideoProcessor) {
cv::Mat frame;
cv::VideoCapture cap;
cv::VideoWriter video;
cap.open("video.mp4");
sensor.setImagePath("video.mp4");
cv::VideoCapture capture = sensor.videoProcessor("read", frame, video);
EXPECT_EQ(capture.get(cv::CAP_PROP_FRAME_HEIGHT),
          cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}
/**
 * @brief test for imageProcessor() method for write operation
 */
TEST(testProcessor, testImageProcessorWrite) {
cv::Mat frame = cv::imread("image.jpg");
EXPECT_NO_FATAL_FAILURE(sensor.imageProcessor("write", frame));
}
/**
 * @brief test for videoProcessor() method for write operation
 */
TEST(testProcessor, testVideoProcessorWrite) {
cv::VideoCapture cap;
cv::VideoWriter video;
cv::Mat frame = cv::imread("image.jpg");
EXPECT_NO_FATAL_FAILURE(sensor.videoProcessor("write", frame, video));
}
