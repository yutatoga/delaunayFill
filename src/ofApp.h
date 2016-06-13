#pragma once

#define INITIAL_POINT_NUMBER 200
#define RADIUS_CENTER_OF_MESH 5

#include "ofMain.h"

// addons
#include "ofxDelaunay.h"
#include "ofxGui.h"
#include "ofxCv.h"

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
	
    
    // listener methods
    // - edit points
    void clearAllPointsChanged();
    void addRandomPointsChanged();
    // -- canny
    void addCannyPointsChanged();
    void cannyPointsDensityChanged(int &cannyPointsDensity);
    void cannyThreshold1Changed(float &threshold1);
    void cannyThreshold2Changed(float &threshold2);
    // - drawing style
    void enableCannyChanged(bool &enable);
    void enableFillRandomColorChanged(bool &enable);
    void enableFillRandomColorTriangleChanged(bool &enable);
    void enableFillImageColorChanged(bool &enable);
    void enableFillImageColorTriangleChanged(bool &enable);
    void enableFillVideoGrabberColorChanged(bool &enable);
    void enableFillVideoGrabberColorTriangleChanged(bool &enable);
    void enableImageChanged(bool &enable);
    void enableVideoGrabberChanged(bool &enable);
    void enableUpdateCannyForVideoGrabberChanged(bool &enable);
    
    void updateTriangles();
    void updateCanny();
    
    // delaunay
    ofxDelaunay triangulation;
    
    // mesh
    ofMesh mesh;
    
    // image
    ofImage image;
    ofImage grayImage, grayBlurImage, edgeImage;
    
    // videoGrabber(webcam)
    ofVideoGrabber videoGrabber;
    ofImage flippedImageFromVideoGrabber;
    
    // gui
    ofxPanel panel;
    ofParameter<bool> showDelaunayBackground;
    ofParameter<bool> showDelaunayWireframe;
    ofParameter<bool> showDelaunayVertices;
    ofParameter<bool> showDelaunayCenter;
    ofParameter<bool> showCannyDebugView;
    // - edit points;
    ofxButton clearAllPoints;
    ofxButton addRandomPoints;
    // -- canny
    int addCannyPointsStyle;
    ofxLabel addCannyPointsStyleLabel;
    ofxButton addCannyPoints;
    ofParameter<int> cannyPointsDensity;
    ofParameter<float> cannyThreshold1;
    ofParameter<float> cannyThreshold2;
    // - draw style
    ofParameter<bool> enableFillRandomColor;
    ofParameter<bool> enableFillRandomColorTriangle;
    ofParameter<bool> enableFillImageColor;
    ofParameter<bool> enableFillImageColorTriangle;
    ofParameter<bool> enableFillVideoGrabberColor;
    ofParameter<bool> enableFillVideoGrabberColorTriangle;

    ofParameter<bool> enableImage;
    ofParameter<bool> enableVideoGrabber;
    ofParameter<bool> enableUpdateCannyForVideoGrabber;
    
    bool showGui;
};
