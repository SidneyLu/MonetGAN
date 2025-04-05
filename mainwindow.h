#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <opencv2/opencv.hpp>
#include "imageviewer.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
    void onReadAndProcess();
    void onSaveImage();

private:
    ImageViewer *imageDisplay1;
    ImageViewer *imageDisplay2;
    QPushButton *processBtn;
    QPushButton *saveBtn;
    cv::Mat originalMat;
    cv::Mat processedMat;
};

#endif // MAINWINDOW_H