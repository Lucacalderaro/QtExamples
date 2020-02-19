#include "periodanalysis.h"

PeriodAnalysis::PeriodAnalysis(QObject *parent) : QObject(parent)
{

}

void PeriodAnalysis::analysePeriod()
{
    qDebug() << "period";
}
