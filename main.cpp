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
            dst.at<Vec3b>(i,k)[2] = round((float)(cdfR[img.at<Vec3b>(i,k)[2]]-cdfR[minIntensR])/(float)((img.rows*img.cols)-cdfR[minIntensR])*255);
        }
    }

    cvNamedWindow("Origin(RGB)",1);
    cvNamedWindow("Result(RGB)",1);
    imshow("Origin(RGB)", img);
    imshow("Result(RGB)", dst);
}

