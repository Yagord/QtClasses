#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#define PT_A -0.15,-0.15,-0.15
#define PT_B -0.15,0.15,-0.15
#define PT_C 0.15,0.15,-0.15
#define PT_D 0.15,-0.15,-0.15
#define PT_E 0.15,-0.15,0.15
#define PT_F -0.15,-0.15,0.15
#define PT_G -0.15,0.15,0.15
#define PT_H 0.15,0.15,0.15

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    void DrawTower();
    void DrawAxes();
    void PerformAllTranslations(double, double, double);
    void PerformAllRotations(double, double, double);
    
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void EnableDepthOverlay();

public slots:
    void ChangeScale(double);

private:

    double angleX, angleY, angleZ;
    double oldX, oldY, oldZ;

    double newScale, oldScale;

    int rotationAxis;
    enum rotationAxis{X,Y,Z};

    
};

#endif // GLWIDGET_H
