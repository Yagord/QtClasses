#include "firingsolution.h"
#include "tmatools.h"
#include <cstdlib>
#include <math.h>
#include "/home/vu2aeo/QT Projects/Classes/seaobject.h"


using namespace std;

FiringSolution::FiringSolution(double tSpd, double rMax,double rMin,double omegaLimit,double thetaMax, double thetaMin)
{
    //Set up FC parameters for type of weapon and particulars of firing limits....

    this->torpCo = 0;
    this->torpSpd = tSpd;
    this->eTMax = rMax;
    this->eTMin = rMin;
    this->omegaLimit = omegaLimit;
    this->thetaMax = thetaMax;
    this->thetaMin = thetaMin;
    this->wakeLength = 0;

    //Set up standard flags for all firing methods...

    omegaGreen=false;
    l1Green=false;
    l2Green=false;
    tgtOutsideDMinDMax=false;
    omegaLimitExceeded=true;
    thetaLimitExceeded=true;
    TTPrep=false;
    TTStoodTo=false;
    DataReadBack=false;
    solutionReady = false;

}

FiringSolution::~FiringSolution()
{

}

void FiringSolution::SetUpSM(double kL, double vL)
{
    this->smCo = kL;
    this->smSpd = vL;
}

void FiringSolution::SetUpTgt(double kK, double vK, double rK)
{
    this->tgtCo = kK;
    this->tgtSpd = vK;
    this->tgtRng = rK;
}

void FiringSolution::SetFiringBrg(double fBrg)
{
    this->fBrg=fBrg;
}

void FiringSolution::CheckTgtGreenATB()
{
    double temptgtCo=tgtCo;

    temptgtCo+=(360-fBrg);

    if (temptgtCo>=360)
    {
            temptgtCo-=360;
    }

    if (sin(d2r*temptgtCo)>0)
    {
            this->tgtGreenATB = true;
    }
    else this->tgtGreenATB = false;
}

void FiringSolution::CalcTorpCourse()
{
    double torpCo;

    CalcPhi();

    if (tgtGreenATB==true)
    {
            torpCo=fBrg+phi;
    }
    else
    {
            torpCo=fBrg-phi;
    }

    if (torpCo>=360)
    {
            torpCo-=360;
    }
    else if (torpCo<0)
    {
            torpCo+=360;
    }

    this->torpCo = torpCo;
}

bool FiringSolution::CheckOmegaGreen()
{
    bool omegaGreen;

    if (smCo>torpCo)
    {
        if (Azimuth_Diff(smCo,torpCo, false)<180)
        {
            omegaGreen = false;
        }
        else omegaGreen = true;

    }

    if (smCo<=torpCo)
    {
        if (Azimuth_Diff(smCo, torpCo, false)>180)
        {
            omegaGreen = false;
        }
        else omegaGreen = true;
    }

//    if (smCo>torpCo)
//    {
//            omegaGreen=true;
//    }
//    else omegaGreen=false;

//    if (smCo>torpCo && smCo-torpCo >= 180)
//    {
//            omegaGreen=true;
//    }

    return omegaGreen;
}

void FiringSolution::CalcTgtATB()
{
    tgtATB=d2r*Azimuth_Diff(fBrg,Reciprocal(tgtCo), true);

    if (tgtGreenATB<1)
    {
        tgtATB*=-1;
    }
}

void FiringSolution::CalcPhi()
{
    phi=r2d*asin(tgtSpd/torpSpd*sin(fabs(tgtATB)));

    wakeLength = tgtSpd/2;

    CalcTheta();

    THitCalculation();

    double throwoff = asin((wakeLength/40)/eT * sin(fabs(d2r*theta)))* r2d;

    phi-=throwoff;

    //phi-=3;
}

void FiringSolution::CalcTheta()
{
    theta=180-(phi+r2d*fabs(tgtATB));
}

void FiringSolution::CalculateOmega()
{

    omegaMag=Azimuth_Diff(smCo,torpCo, true);

    omegaGreen=CheckOmegaGreen();

    if (fabs(omegaMag)<=omegaLimit)
    {
            omegaLimitExceeded=false;
    }
    else
    {
        omegaLimitExceeded=true;
    }

    if (omegaGreen==false)
    {
        omegaMag*=-1;
    }
}

void FiringSolution::DMinDMaxCalculation()
{
    DMin = eTMin * sin(d2r * theta)/sin(fabs(tgtATB)) * 10;

    DMax = 0.7 * eTMax * sin(d2r * theta) / sin(fabs(tgtATB)) * 10;

    if (tgtRng >= DMax / 10 || tgtRng <= DMin / 10)
    {
            tgtOutsideDMinDMax=true;
    }
    else
    {
        tgtOutsideDMinDMax=false;
    }
}

