#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

/**
 * @brief An interface with the end goals of image processing
 * @class An abstract class wrapper of the three final goal methods of image processing
 *  for this year - finding the x,y,z of a pole, the x,y,z of the module, and multiple
 *  x,y,z's of incoming obstacles
 */
using namespace cv;
namespace DroneVision
{
    class IDroneVision
{
    public:
        virtual cv::Point detectPylon(cv::Mat src) = 0;
        virtual cv::Point detectModeule(cv::Mat src) = 0;
        virtual std::vector<cv::Point> detectIncomingObjects(cv::Mat src) = 0;

    };
}
#endif
