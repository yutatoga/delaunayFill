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

void setImageColorToTriangle(ofxDelaunay *delaunay, ofMesh *mesh, ofImage *image){
    mesh->clear();
    ofMesh triangleMesh = delaunay->triangleMesh;
    for (int i = 0; i < delaunay->getNumTriangles(); i++) {
        // get indices
        int index1 = triangleMesh.getIndex(i*3);
        int index2 = triangleMesh.getIndex(i*3+1);
        int index3 = triangleMesh.getIndex(i*3+2);
        
        // add vertices
        ofVec3f vertex1 = triangleMesh.getVertex(index1);
        ofVec3f vertex2 = triangleMesh.getVertex(index2);
        ofVec3f vertex3 = triangleMesh.getVertex(index3);
        mesh->addVertex(vertex1);
        mesh->addVertex(vertex2);
        mesh->addVertex(vertex3);
        
        // add colors
        ofVec3f centerOfTriangle = (vertex1+vertex2+vertex3)/3.0f;
        ofColor centralColor = image->getColor(centerOfTriangle.x, centerOfTriangle.y);
        for (int i = 0; i < 3; i++) {
            mesh->addColor(centralColor);
        }
    }
}

void setVideoGrabberColorToTriangle(ofxDelaunay *delaunay, ofMesh *mesh, ofVideoGrabber *videoGrabber){
    mesh->clear();
    ofMesh triangleMesh = delaunay->triangleMesh;
    // ofImage from ofVideoGrabber
    ofImage image;
    ofxCv::copy(*videoGrabber, image);
    ofImage flippedImage;
    ofxCv::flip(image, flippedImage, 1);
    for (int i = 0; i < delaunay->getNumTriangles(); i++) {
        // get indices
        int index1 = triangleMesh.getIndex(i*3);
        int index2 = triangleMesh.getIndex(i*3+1);
        int index3 = triangleMesh.getIndex(i*3+2);
        
        // add vertices
        ofVec3f vertex1 = triangleMesh.getVertex(index1);
        ofVec3f vertex2 = triangleMesh.getVertex(index2);
        ofVec3f vertex3 = triangleMesh.getVertex(index3);
        mesh->addVertex(vertex1);
        mesh->addVertex(vertex2);
        mesh->addVertex(vertex3);
        
        // add colors
        ofVec3f centerOfTriangle = (vertex1+vertex2+vertex3)/3.0f;
        ofColor centralColor = flippedImage.getColor(centerOfTriangle.x, centerOfTriangle.y);
        for (int i = 0; i < 3; i++) {
            mesh->addColor(centralColor);
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

void setVideoGrabberColorToEachVertex(ofxDelaunay *delaunay, ofMesh *mesh, ofVideoGrabber *videoGrabber){
    mesh->clear();
    ofMesh triangleMesh = delaunay->triangleMesh;
    // ofImage from ofVideoGrabber
    ofImage image;
    ofxCv::copy(*videoGrabber, image);
    ofImage flippedImage;
    ofxCv::flip(image, flippedImage, 1);
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
        mesh->addColor(flippedImage.getColor(triangleMesh.getVertex(index1).x, triangleMesh.getVertex(index1).y));
        mesh->addColor(flippedImage.getColor(triangleMesh.getVertex(index2).x, triangleMesh.getVertex(index2).y));
        mesh->addColor(flippedImage.getColor(triangleMesh.getVertex(index3).x, triangleMesh.getVertex(index3).y));
    }
}

void ofApp::updateTriangles(){
    triangulation.triangulate();
    if (enableFillRandomColor) setRandomColorToEachVertex(&triangulation);
    if (enableFillRandomColorTriangle) setRandomColorToTriangle(&triangulation, &mesh);
    if (enableFillImageColor) setImageColorToEachVertex(&triangulation, &mesh, &image);
    if (enableFillImageColorTriangle) setImageColorToTriangle(&triangulation, &mesh, &image);
    if (enableFillVideoGrabberColor) setVideoGrabberColorToEachVertex(&triangulation, &mesh, &videoGrabber);
    if (enableFillVideoGrabberColorTriangle) setVideoGrabberColorToTriangle(&triangulation, &mesh, &videoGrabber);
}

void ofApp::updateCanny(){
    if (enableVideoGrabber) {
        // use videoGrabber
        ofxCv::convertColor(flippedImageFromVideoGrabber, grayImage, CV_RGB2GRAY);
    } else {
        // use image data
        ofxCv::convertColor(image, grayImage, CV_RGB2GRAY);
    }
    ofxCv::GaussianBlur(grayImage, grayBlurImage, 16);
    ofxCv::Canny(grayBlurImage, edgeImage, cannyThreshold1, cannyThreshold2);
    
    ofxCv::dilate(edgeImage);
    
    grayImage.update();
    grayBlurImage.update();
    edgeImage.update();
}

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableSmoothing();
    ofBackground(0);
    
    // add some(INITIAL_POINT_NUMBER) random points
    for (int i = 0; i < INITIAL_POINT_NUMBER; i++) {
        ofPoint instantPoint(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()));
        
        // delaunay
        triangulation.addPoint(instantPoint);
    }
    
    // delaunay
    triangulation.triangulate();
    
    // image
    image.load("Lenna.png");
    image.resize(ofGetWidth(), ofGetHeight());
    
    // videoGrabber
    videoGrabber.setDeviceID(0);
    videoGrabber.initGrabber(ofGetWidth(), ofGetHeight());
    
    // listener
    // - edit points
    clearAllPoints.addListener(this, &ofApp::clearAllPointsChanged);
    addRandomPoints.addListener(this, &ofApp::addRandomPointsChanged);
    // -- canny
    addCannyPoints.addListener(this, &ofApp::addCannyPointsChanged);
    cannyThreshold1.addListener(this, &ofApp::cannyThreshold1Changed);
    cannyThreshold2.addListener(this, &ofApp::cannyThreshold2Changed);
    // - video grabber
    enableImage.addListener(this, &ofApp::enableImageChanged);
    enableVideoGrabber.addListener(this, &ofApp::enableVideoGrabberChanged);
    enableUpdateCannyForVideoGrabber.addListener(this, &ofApp::enableUpdateCannyForVideoGrabberChanged);
    // - drawing style
    enableFillRandomColor.addListener(this, &ofApp::enableFillRandomColorChanged);
    enableFillRandomColorTriangle.addListener(this, &ofApp::enableFillRandomColorTriangleChanged);
    enableFillImageColor.addListener(this, &ofApp::enableFillImageColorChanged);
    enableFillImageColorTriangle.addListener(this, &ofApp::enableFillImageColorTriangleChanged);
    enableFillVideoGrabberColor.addListener(this, &ofApp::enableFillVideoGrabberColorChanged);
    enableFillVideoGrabberColorTriangle.addListener(this, &ofApp::enableFillVideoGrabberColorTriangleChanged);
    
    // gui
    panel.setup();
    // - enable/disable to show
    panel.add(showDelaunayBackground.set("showDelaunayBackground", true));
    panel.add(showDelaunayWireframe.set("showDelaunayWireframe", true));
    panel.add(showDelaunayVertices.set("showDelaunayVertices", true));
    panel.add(showDelaunayCenter.set("showDelaunayCenter", true));
    panel.add(showCannyDebugView.set("showCannyDebugView", true));
    // - edit points
    panel.add(clearAllPoints.setup("clearAllPoints"));
    panel.add(addRandomPoints.setup("addRandomPoints"));
    // -- canny
    panel.add(addCannyPoints.setup("addCannyPoints"));
    panel.add(cannyThreshold1.set("cannyThreshold1", 0, 0, 256));
    panel.add(cannyThreshold2.set("cannyThreshold1", 30, 0, 256));
    // - select dawing style
    panel.add(enableFillRandomColor.set("enableFillRandomColor", false));
    panel.add(enableFillRandomColorTriangle.set("enableFillRandomColorTriangle", false));
    panel.add(enableFillImageColor.set("enableFillImageColor", false));
    panel.add(enableFillImageColorTriangle.set("enableFillImageColorTriangle", false));
    panel.add(enableFillVideoGrabberColor.set("enableFillVideoGrabberColor", false));
    panel.add(enableFillVideoGrabberColorTriangle.set("enableFillVideoGrabberColorTriangle", false));
    panel.add(enableImage.set("enableImage", true));
    panel.add(enableVideoGrabber.set("enableVideoGrabber", false));
    panel.add(enableUpdateCannyForVideoGrabber.set("enableRealtimeVideoGrabber", false));
    
    showGui = true;
}

