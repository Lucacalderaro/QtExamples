#include "threadsmanagement.h"

ThreadsManagement::ThreadsManagement(QObject *parent) : QObject(parent)
{
    thread1 = new QThread(this); // Create an instance of Qthread with its own event loop
    checkSignal = new CheckSignal;
    checkSignal->moveToThread(thread1);  // All the methods of checkSignal will be processed by the thread controlled by thread1
    connect(thread1, &QThread::finished, checkSignal, &QObject::deleteLater);  // When thread1 exit from its event loop delete checkSignal

    thread2 = new QThread(this); // Create an instance of Qthread with it's own event loop
    periodAnalysis = new PeriodAnalysis;
    periodAnalysis->moveToThread(thread2);  // All the methods of periodAnalysis will be processed by the thread controlled by thread2
    connect(thread2, &QThread::finished, periodAnalysis, &QObject::deleteLater);  // When thread2 exit from its event loop delete periodAnalysis

    connect(checkSignal, &CheckSignal::signalDetected, periodAnalysis, &PeriodAnalysis::analysePeriod);  // connect signalDetected to analysePeriod
    // Since periodAnalysis have been moved to thread2 and checkSignal have been moved to thread1, the connection is automatically set to type queued:
    // When event loop of thread1 emit signalDetected, an event in the thread2's event loop is created with target analysePeriod slot.

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, checkSignal, &CheckSignal::newData);  // connect the timeout to the newData slot of checkSignal
    // Since checkSignal have been moved to thread1 which has its own event loop, the connection is of type queued.

    thread1->start();  // Start the event loop of thread1
    thread2->start();  // Start the event loop of thread2
    timer->start(10);  // Start timer with timeout period of 10 msec
}

ThreadsManagement::~ThreadsManagement()
{
    thread1->quit(); // Tell thread1 to quit from it's event loop
    thread1->wait(); // Before being destroyed, the main loop (GUI loop) has to wait the thread1 event loop to exit.
    thread2->quit(); // Tell thread2 to quit from it's event loop
    thread2->wait(); // Before being destroyed, the main loop (GUI loop) has to wait the thread1 event loop to exit.
}
