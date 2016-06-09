#pragma once

#define INITIAL_POINT_NUMBER 5000


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
    void enableFillRandomColorTriangleChanged(bool &enable);
    void enableFillImageColorChanged(bool &enable);
    void enableFillVideoGrabberColorChanged(bool &enable);
    
    // delaunay
    ofxDelaunay triangulation;
    
    // mesh
    ofMesh mesh;
    
    // image
    ofImage image;
    
    // videoGrabber(webcam)
    ofVideoGrabber videoGrabber;
    
    // gui
    ofxPanel panel;
    ofParameter<bool> showDelaunayBackground;
    ofParameter<bool> showDelaunayWireframe;
    ofParameter<bool> showDelaunayVertices;
    ofParameter<bool> showDelaunayCenter;
    // draw style
    ofParameter<bool> enableFillRandomColor;
    ofParameter<bool> enableFillRandomColorTriangle;
    ofParameter<bool> enableFillImageColor;
    ofParameter<bool> enableFillVideoGrabberColor;
    
    bool showGui;
};
