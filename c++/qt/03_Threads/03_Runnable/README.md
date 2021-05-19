## QThreadPool & Runnable

```c++
class HelloWorldTask : public QRunnable
{
    void run() override
    {
        qDebug() << "Hello world from thread" << QThread::currentThread();
    }
};

HelloWorldTask *hello = new HelloWorldTask();
// QThreadPool takes ownership and deletes 'hello' automatically
QThreadPool::globalInstance()->start(hello);
```
