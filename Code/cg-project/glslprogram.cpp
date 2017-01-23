#include "glslprogram.h"
#include "glutils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
using std::ifstream;
using std::ios;
using std::ostringstream;


// default constructor, sets program handle to 0 and linked status to false
GLSLProgram::GLSLProgram() : handle(0), linked(false) { }


/* glShaderSource sets the source code in shader to the source code in the array of
   strings specified by string. Any source code previously stored in the shader object
   is completely replaced. The number of strings in the array is specified by count.
   If shader_length is NULL, each string is assumed to be null terminated.
   If shader_length is a value other than NULL, it points to an array containing a string length
   for each of the corresponding elements of string. Each element in the length array may
   contain the length of the corresponding string (the null character is not counted as part of
   the string length) or a value less than 0 to indicate that the string is null terminated.
   The source code strings are not scanned or parsed at this time; they are simply copied
   into the specified shader object. */
void GLSLProgram::glcppShaderSource(GLuint shader, std::string const &shader_string)
{
    GLchar const *shader_source = shader_string.c_str();
    GLint const shader_length = shader_string.size();

    GLsizei count = 1;
    glShaderSource(shader, count, &shader_source, &shader_length);
}


// load the shader code from a file
void GLSLProgram::load_shader(GLuint shaderobject, const char* shadersourcefilename)
{
    glcppShaderSource(shaderobject, loadFileToString(shadersourcefilename));
}


/* glCreateShader creates an empty shader object and returns a non-zero value by
   which it can be referenced. A shader object is used to maintain the source code
   strings that define a shader. shaderType indicates the type of shader to be created.
   Two types of shaders are supported. A shader of type GL_VERTEX_SHADER is a shader
   that is intended to run on the programmable vertex processor. A shader of type
   GL_FRAGMENT_SHADER is a shader that is intended to run on the programmable fragment
   processor.

   When created, a shader object's GL_SHADER_TYPE parameter is set to either GL_VERTEX_SHADER
   or GL_FRAGMENT_SHADER, depending on the value of shaderType.*/
GLuint GLSLProgram::createShader(GLenum shaderType)
{
    return glCreateShader(shaderType);
}




/* glCompileShader compiles the source code strings that have been stored in the
   shader object specified by shader.

   The compilation status will be stored as part of the shader object's state.
   This value will be set to GL_TRUE if the shader was compiled without errors and is
   ready for use, and GL_FALSE otherwise. It can be queried by calling glGetShaderiv with
   arguments shader and GL_COMPILE_STATUS.

   Compilation of a shader can fail for a number of reasons as specified by the OpenGL ES
   Shading Language Specification. Whether or not the compilation was successful, information
   about the compilation can be obtained from the shader object's information log by calling
   glGetShaderInfoLog.*/
void GLSLProgram::compileShader(GLuint shader)
{
	glCompileShader(shader);
}



/* glGetShaderiv returns in result the value of a parameter for a specific shader object.
   The following parameters are defined:

   GL_SHADER_TYPE
   result returns GL_VERTEX_SHADER if shader is a vertex shader object, and GL_FRAGMENT_SHADER
   if shader is a fragment shader object.

   GL_DELETE_STATUS
   result returns GL_TRUE if shader is currently flagged for deletion, and GL_FALSE otherwise.

   GL_COMPILE_STATUS
   result returns GL_TRUE if the last compile operation on shader was successful, and GL_FALSE
   otherwise.

   GL_INFO_LOG_LENGTH
   result returns the number of characters in the information log for shader including the null
   termination character (i.e., the size of the character buffer required to store the information
   log). If shader has no information log, a value of 0 is returned.

   GL_SHADER_SOURCE_LENGTH
   result returns the length of the concatenation of the source strings that make up the shader
   source for the shader, including the null termination character. (i.e., the size of the
   character buffer required to store the shader source). If no source code exists, 0 is returned.

   glGetShaderInfoLog returns the information log for the specified shader object.
   The information log for a shader object is modified when the shader is compiled.
   The string that is returned will be null terminated.

   glGetShaderInfoLog returns in log as much of the information log as it can, up to a
   maximum of maxLength characters. The number of characters actually returned, excluding
   the null termination character, is specified by logLen. If the length of the returned
   string is not required, a value of NULL can be passed in the length argument.
   The size of the buffer required to store the returned information log can be obtained by
   calling glGetShaderiv with the value GL_INFO_LOG_LENGTH.

   The information log for a shader object is a string that may contain diagnostic messages,
   warning messages, and other information about the last compile operation.
   When a shader object is created, its information log will be a string of length 0.*/

