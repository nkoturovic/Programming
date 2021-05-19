#include <QThread>
#include "mainwindow.h"
#include "mytask.h"
#include "./ui_mainwindow.h"

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
        QThread * thread = new QThread();
        MyTask * task = new MyTask();
        task->moveToThread(thread);

        /* connection for start working */
        connect(thread, &QThread::started, task, &MyTask::doSleep);

        /* connection to call quit after work done */
        connect(task, &MyTask::doneSleep, thread, &QThread::quit); 

        /* connections for automatic deletion */
        connect(thread, &QThread::finished, thread, &QThread::deleteLater);
        connect(task, &MyTask::doneSleep, task, &MyTask::deleteLater);

        /* connection to print start message to ui */
        connect(task, &MyTask::startedSleep, this,
                    [ui = this->ui, workerIndex = task->workerIndex](unsigned sleepTime) {
                ui->textEdit->append(
                    "Thread " +
                    QString::number(workerIndex) +
                    " started sleeping for " +
                    QString::number(sleepTime) +
                    " seconds."
                );
        });

        /* connection to print task finish message to ui */
        connect(task, &MyTask::doneSleep, this, [ui = this->ui, index = task->workerIndex]() {
            ui->textEdit->append("Task " + QString::number(index) + " finished sleeping.");
        });

        /* connection to print thread finish message to ui */
        connect(thread, &QThread::finished, this, [ui = this->ui, index = task->workerIndex]() {
            ui->textEdit->append("Thread with Task(id:" + QString::number(index) + ") finished.");
        });

        thread->start();
    }
}
