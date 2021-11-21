#include <stdlib.h>
#include <stdio.h>

#include <tesseract/publictypes.h>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

//g++ main.cpp -ltesseract  -llept

using namespace cv;
using namespace std;

void pre_processing(Mat* original){
    cvtColor(*original, *original, COLOR_BGR2GRAY);
    medianBlur(*original, *original, 15);
    Canny(*original, *original, 100, 200);
}

int main(int argc, char** argv) {
    tesseract::TessBaseAPI *tesseract_o = new tesseract::TessBaseAPI();

    if (tesseract_o->Init(NULL, "rus", tesseract::OEM_LSTM_ONLY) < 0) {
        return EXIT_FAILURE;
    }

    tesseract_o->SetVariable("tessedit_char_whitelist","мдулирботtonm");
    //https://digi.bib.uni-mannheim.de/tesseract/doc/old/a00014.html#aec47a81606272a1a7b914d862feae98cadf7d71a201bf1549dccfc7a594dfbf84
    tesseract_o->SetPageSegMode(tesseract::PSM_SPARSE_TEXT);

    VideoCapture cap(0); //capture the video from webcam


    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }

    //Capture a temporary image from the camera
    Mat imgTmp;

    bool bSuccess = cap.read(imgTmp);

    if (!bSuccess) {
        return EXIT_FAILURE;
    }

    while(true){

        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video

         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

        //pre_processing(&imgOriginal);

        int width = imgOriginal.size().width;
        int height = imgOriginal.size().height;

        tesseract_o->SetImage(imgOriginal.data, imgOriginal.cols, imgOriginal.rows, 3, imgOriginal.step);
        if( tesseract_o->Recognize(0)) {
            return EXIT_FAILURE;
        }

        tesseract::ResultIterator *result =  tesseract_o->GetIterator();

        //imgOriginal.copyTo(tmp);
        //cvtColor(tmp, tmp, COLOR_GRAY2RGB);

        result->Begin();
        while ( result->Next(tesseract::RIL_WORD)) {
            int left, top, right, bottom;
            result->BoundingBox(tesseract::RIL_WORD, &left, &top, &right, &bottom);

            double confidence = result->Confidence(tesseract::RIL_WORD);

            if(confidence > 50){
                Rect target = Rect(left, top, right-left, bottom-top);
                //rectangle(imgOriginal, target, Scalar(0, 255, 0));
                //circle(tmp, Point(left, top), 50, Scalar(0,255,255), 2);
                printf("%s: x0:%i x1:%i y0:%i y1:%i conf:%f \n", result->GetUTF8Text(tesseract::RIL_WORD), left, right, bottom, top, confidence);
            }
        }

        delete result;



        //imshow("Finding text...", imgOriginal); //show the original image

        if (waitKey(500) == 27) //wait for 'esc' key press for 2s. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

    tesseract_o->End();

    return EXIT_SUCCESS;
}