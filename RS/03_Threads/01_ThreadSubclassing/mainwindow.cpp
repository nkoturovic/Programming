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
   /* Reading number of threads from ui */
   unsigned numOfThreads = ui->lineEdit->text().toUInt();
   ui->textEdit->setText("Starting threads ...");

   for (unsigned i=0; i < numOfThreads; i++) {
       MyThread * thread = new MyThread();

       /* Connection for automatic thread deletion */
       connect(thread, &MyThread::finished, thread, &MyThread::deleteLater);

       /* Connection for printing when sleep is done to ui */
       connect(thread,
               &MyThread::sleepFinished,
               this,
               [ui = this->ui, index = thread->threadIndex](unsigned sleepTime) {
                   ui->textEdit->append(
                       "Thread " +
                       QString::number(index) +
                       " slept for " +
                       QString::number(sleepTime) +
                       " seconds."
                   );
               }
       );

       /* Connection for writing thread finished message to ui */
       connect(thread, &MyThread::finished, this, [ui = this->ui, thread]() {
           ui->textEdit->append("Thread " + QString::number(thread->threadIndex) + " finished.");
       });

       thread->start();
       ui->textEdit->append("Thread " + QString::number(thread->threadIndex) + " started.");
   }
}