void ofApp::clearAllPointsChanged(){
    triangulation.reset();
    mesh.clear();
}

void ofApp::addRandomPointsChanged(){
    // add some(INITIAL_POINT_NUMBER) random points
    float width = enableVideoGrabber ? videoGrabber.getWidth() : image.getWidth();
    float height = enableVideoGrabber ?  videoGrabber.getHeight() : image.getHeight();
    for (int i = 0; i < INITIAL_POINT_NUMBER; i++) {
        ofPoint instantPoint(ofRandom(0, width), ofRandom(0, height));
        
        // delaunay
        triangulation.addPoint(instantPoint);
    }

    updateTriangles();
}

void ofApp::addCannyPointsChanged(){
    updateCanny();
    
    ofPixels edgePixels = edgeImage.getPixels();
    unsigned char *edgeData = edgePixels.getData();
    int const step = 5;
    float width = enableVideoGrabber ? videoGrabber.getWidth() : image.getWidth();
    float height = enableVideoGrabber ?  videoGrabber.getHeight() : image.getHeight();
    // add points on the edge
    for (int i = 0; i < (int)edgePixels.size(); i += step) {
        if (edgeData[i] != 0) {
            // this pixel is on the edge
            ofPoint edgePoint(i%(int)width, floor(i/width));
            
            // delaunay
            triangulation.addPoint(edgePoint);
        }
    }
    // add corner points
    triangulation.addPoint(ofPoint(0, 0));
    triangulation.addPoint(ofPoint(0, height));
    triangulation.addPoint(ofPoint(width, height));
    triangulation.addPoint(ofPoint(width, 0));
    
    updateTriangles();
}

