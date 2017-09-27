#pragma once


#include "ofMain.h"

#include "ofxVolumeLineRenderer.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    std::shared_ptr<ofxVolumeLineRenderer> _renderer;
    ofEasyCam _cam;
    
    glm::vec3 _position;
    struct PositionHistory {
        glm::vec3 position;
        float velocity = 0.0f;
    };
    std::vector<PositionHistory> _linestrip;
    
    float _p = 10.0f;
	float _r = 28.0f;
	float _b = 2.6666f;

	ofImage _colormap;
	ofImage _radiusmap;
};
