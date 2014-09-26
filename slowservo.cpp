#include "slowservo.h"

SlowServo::SlowServo(int tSpd, int zPos)
{
    //Set the turning speed between 1 and 10
    if (tSpd > 0 && tSpd < 10)
    {
        turnSpeed = tSpd;
    } else turnSpeed = 10;

    //Set the zeroised position between 0 and 180

    if (zPos >= 0 && tSpd <= 180)
    {
        zeroPos = zPos;
    } else zeroPos = 90;

    currPos = zeroPos;

    TurnServoFast();
}

void SlowServo::SetNewPosition(int newPos)
{
    finalPos = newPos;
}

void SlowServo::Zeroise()
{
    finalPos = zeroPos;
}

void SlowServo::TurnServoFast()
{

}

void SlowServo::TurnServoSlow()
{

}
