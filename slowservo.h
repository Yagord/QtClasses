#ifndef SLOWSERVO_H
#define SLOWSERVO_H

class SlowServo
{
public:
    SlowServo(int, int);

    ~SlowServo();

    void SetTurnSpeed(int);//Change the turning speed

    void SetNewPosition(int);

    void Zeroise();

    void StepPostion();//Step towards the final position


private:

    int turnSpeed;

    int currPos;

    int finalPos;

    int zeroPos;
};

#endif // SLOWSERVO_H