void ofApp::cannyThreshold1Changed(float &threshold1){
    updateCanny();
}

void ofApp::cannyThreshold2Changed(float &threshold2){
    updateCanny();
}

void ofApp::enableFillRandomColorChanged(bool &enable){
    if (enable) {
        // disable other draw styles
        enableFillRandomColorTriangle = false;
        enableFillImageColor = false;
        enableFillImageColorTriangle = false;
        enableFillVideoGrabberColor = false;
        enableFillVideoGrabberColorTriangle = false;
        
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
        enableFillImageColorTriangle = false;
        enableFillVideoGrabberColor = false;
        enableFillVideoGrabberColorTriangle = false;
        
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
        enableFillImageColorTriangle = false;
        enableFillVideoGrabberColor = false;
        enableFillVideoGrabberColorTriangle = false;
        
        setImageColorToEachVertex(&triangulation, &mesh, &image);
    } else {
        mesh.clear();
    }
}

void ofApp::enableFillImageColorTriangleChanged(bool &enable){
    if (enable) {
        // disable other draw styles
        enableFillRandomColor = false;
        enableFillRandomColorTriangle = false;
        enableFillImageColor = false;
        enableFillVideoGrabberColor = false;
        enableFillVideoGrabberColorTriangle = false;
        
        setImageColorToTriangle(&triangulation, &mesh, &image);
    } else {
        mesh.clear();
    }
}

void ofApp::enableFillVideoGrabberColorChanged(bool &enable){
    if (enable) {
        if (!enableVideoGrabber) enableVideoGrabber = true;
        // disable other draw styles
        enableFillRandomColor = false;
        enableFillRandomColorTriangle = false;
        enableFillImageColor = false;
        enableFillImageColorTriangle = false;
        enableFillVideoGrabberColorTriangle = false;
        
        setVideoGrabberColorToEachVertex(&triangulation, &mesh, &videoGrabber);
    } else {
        mesh.clear();
    }
}

