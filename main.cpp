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

int main(int argc, char* argv[]){

    

    return 0;
}
