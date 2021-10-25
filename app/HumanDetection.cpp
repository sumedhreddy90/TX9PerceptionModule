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
#include <FrameTransformation.hpp>
/**
 * @brief  constructor for HumanDetection class.
 */
HumanDetection::HumanDetection() {
  inputHeight = 320;
  inputWidth = 320;
  confidenceThreshold = 0.8;
  nmsThreshold = 0.4;
  averageHeight = 175;
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

  // Iterating through detected objects
  for (const auto &out : outs) {
    auto *data = reinterpret_cast<float*>(out.data);
    // iterating to get confidence and class for
    // each detected object
    for (int j = 0; j < out.rows; ++j, data += out.cols) {
      cv::Mat scores = out.row(j).colRange(5, out.cols);
      cv::Point classIdPoint;
      double confidence;

      minMaxLoc(scores, nullptr, &confidence, nullptr, &classIdPoint);

      // Condition to check if confidence threshold is satisfied and the class
      // is human
      if (confidence > confidenceThreshold && classIdPoint.x == 00) {
        int centerX = static_cast<int>(data[0] * frame.cols);
        int centerY = static_cast<int>(data[1] * frame.rows);
        int width = static_cast<int>(data[2] * frame.cols);
        int height = static_cast<int>(data[3] * frame.rows);
        int top_x = centerX - width / 2;
        int top_y = centerY - height / 2;

        // Storing confidence, class and the detection box
        classIds.push_back(classIdPoint.x);
        confidences.push_back(static_cast<float>(confidence));
        boxes.push_back(cv::Rect(top_x, top_y, width, height));
      }
    }
  }

  // Using non-maximum suppression to remove redundant overlapping bounding boxes
  std::vector<int> indices;
  cv::dnn::NMSBoxes(boxes, confidences, confidenceThreshold, nmsThreshold,
                    indices);
  int humanid = 1;
  for (int index : indices) {
    int focalLen = 24;
    int sensorHei = 40;
    cv::Rect box = boxes[index];
    double distance = HumanDetection::humanDistance(averageHeight, box.height,
                                                    focalLen, sensorHei, 720);
    std::cout << "Human " << humanid;
    humanPosition(box, distance);
    humanid++;
    // Drawing the boxes on the frame for output
    drawBox(classIds[index], confidences[index], box.x, box.y,
            box.x + box.width, box.y + box.height, frame, classes, distance);
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
                             int right, int bottom, const cv::Mat &frame,
                             std::vector<std::string> classes,
                             double distance) {
  //define the rectangle that needs to be drawn
  rectangle(frame, cv::Point(left, top), cv::Point(right, bottom),
            cv::Scalar(0, 168, 0), 3);
  std::string label = cv::format("%.2f", conf);
  // Creating label
  if (!classes.empty()) {
    CV_Assert(classId < static_cast<int>(classes.size()));
    label = classes[classId] + ":" + label;
  }

  // printing the box and label on the frame
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

  // get the classes from the configuration file
  config.setYoloClasses();
  classes = config.getYoloClasses();

  // Configure the neural network
  cv::dnn::Net net = cv::dnn::readNetFromDarknet(
      config.getYoloConfigurationFile(), config.getYoloWeightsFile());
  net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
  net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

  // Condition to check if the input is
  // image, video or erroneous input
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
    if (dataType == "video") {
      io.setVideoPath(dataPath);
      cap = io.videoProcessor("read", frame, video);
      io.setOutputWidth(cap.get(cv::CAP_PROP_FRAME_WIDTH));
      io.setOutputHeight(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    }
  } catch (...) {
    std::cout << "Unable to open the input stream" << std::endl;
  }

  // configuring output file if the input is video
  if (parser.has("video")) {
    video.open("../op_test.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
               24, cv::Size(io.getOutputWidth(), io.getOutputHeight()), true);
  }

  // Messag to be printed after completing processing
  while (cv::waitKey(1) < 0) {
    cap >> frame;
    if (frame.empty()) {
      std::cout << "Done processing" << std::endl;
      std::cout << "Output file is stored in the output folder " << outputFile
          << std::endl;
      cap.release();
      video.release();
      cv::waitKey(2000);
      break;
    }

    // creating 4D blob to pass it to the neural network
    cv::dnn::blobFromImage(frame, blob, 1 / 255.0,
                           cv::Size(getInputWidth(), getInputHeight()),
                           cv::Scalar(0, 0, 0), true, false);

    net.setInput(blob);

    std::vector < cv::Mat > outs;
    net.forward(outs, human_detection.getOutputNames(net));

    // Eliminate boxes that are not humans, and are overlapping
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

    if (parser.has("image"))
      io.imageProcessor("write", frame);

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

  // Release the frames from the input
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
  // calculating the height of the detection from pixels to
  // millimeter
  double heightPxMm = (sensorHeight * boxHeight) / frameHeight;
  // Calculating the distance from by assuming he height of the human
  double humanDist = (averageHeight * focalLength) / heightPxMm;
  return humanDist;
}
/**
 * @brief humanPosition combines the distance parameter and bounding box paramters
 * to get 3D positon which can be outputed.
 *
 * @param humanId
 * @param distance
 */
FrameTransformation transform;
void HumanDetection::humanPosition(cv::Rect box, double distance) {
  std::vector<double> position;
  // Calculating the middle point of the detected box
  // to get the human position
  int sensorWidth1 = 24;
  int sensorHeight1 = 35;
  double midpoint_x = (sensorWidth1 * ((box.x + (box.width / 2)) - (1080 / 2)))
      / 720;
  double midpoint_y = (sensorHeight1 * ((box.y + (box.height / 3)) - (720 / 2)))
      / 1080;
  position.push_back(midpoint_x);
  position.push_back(midpoint_y);
  position.push_back(distance / 100);
  position.push_back(1.0);
  // Using transformation matrix to get the position relative to robot
  std::vector<double> finalposition = transform.transformFrame(position);
  finalposition.pop_back();
  std::cout << " position(meters) : ";
  for (auto &x : finalposition) {
    std::cout << x << "\t";
  }
  std::cout << std::endl;

  position.clear();
}
