#pragma once

#include "ofMain.h"

// addons
#include "ofxDelaunay.h"
#include "ofxGui.h"

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
		
    void enableFillRandomColorChanged(bool &enable);
    
    // delaunay
    ofxDelaunay triangulation;
    
    // gui
    ofxPanel panel;
    ofParameter<bool> showDelaunayBackground;
    ofParameter<bool> showDelaunayWireframe;
    ofParameter<bool> showDelaunayVertices;
    ofParameter<bool> showDelaunayCenter;
    ofParameter<bool> enableFillRandomColor;
    
    bool showGui;
};
