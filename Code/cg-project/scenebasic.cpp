#include "scenebasic.h"

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include <fstream>
using std::ifstream;

#include <sstream>
using std::ostringstream;

#include "glutils.h"
#include "C:\Users\mrnim\Desktop\Repos\git-forks\glm-0.9.8.4/glm/glm/gtc/matrix_transform.hpp"
//#include "C:/glm/glm/gtc/matrix_projection.hpp"
#include "C:\Users\mrnim\Desktop\Repos\git-forks\glm-0.9.8.4/glm/glm/gtx/transform2.hpp"

const double PI = 4.0*atan(1.0);

SceneBasic::SceneBasic() : angle(0.0), axis(0.0,1.0,0.0)
{
    readData("shader/scenebasic2.dat");

    for(int i = 0; i < 6; i++)
    {
        this->lineColor[i] = 0.5;
    }
}

void SceneBasic::readData(const char* fname)
{
    ifstream ifs(fname);

    if (!ifs) {
        std::cout << "data file not found\n";
        exit(1);
    } else {
        for (int i=0; i<108; i++) ifs >> positionData[i];
        for (int i=0; i<108; i++) ifs >> colorData[i];
    }
}


void SceneBasic::setAngleAxis(float ang, glm::vec3 ax)
{
    angle = ang;
    axis = ax;
}

void SceneBasic::resetModel()
{
    model = mat4(1.0f);
}

void SceneBasic::rotateModel(XYZTuple b, XYZTuple d, double angle)
{
    model *= glm::translate(mat4(1.0f), vec3(b.x, b.y, b.z))
            * glm::rotate(mat4(1.0f), (float)(angle * PI / 180), glm::normalize(vec3(d.x, d.y, d.z)))
            * glm::translate(mat4(1.0f), -vec3(b.x, b.y, b.z));

    linePositon[0] = b.x;
    linePositon[1] = b.y;
    linePositon[2] = b.z;
    linePositon[3] = b.x + d.x;
    linePositon[4] = b.y + d.y;
    linePositon[5] = b.z + d.z;

    GLuint positionRotationBufferHandle = vboHandles[2];

    glBindBuffer(GL_ARRAY_BUFFER, positionRotationBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), this->linePositon, GL_STATIC_DRAW);
}

void SceneBasic::updateView(XYZTuple eye, XYZTuple direction)
{
    view = glm::lookAt(
                vec3(eye.x, eye.y, eye.z),
                vec3(eye.x + direction.x, eye.y + direction.y, eye.z + direction.z),
                vec3(0.0f,1.0f,0.0f)
                );
}

void SceneBasic::CreateVBO()
{
    // Create and populate the buffer objects
    //GLuint vboHandles[4];
    glGenBuffers(4, vboHandles);

    GLuint positionBufferHandle = vboHandles[0];
    GLuint colorBufferHandle = vboHandles[1];


    // bind positionBufferHandle to GL_ARRAY_BUFFER buffer object target
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);
    // creates and initializes GL_ARRAY_BUFFER buffer object's data store
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), positionData, GL_STATIC_DRAW);

     // bind colorBufferHandle to GL_ARRAY_BUFFER target
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), colorData, GL_STATIC_DRAW);

    // Create and set-up the vertex array object
    glGenVertexArrays(1, &vaoHandle);
    // bind the vertex array object
    glBindVertexArray(vaoHandle);

    /* enables the generic vertex attribute array
       the values in the generic vertex attribute array will be accessed
       and used for rendering when calls are made to vertex array commands
       such as glDrawArrays */
    glEnableVertexAttribArray(0);  // Vertex position
    glEnableVertexAttribArray(1);  // Vertex color

    glBindBuffer(GL_ARRAY_BUFFER, positionBufferHandle);

    /* define an array of generic vertex attribute data
       specifies the location and data format of the array of generic
       vertex attributes at index 0 to use when rendering */
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorBufferHandle);
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint positionRotationBufferHandle = vboHandles[2];
    GLuint colorRotatioBufferHandle = vboHandles[3];

    glBindBuffer(GL_ARRAY_BUFFER, positionRotationBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), this->linePositon, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colorRotatioBufferHandle);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), this->lineColor, GL_STATIC_DRAW);

    glGenVertexArrays(1, &rotationLine);
    glBindVertexArray(rotationLine);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, positionRotationBufferHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, colorRotatioBufferHandle);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}


