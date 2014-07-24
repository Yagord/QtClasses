#ifndef TMATOOLS_H
#define TMATOOLS_H

#include <math.h>

#define pi 3.1415926
#define d2r 0.01745329
#define r2d 57.295779

double Azimuth_Diff(double num1, double num2, bool makeRational);

double Reciprocal(double bearing);

double ptma(double t1, double t2, double t3, double b1, double b2, double b3);

double truncate(double angle, int limit);

double ResolveBearing(double, double, double, double);

double ComputeRange(float x1, float y1, float x2, float y2);


#endif // TMATOOLS_H
