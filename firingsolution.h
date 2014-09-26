#ifndef FIRINGSOLUTION_H
#define FIRINGSOLUTION_H

#include <iostream>
#include "/home/vu2aeo/QT Projects/Classes/tmatools.h"
#include "/home/vu2aeo/QT Projects/Classes/seaobject.h"

class FiringSolution
{
private:
    double smCo, smSpd;
    double tgtCo, tgtSpd, tgtRng, fBrg, DOT, CPA, CPATime;
    double phi, omegaMag, l1Mag, l2Mag, dC, tHit, theta;
    double DMin, DMax, wakeLength;
    double torpSpd, eTMax, eTMin, eT, omegaLimit, torpCo;
    double thetaMax, thetaMin;
    double tgtATB;
    bool tgtGreenATB;
    bool omegaGreen, l1Green, l2Green;
    bool solutionReady, tgtOutsideDMinDMax, thetaLimitExceeded, omegaLimitExceeded, IsNarrowATBFiring;
    bool TTPrep, TTStoodTo, DataReadBack;

    void CalcTgtATB();

    void CalcPhi();

    void CalcTheta();

    void CalcTorpCourse();

    bool CheckOmegaGreen();

    void CheckTgtGreenATB();

    void DMinDMaxCalculation();

    void ThetaCheck();

    void Lambda1Calculation();

    void DOTCalculation();

    void THitCalculation();

public:

    FiringSolution(double tSpd, double rMax,double rMin,double omegaLimit,double thetaMax, double thetaMin);

    ~FiringSolution();

    void SetUpSM(double kL, double vL);

    void SetUpTgt(double kK, double vK, double rK);

    void SetFiringBrg(double fBrg);

    void SetTorpedoCourse(double);

    void UpdateFiringSolution();

    void CalcTranslatedDCSolution();

    void CalculateOmega();

    void StdPrintOut();

    double GetTgtATB();

    double GetOmega();

    double GetLambda1();

    double GetLambda2();

    double GetTheta();

    double GetPhi();

    double GetDMin();

    double GetDMax();

    double GetDOT();

    double GetTHit();

    double GetDC();

    double GetTorpedoSpeed();

    bool GetTgtOutsideDminDmax();

    bool GetOmegaLimitExceeded();

    bool GetThetaOutsideLimits();

    double GetTgtRange();

    double GetSMCo();

    double GeteT();

    double GetFiringBearing();

    double GetWakeLength();

    double GetTgtCo();

    bool GetSolutionReadyFlag();

};

#endif // FIRINGSOLUTION_H
