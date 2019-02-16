#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent): QThread(parent)
{
    qDebug() << "Woker Thread: " << QThread::currentThreadId();
}

WorkerThread::~WorkerThread()
{
    requestInterruption();
    quit();
    wait();
}

void WorkerThread::run() Q_DECL_OVERRIDE
{
    while(!isInterruptionRequested())
    {
        qDebug() << "Woker Run Thread: " << QThread::currentThreadId(); //run中内容才属于另外一个线程
        int nValue = 0;
        while(nValue < 100)
        {
            msleep(50);
            nValue+=5;

            emit resultReady(nValue);
        }
        requestInterruption();
        wait();
    }
}
