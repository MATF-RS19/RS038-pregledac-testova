#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include "image_processing.hpp"

//funkcija za proveru gresaka
void check_error(int expr, std::string & msg){
    if(!(expr)){
        std::cerr << msg << std::endl;
        exit(EXIT_FAILURE);
    }
}
std::string usage("./pregledac img1");

int main(int argc, char* argv[]){

    check_error(argc == 2, usage);

    //ucitavanje slike i kreiranje prozora
    cv::Mat img = cv::imread(argv[1], 0);
    cv::namedWindow("image", CV_WINDOW_NORMAL);


    //prikaz i resize prozora
    cv::resizeWindow("image", 600,600);
    cv::imshow("image", img);
    
    //binarizacija
    cv::Mat img_b = binarizacija(img);
    cv::namedWindow("image_b", CV_WINDOW_NORMAL);
    cv::resizeWindow("image_b", 600,600);
    cv::imshow("image_b", img_b);

    cv::waitKey();



    return 0;
}
