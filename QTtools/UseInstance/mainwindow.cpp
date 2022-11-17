#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "classa.h"
#include "classb.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//不可以通过构造函数获取
//    pa=new classA();
//    pb=new classB();
    classA::getInstance().echo();
    classB::getInstance().echo();
    qDebug()<<&classA::getInstance();
    qDebug()<<&classB::getInstance();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"Class A"<<&classA::getInstance();
    qDebug()<<"Class B"<<&classB::getInstance();
}

