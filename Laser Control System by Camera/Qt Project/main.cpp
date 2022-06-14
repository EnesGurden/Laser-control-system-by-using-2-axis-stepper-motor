#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <QSerialPort>
#include <QStringList>
#include <QTransform>
#include <string>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
