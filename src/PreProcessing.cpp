#include "PreProcessing.h"

static cv::CascadeClassifier cascade;

void cascadeInit()
{
    cv::FileStorage fs;
    fs.open(CASCADE_FILE_PATH, cv::FileStorage::FORMAT_XML);
    cascade.read(fs.getFirstTopLevelNode());
    return;
}

cv::Mat preProcessing(const cv::Mat &_frame)
{

    const auto [width, height] = _frame.size();

    cv::Size frame_desired_size;
    /*
        500
        *********     * * * 5
        *       * OR  *   * 0
        *********     *   * 0
                      * * *
    */
    if (width > height)
    {
        frame_desired_size = cv::Size(RESIZE_FACTOR, height / (width / (double)RESIZE_FACTOR));
    }
    else
    {
        frame_desired_size = cv::Size(width / (height / (double)RESIZE_FACTOR), RESIZE_FACTOR);
    }

    cv::Mat gray;
    cv::resize(_frame, gray, frame_desired_size, cv::INTER_AREA);
    cv::cvtColor(gray, gray, cv::COLOR_BGR2GRAY);

    return gray;
}

cv::Mat cascadeDetect(const cv::Mat &o_frame)
{

    cv::Mat m;
    cv::Mat gray = preProcessing(o_frame);
    std::vector<cv::Rect> detections;

    cascade.detectMultiScale(gray, detections, CASCADE_SCALE_FACTOR, CASCADE_MIN_NEIGHBORS, CASCADE_FLAGS, CASCADE_MIN_DETECTION_SIZE);
    if (detections.empty())
        return m;
    /*
        ********************
        *                  *
        *                  *
        ********************
      x₀, y₀

    */

    const auto [width, height] = o_frame.size();

    const cv::Rect frameArea(0, 0, width, height);

    const cv::Rect roi = detections[0];

    /*
        roi (detection):    frame area:

            &&&&               ****************
            &  &               *              *
            &&&&               *              *
                               ****************

        roi&frameArea true if roi is inside the frame:

            ****************            ****************
            *   &&&&       *  = TRUE    *              *  = FALSE
            *   &  &       *            &&&&           *
            ****&&&&********            &**&************
                                        &&&&
        roi ⊆ frame
    */

    if ((roi & frameArea) == roi)
    {
        const auto [o_width, o_height] = o_frame.size();
        double ratio = (double)(o_width) / gray.size().width;
        cv::Mat crop = o_frame(detections[0] * ratio);

        // crop: detection from the original frame
        const auto [width, height] = crop.size();
        cv::Size cropDesiredSize(500, height / (width / 500.0));

        cv::resize(crop, crop, cropDesiredSize, cv::INTER_CUBIC);
        cv::cvtColor(crop, crop, cv::COLOR_BGR2GRAY);
        // cv::cvtColor(crop, crop, cv::COLOR_GRAY2RGBA);
        cv::GaussianBlur(crop, crop, cv::Size(3, 3), 3.0);
        cv::threshold(crop, crop, 100, 255, cv::THRESH_OTSU);

        return crop;
    };
    return m;
}

cv::Rect operator*(cv::Rect &r, double ratio)
{
    r.height *= ratio;
    r.width *= ratio;
    r.x *= ratio;
    r.y *= ratio;
    return r;
}