#include "mainwindow.h"
#include "generator.h"
#include "dataconverter.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("MonetGAN");
    resize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    imageDisplay1 = new QLabel();
    imageDisplay2 = new QLabel();
    mainLayout->addWidget(imageDisplay1);
    mainLayout->addWidget(imageDisplay2);
    imageDisplay1->setAlignment(Qt::AlignCenter);
    imageDisplay2->setAlignment(Qt::AlignCenter);

    processBtn = new QPushButton("读取并处理图像");
    connect(processBtn, &QPushButton::clicked, this, &MainWindow::onReadAndProcess);
    mainLayout->addWidget(processBtn);

    saveBtn = new QPushButton("保存处理后图像");
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::onSaveImage);
    mainLayout->addWidget(saveBtn);

    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow() = default;

void MainWindow::onReadAndProcess() {
    QString filePath = QFileDialog::getOpenFileName(this, "选择图像", "", "Images (*.png *.jpg *.jpeg)");
    if (filePath.isEmpty()) return;

    originalMat = cv::imread(filePath.toStdString());
    if (originalMat.empty()) {
        QMessageBox::warning(this, "错误", "图像读取失败");
        return;
    }
    cv:cvtColor(originalMat, originalMat, cv::COLOR_BGR2RGB);
    QImage input = MatToQImage(originalMat);
    imageDisplay1->setPixmap(QPixmap::fromImage(input));

    processedMat = Generate(originalMat);
    QImage output = MatToQImage(processedMat);
    imageDisplay2->setPixmap(QPixmap::fromImage(output));
}

void MainWindow::onSaveImage() {
    if (processedMat.empty()) {
        QMessageBox::warning(this, "错误", "无处理后图像可保存");
        return;
    }

    cv::cvtColor(processedMat, processedMat, cv::COLOR_RGB2BGR);

    QString savePath = QFileDialog::getSaveFileName(this, "保存图像", "", "Images (*.png *.jpg)");
    if (!savePath.isEmpty()) {
        cv::imwrite(savePath.toStdString(), processedMat); // 直接用 OpenCV 保存
        QMessageBox::information(this, "提示", "图像保存成功");
    }
}