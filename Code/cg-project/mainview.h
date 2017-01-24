#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "C:\Users\mrnim\Desktop\Repos\git-forks\glew-2.0.0-win32\glew-2.0.0/include/GL/glew.h"
#include "C:\Users\mrnim\Desktop\Repos\git-forks\glm-0.9.8.4/glm/glm/glm.hpp"
#include <QGLWidget>
#include <QTimer>
using glm::vec3;
#include "scenebasic.h"
#include "xyztuple.h"

class MainView : public QGLWidget
{
    Q_OBJECT

private:
    QTimer *timer;
    SceneBasic *scene;
    float angle;
    vec3 axis;

public:
    MainView(const QGLFormat & format, QWidget *parent = 0 );

    void setRotAxis(float ang, float x, float y , float z);
    void rotateModel(XYZTuple a, XYZTuple b, double angle);
    void updateView(XYZTuple eye, XYZTuple direction);
    void resetModel();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

public slots:
    void timerUpdate();
    void toggleAnimation();
    void takeScreenShot();
};

#endif // MAINVIEW_H