void GLSLProgram::checkCompileStatus(GLuint shader)
{	
    GLint result;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &result);
    if( GL_FALSE == result )
    {

       fprintf( stderr, "shader compilation failed!\n" );

       GLint logLen;
       glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLen );

       if( logLen > 0 )
       {
           char * log = (char *)malloc(logLen);

           GLsizei written;
           glGetShaderInfoLog(shader, logLen, &written, log);

           fprintf(stderr, "Shader log: \n%s", log);

           free(log);
       }
	}
}


// load the shader source code from the file into a string
std::string GLSLProgram::loadFileToString( const char*  fname)
{
    std::ifstream ifile(fname);
    if (!ifile) std::cout << "file " << fname << " not found" << "\n";
    std::string filetext;

    while( ifile.good() ) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }

    return filetext;
}

/* read the shader source from a file and compile
   reads shader source into a string and then calls compileShaderFromString */
bool GLSLProgram::compileShaderFromFile( const char * fileName,
                                         GLSLShader::GLSLShaderType type )
{
    if( ! fileExists(fileName) )
    {
        logString = "File not found.";
        return false;
    }

    if( handle <= 0 ) {
        handle = glCreateProgram();
        if( handle == 0) {
            logString = "Unable to create shader program.";
            return false;
        }
    }




    ifstream inFile( fileName, ios::in );
    if( !inFile ) {
       return false;
    }

    ostringstream code;
    while( inFile.good() ) {
        int c = inFile.get();
        if( ! inFile.eof() ) code << (char) c;
    }
    inFile.close();

    return compileShaderFromString(code.str(), type);
}


/* compiles shader source code stored in a string, type specifies the type of the
   shader one of GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, GL_TESS_CONTROL,
   GL_TESS_EVALUTION */
bool GLSLProgram::compileShaderFromString( const string & source, GLSLShader::GLSLShaderType type )
{
    if( handle <= 0 ) {
        handle = glCreateProgram();
        if( handle == 0) {
            logString = "Unable to create shader program.";
            return false;
        }
    }

    GLuint shaderHandle = 0;

    switch( type ) {
    case GLSLShader::VERTEX:
        shaderHandle = glCreateShader(GL_VERTEX_SHADER);
        break;
    case GLSLShader::FRAGMENT:
        shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    case GLSLShader::GEOMETRY:
        shaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    case GLSLShader::TESS_CONTROL:
        shaderHandle = glCreateShader(GL_TESS_CONTROL_SHADER);
        break;
    case GLSLShader::TESS_EVALUATION:
        shaderHandle = glCreateShader(GL_TESS_EVALUATION_SHADER);
        break;
    default:
        return false;
    }

    const char * c_code = source.c_str();
    glShaderSource( shaderHandle, 1, &c_code, NULL );

    // Compile the shader
    glCompileShader(shaderHandle );

    // Check for errors
    int result;
    glGetShaderiv( shaderHandle, GL_COMPILE_STATUS, &result );
    if( GL_FALSE == result ) {
        // Compile failed, store log and return false
        int length = 0;
        logString = "";
        glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &length );
        if( length > 0 ) {
            char * c_log = new char[length];
            int written = 0;
            glGetShaderInfoLog(shaderHandle, length, &written, c_log);
            logString = c_log;
            delete [] c_log;
        }

        return false;
    } else {
        // Compile succeeded, attach shader and return true
        glAttachShader(handle, shaderHandle);
        return true;
    }
}



