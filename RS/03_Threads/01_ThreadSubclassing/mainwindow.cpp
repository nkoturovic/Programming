#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mythread.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   // Reading number of threads
   unsigned numOfThreads = ui->lineEdit->text().toUInt();
   ui->textEdit->setText("Starting threads ...");

   for (unsigned i=0; i < numOfThreads; i++) {
       MyThread * t = new MyThread();
       connect(t, &MyThread::sleepFinished, this, [=](unsigned sleepTime) {
           ui->textEdit->append(
               "Thread " +
               QString::number(t->threadIndex) +
               " slept for " +
               QString::number(sleepTime) +
               " seconds."
           );
       });
       connect(t, &MyThread::finished, this, [ui = this->ui, t]() {
           ui->textEdit->append("Thread " + QString::number(t->threadIndex) + " finished.");
           t->deleteLater();
       });

       t->start();
       ui->textEdit->append("Thread " + QString::number(t->threadIndex) + " started.");
   }
}
