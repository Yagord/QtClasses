#include "tmasolution.h"
#include <cstdlib>

TMASolution::TMASolution()
{
    deltaTTimer = new SimTimer();

    this->brgFmSonar = false;

    //SetBrgFmSonarFlag(false);

    SetSolutionMode(1);

    synthUpdateTimer = new SimTimer();

    synthTgt = new seaobject(0,0,0); // to generate Computer bearings for delta B

    synthSm = new seaobject(0,0,0); // to generate computer bearings for delta B

    smBaseUnit = new seaobject(0,0,0); // non moving base unit to average sm kinematics

    smRovingUnit = new seaobject(0,0,0);// follows sm co and spd to average sm kinematics

    manualTweaking = true;

    averageSmKinematics = true;

 }


TMASolution::~TMASolution()
{
    delete deltaTTimer;

    delete synthUpdateTimer;
}


void TMASolution::SetValuesForBasicQkSolution(double vl, double kl, double b1, double b2, double timeMin, double rCab, double vk)
{
    this->vl = vl;
    this->kl = kl;
    this->b1 = b1;
    this->b2 = b2;
    this->timeMin = timeMin;
    this->rCab = rCab;
    this->vk = vk;
}

void TMASolution::SetValuesForBasicVkSolution(double vl, double kl, double b1, double b2, double timeMin, double rCab, double kk)
{
    this->kk = kk;

    this->vl = vl;
    this->kl = kl;
    this->b1 = b1;
    this->b2 = b2;
    this->timeMin = timeMin;
    this->rCab = rCab;

}

double TMASolution::GetQk()
{
    return qk;
}

int TMASolution::DoBasicQkSolution()
{

    CalcBDot();

    if (bdot==0)
    {
        bdot+=0.000000001;
    }

    ql = Azimuth_Diff(kl,b1,true) * d2r;

    CalcOwnVectorAdditive();

    qk=r2d * asin((sin(bdot) * rCab * 6 + ownVectorAdditive * vl * sin(ql) * timeMin)/(vk * timeMin));

    //if solution is not possible return error code = 1;

    if (qk!=qk)
    {
        return 1;
    }

    //get kk from Qk

    if (isClockwise)
    {
        kk = Reciprocal(b2) - qk;

        if (kk<0)
        {
            kk+=360;
        }
    }
    else
    {
        kk = Reciprocal(b2) + qk;

        if (kk>=360)
        {
            kk-=360;
        }
    }

    return 0;
}

double TMASolution::GetBDot()
{
    return bdot;
}

void TMASolution::CalcOwnVectorAdditive()
{
    //if own motion assists bdot, vector additive is negative
    //if own motin reduces bdot, vector additive is positive

    //to do this correctly, the tma platform will need to maneouver at least once to determine if own motion
    //is causes increasing or reducing the bdot
    //since SM commanders want to do this with NIL maneouver, the following
    //assumption is made...

    //if the target draws clockwise and 0 < owncourse < 180 -->> additive vector and vice-versa

    //if target draws anticlockwise and 180 > owncourse > 360 --> additive vector and vice-versa

    //determine clockwise movement....

    if ((this->b2>this->b1 && b2-b1<180)||(this->b2<this->b1 && b1-b2>180))
    {
        isClockwise = true;
    }
    else if((this->b2<this->b1 && b1-b2<180)||(this->b2>this->b1 && b2-b1>180))
    {
        isClockwise = false;
    }

    if (isClockwise)
    {
//        if (this->kl>=0&&this->kl<=180)
//        {
//            //additive vector;
//
//            this->ownVectorAdditive = 1;
//        }
//        else this->ownVectorAdditive = -1;

        if (kl<b1 || abs(kl-b1)>180)
        {
            this->ownVectorAdditive = -1;
        }
        else this->ownVectorAdditive = 1;
    }
    else
    {
//        if (this->kl>=180&&this->kl<=360)
//        {
//            //additive vector;
//
//            this->ownVectorAdditive = 1;
//        }
//        else this->ownVectorAdditive = -1;

        if (kl>b1 || abs(kl-b1)>180)
        {
            this->ownVectorAdditive = -1;
        }
        else this->ownVectorAdditive = 1;

    }

}

bool TMASolution::GetIsClockwise()
{
    return isClockwise;
}

int TMASolution::GetOwnVectorAdditive()
{
    return this->ownVectorAdditive;
}


double TMASolution::GetKK()
{
    return kk;
}

void TMASolution::CalcBDot()
{
    bdot = Azimuth_Diff(b2, b1, true);

    //bdot*=timeMin/60;

    bdot*=d2r;

}

int TMASolution::DoBasicVkSolution()
{
    CalcBDot();

    ql = Azimuth_Diff(kl,b1,true) * d2r;

    qk = Azimuth_Diff(kk, Reciprocal(b2), true) * d2r;

    if (bdot!=0) {

        CalcOwnVectorAdditive();

        vk= (rCab * sin(bdot) * 6 + ownVectorAdditive * vl * sin(ql) * timeMin) / (sin(qk) * timeMin);

    } else
    {
        vk = sin(ql) * vl / sin(qk);
    }

    //if no solution is possible return error code = 1

    if (vk!=vk)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

double TMASolution::GetVk()
{
    return vk;
}

void TMASolution::SetSolutionMode(int mode)
{
    solutionMode = mode;
}

int TMASolution::GetSolutionMode()
{
    return solutionMode;
}

void TMASolution::SetValuesForBasicRCabSolution(double vl, double kl, double b1, double b2, double timeMin, double vk, double kk)
{
    this->kk = kk;

    this->vl = vl;
    this->kl = kl;
    this->b1 = b1;
    this->b2 = b2;
    this->timeMin = timeMin;
    this->vk = vk;

}

int TMASolution::DoBasicRCabSolution()
{
    CalcBDot();

    ql = Azimuth_Diff(kl,b1,true) * d2r;

    qk = Azimuth_Diff(kk, Reciprocal(b2), true) * d2r;

    CalcOwnVectorAdditive();

    rCab = (vk * sin(qk) * timeMin + ownVectorAdditive * vl * sin(ql) * timeMin)/(6 * sin(bdot));

    if (rCab!=rCab)
    {
        return 1;
    }
    else return 0;


}

double TMASolution::GetRCab()
{
    return rCab;
}

void TMASolution::SetBrgFmSonarFlag(bool flag)
{
    this->brgFmSonar = flag;
}

bool TMASolution::GetBrgFmSonarFlag()
{
    return brgFmSonar;
}

void TMASolution::SetManualTweakingFlag(bool flag)
{
    manualTweaking = flag;
}

bool TMASolution::GetManualTweakingFlag()
{
    return manualTweaking;
}

void TMASolution::SetSmKinematicsAverageMethodFlag(bool val)
{
    this->averageSmKinematics = val;
}

bool TMASolution::GetSmKinematicsAverageMethodFlag()
{
    return averageSmKinematics;
}
