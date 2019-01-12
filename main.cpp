#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <string>
#include "image_processing.hpp"
#include "handler.hpp"
#include <fstream>

//funkcija za proveru gresaka
void check_error(int expr, std::string & msg){
    if(!(expr)){
        std::cerr << msg << std::endl;
        exit(EXIT_FAILURE);
    }
}
std::string usage("./pregledac img1 input_answ_file");

int main(int argc, char* argv[]){

    check_error(argc == 3, usage);

    //ucitavanje resenja
    std::ifstream in_file(argv[2]);
    //fali obrada greske
    auto vektor_resenja = get_answers_from_file(in_file);

    //ucitavanje slike i kreiranje prozora
    cv::Mat img = cv::imread(argv[1], 0);
    
    //prikaz i resize prozora
    cv::namedWindow("image", CV_WINDOW_NORMAL);
    cv::resizeWindow("image", 600,600);
    cv::imshow("image", img);

    izolovanje_pravougaonika(img);

    cv::waitKey();

    return 0;
}
