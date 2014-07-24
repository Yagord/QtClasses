#include "gltemplate.h"
#include <iostream>
#include <qmath.h>
#include <QDebug>

GLTemplate::GLTemplate(QWidget *parent) :
    QGLWidget(parent)
{

    setMouseTracking(true);

    rightPenOn = false;

    leftPenOn = false;

    drawScale = 0.75;

    scale = 15;

    spriteScale = 0.6;

    showTMarker = false;

}

void GLTemplate::initializeGL()
{
    glShadeModel(GL_SMOOTH);

    glClearColor(0.0f,0.0f,0.0f,0.0f);

    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

}

void GLTemplate::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    updateGL();

}

void GLTemplate::mouseMoveEvent(QMouseEvent *event)
{
    currentMouseX = event->x()/this->width()*2 - 1;

    currentMouseY = 1 - event->y()/this->height()*2;

    MousePosition(event->x(), event->y());
}

void GLTemplate::DrawPoint(double x, double y, int penSize)
{
    glColor3f(1,0,0);

    glPointSize(penSize);

    glBegin(GL_POINTS);

    glVertex3f(x/this->width()*2-1,1-y/this->height()*2,0);

    glEnd();

    swapBuffers();

    //updateGL();

}

void GLTemplate::mousePressEvent(QMouseEvent *event2)
{

    if (event2->button() == Qt::LeftButton)
    {
        MouseLeftPress();

        leftPenOn = true;
    }
    else if (event2->button() == Qt::RightButton)
    {
        MouseRightPress();

        rightPenOn = true;
    }

}

void GLTemplate::mouseReleaseEvent(QMouseEvent *event2)
{

    if (event2->button() == Qt::LeftButton)
    {
        MouseLeftRelease(event2->x(), event2->y());

        leftPenOn = false;

        this->tMarkerX = event2->x();

        this->tMarkerY = event2->y();

    }
    else if (event2->button() == Qt::RightButton)
    {
        MouseRightRelease(event2->x(), event2->y());

        rightPenOn = false;
    }

//    this->currentMouseX = event->x()/this->width()*2 - 1;

//    this->currentMouseY = 1 - event->y()/this->height()*2;
}

bool GLTemplate::GetLeftPenStatus()
{
    return leftPenOn;
}

bool GLTemplate::GetRightPenStatus()
{
    return rightPenOn;
}

void GLTemplate::DrawAxes()
{
    glLineWidth(1);

    glColor3f(1,0,0);

    double lineLimit = 0.98;

    glBegin(GL_LINES);

    //vertical lines
    glVertex3f(0.0,1*lineLimit,0);
    glVertex3f(0.0,0.25,0);

    glVertex3f(0.0,-1*lineLimit,0);
    glVertex3f(0.0,-0.25,0);

    //horizontal lines
    glVertex3f(1*lineLimit,0,0);
    glVertex3f(0.25,0,0);
    glVertex3f(-1*lineLimit,0,0);
    glVertex3f(-0.25,0,0);

    //diagonal lines
    glVertex3f(sin(pi/4)*lineLimit*0.25,cos(pi/4)*lineLimit*0.25,0);
    glVertex3f(sin(pi/4)*lineLimit,cos(pi/4)*lineLimit,0);

    glVertex3f(sin(5*pi/4)*lineLimit,cos(5*pi/4)*lineLimit,0);
    glVertex3f(sin(5*pi/4)*lineLimit*0.25,cos(5*pi/4)*lineLimit*0.25,0);

    glVertex3f(sin(3*pi/4)*lineLimit,cos(3*pi/4)*lineLimit,0);
    glVertex3f(sin(3*pi/4)*lineLimit*0.25,cos(3*pi/4)*lineLimit*0.25,0);

    glVertex3f(sin(7*pi/4)*lineLimit,cos(7*pi/4)*lineLimit,0);
    glVertex3f(sin(7*pi/4)*lineLimit*0.25,cos(7*pi/4)*lineLimit*0.25,0);
    glEnd();

    DrawCircle(0,0,0.25*lineLimit);
    DrawCircle(0,0,0.5*lineLimit);
    DrawCircle(0,0,0.75*lineLimit);
    DrawCircle(0,0,1.0*lineLimit);

}

void GLTemplate::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    //glViewport(0,0,800,800);

    glLineWidth(1);

}


void GLTemplate::DrawFillCircle(double x, double y, double rad)
{
    glBegin(GL_POLYGON);

     for (float i=0;i<6.29;i+=0.01)
    {
        glVertex3f(x+rad*sin(i),y+rad*cos(i),0);
    }

    glEnd();

    //swapBuffers();

    updateGL();
}

