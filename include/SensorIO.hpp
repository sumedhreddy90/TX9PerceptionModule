#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::endl;
using cv::CommandLineParser;
using cv::VideoCapture;
using cv::Mat;

class SensorIO {
 private:
  string imagePath;
  string videoPath;
  int outputWidth;
  int outputHeight;

 public:
  SensorIO();

  void setOutputWidth(int width);

  void setOutputHeight(int height);

  int getOutputWidth();

  int getOutputHeight();

  void setImagePath(string path);

  void setVideoPath(string path);

  string getImagePath();

  string getVideoPath();

  string getDataType(const CommandLineParser parser);

  string getDataPath(const CommandLineParser &parser, const string &dataType);

  VideoCapture imageProcessor(const string &ops, Mat frame);

  VideoCapture videoProcessor(const string &ops, Mat frame, VideoWriter video)
};