void FiringSolution::ThetaCheck()
{
    if(theta <= thetaMax && theta >= thetaMin)
    {
            thetaLimitExceeded=false;
            IsNarrowATBFiring=true;
    }
    else
    {
        thetaLimitExceeded=true;
        IsNarrowATBFiring=false;
    }
}

void FiringSolution::StdPrintOut()
{
    cout <<"********************"<<endl;
    cout << "Target Parameters"<<endl;
    cout << "********************"<<endl;
    cout <<"F Brg:"<<fBrg<<endl;
    cout << "Course:"<< tgtCo<<endl;
    cout << "Speed:"<< tgtSpd<<endl;
    cout << "Range:"<< tgtRng<<endl;
    cout <<"TgtATB:"<< r2d * tgtATB<<endl;
    cout <<"ATB Green Flag:"<< tgtGreenATB<<endl;

    cout <<"********************"<<endl;
    cout <<"Submarine Parameters"<<endl;
    cout <<"********************"<<endl;
    cout <<"Course:"<<smCo<<endl;
    cout <<"Speed:"<<smSpd<<endl;
    cout <<"********************"<<endl;

    cout <<"Firing Solution"<<endl;
    cout <<"********************"<<endl;
    cout <<"Lead Angle:"<<phi<<endl;
    cout <<"Omega:"<<omegaMag<<endl;
    cout <<"Omega Green Flag:"<<omegaGreen<<endl;
    cout <<"Omega Outside Limits:"<<omegaLimitExceeded<<endl;
    cout <<"Lambda1:" << l1Mag << endl;
    cout <<"Theta:"<<theta<<endl;
    cout <<"Theta Outside Limits:"<<thetaLimitExceeded<<endl;
    cout <<"Dmin:"<<DMin<<", DMax:"<<DMax<<endl;
    cout <<"Tgt Outside Dmin-Dmax:"<<tgtOutsideDMinDMax<<endl;
    cout << "t Hit:"<<tHit<<endl;

}

void FiringSolution::UpdateFiringSolution()
{
    CheckTgtGreenATB();

    CalcTgtATB();

    //Omega Calculation

    CalcTorpCourse();

    CalculateOmega();

    //Dmin DMax Calculation

    //CalcTheta();

    ThetaCheck();

    DMinDMaxCalculation();

    Lambda1Calculation();

    DOTCalculation();

    THitCalculation();

    solutionReady = true;
}

void FiringSolution::Lambda1Calculation()
{
    if (tgtGreenATB)
    {
        l1Mag=90;
    }
    else
    {
        l1Mag=-90;
    }
}

void FiringSolution::DOTCalculation()
{
    DOT = fabs(sin(tgtATB) * tgtRng * 10);
}

double FiringSolution::GetLambda1()
{
    return l1Mag;
}

double FiringSolution::GetLambda2()
{
    return l2Mag;
}

double FiringSolution::GetOmega()
{
    return omegaMag;
}

double FiringSolution::GetTgtATB()
{
    return tgtATB;
}

double FiringSolution::GetTheta()
{
    return theta;
}

double FiringSolution::GetPhi()
{
    return phi;
}

double FiringSolution::GetDMax()
{
    return DMax;
}

double FiringSolution::GetDMin()
{
    return DMin;
}

double FiringSolution::GetDOT()
{
    return DOT;
}

bool FiringSolution::GetTgtOutsideDminDmax()
{
    return tgtOutsideDMinDMax;
}

bool FiringSolution::GetOmegaLimitExceeded()
{
    return omegaLimitExceeded;
}

void FiringSolution::THitCalculation()
{
    eT = fabs(sin(tgtATB) * tgtRng / sin(d2r * theta));

    dC = eT * 1.852 / 3 ; //default DC value will be one third of the torpedo run

    tHit =  fabs(eT / torpSpd * 60 + ((torpSpd - tgtSpd)/0.7)/*speed advantage*/ / (tgtSpd/20)/*wakelength*/ / 60);
}

double FiringSolution::GetTHit()
{
    return tHit;
}

bool FiringSolution::GetThetaOutsideLimits()
{
    return thetaLimitExceeded;
}

double FiringSolution::GetFiringBearing()
{
    return fBrg;
}

double FiringSolution::GeteT()
{
    return eT;
}

double FiringSolution::GetSMCo()
{
    return smCo;
}

double FiringSolution::GetTgtRange()
{
    return tgtRng;
}

double FiringSolution::GetDC()
{
    return dC;
}

double FiringSolution::GetWakeLength()
{
    return wakeLength;
}

double FiringSolution::GetTgtCo()
{
    return tgtCo;
}

double FiringSolution::GetTorpedoSpeed()
{
    return torpSpd;
}

void FiringSolution::SetTorpedoCourse(double value)
{
    torpCo = value;
}

bool FiringSolution::GetSolutionReadyFlag()
{
    return solutionReady;
}

void FiringSolution::CalcTranslatedDCSolution()
{

}
