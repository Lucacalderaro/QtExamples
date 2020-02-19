#ifndef CHECKSIGNAL_H
#define CHECKSIGNAL_H

#include <QObject>
#include <QDebug>

class CheckSignal : public QObject
{
    Q_OBJECT
public:
    explicit CheckSignal(QObject *parent = nullptr);

signals:
    void signalDetected(void);

public slots:
    void newData(void);
};

#endif // CHECKSIGNAL_H
