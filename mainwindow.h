//
// Created by 31515 on 25-4-3.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#undef slots
#include <QMainWindow>
#include <QString>
#include <QImage>
#include <QPushButton>
#include "dataconverter.h"
#include "generator.h"
#define slots Q_SLOTS

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    QString m_filename;
    QImage m_image;

private slots:
    void on_Open_triggered();
    void on_Generate_triggered();
    void on_Save_triggered();
};


#endif //MAINWINDOW_H
