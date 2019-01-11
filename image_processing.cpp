#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "image_processing.hpp"

cv::Mat binarizacija(cv::Mat &img){
    
    cv::GaussianBlur(img, img, cv::Size(5,5),0);
    adaptiveThreshold(img, img,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10);
    cv::bitwise_not(img, img);
    return img;  
}