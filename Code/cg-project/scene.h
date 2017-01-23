#ifndef SCENE_H
#define SCENE_H

#include "C:\Users\mrnim\Desktop\Repos\git-forks\glm-0.9.8.4/glm/glm/glm.hpp"
using glm::vec3;

class Scene
{
public:
    /**
      Load textures, initialize shaders, etc.
      */
    virtual void initScene() = 0;

    /**
      This is called prior to every frame.  Use this
      to update your animation.
      */
    virtual void update( float t ) = 0;

    /**
      Draw your scene.
      */
    virtual void render() = 0;

    /**
      Called when screen is resized
      */
    virtual void resize(int, int) = 0;

    virtual void setAngleAxis(float angle, vec3 axis) = 0;
};

#endif // SCENE_H
