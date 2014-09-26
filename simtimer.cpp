#include "/home/vu2aeo/QT Projects/Classes/simtimer.h"

SimTimer::SimTimer()
{
    counterValue=0;
    timer1 = new QTimer;
    connect(timer1,SIGNAL(timeout()), this , SLOT(TimerTicked()));

}

void SimTimer::TimerTicked()
{
    counterValue++;
    //qDebug() << "Tick Tock"<< counterValue;
}

double SimTimer::GetCounterValue()
{
    return counterValue;
}

void SimTimer::StartTimer(int speed)
{
    timer1->start(speed);
}

void SimTimer::ResetCounterValue()
{
    counterValue = 0;
}
