#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>

WorkerThread::WorkerThread(){}

void WorkerThread::onStart(){
    emit sendMessage("start", 100);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    wt = new WorkerThread;
    thread = new QThread;

    connect(thread, &QThread::finished, wt, &QObject::deleteLater);
    connect(ui->btStart, &QPushButton::clicked, wt, &WorkerThread::onStart);
    connect(wt, &WorkerThread::sendMessage, this, &MainWindow::onGetMessage);
    wt->moveToThread(thread);
    thread->start();

    test();

}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <iostream>
#include <QDebug>
void MainWindow::onGetMessage(const QString &msg, const int &code)
{
    //qDebug() << msg << code;
    std::cout << "message " << msg.toStdString() << "code "<< code<< std::endl; // this never being called ????
}


#include <QProgressDialog>
void MainWindow::test()
{
    filereader qfr;

    QProgressDialog progress("Importing file.", "Cancel", 0, 10);

    connect(&qfr, &filereader::signalProgress, &progress, &QProgressDialog::setValue, Qt::QueuedConnection);

    QThread worker_thread;

    int success = 10;

    connect(&worker_thread, &QThread::started,
            [&]() {
        if (success == progress.value())
            worker_thread.quit();
    });

    worker_thread.start();

    //progress.setWindowModality(Qt::WindowModal); // Works only fine when this line is commented !!

    while (worker_thread.isRunning()) {
        QApplication::processEvents();
        QThread::sleep(0);
    }

    progress.close();
}

filereader::filereader(QObject *poParent) : QObject(poParent)
{
    m_tmr = new QTimer(this);
    connect(m_tmr, &QTimer::timeout, this, &filereader::timeProc);
    m_tmr->setInterval(1000);
    m_tmr->start();
}

void filereader::timeProc()
{
    static int i=0;
    i++;
    emit signalProgress(i);
}
