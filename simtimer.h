#ifndef SIMTIMER_H
#define SIMTIMER_H

#include <QtCore>
#include <QDebug>

class SimTimer : public QObject
{
    Q_OBJECT

private:
    double counterValue;

public:
    SimTimer();
    QTimer *timer1;
    double GetCounterValue();
    void ResetCounterValue();
    void StartTimer(int speed);


public slots:
    void TimerTicked();
};

#endif // SIMTIMER_H
