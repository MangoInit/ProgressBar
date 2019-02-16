#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Main Thread ID: " << QThread::currentThreadId();

    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(startThread()));
    connect(&m_workerThread,SIGNAL(resultReady(int)), this,SLOT(handleResults(int)));

    FindFile *findfile = new FindFile;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleResults(int value)
{
//    qDebug() << "Handle Thread: " << QThread::currentThreadId();
    ui->progressBar->setValue(value);
}

//void MainWindow::startThread()
//{
//    WorkerThread *workerThread = new WorkerThread(this);
//    connect(workerThread,SIGNAL(resultReady(int)), this, SLOT(handleResults(int)), Qt::BlockingQueuedConnection);
//    connect(workerThread,SIGNAL(finished()), workerThread,SLOT(deleteLater()));
//    workerThread->start();
//}

void MainWindow::startThread()
{
    if(!m_workerThread.isRunning())
    {
        m_workerThread.start();
    }
}
