#include "mytask.h"
#include <QThread>
#include <QTime>

MyTask::MyTask(QObject *parent) : QObject(parent)
{
    static unsigned counter = 0;
    workerIndex = counter++; 
}

void MyTask::doSleep()
{
    qsrand(static_cast<unsigned>(QTime(0,0).secsTo(QTime::currentTime())));
    // Thread sleeps for 1,2,3,4 or 5 sec
    unsigned sleepingFor = rand() % 5 + 1;
    emit(startedSleep(sleepingFor));
    QThread::sleep(sleepingFor);
    emit(doneSleep());
}
