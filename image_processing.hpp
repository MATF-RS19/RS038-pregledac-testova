#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


cv::Mat binarizacija(cv::Mat & img);
std::vector<std::string> izolovanje_pravougaonika(cv::Mat & img);
cv::Point2f izracunajPresek(cv::Vec4i a, cv::Vec4i b);
void sortirajCoskove(std::vector<cv::Point2f>& corners, cv::Point2f center);
bool comparator2(double a,double b);
bool comparator3(cv::Vec3f a,cv::Vec3f b);
bool comparator(cv::Point2f a,cv::Point2f b);

#endif
