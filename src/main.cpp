#include "pch.h"

// temp
#define LOG(x) std::cout << x << std::endl;
int main()
{
    // temp
    const std::string path = "/home/orel/Dev/Cpp/lpds/src/testing_assets/20210701_150417.mp4";

    ocrInit();
    cascadeInit();

    cv::VideoCapture cap(path);
    cv::Mat frame, preProcessed;
    std::string text;
    std::optional<cv::Mat> cascadeRes;
    while (true)
    {
        {
            Timer t;
            cap >> frame;
            if (frame.empty())
                break;
            cv::Mat cascadeRes = cascadeDetect(frame);
            if (!cascadeRes.empty())
            {
                {
                    cv::imshow("cascade", cascadeRes);
                    getTextFromImage(cascadeRes);
                }
            }

            cv::imshow("main", frame);
        }
        cv::waitKey(15);
    }

    ocrCleanUp();
}