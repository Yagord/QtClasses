#include "seaobject.h"
#include "/home/vu2aeo/QT Projects/Classes/tmatools.h"
#include <iostream>
#include <QtCore>

seaobject::seaobject(double setTurnRateSec, double setSpdRateSec, double setSpdTurnConst)
{
    wheel2Port=true;

    turnRateSec=setTurnRateSec;

    spdRateSec=setSpdRateSec;

    spdTurnConst=setSpdTurnConst;

    SimStarted = false;
}

seaobject::~seaobject()
{

}

void seaobject::SetUpSub(double smCo, double smSpd)
{
    simCo = smCo;
    simSpd = smSpd;

    //xyPositionLog = new QVector <xyPositionRecord>;

    if (SimStarted==false)
    {
        xpos = 0;
        ypos = 0;

        simCoNow = simCo;
        simSpdNow = simSpd;
    }
}

void seaobject::SetUpTarget(double rng, double brg, double tgtCo, double tgtSpd)
{
    simCo = tgtCo;
    simSpd = tgtSpd;

    //xyPositionLog = new QVector <xyPositionRecord>;

    if (SimStarted==false)
    {

        simRng = rng;
        simBrg = brg;
        xpos = rng * sin (d2r * brg);
        ypos = rng * cos (d2r * brg);
        simSpdNow = simSpd;
        simCoNow = simCo;

    }

}


void seaobject::DistanceFrom(seaobject* trk2)
{
    simRng = sqrt(pow(xpos - trk2->xpos,2)+pow(ypos-trk2->ypos,2));

}

void seaobject::BearingFrom(seaobject* trk2, double noiseLimit)
{
    double rawBrg = r2d * atan((xpos - trk2->xpos)/(ypos - trk2->ypos));

    rawBrg = AddNoise(rawBrg, noiseLimit);

    bool dirNorth, dirEast;

    if (xpos>trk2->xpos)
    {
        dirEast = true;
    }
    else
    {
        dirEast = false;
    }

    if (ypos>trk2->ypos)
    {
        dirNorth = true;
    }
    else
    {
        dirNorth = false;
    }

    if (dirEast==true&&dirNorth==false)
    {
        rawBrg=180+rawBrg;
    }

    if (dirEast==false&&dirNorth==false)
    {
        rawBrg+=180;
    }

    if (dirEast==false&&dirNorth==true)
    {
        rawBrg=360 + rawBrg;
    }

    simBrg = rawBrg;
}

bool seaobject::GetSimStarted()
{
    return SimStarted;
}

void seaobject::ZeroiseParameters()
{
        simCo=0;
        simSpd=0;
        simCoNow=simCo;
        simSpdNow=simSpd;
        simBrg=0;
        simBrgErr=0.25;
        simRng=0;
        wheel2Port=true;
        xpos=0;
        ypos=0;
}

void seaobject::TurnSeaObject()
{
        float turnDir;

        if (wheel2Port==true)
        {
                turnDir=-1;
        }
        else
        {
                turnDir=1;
        }

        if (fabs(simCoNow-simCo)<=turnRateSec*spdTurnConst)
        {
            simCoNow=simCo;
        }
        else
        {
            simCoNow+=turnRateSec*turnDir*simSpdNow/spdTurnConst;
        }

        if (simCoNow<0)
        {
                simCoNow+=360;
        }

        if (simCoNow>=360)
        {
                simCoNow-=360;
        }

        return;
}

void seaobject::AccelerateSeaObject()
{
        double spdDir;

        if (simSpdNow>simSpd)
        {
            spdDir = -1;
        }
        else if (simSpdNow<simSpd)
        {
            spdDir = 1;
        }

        if (fabs(simSpdNow-simSpd)<=spdRateSec)
        {
            simSpdNow=simSpd;
        }
        else
        {
            simSpdNow+=spdRateSec*spdDir;
        }

        return;
}

void seaobject::MoveSeaObject(double timeSec, double timeStamp)
{
    //for scaling purposes,....

    //the value of timeSec should be equal to time (in hours) * 360.

    xpos += simSpdNow * sin (d2r * simCoNow) * timeSec/360;

    ypos += simSpdNow * cos (d2r * simCoNow) * timeSec/360;

    // this->WritePositionLog(xpos, ypos, timeStamp);

 }

void seaobject::MoveSeaObject(double timeSec)
{
    //for scaling purposes,....

    //the value of timeSec should be equal to time (in hours) * 360.

    xpos += simSpdNow * sin (d2r * simCoNow) * timeSec/360;

    ypos += simSpdNow * cos (d2r * simCoNow) * timeSec/360;



 }

double seaobject::GetCurrentHdg()
{
    return simCoNow;
}

double seaobject::GetCurrentRange()
{
    return simRng;
}

double seaobject::GetCurrentSpd()
{
    return simSpdNow;
}

double seaobject::GetCurrentBearing()
{
    return simBrg;
}

double seaobject::GetXPos()
{
    return xpos;
}

double seaobject::GetYPos()
{
    return ypos;
}

void seaobject::SimStart()
{
    SimStarted = true;
}

void seaobject::SimStop()
{
    SimStarted = false;
}

double seaobject::GetOrderedHdg()
{
    return simCo;
}


double seaobject::GetOrderedSpd()
{
    return simSpd;
}

double seaobject::GetSpeedRate()
{
    return spdRateSec;
}

double seaobject::GetTurnRate()
{
    return turnRateSec;
}

void seaobject::SetWheel(bool PortWheel)
{
    if (PortWheel==true)
    {
        wheel2Port = true;
    }
    else
    {
        wheel2Port = false;
    }
}

double seaobject::AddNoise(double brg, double nLimit)
{
    if (qrand() % 100 > 50)
    {
        return brg + nLimit * qrand()/(RAND_MAX);
    }
    else
    {
        return brg - nLimit * qrand()/(RAND_MAX);
    }
}

void seaobject::WritePositionLog(double x, double y, double time)
{
    this->posNow.timeStamp = time;

    this->posNow.xyPos.setX(x);

    this->posNow.xyPos.setY(y);

    this->xyPositionLog->append(posNow);
}

double seaobject::GetXPosRecord(int timeStamp)
{
    xyPositionRecord temp1 = xyPositionLog->at(timeStamp);

    return temp1.xyPos.x();
}

double seaobject::GetYPosRecord(int timeStamp)
{
    xyPositionRecord temp1 = xyPositionLog->at(timeStamp);

    return temp1.xyPos.y();
}

int seaobject::GetRecordSize()
{
    return xyPositionLog->size();
}


void seaobject::SetSimCoNow(double co)
{
    this->simCoNow = co;
}

void seaobject::SetSimSpdNow(double spd)
{
    this->simSpdNow = spd;
}


