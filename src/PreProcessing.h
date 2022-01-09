#pragma once
#include "pch.h"

constexpr const char *CASCADE_FILE_PATH = "/home/orel/Dev/Cpp/lpds/src/cascades/cascade.xml";
constexpr const double CASCADE_SCALE_FACTOR = 1.1;
constexpr const int CASCADE_MIN_NEIGHBORS = 3;
constexpr const int CASCADE_FLAGS = 0;

// ?
const cv::Size CASCADE_MIN_DETECTION_SIZE(53, 13);

// img resize factor set to 500 pixles wide
constexpr const int RESIZE_FACTOR = 500;

void cascadeInit();

cv::Mat preProcessing(const cv::Mat &_frame);
cv::Mat cascadeDetect(const cv::Mat &_frame);
cv::Rect operator*(cv::Rect &r, double ratio);
