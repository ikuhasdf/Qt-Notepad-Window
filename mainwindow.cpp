#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("无标题 -记事本");

    connect(ui->newAction_2,&QAction::triggered,this,&MainWindow::newAction_2Slot);
    connect(ui->openAction_2,&QAction::triggered,this,&MainWindow::openAction_2Slot);
    connect(ui->saveAction_2,&QAction::triggered,this,&MainWindow::saveAction_2Slot);
    connect(ui->songti,&QAction::triggered,this,&MainWindow::songtiSlot);
    connect(ui->msys,&QAction::triggered,this,&MainWindow::msysSlot);
    connect(ui->About,&QAction::triggered,this,&MainWindow::AboutSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newAction_2Slot()
{
    QMessageBox::warning(this,"警告","新建文档会清除信息");
    ui->textEdit->clear();
    this->setWindowTitle("无标题 -记事本");
}

void MainWindow::openAction_2Slot()
{
    QString fileName = QFileDialog::getOpenFileName(this,"选择一个文件",QCoreApplication::applicationFilePath(),"*所有的文件;;*.txt");
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
        this ->setWindowTitle(QFileInfo(fileName).fileName() + " -记事本");
    }
}

void MainWindow::saveAction_2Slot()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存一个文件",QCoreApplication::applicationFilePath(),"*所有的文件;;*.txt");
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
void MainWindow::songtiSlot()
{
    QFont f("宋体",10);
    ui->textEdit->setFont(f);
}
void MainWindow::msysSlot()
{
    QFont f("微软雅黑",9);
    ui->textEdit->setFont(f);
}
void MainWindow::AboutSlot()
{
    QMessageBox::about(this,tr("关于记事本"),tr("2025-2026记事本"));
}