void SceneBasic::initScene()
{
    //////////////////////////////////////////////////////
    /////////// Vertex shader //////////////////////////
    //////////////////////////////////////////////////////

    /* The OpenGL Extension Wrangler Library (GLEW) is a cross-platform
     open-source C/C++ extension loading library. GLEW provides efficient
     run-time mechanisms for determining which OpenGL extensions are supported
     on the target platform.

     if you link with some function - it must exist on target platform,
     or your program wouldn't launch. GLEW handles that - you're not linking
     with GL functions directly, but instead getting function pointers after
     initialization phase. It allows you to check at runtime which extensions
     are present and which functions may be used.

     GLEW obtains information on the supported extensions from the graphics driver.
     Experimental or pre-release drivers, however, might not report every available
     extension through the standard mechanism, in which case GLEW will report
     it unsupported. To circumvent this situation, the glewExperimental global switch
     can be turned on by setting it to GL_TRUE before calling glewInit(), which ensures
     that all extensions with valid entry points will be exposed. */

    glewExperimental = GL_TRUE;
    glewInit();

	// Create the vertex shader object
    GLuint vertShader = prog.createShader(GL_VERTEX_SHADER);

    // Check status
    if( 0 == vertShader)
    {
		fprintf(stderr, "Error creating vertex shader.\n");
		exit(1);
    }

	// load the shader from the file
    prog.load_shader(vertShader,"shader/basic.vert");

	// compile the shader
    prog.compileShader(vertShader);

    // Check compilation status
    prog.checkCompileStatus(vertShader);

  
    //////////////////////////////////////////////////////
    /////////// Fragment shader //////////////////////////
    //////////////////////////////////////////////////////


   // Create the fragment shader object
    GLuint fragShader = prog.createShader(GL_FRAGMENT_SHADER);

    // Check status
    if( 0 == fragShader)
    {
		fprintf(stderr, "Error creating fragment shader.\n");
		exit(1);
    }

	// load the shader from the file
    prog.load_shader(fragShader,"shader/basic.frag");

	// compile the shader
    prog.compileShader(fragShader);

    // Check compilation status
    prog.checkCompileStatus(fragShader);

    // Create the program object
    if (!prog.createObject()) printf("error\n");

    // attach shaders to program object
    prog.attachShader(vertShader);
    prog.attachShader(fragShader);

    // Bind index 0 to the shader input variable "VertexPosition"
    prog.bindAttribLocation(0, "VertexPosition");
    // Bind index 1 to the shader input variable "VertexColor"
    prog.bindAttribLocation(1, "VertexColor");

    // link the program
    prog.link();

    // create and populate the vertex buffer opbject
    CreateVBO();

    prog.printActiveUniforms();

    model = mat4(1.0f);

    view = glm::lookAt(vec3(0.0f,0.0f,2.0f), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
    projection = mat4(1.0f);

    glClearColor(0.0, 0.0, 0.0, 1.0 );
    glEnable(GL_DEPTH_TEST);
}


void SceneBasic::update( float t )
{
    angle += t*2*PI/360.0;
    if( t >= 360.0) angle -= 360.0;
}


void SceneBasic::setMatrices()
{
    mat4 mv = view * model;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("MVP", projection * mv);
}


void SceneBasic::render()
{

    /* sets the bitplane area of the window to values previously
       selected by glClear. GL_COLOR_BUFFER_BIT indicates the buffers
       currently enabled for color writing. */

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* render primitives from array data
       GL_TRIANGLES Specifies what kind of primitives to render.
       Possibilities are symbolic constants GL_POINTS, GL_LINE_STRIP,
       GL_LINE_LOOP, GL_LINES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN and GL_TRIANGLES.
       0 specifies the starting index in the enabled arrays.
       36 specifies the number of indices to be rendered. */

    setMatrices();
    glBindVertexArray(vaoHandle);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    mat4 mv = view;
    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("MVP", projection * mv);

    glBindVertexArray(rotationLine);
    glDrawArrays(GL_LINES, 0, 2);
}

void SceneBasic::resize(int w, int h)
{
    glViewport(0,0,w,h);
    width = w;
    height = h;
    projection = glm::perspective(20.0f, (float)w/h, 0.3f, 30.0f);
}


void SceneBasic::printActiveUniforms(GLuint programHandle) {

    GLint nUniforms, size, location, maxLen;
    GLchar * name;
    GLsizei written;
    GLenum type;

    glGetProgramiv( programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetProgramiv( programHandle, GL_ACTIVE_UNIFORMS, &nUniforms);

    name = (GLchar *) malloc( maxLen );

    printf(" Location | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nUniforms; ++i ) {
        glGetActiveUniform( programHandle, i, maxLen, &written, &size, &type, name );
        location = glGetUniformLocation(programHandle, name);
        printf(" %-8d | %s\n",location, name);
    }

    free(name);
}

void SceneBasic::printActiveAttribs(GLuint programHandle) {

    GLint written, size, location, maxLength, nAttribs;
    GLenum type;
    GLchar * name;

    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    glGetProgramiv(programHandle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

    name = (GLchar *) malloc( maxLength );

    printf(" Index | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nAttribs; i++ ) {
        glGetActiveAttrib( programHandle, i, maxLength, &written, &size, &type, name );
        location = glGetAttribLocation(programHandle, name);
        printf(" %-5d | %s\n",location, name);
    }

    free(name);
}
