#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>

class MyTask : public QObject
{
    Q_OBJECT
public:
    explicit MyTask(QObject *parent = nullptr);

    unsigned workerIndex = 0;

public slots:
    void doSleep();

signals:
    void startedSleep(unsigned numOfSeconds);
    void doneSleep();

};

#endif // MYWORKER_H
