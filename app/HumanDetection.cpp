/**
 * @copyright  MIT License (c) 2021 Sumedh Koppula and Pratik Acharya
 * @file  HumanDetection.cpp
 * @brief Implementaion of HumanDetection class, In order to implement
 *  detection algorithm for input video stream/ Image Frames
 * It also helps in storing video and displays output with Bounding Boxes.
 * @author Sumedh Koppula and Pratik Acharya
 */

#include <vector>
#include <iostream>
#include <HumanDetection.hpp>
#include <SensorIO.hpp>
#include <YoloConfig.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
/**
 * @brief  constructor for HumanDetection class.
 */
HumanDetection::HumanDetection() {
  inputHeight = 416;
  inputWidth = 416;
  confidenceThreshold = 0.8;
  nmsThreshold = 0.4;
}
/**
 * @brief set the inputWidth value.
 * @param width
 * @return type void.
 */
void HumanDetection::setInputWidth(int width) {
  inputWidth = width;
}
/**
 * @brief set the inputHeight value.
 * @param height
 * @return type void.
 */
void HumanDetection::setInputHeight(int height) {
  inputHeight = height;
}
/**
 * @brief set the confidenceThreshold value.
 * @param configThres
 * @return type void.
 */
void HumanDetection::setConfidenceThreshold(float configThres) {
  confidenceThreshold = configThres;
}
/**
 * @brief set the nmsThreshold value.
 * @param nmsThres
 * @return type void.
 */
void HumanDetection::setNmsThreshold(float nmsThres) {
  nmsThreshold = nmsThres;
}
/**
 * @brief returns the inputWidth value.
 * @param None
 * @return type int.
 */
int HumanDetection::getInputWidth() {
  return inputWidth;
}
/**
 * @brief returns the inputHeight value.
 * @param None
 * @return type int.
 */
int HumanDetection::getInputHeight() {
  return inputHeight;
}
/**
 * @brief returns the confidenceThreshold value.
 * @param None
 * @return type float.
 */
float HumanDetection::getConfidenceThreshold() {
  return confidenceThreshold;
}
/**
 * @brief returns the nmsThreshold value.
 * @param None
 * @return type float.
 */
float HumanDetection::getNmsThreshold() {
  return nmsThreshold;
}
/**
 * @brief This method predicts the best bounding box
 *         for each detection and eliminates the redundant/ overlapping box.
 * @param frame
 * @param outs
 * @param confThreshold
 * @param classes
 * @return None.
 */
void HumanDetection::eliminateBox(cv::Mat &frame,
                                  const std::vector<cv::Mat> &outs,
                                  float confThreshold,
                                  const std::vector<std::string> &classes) {
  std::vector<int> classIds;
  std::vector<float> confidences;
  std::vector < cv::Rect > boxes;

  for (const auto &out : outs) {
    auto *data = (double*) out.data;
    for (int j = 0; j < out.rows; ++j, data += out.cols) {
      cv::Mat scores = out.row(j).colRange(5, out.cols);
      cv::Point classIdPoint;
      double confidence;

      minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);
      if (confidence > confidenceThreshold) {
        int centerX = (int) (data[0] * frame.cols);
        int centerY = (int) (data[1] * frame.rows);
        int width = (int) (data[2] * frame.cols);
        int height = (int) (data[3] * frame.rows);
        int top_x = centerX - width / 2;
        int top_y = centerY - height / 2;

        classIds.push_back(classIdPoint.x);
        confidences.push_back((float) confidence);
        boxes.push_back(cv::Rect(top_x, top_y, width, height));
      }
    }
  }

  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, confidenceThreshold, nmsThreshold,
                    indices);
  for (int index : indices) {
    cv::Rect box = boxes[index];
    drawBox(classIds[index], confidences[index], box.x, box.y,
            box.x + box.width, box.y + box.height, frame, classes);
  }
}
/*
 * @brief This Method helps in drawing the bounding box
 for detected object with its label/ class ID
 * @param classId
 * @param conf
 * @param left
 * @param right
 * @param bottom
 * @param &frame
 * @param classes
 * @return None
 */
void HumanDetection::drawBox(int classId, float conf, int left, int top,
                             int right, int bottom, cv::Mat &frame,
                             std::vector<std::string> classes) {
  rectangle(frame, cv::Point(left, top), cv::Point(right, bottom),
            cv::Scalar(0, 168, 0), 3);
  std::string label = cv::format("%.2f", conf);
  if (!classes.empty()) {
    CV_Assert(classId < (int) classes.size());
    label = classes[classId] + ":" + label;
  }
  int baseLine;
  cv::Size labelSize = getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1,
                                   &baseLine);
  top = std::max(top, labelSize.height);
  rectangle(frame, cv::Point(left, top - round(1.5 * labelSize.height)),
            cv::Point(left + round(1.5 * labelSize.width), top + baseLine),
            cv::Scalar(255, 255, 255), cv::FILLED);
  putText(frame, label, cv::Point(left, top), cv::FONT_HERSHEY_SIMPLEX, 0.75,
          cv::Scalar(0, 0, 0), 1);
}
/* @brief This method returns the label
 * names of the detected objects
 * @param net
 * @return type std::vector<std::string>
 */
