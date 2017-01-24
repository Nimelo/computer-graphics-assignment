#ifndef SCENEBASIC_H
#define SCENEBASIC_H

#include "scene.h"
#include "C:\Users\mrnim\Desktop\Repos\git-forks\glew-2.0.0-win32/glew-2.0.0/include/GL/glew.h"
#include "glslprogram.h"
#include "C:\Users\mrnim\Desktop\Repos\git-forks\glm-0.9.8.4/glm/glm/glm.hpp"
#include "xyztuple.h"

using glm::mat4;

class SceneBasic : public Scene
{
private:
    int width, height;
    GLuint vboHandles[4];
    GLuint vaoHandle;
    GLuint rotationLine;
    float linePositon[6];
    float lineColor[6];

    float angle;
    vec3 axis;
    mat4 rotationMatrix;
    GLSLProgram prog;

    mat4 model;
    mat4 view;
    mat4 projection;

    void readData(const char* fname);
    void CreateVBO();

    float positionData[108];
    float colorData[108];
public:
    SceneBasic();
    void setMatrices();

    void initScene();
    void render();
    void resize(int, int);
    void update(float t);
    void setAngleAxis(float ang, vec3 ax);
    void resetModel();
    void rotateModel(XYZTuple a, XYZTuple b, double angle);
    void updateView(XYZTuple eye, XYZTuple direction);
    void printActiveUniforms(GLuint programHandle);
    void printActiveAttribs(GLuint programHandle);
};

#endif // SCENEBASIC_H
