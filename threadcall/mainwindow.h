#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class QThread;
class WorkerThread: public QObject
{
    Q_OBJECT
public:
    WorkerThread();

public slots:
    void onStart();
signals:
    void sendMessage(const QString& msg, const int& code);
};

#include <QTimer>
class filereader : public QObject
{
    Q_OBJECT
private:
    QTimer * m_tmr;
public:
    filereader(QObject * poParent = Q_NULLPTR);
    void timeProc();
signals:
    void signalProgress(int);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    void test();
private:
    void onGetMessage(const QString &msg, const int& code);
    Ui::MainWindow *ui;
    QThread *thread = nullptr;
    WorkerThread *wt = nullptr;
};

#endif // MAINWINDOW_H
