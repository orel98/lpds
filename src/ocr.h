#pragma once
#include "pch.h"

typedef tesseract::TessBaseAPI tessApi;

void ocrInit();
void ocrCleanUp();
void getTextFromImage(const cv::Mat &frame);

constexpr int BYTES_PER_PIXLE = 1;
constexpr const char *USER_DEFINED_DPI = "user_defined_dpi";
constexpr const char *DPI_VALUE = "300";
constexpr const char *TESSEDIT_CHAR_WHITELIST = "tessedit_char_whitelist";
constexpr const char *CHARS_WHITE_LIST = "0123456789";
