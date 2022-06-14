#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <QSerialPort>
#include <QStringList>
#include <QTransform>
#include <string>
#include "ui_mainwindow.h"
#include <QtMath>
QString serialportName="COM4";
int serialportBaudrate = 9600;
QSerialPort serialPort;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    int setpoint=(100000*(setx))+(100*(motor_y));
    double s1=36001;
    qint64 s2=(100000*(s1))+(100*(35.2644));
    //qDebug()<<s2;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString x =ui->lineEdit->text();
    QString y =ui->lineEdit2->text();
    QString z =ui->lineEdit3->text();
    double x_point=x.toDouble();
    double y_point=y.toDouble();
    double z_point=z.toDouble();
    double motor_x;
    double motor_y;
    if(x_point>=0){
        motor_x=qRadiansToDegrees(qAtan(y_point/x_point));
     //   qDebug()<<motor_x;
    }else{
        motor_x=qRadiansToDegrees(qAtan(y_point/x_point))+180;
     //   qDebug()<<motor_x;
    }
    motor_y=qRadiansToDegrees(qAtan(z_point/(qSqrt(qPow(x_point,2)+qPow(y_point,2)))));

    serialPort.setPortName(serialportName);
    serialportBaudrate=QSerialPort::Baud9600;
    serialPort.setBaudRate(serialportBaudrate);
    serialPort.open(QIODevice::ReadWrite);
    if(x_point==0 && y_point==0){
        motor_x=0;
        qDebug()<<"motor_x: "<<motor_x;
    }
    if(x_point==0 && y_point==0 && z_point==0){
        motor_y=0;
        qDebug()<<"motor_x: "<<motor_x<<"    motor_y: "<<motor_y;
    }
    if(z_point<0){
        motor_y=0;
    }
    if(y_point<0 && x_point>0){
        motor_y=-motor_y;
        qDebug()<<"motor_y değişti: "<<motor_y;
    }
    qDebug()<<"x"<<motor_x;
    qDebug()<<"y"<<motor_y;

    qint64 setx=(motor_x)*100;
    qint64 setpoint=(100000*(setx))+(100*(motor_y));
    qDebug()<<"setpoint: "<<setpoint;
//    int setpoint=1000*motor_x+motor_y;
    QString buf=QString("%1\n").number(setpoint);
    serialPort.write(buf.toStdString().c_str(),buf.size());
    if(serialPort.waitForReadyRead(3000))
    {
         QByteArray data = serialPort.readAll();
         qDebug() << data;
    }
}
