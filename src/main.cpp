#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("M2 Engine");
    w.show();

    return a.exec();
}