/* glCreateProgram creates an empty program object and returns a non-zero value by which it
   can be referenced. A program object is an object to which shader objects can be attached.
   This provides a mechanism to specify the shader objects that will be linked to create a program.
   It also provides a means for checking the compatibility of the shaders that will be used to create
   a program (for instance, checking the compatibility between a vertex shader and a fragment shader).
   When no longer needed as part of a program object, shader objects can be detached.

   One or more executables are created in a program object by successfully attaching shader objects
   to it with glAttachShader, successfully compiling the shader objects with glCompileShader,
   and successfully linking the program object with glLinkProgram.
   These executables are made part of current state when glUseProgram is called.
   Program objects can be deleted by calling glDeleteProgram.
   The memory associated with the program object will be deleted when it is no
   longer part of current rendering state for any context.*/
bool GLSLProgram::createObject()
{
    // Create the program object
    handle = glCreateProgram();
    if (handle == 0) return false;
    else return true;
}


/* glLinkProgram links the program object specified by handle.

   A shader object of type GL_VERTEX_SHADER attached to handle is used to create
   an executable that will run on the programmable vertex processor.

   A shader object of type GL_FRAGMENT_SHADER attached to program is used to create an executable
   that will run on the programmable fragment processor.

   The status of the link operation will be stored as part of the program object's state.
   This value will be set to GL_TRUE if the program object was linked without errors and is
   ready for use, and GL_FALSE otherwise. It can be queried by calling glGetProgramiv with
   arguments handle and GL_LINK_STATUS */
bool GLSLProgram::link()
{
    if( linked ) return true;
    if( handle <= 0 ) return false;

    glLinkProgram(handle);

    int status = 0;
    glGetProgramiv( handle, GL_LINK_STATUS, &status);
    if( GL_FALSE == status ) {
        // Store log and return false
        int length = 0;
        logString = "";

        glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &length );

        if( length > 0 ) {
            char * c_log = new char[length];
            int written = 0;
            glGetProgramInfoLog(handle, length, &written, c_log);
            logString = c_log;
            delete [] c_log;
        }

        return false;
    } else {
        linked = true;
        glUseProgram( handle);
        return linked;
    }
}


/* In order to create an executable, there must be a way to specify the list of things
   that will be linked together. Program objects provide this mechanism. Shaders that are
   to be linked together in a program object must first be attached to that program object.
   glAttachShader attaches the shader object specified by shader to the program object specified
   by handle. This indicates that shader will be included in link operations that will be
   performed on handle.*/
void GLSLProgram::attachShader(GLuint shader)
{
     glAttachShader( handle, shader);
}


/* glUseProgram installs the program object specified by handle as part of current
   rendering state. Executables for each stage are created in a program object by
   successfully attaching shader objects to it with glAttachShader, successfully compiling
   the shader objects with glCompileShader, and successfully linking the program object with
   glLinkProgram.

   A program object will contain executables that will run on the vertex and fragment processors
   if it contains one shader object of type GL_VERTEX_SHADER and one shader object of type
   GL_FRAGMENT_SHADER that have both been successfully compiled and linked.*/
void GLSLProgram::use()
{
    if( handle <= 0 || (! linked) ) return;
    glUseProgram( handle );
}

// returns the logString
string GLSLProgram::log()
{
    return logString;
}

// return the program object handle
GLuint GLSLProgram::getHandle()
{
    return handle;
}

// returns the link status
bool GLSLProgram::isLinked()
{
    return linked;
}


/* glBindAttribLocation is used to associate a user-defined attribute variable in the
   program object specified by handle with a generic vertex attribute index. The name
   of the user-defined attribute variable is passed as a null terminated string in name.
   The generic vertex attribute index to be bound to this variable is specified by location.
   When handle is made part of current state, values provided via the generic vertex attribute
   index will modify the value of the user-defined attribute variable specified by name.

   This command makes it possible for vertex shaders to use descriptive names for attribute
   variables rather than generic variables that are numbered from 0 to GL_MAX_VERTEX_ATTRIBS -1 */
void GLSLProgram::bindAttribLocation( GLuint location, const char * name)
{
    glBindAttribLocation(handle, location, name);
}

