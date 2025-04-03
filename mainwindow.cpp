//
// Created by 31515 on 25-4-3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    QPushButton *Open = new QPushButton("Open", this);
    Open->move(50,50);
    QPushButton *Generate = new QPushButton("Generate", this);
    Generate->move(50,100);
    QPushButton *Save = new QPushButton("Save", this);
    Save->move(50,150);

    connect(Open, &QPushButton::clicked, this, &MainWindow::on_Open_triggered);
    connect(Generate, &QPushButton::clicked, this, &MainWindow::on_Generate_triggered);
    connect(Save, &QPushButton::clicked, this, &MainWindow::on_Save_triggered);
}

MainWindow::~MainWindow() {
}

void MainWindow::on_Open_triggered(){
}

void MainWindow::on_Generate_triggered() {
    cv::Mat input_mat = QImageToMat(m_image);
    cv::Mat output_mat = Generate(input_mat);
    QImage output = MatToQImage(output_mat);
}

void MainWindow::on_Save_triggered() {
}