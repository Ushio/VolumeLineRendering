//
//  Shader.hpp
//  emptyExample
//
//  Created by yoshimura on 7/22/15.
//
//

#pragma once

#include "ofMain.h"
class Shader {
public:
    Shader(GLenum program, GLenum type, const char *glsl) {
        _shader = glCreateShader(type);
        std::string buffer = ofBufferFromFile(glsl).getText();
        const char *bufferPtr = buffer.c_str();
        int bufferSize = buffer.size();
        glShaderSource(_shader, 1, &bufferPtr, &bufferSize);
        glCompileShader(_shader);
        
        GLint status = GL_FALSE;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE){
            GLsizei infoLength;
            glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &infoLength);
            if (infoLength > 1) {
                GLchar* infoBuffer = new GLchar[infoLength];
                glGetShaderInfoLog(_shader, infoLength, &infoLength, infoBuffer);
                _compileError = infoBuffer;
                delete [] infoBuffer;
            }
        }
    }
    ~Shader() {
        glDeleteShader(_shader);
    }
    bool hasError() const {
        return !_compileError.empty();
    }
    std::string getError() const {
        return _compileError;
    }
    void attach(GLenum program) {
        glAttachShader(program, _shader);
    }
private:
    Shader(const Shader&);
    void operator=(const Shader&);
    
    GLuint _shader;
    std::string _compileError;
};

inline bool shader_link(GLuint program, std::string *log) {
    glLinkProgram(program);
    
    GLint status = GL_FALSE;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        GLsizei infoLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
        if (infoLength > 1) {
            GLchar* infoBuffer = new GLchar[infoLength];
            glGetProgramInfoLog(program, infoLength, &infoLength, infoBuffer);
            *log = infoBuffer;
            delete [] infoBuffer;
            return false;
        }
    }
    return true;
}
