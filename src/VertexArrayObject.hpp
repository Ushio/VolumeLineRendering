//
//  VertexArrayObject.hpp
//  emptyExample
//
//  Created by yoshimura on 7/6/15.
//
//

#pragma once
#include "ofMain.h"

class VertexArrayObject {
public:
    VertexArrayObject() {
        glGenVertexArrays(1, &_vao);
    }
    ~VertexArrayObject() {
        glDeleteBuffers(1, &_vao);
    }
    void bind() {
        glBindVertexArray(_vao);
    }
    void unbind() {
        glBindVertexArray(0);
    }
private:
    VertexArrayObject(const VertexArrayObject&);
    void operator=(const VertexArrayObject&);
private:
    GLuint _vao;
    
};