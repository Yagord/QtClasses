#ifndef GLTEMPLATE_H
#define GLTEMPLATE_H

#include <QGLWidget>
#include <QMouseEvent>
#include "/home/vu2aeo/QT Projects/Classes/firingsolution.h"

#ifndef d2r
#define d2r 0.01745
#endif

class GLTemplate : public QGLWidget
{
    Q_OBJECT
public:

    explicit GLTemplate(QWidget *parent = 0);

    void ClearScreen();

    void DrawPoint(double,double, int);

    bool GetRightPenStatus();

    bool GetLeftPenStatus();

    double GetTMarkerX();

    double GetTMarkerY();

    void DrawAxes();

    void DrawFillCircle (double, double, double);

    void DrawCircle (double, double, double);

    void DrawTMarker();

    void TranslateTo(double, double, double);

    void DrawPlotAxes();

    void DrawTarget(double x, double y, double co);

    void DrawSubmarine(double x, double y, double co);

    void DrawImpactTarget(double x, double y, double wakeLength, double co, double scale);

    void DrawTorpedoTriangle(FiringSolution* PlotSol);

    void DrawTorpedoQuadrilateral(double smCo, double fBrg1, double fRng1, double DCRng,
                                  double DCBrg, double eT, double phi, double fBrg2, double wakeLength,
                                  double ATB, double tgtCo);

    void DrawFiringAxes(double xT, double yT, double xS, double yS, double xI, double yI, double xDC, double yDC);

    void DrawDCPosition(double xDC, double yDC);

    void RefreshPlot();

    //FiringSolution *PlotSol;

    void PrintPlotParameters(FiringSolution *printSol);

    void SetDrawScale(double);

    void IncreaseDrawScale();

    void DecreaseDrawScale();

    double GetCurrentMouseX();

    double GetCurrentMouseY();

    double GetSMXOrigin();

    double GetSMYOrigin();

    double GetScalingRefDistance();

    void SetTMarkerFlag(bool);

    double GetPlottingScaleFactor();

//    void DrawTorpedoQuadrilateral(FiringSolution* quadSol);

signals:

    void MousePosition(int, int);

    void MouseLeftPress();

    void MouseRightPress();

    void MouseLeftRelease(int,int);

    void MouseRightRelease(int, int);




public slots:

protected:

    void initializeGL();

    void paintGL();

    void mouseMoveEvent(QMouseEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseReleaseEvent(QMouseEvent *);

private:

    bool leftPenOn, rightPenOn;

    int currentMouseX, currentMouseY;

    double drawScale,scale;

    double smXOrigin, smYOrigin;

    double ScalingReferenceDistance;

    double spriteScale;

    bool showTMarker;

    double tMarkerX, tMarkerY;

};

#endif // GLTEMPLATE_H
