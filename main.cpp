#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(560,630);
    w.setWindowTitle("CHESS GAME");
    w.show();

    return a.exec();
}
