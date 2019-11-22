#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    cv::VideoCapture cam(cv::CAP_ANY);
    cam.open(cv::CAP_ANY); //Pass camera index through command line

    cv::Mat src;

    cv::namedWindow("hsv", WINDOW_AUTOSIZE);

    int hVal, sVal, vVal;

    cv::createTrackbar("hVal [+/- 30]", "hsv", &hVal, 30);
    cv::createTrackbar("sVal [0, sVal]", "hsv", &sVal, 255);
    cv::createTrackbar("vVal [0, vVal]", "hsv", &vVal, 255);

    while(true)
    {
        cv::Mat hsv, out;

        if(cam.grab())
        {
            cam.retrieve(src);
        }

        cv::cvtColor(src, hsv, COLOR_BGR2HSV);
        cv::inRange(hsv, cv::Scalar(30 - hVal, 0, 0), cv::Scalar(30 + hVal, sVal, vVal), out);

        imshow("hsv", out);

        if(cv::waitKey(1) == 32){
            break;
        }
    }
}