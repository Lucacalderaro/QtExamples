#include "checksignal.h"

CheckSignal::CheckSignal(QObject *parent) : QObject(parent)
{

}

void CheckSignal::newData()
{
    qDebug() << "new data";
    emit signalDetected();
}
