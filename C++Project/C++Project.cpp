// C++Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>

using namespace cv;
using namespace std;

int main() {
    Mat myImage;
    namedWindow("Video Player");
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cout << "No video stream detected" << endl;
        system("pause");
        return-1;
    }
    while (true) {
        cap >> myImage;
        if (myImage.empty()) {
            break;
        }
        imshow("Video Player", myImage);
        char c = (char)waitKey(25);
        cv::flip(1,myImage,1);
        if (c == 27) {
            break;
        }
    }
    cap.release();
    return 0;
}