void ofApp::enableFillVideoGrabberColorTriangleChanged(bool &enable){
    if (enable) {
        if (!enableVideoGrabber) enableVideoGrabber = true;
        // disable other draw styles
        enableFillRandomColor = false;
        enableFillRandomColorTriangle = false;
        enableFillImageColor = false;
        enableFillImageColorTriangle = false;
        enableFillVideoGrabberColor = false;
        
        setVideoGrabberColorToTriangle(&triangulation, &mesh, &videoGrabber);
    } else {
        mesh.clear();
    }
}

void ofApp::enableImageChanged(bool &enable){
    // disable enableVideoGrabber
    if (enable) {
        enableVideoGrabber = false;
        if (videoGrabber.isInitialized()) {
            videoGrabber.close();
        }
        updateCanny();
    } else {
    // enable enableVideoGrabber
        enableVideoGrabber = true;
    }
}

void ofApp::enableVideoGrabberChanged(bool &enable){
    if (enable) {
        // disable enableImage
        enableImage = false;
        if (!videoGrabber.isInitialized()) {
            videoGrabber.setDeviceID(0);
            videoGrabber.setDesiredFrameRate(60);
            videoGrabber.initGrabber(ofGetWidth(), ofGetHeight());
            ofImage imageFromVideoGrabber;
            ofxCv::copy(videoGrabber, imageFromVideoGrabber);
            ofxCv::flip(imageFromVideoGrabber, flippedImageFromVideoGrabber, 1);
            flippedImageFromVideoGrabber.update();
            updateCanny();
        }
    } else {
        // enable enableImage
         enableImage = true;
    }
}

void ofApp::enableUpdateCannyForVideoGrabberChanged(bool &enable){
    if (enable) {
        if (!enableVideoGrabber) enableVideoGrabber = true;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    // debug
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
    
    // update videograbber
    if (videoGrabber.isInitialized()) {
        videoGrabber.update();
        ofImage imageFromVideoGrabber;
        ofxCv::copy(videoGrabber, imageFromVideoGrabber);
        ofxCv::flip(imageFromVideoGrabber, flippedImageFromVideoGrabber, 1);
        flippedImageFromVideoGrabber.update();
        if (enableUpdateCannyForVideoGrabber) {
            // reset all points
            clearAllPointsChanged();
            // add canny points
            addCannyPointsChanged();
        } else {
            updateCanny();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw the background of triangles
    if (enableFillRandomColorTriangle || enableFillImageColor || enableFillImageColorTriangle || enableFillVideoGrabberColor || enableFillVideoGrabberColorTriangle) {
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
            
            ofDrawCircle(center, RADIUS_CENTER_OF_MESH);
        }
        ofSetColor(255);
    }
    
    // gui
    if (showGui) panel.draw();
    
    // debug
    if (showCannyDebugView) {
        ofVec2f cannyDebugViewSize(ofGetWidth()/4.0f, ofGetHeight()/4.0f);
        if (enableVideoGrabber) {
            flippedImageFromVideoGrabber.draw(ofGetWidth()-2*cannyDebugViewSize.x, 0, cannyDebugViewSize.x, cannyDebugViewSize.y);
        } else {
            image.draw(ofGetWidth()-2*cannyDebugViewSize.x, 0, cannyDebugViewSize.x, cannyDebugViewSize.y);
        }
        grayImage.draw(ofGetWidth()-cannyDebugViewSize.x, 0, cannyDebugViewSize.x, cannyDebugViewSize.y);
        grayBlurImage.draw(ofGetWidth()-2*cannyDebugViewSize.x, cannyDebugViewSize.y, cannyDebugViewSize.x, cannyDebugViewSize.y);
        edgeImage.draw(ofGetWidth()-cannyDebugViewSize.x, cannyDebugViewSize.y, cannyDebugViewSize.x, cannyDebugViewSize.y);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
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
    
    updateTriangles();
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
