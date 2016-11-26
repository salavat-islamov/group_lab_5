
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
#include <math.h>
using namespace std;
using namespace cv;
void grayscalesHistogramm(Mat img); // функция для черно-белых изобр.
void rgbHistogramm(Mat img);  // функция для цветных изобр.
int main (){
    Mat img = cvLoadImage("/home/../images/neymar1.jpeg");
    rgbHistogramm(img);  // вызываем дляя цветного изобр.
    grayscalesHistogramm(img);// вызываем для черно-белого изоб
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

    for (int i = 0; i < img.rows; i++){        //Находим количества интенсивностей
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

    int sumR = 0;
    int sumG = 0;
    int sumB = 0;

    for (int i = minIntensR; i < 255; i++){  // вычисление CDF для каждой интенсивности красного цвета
        if (i == minIntensR){
            cdfR[i] = countR[minIntensR];
            sumR+=cdfR[i];
        }else if(countR[i] != 0) {
            sumR += countR[i];
            cdfR[i] = sumR;
        }
    }

    for (int i = minIntensG; i < 255; i++){ // вычисление CDF для каждой интенсивности зеленого цвета
        if (i == minIntensG){
            cdfG[i] = countG[minIntensG];
            sumG+=cdfG[i];
        }else if(countG[i] != 0) {
            sumG += countG[i];
            cdfG[i] = sumG;
        }

    }

    for (int i = minIntensB; i < 255; i++){   // вычисление CDF для каждой интенсивности зеленого цвета
        if (i == minIntensB){
            cdfB[i] = countB[minIntensB];
            sumB+=cdfB[i];
        }else if(countB[i] != 0) {
            sumB += countB[i];
            cdfB[i] = sumB;
        }

    }

    for (int i = 0; i < img.rows; i++){
        for (int k = 0; k < img.cols; k++){
            // функция  round((cdf(v)-cdfmin)/((N*M)-cdfmin)*(L-1))
            dst.at<Vec3b>(i,k)[0] = round((float)(cdfB[img.at<Vec3b>(i,k)[0]]-cdfB[minIntensB])/(float)((img.rows*img.cols)-cdfB[minIntensB])*255);
            dst.at<Vec3b>(i,k)[1] = round((float)(cdfG[img.at<Vec3b>(i,k)[1]]-cdfG[minIntensG])/(float)((img.rows*img.cols)-cdfG[minIntensG])*255);
            dst.at<Vec3b>(i,k)[0] = round((float)(cdfR[img.at<Vec3b>(i,k)[0]]-cdfR[minIntensR])/(float)((img.rows*img.cols)-cdfR[minIntensR])*255);
        }
    }

    cvNamedWindow("Origin(RGB)",1);
    cvNamedWindow("Result(RGB)",1);
    imshow("Origin(RGB)", img);
    imshow("Result(RGB)", dst);
}


void grayscalesHistogramm(Mat img) {

    cvtColor(img, img, COLOR_BGR2GRAY );
    Mat dst = img.clone();
    int cdf [255];
    int count[255];

    for (int k = 0; k < 255; k++){
        count[k] = 0;
    }

    int cdfMin ;
    int minIntens;

    for (int i = 0; i < img.rows; i++){
        for (int k = 0; k < img.rows; k++){
            count[img.at<uchar>(i,k)]+=1;

        }
    }

    int temp = 0;
    for (int k = 0; k < 255; k++){
        if (count[k] != 0) {
            minIntens = k;
            cdfMin = count[k];
            break;
        }
    }

    int sum = 0;

    for (int i = minIntens; i < 255; i++){
        if (i == minIntens){
            cdf[i] = count[minIntens];
            sum+=cdf[i];
        }else if(count[i] != 0) {
            sum += count[i];
            cdf[i] = sum;
        }

    }

    for (int i = 0; i < img.rows; i++){
        for (int k = 0; k < img.cols; k++){
            // функция (cdf(v)-cdfmin)/((N*M)-cdfmin)*(L-1)
            dst.at<uchar>(i,k) = round((float)(cdf[img.at<uchar>(i,k)]-cdf[minIntens])/(float)((img.rows*img.cols)-cdf[minIntens])*255);
        }
    }

    cvNamedWindow("Origin(Grayscale)",1);
    cvNamedWindow("Result(Grayscale)",1);

    imshow("Origin(Grayscale)", img);
    imshow("Result(Grayscale)", dst);

}

