#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("无标题 -记事本");

    connect(ui->newAction,&QAction::triggered,this,&MainWindow::newActionSlot);
    connect(ui->openAction,&QAction::triggered,this,&MainWindow::openActionSlot);
    connect(ui->saveAction,&QAction::triggered,this,&MainWindow::saveActionSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newActionSlot()
{
    ui->textEdit->clear();
    this->setWindowTitle("无标题 -记事本");
}

void MainWindow::openActionSlot()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),"*.txt");
    if (fileName.isEmpty())
    {
        QMessageBox::warning(this,"警告！！！","你要选则一个文件");
    }
    else
    {
        // qDebug() << fileName;
        QFile file(fileName);
        file.open(QIODevice::ReadOnly);
        QByteArray ba = file.readAll();
        ui->textEdit->setPlainText(QString(ba));
        file.close();
    }
}

void MainWindow::saveActionSlot()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存一个文件",QCoreApplication::applicationFilePath(),"*.txt");
    if (filename.isEmpty())
    {
        QMessageBox::warning(this,"警告！！！！！！","要保存一个文件！！！");
    }
    else
    {
        QFile file(filename);
        file.open(QIODevice::WriteOnly);
        ui->textEdit->toPlainText();
        QByteArray ba;
        ba.append(ui->textEdit->toPlainText().toUtf8());
        file.write(ba);
        file.close();

    }
}
