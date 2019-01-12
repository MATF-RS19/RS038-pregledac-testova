#ifndef HANDLER_H
#define HANDLER_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>

std::vector<std::string> get_answers_from_file(std::ifstream & in_file);
std::vector<bool> compare_result(const std::vector<std::string> & user_input,const std::vector<std::string> & answers);
std::vector<bool> process_result(std::string input_img_path);

#endif