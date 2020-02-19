#ifndef PERIODANALYSIS_H
#define PERIODANALYSIS_H

#include <QDebug>

#include <QObject>


class PeriodAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit PeriodAnalysis(QObject *parent = nullptr);

signals:


public slots:
    void analysePeriod(void);
};

#endif // PERIODANALYSIS_H
