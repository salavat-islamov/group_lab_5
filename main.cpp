#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <math.h>
using namespace std;
using namespace cv;
void grayscalesHistogramm(Mat img); // функция для черно-белых изобр.
void rgbHistogramm(Mat img);  // функция для цветных изобр.
void openCvMethod(char* path);
int main (){
    Mat img = cvLoadImage("/home/guka/Downloads/images/r.jpeg");
    rgbHistogramm(img);  // вызываем дляя цветного изобр.
    grayscalesHistogramm(img);// вызываем для черно-белого изоб
    char* path = "/home/guka/Downloads/images/r.jpeg";//путь кзображению для готовой функции
    openCvMethod(path);
    waitKey(0);
    return 0;
}
void rgbHistogramm(Mat img) {
    Mat dst = img.clone();
    int cdfR [255];
    int countR[255];
    int cdfG [255];
    int countG[255];
    int cdfB [255];
    int countB[255];

    for (int k = 0; k < 255; k++){
        countR[k] = 0;
        countG[k] = 0;
        countB[k] = 0;
    }

    int cdfMinR ;
    int cdfMinG ;
    int cdfMinB ;
    int minIntensR;
    int minIntensG;
    int minIntensB;

    for (int i = 0; i < img.rows; i++){
        for (int k = 0; k < img.rows; k++){
            countB[img.at<Vec3b>(i,k)[0]]+=1;
            countG[img.at<Vec3b>(i,k)[1]]+=1;
            countR[img.at<Vec3b>(i,k)[2]]+=1;
        }
    }

    int temp = 0;
    bool  r = false;
    bool  g = false;
    bool  b = false;

    for (int k = 0; k < 255; k++){
        if (countR[k] != 0 && !r) {
            minIntensR = k;         // находим первое значение CDF для красного цвета
            cdfMinR = countR[k];
            r = true;
            break;
        }
        if (countG[k] != 0 && !g) {
            minIntensG = k;       // находим первое значение CDF для зеленого цвета
            cdfMinG = countG[k];
            g = true;
            break;
        }
        if (countB[k] != 0 && !b) {
            minIntensB = k;        // находим первое значение CDF для синего цвета
            cdfMinR = countB[k];
            b = true;
            break;
        }
    }

    }