void GLTemplate::DrawCircle(double x, double y, double rad)
{

    glBegin(GL_LINE_LOOP);

     for (float i=0;i<6.29;i+=0.01)
    {
        glVertex3f(x+rad*sin(i),y+rad*cos(i),0);
    }

    glEnd();

    //swapBuffers();
}

void GLTemplate::TranslateTo(double x, double y, double z)
{
    glTranslatef(x,y,z);
}

void GLTemplate::DrawTarget(double x, double y, double co)
{
    glColor3f(1.0f,1.0f,1.0f);

    glPushMatrix();

  //  glScalef(drawScale, drawScale, 1);

    glTranslatef(x,y,0);

    glRotatef(90-co,0,0,1);

  //  glScalef(1/drawScale, 1/drawScale, 1);

    glBegin(GL_LINE_LOOP);

    glVertex3f(0,0,0);
    glVertex3f(0.0,0.025*spriteScale,0);
    glVertex3f(0.09*spriteScale,0.025*spriteScale,0);
    glVertex3f(0.12*spriteScale,0,0);
    glVertex3f(0.09*spriteScale,-0.025*spriteScale,0);
    glVertex3f(0.0,-0.025*spriteScale,0);
    
    glEnd();

    glPopMatrix();
}

void GLTemplate::DrawSubmarine(double x, double y, double co)
{
    glColor3f(0.0f,1.0f,0.0f);
    glPushMatrix();

    //glScalef(drawScale, drawScale, 1);

    glTranslatef(x,y,0);// move to the submarine coordinates

    glRotatef(90-co/d2r,0,0,1);

    if(co / d2r >= 180)//if co>180, flip the sm so that it looks upright
    {       
        glRotatef(180,1,0,0);
    }

    //glScalef(1/drawScale, 1/drawScale, 1);

    glBegin(GL_LINE_LOOP);

    glVertex3f(0,0,0);
    glVertex3f(0.3*spriteScale,0,0);
    glVertex3f(0.24*spriteScale,0.02*spriteScale,0);
    glVertex3f(0.3*spriteScale,0,0);
    glVertex3f(0.24*spriteScale,-0.02*spriteScale,0);
    glVertex3f(0.3*spriteScale,0,0);
    glVertex3f(-0.10*spriteScale,0,0);
    glVertex3f(-0.05*spriteScale,0.05*spriteScale,0);
    glVertex3f(0,0.05*spriteScale,0);
    glEnd();

    glPopMatrix();

}

void GLTemplate::DrawImpactTarget(double x, double y, double wakeLength, double co, double scale)
{
    glPushMatrix();

   // glScalef(drawScale, drawScale, 1);

    glTranslatef(x,y,0);

    glRotatef(90-co,0,0,1);

    wakeLength = wakeLength / 100 * scale * drawScale;

    //draw the effective target wake centred on (x,y)

    glColor3f(0.0f,0.0f,1.0f);

   // glScalef(1/drawScale, 1/drawScale, 1);

    glBegin(GL_LINE_LOOP);

    glVertex3f(-wakeLength/2,0,0);
    glVertex3f(-wakeLength/2,0.025*spriteScale,0);
    glVertex3f(wakeLength/2,0.025*spriteScale,0);
    glVertex3f(wakeLength/2,-0.025*spriteScale,0);
    glVertex3f(-wakeLength/2,-0.025*spriteScale,0);
    glVertex3f(-wakeLength/2,0,0);

    glEnd();

    //draw the future position of the target

    glColor3f(1.0f,0.0f,0.0f);

    glBegin(GL_LINE_LOOP);

    glVertex3f(wakeLength/2,0,0);
    glVertex3f(wakeLength/2,0.025*spriteScale,0);
    glVertex3f(wakeLength/2+0.09*spriteScale,0.025*spriteScale,0);
    glVertex3f(wakeLength/2+0.12*spriteScale,0,0);
    glVertex3f(wakeLength/2+0.09*spriteScale,-0.025*spriteScale,0);
    glVertex3f(wakeLength/2,-0.025*spriteScale,0);

    glEnd();

    glPopMatrix();
}

