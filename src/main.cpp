#include "pch.h"

#include "ocr.h"
#include "PreProcessing.h"
#include "Timer.h"

#define LOG(x) std::cout << x << '\n';
int main()
{
    // temp
    const std::string path = "res/testing_assets/58086402.mp4";

    ocrInit();
    cascadeInit();

    cv::VideoCapture cap(path);
    cv::Mat frame, preProcessed;
    const char *text;
    std::optional<cv::Mat> cascadeRes;
    while (true)
    {
        cap >> frame;
        if (frame.empty())
            break;

        Timer t;
        cv::Mat cascadeRes = cascadeDetect(frame);
        if (!cascadeRes.empty())
        {
            {
                cv::imshow("cascade", cascadeRes);
                text = getTextFromImage(cascadeRes);
                LOG(text);
            }
        }

        cv::imshow("main", frame);

        if (cv::waitKey(1) == 27) // esc
            break;
    }

    ocrCleanUp();
}
