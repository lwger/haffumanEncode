#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myhuffman.h"
#include <QLineEdit>
#include <QPalette>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <iostream>
//using namespace std;
//#include <QBrush>
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    flag =0;
    ui->setupUi(this);
    this->setWindowTitle("compress software");
    this->setWindowIcon(QIcon(":/new/images/icon.png"));
    this->setMaximumSize(500,500);
    this->setMinimumSize(500,500);
    QPalette pale;
    pale.setBrush(QPalette::Background, QBrush(QPixmap(":/new/images/background.png").scaled(this->size())));
    this->setPalette(pale);
    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(110,160,300,40);
    lineEdit->setHidden(true);
//    connect(lineEdit, SIGNAL(returnPressed()), this,SLOT(onInLineEditPress()));
    connect(lineEdit, SIGNAL(returnPressed()), this,SLOT(onOutLineEditPress()));
//    connect(this, SIGNAL(inFnameComfirmed()), this, SLOT(onInFnameComfirmed()));
    connect(this, SIGNAL(outFnameComfirmed()), this, SLOT(onOutFnameComfirmed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()    //compress
{
    flag = 1;
    QFileDialog* fileDialog = new QFileDialog;
    fileDialog->setDirectory("c:");
    fileDialog->setWindowTitle("选择你要压缩的文件");
    fileDialog->setWindowIcon(QIcon(":/new/images/icon.png"));
    QString path;
    if(fileDialog->exec() == QFileDialog::Accepted)
    {
        path = fileDialog->selectedFiles()[0];
    }
    QByteArray tmp = path.toLatin1();  // must
    inFname = tmp.data();
//    qDebug()<<inFname;
    qDebug()<<"huff1";
    huff(1, inFname,nullptr, nullptr);
    QMessageBox::information(this,"tip","compression succeed!",QMessageBox::Yes);
  //  this->lineEdit->clear();
  //  this->lineEdit->setHidden(false);
  //  this->lineEdit->setPlaceholderText("请输入你要压缩的文件名");
   // this->lineEdit->setFocus();
}

void MainWindow::on_pushButton_2_clicked()   //decompress
{
    flag = 2;
    QFileDialog* fileDialog = new QFileDialog;
    fileDialog->setDirectory("c:");
    fileDialog->setWindowTitle("选择你要解压的文件");
    fileDialog->setWindowIcon(QIcon(":/new/images/icon.png"));
    if(fileDialog->exec() == QFileDialog::Accepted)
    {
        path = fileDialog->selectedFiles()[0];
        qDebug()<<"path";
        qDebug()<<path;
        this->lineEdit->clear();
        this->lineEdit->setHidden(false);
        this->lineEdit->setPlaceholderText("请输入解压后的文件名");
//        this->setWindowTitle("compress  software");
        this->lineEdit->setFocus();
        qDebug()<<"dddd";
    }
    tmp = path.toLatin1();  // must
    deFname = tmp.data();
    qDebug()<<"deFname111";
    qDebug()<<deFname;
    this->lineEdit->setFocus();

//    this->lineEdit->setFocusProxy(this);

}

void MainWindow::on_pushButton_3_clicked()   //leave
{
    this->close();
    QApplication *app;
    app->quit();
}

/*
int MainWindow::onInLineEditPress()
{
    if(flag == 2) { flag = 0; return 0; }
    QString str = lineEdit->text();
    QByteArray tmp = str.toLatin1(); // must
    inFname = tmp.data();
    emit inFnameComfirmed();
    return 1;
}
*/
int MainWindow::onOutLineEditPress()
{
//    if(flag ==1)   { flag = 0; return 0; }
    QString str = lineEdit->text();
    QByteArray tmp = str.toLatin1(); // must
    outFname = tmp.data();
    lineEdit->setHidden(true);
    emit outFnameComfirmed();
    return 1;
}
/*
void MainWindow::onInFnameComfirmed()
{
//    qDebug()<<inFname;
    //huff(1, inFname,nullptr);
    this->lineEdit->setHidden(true);
    QMessageBox::information(this,"tip","compression succeed!",QMessageBox::Yes);
}
*/
void MainWindow::onOutFnameComfirmed()
{
    qDebug()<<"f7";
    qDebug()<<deFname;
    qDebug()<<outFname;
    qDebug()<<"huff2";
    huff(2, nullptr, deFname, outFname);
    QMessageBox::information(this,"tip","decompression succeed!",QMessageBox::Yes);
    this->lineEdit->setHidden(true);
}
