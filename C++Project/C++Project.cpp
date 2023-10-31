

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
        return -1;
    }

    CascadeClassifier faceCascade;
    if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
        cout << "Error loading Haar Cascade for face detection." << endl;
        system("pause");
        return -1;
    }

    CascadeClassifier eyeCascade;
    if (!eyeCascade.load("haarcascade_eye.xml")) {
        cout << "Error loading Haar Cascade for eye detection." << endl;
        system("pause");
        return -1;
    }

    while (true) {
        cap >> myImage;
        if (myImage.empty()) {
            break;
        }

        cv::flip(myImage, myImage, 1);
        Mat gray;
        cvtColor(myImage, gray, COLOR_BGR2GRAY);

        vector<Rect> faces;
        faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, Size(30, 30));

        for (const Rect& face : faces) {
            rectangle(myImage, face, Scalar(255, 0, 255), 2);

            // Region of interest (ROI) for the detected face
            Mat faceROI = gray(face);

            vector<Rect> eyes;
            eyeCascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0, Size(20, 20));

            for (const Rect& eye : eyes) {
                Point eyeCenter(face.x + eye.x + eye.width / 2, face.y + eye.y + eye.height / 2);
                int radius = cvRound((eye.width + eye.height) * 0.25);
                circle(myImage, eyeCenter, radius, Scalar(0, 255, 0), 2);
            }
        }

        imshow("Video Player", myImage);

        char c = (char)waitKey(25);
        if (c == 27) {
            break;
        }
    }

    cap.release();
    return 0;
}
