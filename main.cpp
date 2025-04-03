#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication App(argc, argv);
    MainWindow Monet;
    Monet.show();
    return App.exec();
}