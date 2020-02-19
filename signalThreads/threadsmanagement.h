#ifndef THREADSMANAGEMENT_H
#define THREADSMANAGEMENT_H

#include <QObject>
#include <QThread>
#include <QTimer>

#include <checksignal.h>
#include <periodanalysis.h>

class ThreadsManagement : public QObject
{
    Q_OBJECT
public:
    explicit ThreadsManagement(QObject *parent = nullptr);
    ~ThreadsManagement();

signals:


public slots:

private:
    QThread *thread1, *thread2;

    CheckSignal *checkSignal;
    PeriodAnalysis * periodAnalysis;

    QTimer *timer;
};

#endif // THREADSMANAGEMENT_H
