#include "ocr.h"

static tessApi *ocr = nullptr;
void ocrInit()
{

    ocr = new tessApi();

    // ocr->Init return -1 if faild to initialize,
    if (ocr->Init(nullptr, "eng", tesseract::OEM_LSTM_ONLY))
    {
        std::cerr << "\"ocrInit faild...\"" << std::endl;
        exit(-1);
    }

    // Treat the image as a single text line
    ocr->SetPageSegMode((tesseract::PageSegMode)tesseract::PSM_SINGLE_WORD);

    // OpenCV dosen't pass metadata if the image to tesseract, tesseract will default to 70 dpi.
    // Minimum recommended dpi is 300.
    // https://tesseract-ocr.github.io/tessdoc/ImproveQuality.html#:~:text=Tesseract%20works%20best%20on%20images,be%20beneficial%20to%20resize%20images.
    ocr->SetVariable(USER_DEFINED_DPI, DPI_VALUE);

    ocr->SetVariable(TESSEDIT_CHAR_WHITELIST, CHARS_WHITE_LIST);

    std::cout << "ocr initialize." << std::endl;
    return;
}

const char *getTextFromImage(const cv::Mat &frame)
{
    ocr->SetImage(frame.data, frame.cols, frame.rows, BYTES_PER_PIXLE, BYTES_PER_PIXLE * frame.cols);
    char *text = ocr->GetUTF8Text();

    std::string textFromImage = text;
    // memory leak without this ref: tesseract/src/api/baseapi.cpp:1363
    delete[] text;
    // Clean the text from white spaces
    *std::remove(textFromImage.begin(), textFromImage.end(), ' ') = 0;
    // std::cout << textFromImage << std::endl;
    if (textFromImage.empty() | (textFromImage.size() > 9))
        return "";
    return textFromImage.c_str();
}

//
void ocrCleanUp()
{
    if (ocr)
    {
        ocr->Clear();
        ocr->End();
        delete ocr;
    }
}