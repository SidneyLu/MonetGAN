#include "dataconverter.h"

//Input and output on userinterface are both QImages in RGB mode.

cv::Mat QImageToMat(const QImage& image) {
    return cv::Mat(image.height(),image.width(),CV_8UC3, const_cast<uchar*>(image.bits()),image.bytesPerLine());
}

QImage MatToQImage(const cv::Mat& image) {
    return QImage(image.data,image.cols,image.rows,image.step,QImage::Format_RGB888);
}

