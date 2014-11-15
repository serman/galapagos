#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    mapa.loadImage("mapa.png");
    mbarcos.setup();
    mtracking.setup();
    gui=new ofxUICanvas(0,0,300,300);
    gui->addSlider("threshold", 240, 255, &(mtracking.threshold));
}

//--------------------------------------------------------------
void ofApp::update(){
    mbarcos.update();
    mbarcos.checkColision((int)mtracking.loc.x,(int)mtracking.loc.y);
    mtracking.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    mapa.draw(0,0,1024,768);
    mtracking.draw();
    mbarcos.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
