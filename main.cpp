#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.setStyleSheet(R"(QMainWindow {
    background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                stop:0 #DAF7EF,
                                stop:0.125 #668687,
                                stop:0.25 #467AC9,
                                stop:0.375 #A8BCA9,
                                stop:0.5 #F0C972,
                                stop:0.625 #D69F21,
                                stop:0.75 #A1CAF0,
                                stop:0.875 #76B1EA,
                                stop:1 #87CEFA);
}
)");
    window.show();
    return app.exec();
}