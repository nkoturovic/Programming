#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    unsigned threadIndex = 0;
    unsigned sleepingFor = 0;

    void run() override;

signals:
    void sleepFinished(unsigned sleepSeconds);
};

#endif // MYTHREAD_H
