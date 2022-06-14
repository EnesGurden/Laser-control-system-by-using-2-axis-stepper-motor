#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QDebug>
#include <QSerialPort>
#include <QStringList>
#include <QTransform>
#include <string>
#include "ui_mainwindow.h"
QString serialportName;
int serialportBaudrate;
QSerialPort serialPort;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMouseTracking(true);
    ui->label->setText("Press any point down to send laser ");
   // qDebug()<<xx;
}

void QWidget::mousePressEvent(QMouseEvent *ev)  {
    bool leftButton=false;
    if(ev->button()==Qt::LeftButton)
    {
        leftButton=true;
    }
    QTransform t;
    t.scale(1, -1);
    t.translate(0, -height()+1);
    QPoint pos = ev->pos() * t;
    double pos_x;double pos_y;
    serialPort.setPortName(serialportName);
    if(serialportBaudrate==9600)
    {
        serialportBaudrate=QSerialPort::Baud9600;
    }
    else if(serialportBaudrate==4800)
    {
        serialportBaudrate=QSerialPort::Baud4800;
    }
    else if(serialportBaudrate==115200)
    {
        serialportBaudrate=QSerialPort::Baud115200;
    }
    serialPort.setBaudRate(serialportBaudrate);
    serialPort.open(QIODevice::ReadWrite);
    if(pos.x()>9 && pos.x()<QWidget::frameGeometry().width()-12 &&
       pos.y()>9 && pos.y()<QWidget::frameGeometry().height()-66 &&
       leftButton)
    {
        pos_x=pos.x()-9;
        pos_y=pos.y()-9;
        double xx=(double)(QWidget::frameGeometry().width()-22)/7;
        double yy=(double)(QWidget::frameGeometry().height()-76)/5;
 //       qDebug()<<"xx: "<<xx<<" yy:"<<yy;
  //      qDebug() << pos_x<<"  "<<pos_y;
        QByteArray writeData;
        int setx=(pos_x/xx)*100;

        int setpoint=(100000*(setx))+(100*(pos_y/yy));
        double motor_x=(double)(setpoint/100000)/100;
        double motor_y=(double)(setpoint%100000)/100;
        qDebug()<<motor_x<<"   "<<motor_y;
//        qDebug()<<"setpoint: "<<setpoint<<" pos_x/xx: "<<(setx)<<" pos_y/yy: "<<(pos_y/yy);
        QString buf=QString("%1\n").number(setpoint);
        serialPort.write(buf.toStdString().c_str(),buf.size());
     //   qDebug()<<"buf: "<<buf;
      //  qWarning("port seçilmedi");
        if(serialPort.waitForReadyRead(3000))
        {
             QByteArray data = serialPort.readAll();
             qDebug() << data;
        }
    }else{
            pos_x=0;
            pos_y=0;
            qDebug() << pos_x<<"  "<<pos_y;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_textActivated(const QString &arg1)
{
   serialportName = ui->comboBox->currentText();
}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
    serialportBaudrate=ui->comboBox_2->currentText().toInt();
}
void QErrorMessage::showMessage(const QString &message, const QString &type)
{

}
