#include "mainview.h"
#include "scenebasic.h"
#include "glutils.h"
#include <iostream>
#include <cstdio>
using std::cout;
using std::endl;


MainView::MainView(const QGLFormat & format, QWidget *parent) : QGLWidget(format, parent)
{
    // This tells the widget to accept keyboard focus when the widget is clicked.
    this->setFocusPolicy(Qt::ClickFocus);

    timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), this, SLOT(timerUpdate()) );
    timer->start(50);

    //this->setMinimumSize(800,600);
}

void MainView::initializeGL() {

    //////////////// PLUG IN SCENE HERE /////////////////
    scene = new SceneBasic();
    ////////////////////////////////////////////////////

    GLenum err = glewInit();
    if( GLEW_OK != err )
    {
        cout <<"Error initializing GLEW: " << glewGetErrorString(err) << endl;
    }
   // GLUtils::checkForOpenGLError(__FILE__,__LINE__);
     GLUtils::checkForOpenGLError();

    QGLFormat format = this->format();
    printf("QGLFormat reports profile: ");
    if( format.profile() == QGLFormat::CompatibilityProfile )
        printf("compatability.\n");
    else if( format.profile() == QGLFormat::CoreProfile )
        printf("core.\n");
    else
        printf("none.\n");

    GLUtils::dumpGLInfo();

    glClearColor(0.0f,0.0f,0.0f,1.0f);

    scene->initScene();
}

void MainView::paintGL() {
    GLUtils::checkForOpenGLError();
    scene->render();
}

void MainView::resizeGL(int w, int h ) {
    scene->resize(w,h);
}

void MainView::takeScreenShot() {
    QImage img = this->grabFrameBuffer(true);
    img.save("screen.png", "PNG");
}

void MainView::toggleAnimation() {
    if( timer->isActive() )
        timer->stop();
    else
        timer->start();
}

void MainView::timerUpdate() {
    scene->update(0.0f);
    updateGL();
}


 void MainView::setRotAxis(float ang, float x, float y , float z)
 {
    // angle = ang;
     //axis = vec3(x,y,z);
     scene->setAngleAxis(ang,vec3(x,y,z));
     updateGL();
 }

 void MainView::rotateModel(XYZTuple a, XYZTuple b, double angle)
 {
    scene->rotateModel(a, b, angle);
 }

 void MainView::updateView(XYZTuple eye, XYZTuple direction)
 {
     scene->updateView(eye, direction);
 }