std::vector<std::string> HumanDetection::getOutputNames(
    const cv::dnn::Net &net) {
  static std::vector<cv::String> names;
  if (names.empty()) {
    std::vector<int> outLayers = net.getUnconnectedOutLayers();
    std::vector < cv::String > layersNames = net.getLayerNames();
    names.resize(outLayers.size());
    for (size_t i = 0; i < outLayers.size(); ++i) {
      names[i] = layersNames[outLayers[i] - 1];
    }
  }
  return names;
}
/*
 * @brief Our Human Detection algorithm is implemented in
 this method. This performs detection of input stream.
 It also stores video and displays output with Bounding Boxes.
 * @param parser
 * @param SensorIO
 * @param HumanDetection
 * @param YoloConfig
 */
void HumanDetection::humanDetection(cv::CommandLineParser parser, SensorIO io,
                                    HumanDetection human_detection,
                                    YoloConfig config) {
  std::vector < std::string > classes;

  config.setYoloClasses();
  classes = config.getYoloClasses();

  cv::dnn::Net net = cv::dnn::readNetFromDarknet(
      config.getYoloConfigurationFile(), config.getYoloWeightsFile());
  net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
  net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

  std::string str, outputFile;
  cv::VideoCapture cap;
  cv::VideoWriter video;
  cv::Mat frame, blob;

  try {
    std::string dataType = io.getDataType(parser);
    std::string dataPath = io.getDataPath(parser, dataType);
    if (dataType == "image") {
      io.setImagePath(dataPath);
      cap = io.imageProcessor("read", frame);
    }
  } catch (...) {
    std::cout << "Unable to open the input stream" << std::endl;
  }

  while (cv::waitKey(1) < 0) {
    cap >> frame;
    if (frame.empty()) {
      std::cout << "Done processing" << std::endl;
      std::cout << "Output file is stored in the output folder " << outputFile
          << std::endl;
      cap.release();
      video.release();
      cv::waitKey(5000);
      break;
    }

    cv::dnn::blobFromImage(frame, blob, 1 / 255.0,
                           cv::Size(getInputWidth(), getInputHeight()),
                           cv::Scalar(0, 0, 0), true, false);

    net.setInput(blob);

    std::vector < cv::Mat > outs;
    net.forward(outs, human_detection.getOutputNames(net));

    human_detection.eliminateBox(frame, outs, getConfidenceThreshold(),
                                 classes);

    std::vector<double> layersTimes;
    double freq = cv::getTickFrequency() / 1000;
    double t = net.getPerfProfile(layersTimes) / freq;
    std::string label = cv::format("Inference time for a frame : %.2f ms", t);
    putText(frame, label, cv::Point(0, 15), cv::FONT_HERSHEY_SIMPLEX, 0.5,
            cv::Scalar(0, 0, 255));

    cv::Mat detectedFrame;
    frame.convertTo(detectedFrame, CV_8U);

    if (parser.has("video")) {
      io.setOutputWidth(frame.size().width);
      io.setOutputHeight(frame.size().height);
      io.videoProcessor("write", frame, video);
    }
    if (parser.has("show_output")) {
      static const std::string kWinName = " Human/object detection in OpenCV";
      namedWindow(kWinName, cv::WINDOW_NORMAL);
      imshow(kWinName, frame);
      if (parser.has("image")) {
        cv::waitKey(5000);
      }
    }
  }
  cap.release();
  video.release();
  if (!parser.has("image"))
    video.release();
}
/**
 * @brief humanDistance method calculates the distance between the robot
 * and detected human by assuming the height of the human to as
 * 178cm
 *
 * @param averageHeight
 * @param boxHeight
 * @param focalLength
 * @param sensorHeight
 * @param frameHeight
 * @return double
 */
double HumanDetection::humanDistance(int averageHeight, int boxHeight,
                                     double focalLength, double sensorHeight,
                                     int frameHeight) {
  return 0;
}
/**
 * @brief humanPosition combines the distance parameter and bounding box paramters
 * to get 3D positon which can be outputed.
 *
 * @param humanId
 * @param distance
 */
void HumanDetection::humanPosition(std::string humanId, double distance) {
}
