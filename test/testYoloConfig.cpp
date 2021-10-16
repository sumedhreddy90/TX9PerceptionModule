/**
 * @copyright  MIT License (c) 2021 Sumedh Koppula and Pratik Acharya
 * @file  YoloConfig.hpp
 * @brief Unit tests for YoloConfig Class. Unit tests for get() set() methods to
 * verify file paths of Yolo cgf, Yolo weights and coco dataset, i.e yoloClasses
 * @author Sumedh Koppula and Pratik Acharya
 */

#include <gtest/gtest.h>
#include <YoloConfig.hpp>
YoloConfig yoloConfig;
/**
 * @brief Test case for getYoloClasses method of YoloConfig class.
 */
TEST(YoloConfigGetterSetter, checkCocoSize) {
    yoloConfig.setYoloClassesLocation("../coco.names");
    yoloConfig.setYoloClasses();
    std::vector<std::string> classes = yoloConfig.getYoloClasses();
    EXPECT_EQ(classes.size(), 80);
}

/**
 * @brief Test case for setYoloClasses method of YoloConfig class.
 */
TEST(YoloConfigSetter, inputCheck) {
    EXPECT_NO_FATAL_FAILURE({
    yoloConfig.setYoloClasses();
    });
}
/**
 * @brief It verifies whether the setYoloClassesLocation sets the coco classes file correctly or not.
 */
TEST(YoloConfigGetterSetter, verifyCocoPath) {
    yoloConfig.setYoloClassesLocation("../coco.names");
    EXPECT_EQ(yoloConfig.getYoloClassesLocation(), "../coco.names");
}

/**
 * @brief It checks whether the setYoloConfigurationFile sets the yolo model configuration file correctly or not.
 */
TEST(YoloConfigGetterSetter, verifyConfigFile) {
    yoloConfig.setYoloConfigurationFile("../yolov3.cfg");
    EXPECT_EQ(yoloConfig.getYoloConfigurationFile(), "../yolov3.cfg");
}

/**
 * @brief It checks whether the setYoloWeightsFile sets the yoloV3 weights file correctly or not.
 */
TEST(YoloConfigGetterSetter, verifyWeightFile) {
    yoloConfig.setYoloWeightsFile("../yolov3.weights");
    EXPECT_EQ(yoloConfig.getYoloWeightsFile(), "../yolov3.weights");
}