/* bind a user-defined varying out variable specified by name to a fragment shader color
   number specified by location

   glBindFragDataLocation explicitly specifies the binding of the user-defined varying out variable name
   to fragment shader color number location for program handle. If name was bound previously,
   its assigned binding is replaced with location. name must be a null-terminated string.
   location must be less than GL_MAX_DRAW_BUFFERS.

   The bindings specified by glBindFragDataLocation have no effect until program is next linked.
   Bindings may be specified at any time after program has been created.
   Specifically, they may be specified before shader objects are attached to the program.
   Therefore, any name may be specified in name, including a name that is never used as a varying out variable
   in any fragment shader object. */
void GLSLProgram::bindFragDataLocation( GLuint location, const char * name )
{
    glBindFragDataLocation(handle, location, name);
}




/* glGetUniformLocation returns the location of a uniform variable specified by name
   it returns an integer that represents the location of a specific uniform variable within
   the default uniform block of a program object.

   glUniform modifies the value of a uniform variable or a uniform variable array.
   The location of the uniform variable to be modified is specified by loc, which should
   be a value returned by glGetUniformLocation. glUniform operates on the program object
   that was made part of current state by calling glUseProgram.

   val is the new value for the uniform variable */
void GLSLProgram::setUniform( const char *name, float val )
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniform1f(loc, val);
    }
}

// val is the new value for the uniform variable
void GLSLProgram::setUniform( const char *name, int val )
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniform1i(loc, val);
    }
}

// val is the new value for the uniform variable
void GLSLProgram::setUniform( const char *name, bool val )
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniform1i(loc, val);
    }
}



// x,y,z are the new values to be used for the specified uniform variable
void GLSLProgram::setUniform( const char *name, float x, float y, float z)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 ) {
        glUniform3f(loc,x,y,z);
    }
}


// v.x,v.y,v.z are the new values to be used for the specified uniform variable
void GLSLProgram::setUniform( const char *name, const vec3 & v)
{
    this->setUniform(name,v.x,v.y,v.z);
}


// v.x,v.y,v.z, v.w are the new values to be used for the specified uniform variable
void GLSLProgram::setUniform( const char *name, const vec4 & v)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 ) {
        glUniform4f(loc,v.x,v.y,v.z,v.w);
    }
}



/* The commands glUniformMatrix{2|3|4}fv are used to modify a matrix or an array of matrices.
   The numbers in the command name are interpreted as the dimensionality of the matrix.
   The number 2 indicates a 2 × 2 matrix (i.e., 4 values), the number 3 indicates a 3 × 3 matrix
   (i.e., 9 values), and the number 4 indicates a 4 × 4 matrix (i.e., 16 values).
   Each matrix is assumed to be supplied in column major order.
   The second argument indicates the number of matrices to be passed.
   A value of 1 should be used if modifying the value of a single matrix,
   and a count greater than 1 can be used to modify an array of matrices.

   loc specifies the location of the uniform value to be modified.

   1 specifies the number of matrices that are to be modified.
   This should be 1 if the targeted uniform variable is not an array of matrices,
   and 1 or more if it is an array of matrices.

   GL_FALSE specifies not to transpose the matrix as the values are loaded into the uniform variable.
   Must be GL_FALSE.

   &m[0][0] specifies a pointer to an array of 1 value that will be used to update the specified
   uniform variable. */
void GLSLProgram::setUniform( const char *name, const mat4 & m)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
    }
}

/* &m[0][0] specifies a pointer to an array of 1 value that will be used to update the
   specified uniform variable. */
void GLSLProgram::setUniform( const char *name, const mat3 & m)
{
    int loc = getUniformLocation(name);
    if( loc >= 0 )
    {
        glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
    }
}


