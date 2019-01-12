#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "image_processing.hpp"
#include <iostream>
#include <vector>
#include <fstream>
#include "handler.hpp"

std::vector<std::string> get_answers_from_file(std::ifstream & in_file){

    std::vector<std::string> vek;
    int pitanje;
    std::string odgovor;

    while(in_file >> pitanje){
        in_file >> odgovor;
        vek.push_back(odgovor);
    }

    return vek;
}

std::vector<bool> compare_result(const std::vector<std::string> & user_input,const std::vector<std::string> & answers){

    std::vector<bool> result(answers.size());
    for(int i = 0; i < answers.size(); i++ ){

        result[i] = user_input[i] == answers[i];
    }

    return result;   
}

std::vector<bool> process_result(std::string input_img_path){

    //ucitavanje resenja
    std::ifstream in_file("./test_input/resenje.txt");
    //fali obrada greske
    auto vektor_resenja = get_answers_from_file(in_file);

    //ucitavanje slike
    cv::Mat img = cv::imread(input_img_path, 0);

    auto vektor_korisnikovog_unosa = izolovanje_pravougaonika(img);
    auto rezultat = compare_result(vektor_korisnikovog_unosa, vektor_resenja);

    return rezultat;
}