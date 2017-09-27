#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.glVersionMajor = 4;
    settings.glVersionMinor = 1;
    settings.width = 1024;
    settings.height = 768;
    settings.windowMode = OF_WINDOW;
    ofCreateWindow(settings);
    
    ofRunApp(new ofApp());
}
