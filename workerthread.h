#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H
#include <QThread>
#include <QDebug>


class WorkerThread: public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent = 0);
    ~WorkerThread();

protected:
    virtual void run();

signals:
    void resultReady(int value);

};

#endif // WORKERTHREAD_H
