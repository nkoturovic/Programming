#include "mythread.h"
#include <QTime>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
    static unsigned counter = 0;
    threadIndex = counter++;
}

void MyThread::run()
{
   qsrand(static_cast<unsigned>(QTime(0,0).secsTo(QTime::currentTime())));
   // Nit spava 1,2,3,4 ili 5 sekundi
sleepingFor = rand() % 5 + 1;
   this->sleep(sleepingFor);
   emit(sleepFinished(sleepingFor));
}