/* glGetProgramiv returns a parameter from a program object
   handle is the program object to be queried
   the second argument specifies the object parameter
   the third argument returns the requested object parameter

   GL_ACTIVE_UNIFORM_MAX_LENGTH
   returns the length of the longest active uniform variable name for program,
   including the null termination character (i.e., the size of the character buffer
   required to store the longest uniform variable name). If no active uniform variables exist,
   0 is returned

   GL_ACTIVE_UNIFORMS
   returns the number of active uniform variables for program.

   glGetActiveUniform returns information about an active uniform variablee

   handle specifies the program object to be queried.

   i specifies the index of the uniform variable to be queried.

   maxLength specifies the maximum number of characters OpenGL is allowed to write in the character
   buffer indicated by name.

   written returns the number of characters actually written by OpenGL in the string indicated
   by name (excluding the null terminator) if a value other than NULL is passed.

   size returns the size of the uniform variable.

   type returns the data type of the attribute variable.
   one of (GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4, GL_INT, GL_INT_VEC2, GL_INT_VEC3,
   GL_INT_VEC4, GL_BOOL, GL_BOOL_VEC2, GL_BOOL_VEC3, GL_BOOL_VEC4, GL_FLOAT_MAT2, GL_FLOAT_MAT3,
   GL_FLOAT_MAT4, GL_SAMPLER_2D, or GL_SAMPLER_CUBE

   name returns a null terminated string containing the name of the attribute variable. */
void GLSLProgram::printActiveUniforms() {

    GLint nUniforms, size, location, maxLen;
    GLchar * name;
    GLsizei written;
    GLenum type;

    glGetProgramiv( handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLen);
    glGetProgramiv( handle, GL_ACTIVE_UNIFORMS, &nUniforms);

    name = (GLchar *) malloc( maxLen );

    printf(" Location | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nUniforms; ++i ) {
        glGetActiveUniform( handle, i, maxLen, &written, &size, &type, name );
        location = glGetUniformLocation(handle, name);
        printf(" %-8d | %s\n",location, name);
    }

    free(name);
}


/* glGetProgramiv returns a parameter from a program object
   handle is the program object to be queried
   the second argument specifies the object parameter
   the third argument returns the requested object parameter

   GL_ACTIVE_ATTRIBUTE_MAX_LENGTH
   the paremeter returned is the length of the longest active attribute name for handle,
   including the null termination character (i.e., the size of the character buffer required
   to store the longest attribute name). If no active attributes exist, 0 is returned.

   GL_ACTIVE_ATTRIBUTES
   the parameter retruned is the number of active attribute variables for handle

   glGetActiveAttrib returns information about an active attribute variable

   handle specifies the program object to be queried.

   i specifies the index of the attribute variable to be queried.

   maxLength specifies the maximum number of characters OpenGL is allowed to write in the
   character buffer indicated by name.

   written returns the number of characters actually written by OpenGL in the string
   indicated by name (excluding the null terminator) if a value other than NULL is passed.

   size returns the size of the attribute variable.

   type returns the data type of the attribute variable.
   one of (GL_FLOAT, GL_FLOAT_VEC2, GL_FLOAT_VEC3, GL_FLOAT_VEC4, GL_FLOAT_MAT2, GL_FLOAT_MAT3, GL_FLOAT_MAT4)

   name returns a null terminated string containing the name of the attribute variable.*/
void GLSLProgram::printActiveAttribs() {

    GLint written, size, location, maxLength, nAttribs;
    GLenum type;
    GLchar * name;

    glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxLength);
    glGetProgramiv(handle, GL_ACTIVE_ATTRIBUTES, &nAttribs);

    name = (GLchar *) malloc( maxLength );

    printf(" Index | Name\n");
    printf("------------------------------------------------\n");
    for( int i = 0; i < nAttribs; i++ ) {
        glGetActiveAttrib( handle, i, maxLength, &written, &size, &type, name );
        location = glGetAttribLocation(handle, name);
        printf(" %-5d | %s\n",location, name);
    }

    free(name);
}


/* glGetUniformLocation returns the location of a uniform variable specified by name
   it returns an integer that represents the location of a specific uniform variable
   within the default uniform block of a program object.

   handle specifies the program object to be queried name points to a null terminated
   string containing the name of the uniform variable whose location is to be queried */
int GLSLProgram::getUniformLocation(const char * name )
{
    return glGetUniformLocation(handle, name);
}

// check whether requested file exists or not
bool GLSLProgram::fileExists( const string & fileName )
{
    struct stat info;
    int ret = -1;

    ret = stat(fileName.c_str(), &info);
    return 0 == ret;
}
