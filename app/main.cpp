/**
 * @copyright  MIT License (c) 2021 Pratik Acharya and Sumedh Koppula
 * @file  main.cpp
 * @brief main method implementation
 * @author Pratik Acharya and Sumedh Koppula
 */

#include <fstream>
#include <sstream>
#include <iostream>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <SensorIO.hpp>
#include <HumanDetection.hpp>
#include <YoloConfig.hpp>

/*
 * @brief This gets displayed if the help parameter is
 * passed as an argument.
 */
const char* keys =
    "{help h usage ? | | Usage examples: "
    "\n\t\t./object_detection_yolo.out --image=image.jpg "
    "\n\t\t./object_detection_yolo.out --video=sample.mp4"
    "\n\t\t./object_detection_yolo.out --show_output}"
    "{image img        | ../image.jpg | input image   }"
    "{video vid       |<none>| input video   }"
    "{show_output       |true| show output   }";

int main(int argc, char** argv) {
    /*
   * @brief Instantiate objects for each class.
   */
  HumanDetection detection;
  SensorIO sensIO;
  YoloConfig configY;

  cv::CommandLineParser parser(argc, argv, keys);
  parser.about("script to run object"
               "detection using YOLO3 in OpenCV.");

  if (parser.has("help")) {
    parser.printMessage();
    return 0;
  }
  /*
   * @brief Running Human Detection algorithm.
   */
  detection.humanDetection(parser, sensIO, detection, configY);
  return 0;
}
