#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QImage>
#include <opencv2/opencv.hpp>

cv::Mat QImageToMat(const QImage& image);
QImage MatToQImage(const cv::Mat& image);

#endif //DATACONVERTER_H
