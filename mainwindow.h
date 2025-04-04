#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <opencv2/opencv.hpp>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    private slots:
    void onReadAndProcess();
    void onSaveImage();

private:
    QLabel *imageDisplay1;
    QLabel *imageDisplay2;
    QPushButton *processBtn;
    QPushButton *saveBtn;
    cv::Mat originalMat;
    cv::Mat processedMat;
};

#endif // MAINWINDOW_H