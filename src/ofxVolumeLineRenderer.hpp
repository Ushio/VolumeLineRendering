//
//  ofxVolumeLineRenderer.hpp
//  VolumeLine
//
//  Created by Nakazi_w0w on 2015/10/28.
//
//

#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ofMain.h"

#include "VertexArrayObject.hpp"

class ofxVolumeLineRenderer {
public:
    ofxVolumeLineRenderer();
    ~ofxVolumeLineRenderer();
    
    ofxVolumeLineRenderer(const ofxVolumeLineRenderer&) = delete;
    void operator=(const ofxVolumeLineRenderer&) = delete;
    
    struct LinePoint {
        glm::vec3 position;
        float radius = 0.06f;
    };
    
    void reserve(int linePointCount);
    
	LinePoint *map(int linePointCount);
	void unmap();
    
    void draw(const glm::mat4& vmat, const glm::mat4& pmat, bool cullingFlip, GLuint colorTexture2dWithOutArb, GLuint radiusTexture2dWithOutArb);
private:
	ofBufferObject _vbo;
	int _drawLinePointCount = 0;
    GLuint _shader;
    std::shared_ptr<VertexArrayObject> _vao;
};
