/**
 * @copyright  MIT License (c) 2021 Sumedh Koppula and Pratik Acharya
 * @file  YoloConfig.cpp
 * @brief YoloConfig Class implementation to consume Yolo cgf, Yolo weights 
 * and coco dataset
 * @author Sumedh Koppula and Pratik Acharya
 */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <YoloConfig.hpp>

/**
 * @brief Constructor for the YoloConfig class.
 */
YoloConfig::YoloConfig()= default;
/**
 * @brief It adds Coco classes in std::vector<std::string>.
 * @param None
 * @return void
 */
void YoloConfig::setYoloClasses() {
}
/**
     * @brief It returns classes of type std::vector<std::string>.
     * @param None
     * @return std::vector<std::string>.
     */
std::vector<std::string> YoloConfig::getYoloClasses() {
    return yoloClasses;
}
/**
 * @brief It sets the Yolo Classes value.
 * @param Path
 * @return None
 */
void YoloConfig::setYoloClassesLocation(const std::string& Path) {
}
/**
 * @brief It gets the Yolo Classes file
 * @param None
 * @return Yolo Classes file Location
 */
std::string YoloConfig::getYoloClassesLocation() {
    return yoloClassesLocation;
}
/**
 * @brief It sets the the yolo.cgf file path.
 * @param yoloConfigurationFile
 * @return None
 */
void YoloConfig::setYoloConfigurationFile(const std::string& config) {
}
/**
 * @brief It gets Yolo configuration file
 * @param None
 * @return yoloConfigurationFile i.e YoloV3.cgf file
 */
std::string YoloConfig::getYoloConfigurationFile() {
    return yoloConfigurationFile;
}
/**
 * @brief It sets the yolo weights path
 * @param weights Weights File Path
 * @return None
 */
void YoloConfig::setYoloWeights(const std::string& weights) {
}
/**
 * @brief It gets the yolo weights path
 * @param None
 * @return YoloWeights File Path
 */
std::string YoloConfig::getWeights() {
    return yoloWeights;
}
/**
 * @brief Destructor for YoloConfig Class.
 */
YoloConfig::~YoloConfig() {
}
