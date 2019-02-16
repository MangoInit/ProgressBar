#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <workerthread.h>
#include <findfile.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleResults(int value);
    void startThread();

private:
    Ui::MainWindow *ui;

    WorkerThread m_workerThread;
};

#endif // MAINWINDOW_H
