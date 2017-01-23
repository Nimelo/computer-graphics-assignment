#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "C:\Users\mrnim\Desktop\Repos\git-forks\glew-2.0.0-win32\glew-2.0.0/include/GL/glew.h"
#include <string>
using std::string;

#include "C:\Users\mrnim\Desktop\Repos\git-forks\glm-0.9.8.4/glm/glm/glm.hpp"
using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::mat3;

namespace GLSLShader {
    enum GLSLShaderType {
        VERTEX, FRAGMENT, GEOMETRY,
        TESS_CONTROL, TESS_EVALUATION
    };
};

class GLSLProgram
{
private:
    // the program object handle
    GLuint  handle;

    // linked status
    bool linked;

    // string for log information
    string logString;

    // returns the location of a uniform variable specified by name
    int  getUniformLocation(const char * name );

    // checks if the file specified by filename exists
    bool fileExists( const string & fileName );

public:
    GLSLProgram();

    // read the shader source from a file and compile
    bool compileShaderFromFile( const char * fileName, GLSLShader::GLSLShaderType type );

    // compiles shader source code stored in a string
    bool compileShaderFromString( const string & source, GLSLShader::GLSLShaderType type );

    // load the shader source code from the file into a string
    std::string loadFileToString(const char* fname);

    // load the shader code from a file
    void load_shader(GLuint shaderobject, const char*  shadersourcefilename);

    // glShaderSource sets the source code in shader to the source code in the array of
    // strings specified by string.
    void glcppShaderSource(GLuint shader, std::string const &shader_string);


    // glCreateShader creates an empty shader object and returns a non-zero value by
    // which it can be referenced.
    GLuint createShader(GLenum shaderType);

    // glCompileShader compiles the source code strings that have been stored in the
    // shader object specified by shader.
    void compileShader(GLuint shader);

    // provides error log information for compilation of shader
    void checkCompileStatus(GLuint shader);

    // attaches the shader object specified by shader to the program object specified by handle.
    void attachShader(GLuint shader);

    // links the program object specified by handle.
    bool link();

    // installs the program object specified by handle as part of current rendering state.
    void use();

    // creates an empty program object and returns a non-zero value by which it can be referenced.
    bool createObject();

    // returns the logString
    string log();

    // return the program object handle
    GLuint getHandle();

    // returns the link status
    bool isLinked();

    // associates a user-defined attribute variable in the program object
    // specified by handle with a generic vertex attribute index.
    void bindAttribLocation( GLuint location, const char * name);

    // bind a user-defined varying out variable specified by name to a fragment shader color
    // number specified by location
    void bindFragDataLocation( GLuint location, const char * name );


    // the following group of setUniform methods modify the value of a uniform variable or a uniform variable array.

    // x,y,z are the new values to be used for the specified uniform variable
    void setUniform( const char *name, float x, float y, float z);

    // v.x,v.y,v.z are the new values to be used for the specified uniform variable
    void setUniform( const char *name, const vec3 & v);

    // v.x,v.y,v.z, v.w are the new values to be used for the specified uniform variable
    void setUniform( const char *name, const vec4 & v);

    // val is the new value for the uniform variable
    void setUniform( const char *name, float val );

    // val is the new value for the uniform variable
    void setUniform( const char *name, int val );

    // val is the new value for the uniform variable
    void setUniform( const char *name, bool val );


    // The commands glUniformMatrix{2|3|4}fv are used to modify a matrix or an array of matrices.
    // The numbers in the command name are interpreted as the dimensionality of the matrix.
    void setUniform( const char *name, const mat4 & m);
    void setUniform( const char *name, const mat3 & m);

    // prints all the active uniform variables
    void printActiveUniforms();

    // prints all the active attribute variables
    void printActiveAttribs();
};

#endif // GLSLPROGRAM_H
