#ifndef GENERATOR_H
#define GENERATOR_H

#undef slots
#include <torch/torch.h>
#include <torch/script.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#define slots Q_SLOTS

cv::Mat Generate(const cv::Mat& input_image);

#endif //GENERATOR_H
