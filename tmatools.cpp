#include "tmatools.h"

double Azimuth_Diff(double num1, double num2, bool makeRational)
{
        double adiff;

        adiff = fabs(num1-num2);

        if(makeRational==true)
        {

            if (adiff>180)
            {
                adiff-=360;
            }

        }

        return fabs(adiff);

}

double Reciprocal(double bearing)
{
        bearing=bearing+180;
        if (bearing>=360)
                {
                        bearing=bearing-360;
                }
        return bearing;

}


double truncate(double angle, int limit)
{
        //Truncates a large number into less than
        //one times the size of limit

        //Used for reducing hour angles to less than 360 deg
        //and time to less than 24h

        double modulo;

        modulo=fmod(angle,limit);

        if (modulo<0)
        {
                modulo=limit+modulo;
        }

        return modulo;
}

double ptma(double t1, double t2, double t3, double b1, double b2, double b3)
{

        //all bearing arguments are in radians
        //all time arguments are in seconds
        //value of calcrel returned is in radians

        double rel_b13,rel_b12;

        rel_b13=(t3-t1)/tan(b3-b1);

        rel_b12=(t2-t1)/tan(b2-b1);

        return d2r * Reciprocal(b1 * r2d)+atan((t3-t2)/(rel_b13-rel_b12));
}

double ResolveBearing(double x1, double y1, double x2, double y2)
{
    double rawBrg = r2d * atan((x1 - x2)/(y1 - y2));

    bool dirNorth, dirEast;

    if (x1>x2)
    {
        dirEast = true;
    }
    else
    {
        dirEast = false;
    }

    if (y1>y2)
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

    return rawBrg;
}

double ComputeRange(float x1, float y1, float x2, float y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1-y2)*(y1-y2));
}