void GLTemplate::DrawTorpedoTriangle(FiringSolution *plotSol)
{

    double xS, yS, xT, yT,xI, yI, xC, yC, xDC, yDC; //x and y coords of sm, tgt, impact and centroid

    //xS=0;yS=0;xT=0;yT=0;xI=0;yI=0;xC=0;yC=0;xDC=0;yDC=0;

    //double scale = 50;//plotSol->GetTgtRange() * 3;

    xS = 0; yS = 0;

    double smCo, fBrg, phi, wakeLength, eT, DC, tgtCo, tgtRng;

    smCo = plotSol->GetSMCo()*d2r;

    fBrg = plotSol->GetFiringBearing();

    phi = plotSol->GetPhi();

    if (plotSol->GetTgtATB()<0) phi*=-1;

    wakeLength = plotSol->GetWakeLength()/10;

    eT = plotSol->GeteT();

    DC = plotSol->GetDC()/1.852;//dc needs to be converted from km into miles

    tgtRng = plotSol->GetTgtRange();

    tgtCo = plotSol->GetTgtCo();

    xT = tgtRng * cos (d2r * fBrg);

    yT = tgtRng * sin (d2r * fBrg);

    xI = eT * cos (d2r * (fBrg+phi));

    yI = eT * sin (d2r * (fBrg+phi));

    xDC = DC * cos (d2r * (fBrg+phi));

    yDC = DC * sin (d2r * (fBrg+phi));

    xC = (xS + xT + xI)/3;

    yC = (yS + yT + yI)/3;

    xC = 0; yC = 0;

    //glTranslatef(xC/100, yC/100, 0);

    xT = (xT - xC)/100 * scale * drawScale;

    yT = (yT - yC)/100 * scale * drawScale;

    xS = (xS - xC)/100 * scale * drawScale;

    yS = (yS - yC)/100 * scale * drawScale;

    xI = (xI - xC)/100 * scale * drawScale;

    yI = (yI - yC)/100 * scale * drawScale;

    xDC = (xDC - xC)/100 * scale * drawScale;

    yDC = (yDC - yC)/ 100 * scale * drawScale;

    //set the drawing scale

    //drawScale = fabs(0.5/maxPoint); // the scale chosen should cover about 0.8 of the available draw space

    //Set the SM origin and ScalingReferenceDistance for display purposes

    smXOrigin = xS;

    smYOrigin = yS;

    ScalingReferenceDistance = 80;//tgtRng * 10 / sqrt(pow((yS-yT),2)+pow((xS-xT),2));

    //draw all objects...

    DrawAxes();

    DrawSubmarine(yS, xS, smCo);

    DrawTarget(yT, xT, tgtCo);

    DrawImpactTarget(yI, xI, wakeLength, tgtCo, scale); // Impact point

    DrawFiringAxes(xT, yT, xS, yS, xI, yI, xDC, yDC);

    DrawDCPosition(xDC, yDC);

    // std::cout << xS << " " << yS << std::endl;

    //plot the TMarker if required

    if(this->showTMarker)
    {
        DrawTMarker();
    }

    swapBuffers();

}

void GLTemplate::DrawFiringAxes(double xT, double yT, double xS, double yS,
                                double xI, double yI, double xDC, double yDC)
{

    //glScalef(drawScale, drawScale, 1);

    //from sm to target present position...
//    glColor3f(1,1,1);
//    glBegin(GL_LINE);
//    glVertex3f(yS, xS, 0);
//    glVertex3f(yT,xT,0);
//    glEnd();

    //from sm to DC position
    glColor3f(0,1,1);
    glBegin(GL_LINE);
    glVertex3f(yS, xS, 0);
    glVertex3f(yDC,xDC,0);
    glEnd();

    //from DC to future position
    glColor3f(0,1,1);
    glBegin(GL_LINE);
    glVertex3f(yDC, xDC, 0);
    glVertex3f(yI,xI,0);
    glEnd();


}

void GLTemplate::DrawDCPosition(double xDC, double yDC)
{
    glColor3f(1,1,0);

    double offset=0; double radius = 0.015;

    glBegin(GL_POLYGON);

    for(double i=0;i<6.30;i+=0.1)
    {
        glVertex3f(yDC+offset+radius*sin(i),xDC+offset+radius*cos(i),0);
    }

    glEnd();
}


void GLTemplate::RefreshPlot()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
}

