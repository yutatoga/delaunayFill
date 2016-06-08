#include "ofApp.h"

void setRandomColorToTriangle(ofxDelaunay *delaunay, ofMesh *mesh){
    mesh->clear();
    ofMesh triangleMesh = delaunay->triangleMesh;
    for (int i = 0; i < delaunay->getNumTriangles(); i++) {
        // get indices
        int index1 = triangleMesh.getIndex(i*3);
        int index2 = triangleMesh.getIndex(i*3+1);
        int index3 = triangleMesh.getIndex(i*3+2);

        // add vertices
        mesh->addVertex(triangleMesh.getVertex(index1));
        mesh->addVertex(triangleMesh.getVertex(index2));
        mesh->addVertex(triangleMesh.getVertex(index3));
        
        // add colors
        ofColor randomColor(ofRandom(255), ofRandom(255), ofRandom(255), 255);
        for (int i = 0; i < 3; i++) {
            mesh->addColor(randomColor);
        }
    }
}

void setRandomColorToEachVertex(ofxDelaunay *delaunay){
    delaunay->triangleMesh.clearColors();
    for (int i = 0; i < delaunay->getNumTriangles(); i ++){
        for (int j = 0; j < 3; j++) {
            delaunay->triangleMesh.addColor(ofColor(ofRandom(30, 255), ofRandom(30, 255), ofRandom(30, 255), 255));
        }
    }
}

void setImageColorToEachVertex(ofxDelaunay *delaunay, ofMesh *mesh, ofImage *image){
    mesh->clear();
    ofMesh triangleMesh = delaunay->triangleMesh;
    for (int i = 0; i < delaunay->getNumTriangles(); i++) {
        // get indices
        int index1 = triangleMesh.getIndex(i*3);
        int index2 = triangleMesh.getIndex(i*3+1);
        int index3 = triangleMesh.getIndex(i*3+2);
        
        // add vertices
        mesh->addVertex(triangleMesh.getVertex(index1));
        mesh->addVertex(triangleMesh.getVertex(index2));
        mesh->addVertex(triangleMesh.getVertex(index3));
        
        // add colors
        mesh->addColor(image->getColor(triangleMesh.getVertex(index1).x, triangleMesh.getVertex(index1).y));
        mesh->addColor(image->getColor(triangleMesh.getVertex(index2).x, triangleMesh.getVertex(index2).y));
        mesh->addColor(image->getColor(triangleMesh.getVertex(index3).x, triangleMesh.getVertex(index3).y));
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    
    // add random 5 points
    for (int i = 0; i < 5000; i++) {
        ofPoint instantPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        
        // delaunay
        triangulation.addPoint(instantPoint);
    }
    
    // delaunay
    triangulation.triangulate();
    
    // image
    image.load("Lenna.png");
    image.resize(ofGetWidth(), ofGetHeight());
    
    // listener
    enableFillRandomColor.addListener(this, &ofApp::enableFillRandomColorChanged);
    enableFillRandomColorTriangle.addListener(this, &ofApp::enableFillRandomColorTriangleChanged);
    enableFillImageColor.addListener(this, &ofApp::enableFillImageColorChanged);
    
    // gui
    panel.setup();
    panel.add(showDelaunayBackground.set("showDelaunayBackground", true));
    panel.add(showDelaunayWireframe.set("showDelaunayWireframe", true));
    panel.add(showDelaunayVertices.set("showDelaunayVertices", true));
    panel.add(showDelaunayCenter.set("showDelaunayCenter", true));
    panel.add(enableFillRandomColor.set("enableFillRandomColor", false));
    panel.add(enableFillRandomColorTriangle.set("enableFillRandomColorTriangle", false));
    panel.add(enableFillImageColor.set("enableFillImageColor", false));
        
    showGui = true;
}

void ofApp::enableFillRandomColorChanged(bool &enable){
    if (enable) {
        // disable other draw styles
        enableFillRandomColorTriangle = false;
        enableFillImageColor = false;
        
        setRandomColorToEachVertex(&triangulation);
    }else {
        triangulation.triangleMesh.clearColors();
    }
}

void ofApp::enableFillRandomColorTriangleChanged(bool &enable){
    if (enable) {
        // disable other draw styles
        enableFillRandomColor = false;
        enableFillImageColor = false;
        
        setRandomColorToTriangle(&triangulation, &mesh);
    }else {
        mesh.clear();
    }
}

void ofApp::enableFillImageColorChanged(bool &enable){
    if (enable) {
        // disable other draw styles
        enableFillRandomColorTriangle = false;
        enableFillRandomColor = false;

        setImageColorToEachVertex(&triangulation, &mesh, &image);
    } else {
        mesh.clear();
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw the background of triangles
    if (enableFillRandomColorTriangle || enableFillImageColor) {
        // draw mesh
        mesh.draw();
    } else {
        if (showDelaunayBackground) {
            ofSetColor(0, 0, 127);
            ofFill();
            triangulation.draw();
            ofSetColor(255);
        }
    }
    
    // draw wire frame of triangles
    if (showDelaunayWireframe) {
        ofNoFill();
        ofSetColor(255);
        triangulation.draw();
        ofFill();
    }
    
    // draw vertices of triangles
    if (showDelaunayVertices) {
        ofFill();
        glPointSize(10.0);
        ofSetColor(255, 0, 0, 255);
        ofMesh mesh = triangulation.triangleMesh;
        mesh.setMode(OF_PRIMITIVE_POINTS);
        mesh.draw();
        glPointSize(1.0);
        ofSetColor(255);
    }
    
    // draw centers of the mesh
    if (showDelaunayCenter) {
        ofSetColor(0, 255, 0, 255);
        for (int i = 0; i < triangulation.getNumTriangles(); i++) {
            int index1 = triangulation.triangleMesh.getIndex(i*3);
            int index2 = triangulation.triangleMesh.getIndex(i*3+1);
            int index3 = triangulation.triangleMesh.getIndex(i*3+2);
            
            ofVec3f vertex1 = triangulation.triangleMesh.getVertex(index1);
            ofVec3f vertex2 = triangulation.triangleMesh.getVertex(index2);
            ofVec3f vertex3 = triangulation.triangleMesh.getVertex(index3);
            
            ofVec3f center = (vertex1+vertex2+vertex3)/3.0;
            
            ofDrawCircle(center, 5);
        }
        ofSetColor(255);
    }
    
    // gui
    if (showGui) panel.draw();
    
    // debug
    ofDrawBitmapString("'r' to reset", ofPoint(10,20));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
            triangulation.reset();
            mesh.clear();
            break;
        case 'h':
            showGui = !showGui;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // update delaunay
    triangulation.addPoint(ofPoint(x, y));
    triangulation.triangulate();
    if (enableFillRandomColor) setRandomColorToEachVertex(&triangulation);
    if (enableFillRandomColorTriangle) setRandomColorToTriangle(&triangulation, &mesh);
    if (enableFillImageColor) setImageColorToEachVertex(&triangulation, &mesh, &image);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
