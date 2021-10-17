set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    testSensorIO.cpp
    testYoloConfig.cpp
    testFrameTransformation.cpp
    testHumanDetection.cpp
    ../include/SensorIO.hpp ../include/YoloConfig.hpp ../include/FrameTransformation.hpp ../include/HumanDetection.hpp)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})
