#ifndef TMASOLUTION_H
#define TMASOLUTION_H

#include "tmatools.h"
#include "simtimer.h"
#include "seaobject.h"

class TMASolution
{

private:

    double qk, ql, vk, vl, kk, kl;
    double b1, b2, bdot;
    double rCab;
    double timeMin;
    int ownVectorAdditive;
    bool brgFmSonar;

    int solutionMode;

    bool averageSmKinematics;

    bool isClockwise;

    void CalcBDot();

    void CalcOwnVectorAdditive();

    bool manualTweaking;

public:

    SimTimer* deltaTTimer;

    SimTimer* synthUpdateTimer;

    seaobject* synthTgt;

    seaobject* synthSm;

    seaobject* smBaseUnit;

    seaobject* smRovingUnit;

    TMASolution();

    ~TMASolution();

    double GetQk();

    void SetValuesForBasicQkSolution(double vl,double kl, double b1, double b2,
                   double timeMin, double rCab, double vk);

    void SetValuesForBasicVkSolution(double vl,double kl, double b1, double b2,
                   double timeMin, double rCab, double kk);

    int DoBasicQkSolution();

    int DoBasicVkSolution();

    double GetBDot();

    bool GetIsClockwise();

    int GetOwnVectorAdditive();

    double GetKK();

    double GetVk();

    void SetSolutionMode(int mode);

    int GetSolutionMode();

    void SetValuesForBasicRCabSolution(double vl, double kl, double b1, double b2,
                                       double timeMin, double vk, double kk);

    int DoBasicRCabSolution();

    double GetRCab();

    void SetBrgFmSonarFlag(bool);

    bool GetBrgFmSonarFlag();

    void SetManualTweakingFlag(bool);

    bool GetManualTweakingFlag();

    void SetSmKinematicsAverageMethodFlag(bool val);

    bool GetSmKinematicsAverageMethodFlag();
};

#endif // TMASOLUTION_H
