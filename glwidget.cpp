#include "glwidget.h"
#include <QDebug>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLWidget::initializeGL()
{
    glClearColor(0,0,0,1.0);

    EnableDepthOverlay();

    angleX = 0;
    angleY = 0;
    angleZ = 0;

    oldX = 0;
    oldY = 0;
    oldZ = 0;

    oldScale = 1; newScale = 1;

}

void GLWidget::paintGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0,0,this->width(), this->height());

    //DrawAxes();

    //glPushMatrix();
    DrawTower();
    //glPopMatrix();

}

void GLWidget::resizeGL(int w, int h)
{

}

void GLWidget::DrawTower()
{

    glBegin(GL_QUADS);

    glColor3f(0,0,1);
    glVertex3f(PT_A);
    glVertex3f(PT_B);
    glVertex3f(PT_C);
    glVertex3f(PT_D);

    glColor3f(0,1,0);
    glVertex3f(PT_A);
    glVertex3f(PT_F);
    glVertex3f(PT_G);
    glVertex3f(PT_B);

    glColor3f(0,1,1);
    glVertex3f(PT_A);
    glVertex3f(PT_D);
    glVertex3f(PT_E);
    glVertex3f(PT_F);

    glColor3f(1,0,0);
    glVertex3f(PT_C);
    glVertex3f(PT_D);
    glVertex3f(PT_E);
    glVertex3f(PT_H);

    glColor3f(1,0,1);
    glVertex3f(PT_E);
    glVertex3f(PT_F);
    glVertex3f(PT_G);
    glVertex3f(PT_H);

    glColor3f(1,1,0);
    glVertex3f(PT_B);
    glVertex3f(PT_C);
    glVertex3f(PT_H);
    glVertex3f(PT_G);

    glEnd();

}

void GLWidget::ChangeScale(double scale)
{
    newScale = 1/scale;

    updateGL();
}

void GLWidget::DrawAxes()
{
    //Draw the coordinate axes

        glBegin(GL_LINES);

        glColor3f(1,1,1);

        glVertex3f(0,0,0);
        glVertex3f(1,0,0);

        glVertex3f(0,0,0);
        glVertex3f(0,1,0);

        glVertex3f(0,0,0);
        glVertex3f(0,0,1);

        glEnd();
}

void GLWidget::EnableDepthOverlay()
{
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
}

void GLWidget::PerformAllTranslations(double x, double y, double z)
{
    glTranslated(x, y, z);

    updateGL();
}

void GLWidget::PerformAllRotations(double y, double z, double x)
{

        angleX = x - oldX;
        glRotated(angleX, 1, 0, 0);
        oldX = x;
        //qDebug() <<"oldX:" << oldX <<", Incoming x:" << x << ",rotating by:" << angleX;

        angleY = y - oldY;
        glRotated(angleY, 0, 1, 0);
        oldY = y;

        angleZ = z - oldZ;
        glRotated(angleZ, 0, 0, 1);
        oldZ = z;

    updateGL();
}
