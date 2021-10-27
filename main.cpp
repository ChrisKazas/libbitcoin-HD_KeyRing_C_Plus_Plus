#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();

    return a.exec();
}