void GLTemplate::PrintPlotParameters(FiringSolution *printSol)
{
    std::cout << "********************" << std::endl;
    std::cout << "SM Co:" << printSol->GetSMCo() << std::endl;
    std::cout << "Tgt Co:" << printSol->GetTgtCo() << std::endl;
    std::cout << "Firing Brg:" << printSol->GetFiringBearing() << std::endl;
    std::cout << "Firing Range:" << printSol->GetTgtRange() << std::endl;
    std::cout << "Phi:" << printSol->GetPhi() << std::endl;
    std::cout << "Wakelength:" << printSol->GetWakeLength() << std::endl;
    std::cout << "eT:" << printSol->GeteT() << std::endl;
    std::cout << "DC:" << printSol->GetDC() << std::endl;
    std::cout << "********************" << std::endl;
}

void GLTemplate::SetDrawScale(double value)
{
    drawScale = value;
}

double GLTemplate::GetCurrentMouseX()
{
    return currentMouseX;
}

double GLTemplate::GetCurrentMouseY()
{
    return currentMouseY;
}

double GLTemplate::GetSMXOrigin()
{
    return smXOrigin;
}

double GLTemplate::GetSMYOrigin()
{
    return smYOrigin;
}

double GLTemplate::GetScalingRefDistance()
{
    return ScalingReferenceDistance;
}

void GLTemplate::DrawTorpedoQuadrilateral(double smCo, double fBrg1, double fRng1, double DCRng,
                                          double DCBrg, double eT, double phi, double fBrg2, double wakeLength,
                                          double ATB, double tgtCo)
{
    double xS, yS, xDC, yDC, xI, yI, xT, yT, xC, yC;

    //double scale = 40;//fRng1 * 3 /10;

    if (ATB < 0) phi*=-1;

    xS = 0; yS = 0;

    xT = fRng1 * cos (fBrg1 * d2r) * 10;

    yT = fRng1 * sin (fBrg1 * d2r) * 10;

    xDC = DCRng * cos (DCBrg * d2r);

    yDC = DCRng * sin (DCBrg * d2r);

    xI = xDC + eT * cos ((fBrg2 + phi) * d2r) * 10;

    yI = yDC + eT * sin ((fBrg2 + phi) * d2r) * 10;

    xC = (xS + xT + xI)/3;

    yC = (yS + yT + yI)/3;
    
    xC = 0; yC = 0;

    xT = (xT - xC)/100 * scale * drawScale;

    yT = (yT - yC)/100 * scale * drawScale;

    xS = (xS - xC)/100 * scale * drawScale;

    yS = (yS - yC)/100 * scale * drawScale;

    xI = (xI - xC)/100 * scale * drawScale;

    yI = (yI - yC)/100 * scale * drawScale;

    xDC = (xDC - xC)/100 * scale * drawScale;

    yDC = (yDC - yC)/ 100 * scale * drawScale;

    //Set the SM origin and ScalingReferenceDistance for display purposes

    smXOrigin = xS;

    smYOrigin = yS;

    ScalingReferenceDistance = 80;//fRng1 * 10 / sqrt(pow((yS-yT),2)+pow((xS-xT),2));

    //draw all objects...

    DrawAxes();

    DrawSubmarine(yS, xS, smCo);

    DrawTarget(yT, xT, tgtCo);

    DrawImpactTarget(yI, xI, wakeLength, tgtCo, scale); // Impact point

    DrawFiringAxes(xT, yT, xS, yS, xI, yI, xDC, yDC);

    DrawDCPosition(xDC, yDC);

    if(this->showTMarker)
    {
        DrawTMarker();
    }

    swapBuffers();

    //updateGL();

}

void GLTemplate::IncreaseDrawScale()
{
    drawScale+=0.25;
}

void GLTemplate::DecreaseDrawScale()
{
    if (drawScale>0.25)
    {
        drawScale-=0.25;
    }
}

void GLTemplate::DrawTMarker()
{
    double x= (tMarkerX/this->width()*2 - 1);

    double y= (1 - tMarkerY/this->height()*2);

    //qDebug() << "x:" << tMarkerX << ",y:" << tMarkerY;

    glLineWidth(4);

    glColor3f(1,1,1);

    glBegin(GL_LINES);

    //vertical lines
    glVertex3f(x-0.05,y,0);
    glVertex3f(x+0.05,y,0);

    //horizontal lines
    glVertex3f(x,y-0.05,0);
    glVertex3f(x,y+0.05,0);

    glEnd();

}

void GLTemplate::SetTMarkerFlag(bool value)
{
    this->showTMarker = value;
}

double GLTemplate::GetTMarkerX()
{
    return this->tMarkerX;
}

double GLTemplate::GetTMarkerY()
{
    return this->tMarkerY;
}

double GLTemplate::GetPlottingScaleFactor()
{
    return scale * drawScale * this->width();
}
