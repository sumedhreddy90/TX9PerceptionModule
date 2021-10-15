/**
 * @copyright  MIT License (c) 2021 Sumedh Koppula and Pratik Acharya
 * @file  YoloConfig.hpp
 * @brief YoloConfig Class helps us to consume Yolo cgf, Yolo weights 
 * and coco dataset
 * @author Sumedh Koppula and Pratik Acharya
 */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

class YoloConfig{
 private:
    /**
    * @brief private variable for yoloClasses.
    */
    std::vector<std::string> yoloClasses;

    /**
     * @brief private variable for yoloClassesLocation.
     */
    std::string yoloClassesLocation ="../coco.names";

    /**
     * @brief private variable for yoloConfiguration.
     */
    std::string yoloConfigurationFile ="../yolov3.cfg";


    /**
     * @brief private variable for yoloWeights.
     */
    std::string yoloWeights ="../yolov3.weights";

 public:
     /**
     * @brief constructor for Yoloconfig class with no parameters.
     */
    YoloConfig();
    /**
     * @brief It returns yoloclasses of type std::vector<std::string>.
     * @param None
     * @return std::vector<std::string>.
     */
    std::vector<std::string> getYoloClasses();
    /**
     * @brief It adds classes in std::vector<std::string>.
     * @param None
     * @return void.
     */
    void setYoloClasses();
    /**
     * @brief It returns the Coco.names file.
     * @param None
     * @return std::string.
     */
    std::string getYoloClassesLocation();
    /**
     * @brief It sets the Coco.names file value.
     * @param cocoPath (It is the path for the Coco.names file.)
     * @return void.
     */
    void setYoloClassesLocation(const std::string& cocoPath);
    /**
     * @brief It returns the getYoloConfigurationFile value.
     * @param None
     * @return std::string.
     */
    std::string getYoloConfigurationFile();

    /**
     * @brief It sets the yoloConfigurationFile value.
     * @param YoloConfigurationFile (It is the file containing Yolov3 model cgf file.)
     * @return void.
     */
    void setYoloConfigurationFile(const std::string& yoloConfigurationFile);

    /**
     * @brief It returns the yoloWeights value.
     * @param None
     * @return std::string.
     */
    std::string getWeights();

    /**
     * @brief It sets the yoloWeights value.
     * @param yoloWeights (File path to yolov3 weights.)
     * @return void.
     */
    void setYoloWeights(const std::string& yoloWeights);

    /**
     * @brief Destructor for YoloConfig Class
     */
     ~YoloConfig();
};
