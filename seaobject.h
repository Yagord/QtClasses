#ifndef SEAOBJECT_H
#define SEAOBJECT_H

//#include <math.h>
#include <QVector>
#include <QPointF>

struct xyPositionRecord
{
public:
    QPointF xyPos;
    double timeStamp;

};

class seaobject
{

private:

    double simCo;

    double simSpd;

    double simCoNow;

    double simSpdNow;

    double simBrg;

    double simBrgErr;

    double simRng;

    bool wheel2Port;

    double turnRateSec;

    double spdRateSec;

    double spdTurnConst;

    double xpos;

    double ypos;

    bool SimStarted;

    double AddNoise(double, double);

    xyPositionRecord posNow;

    QVector <xyPositionRecord> *xyPositionLog;

public:

    seaobject(double setTurnRateSec, double setSpdRateSec, double setSpdTurnConst);

    ~seaobject();

    void SetUpSub(double smCo, double smSpd);

    void SetUpTarget(double rng, double brg, double tgtCo, double tgtSpd);

    void DistanceFrom(seaobject* trk2);

    void BearingFrom(seaobject* trk2, double noiseLimit);

    void MoveSeaObject(double timeSec, double timeStamp);

    void MoveSeaObject(double timeSec);

    void ZeroiseParameters();

    void TurnSeaObject();

    void AccelerateSeaObject();

    double GetCurrentHdg();

    double GetCurrentSpd();

    double GetCurrentRange();

    double GetCurrentBearing();

    double GetOrderedHdg();

    double GetSpeedRate();

    double GetTurnRate();

    double GetOrderedSpd();

    bool GetSimStarted();

    double GetXPos();

    double GetYPos();

    void SimStart();

    void SimStop();

    void SetWheel(bool PortWheel);

    void WritePositionLog(double, double, double);

    double GetXPosRecord(int timeStamp);

    double GetYPosRecord(int timeStamp);

    int GetRecordSize();

    void SetSimCoNow(double co);

    void SetSimSpdNow(double spd);

};

#endif // SEAOBJECT_H
