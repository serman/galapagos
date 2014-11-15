#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(40);
    mmenu.setup();
    franchise.loadFont("Franchise-Bold-hinted.ttf",30);
    franchiseBig.loadFont("Franchise-Bold-hinted.ttf",100);
    isla.setup();
    cam.setAutoDistance(true);
    ofxLoadCamera(cam, "ofEasyCamSettings");
    cam.move(150, 0, 0);
    
    mapping = new ofxMtlMapping2D();
    mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
    mislapuzle.setup();
  	mClient.setup();
    mClient.set("pajaros","animacion");
    //mislapuzle.cam.enableMouseInput();
    
//    ofAddListener( ofEvents().update , this, &ofEasyCam::update);
}

//--------------------------------------------------------------
void ofApp::update(){
    mmenu.update();
        isla.update();
    mapping->update();
        mislapuzle.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    mapping->bind();
    
    ofBackground (0,191,255) ;
//ISLA CO2
    ofPushMatrix();
        ofPushStyle();
        ofSetColor(255);
        isla.draw();
        franchise.drawString(ofToString(isla.islaSize/0.8) + "m^2",20,110);
        franchise.drawString("mediria una isla de 0.5m de altura",20,150);
        franchise.drawString("con el co2 emitido por X trayectos",20,190);
        franchise.drawString("diarios en un a–o",20,230);
        ofPopStyle();
    ofPopMatrix();

//PAJAROS
    mClient.draw(480, 0);

//BUQUE
    ofPushMatrix();
        ofPushStyle();
        ofTranslate(480, 520);
        
        franchiseBig.drawString("1000",20,150);
        franchise.drawString("litros petroleo",20,190);
        franchise.drawString("ahorrados",20,230);
        ofScale(0.5, 0.5);
        mmenu.draw();
        ofPopStyle();
        ofPopMatrix();
//ISLZPUZLE
    ofPushMatrix();
    ofPushStyle();
        ofTranslate(0, 480);
        ofSetColor(0,127,127);
        ofRect(0,0,islapuzle_w, islapuzle_h);

        cam.begin( ofRectangle(0,480,islapuzle_w, islapuzle_h) );
        cam.roll(  30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
        
        mislapuzle.draw();
        
        cam.roll(  -30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
        cam.end();
        ofSetColor(255);
        franchise.drawString("CLIMATIC",20,50);
        franchise.drawString("CHANGE?",20,90);
    ofPopStyle();
    ofPopMatrix();

    
    mapping->unbind();
    
    
    //-------- mapping of the towers/shapes
    mapping->draw();

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='A'){
        mmenu.start(NUCLEAR_DEBIL);
    }
    if(key=='S'){
        mmenu.start(NUCLEAR_FUERTE);
    }
    if(key=='D'){
        mmenu.start(MENU);
    }
    if(key=='F'){
        mmenu.start(GRAVEDAD);
    }
    if(key=='O'){
        isla.setSize(isla.islaSize+30);
    }
    if(key=='L'){
        isla.setSize(isla.islaSize-30);
    }
    if(key=='T'){
        isla.setSizeTon(6.8);
    }
    if(key=='s'){
        ofxSaveCamera(cam, "ofEasyCamSettings");
    }
    mislapuzle.keyPressed(key);
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
