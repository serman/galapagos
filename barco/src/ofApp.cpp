#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(40);
    mmenu.setup();
    franchise.loadFont("Franchise-Bold-hinted.ttf",25);
    franchiseBig.loadFont("Franchise-Bold-hinted.ttf",65);
    isla.setup();
   // cam.setAutoDistance(true);
    ofxLoadCamera(cam, "ofEasyCamSettings");
    //cam.move(150, 0, 0);
    
    mapping = new ofxMtlMapping2D();
    mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
    mislapuzle.setup();
  	mClient.setup();
    mClient.set("pajaros","animacion");
    
    myOSCrcv=new cheapCommRcv();
    myOSCrcv->setup();
    px=100;
    py=0;
    pz=0;
    
    gui=new ofxUICanvas(1050,0,200,150);
    gui->addSlider("x", -680, 680, &px);
    gui->addSlider("y", -680, 680, &py);
    gui->addSlider("z", -680, 5080, &pz);
    nnormales=1;
    nsolares=0;
   // cam.enableMouseInput();
    
//    ofAddListener( ofEvents().update , this, &ofEasyCam::update);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle("visualizaciones fps:" + ofToString(ofGetFrameRate()));

    mmenu.update();
        isla.update();
    mapping->update();
        mislapuzle.update();

    myOSCrcv->update();
}

void ofApp::updateResult(int solar, int normal){
    nsolares=solar;
    nnormales=normal;
    cout << "update updateResult ofApp" << endl ;
}


void ofApp::start(){
    
}
void ofApp::end(){
    
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
    ofSetColor(85,98,112);
        franchise.drawString(ofToString(isla.islaSize/0.8) + "m^2",20,30);
        franchise.drawString("mediria una isla de 0.5m de altura",20,60);
        franchise.drawString("con el co2 emitido por " + ofToString(nnormales * trayectosRealesBarco) + " trayectos",20,90);

        ofPopStyle();
    ofPopMatrix();

//PAJAROS
    mClient.draw(480, 0);

//BUQUE
    ofPushMatrix();
        ofPushStyle();
        ofTranslate(480, 520);
    ofPushMatrix();
        ofScale(0.5, 0.5);
        mmenu.draw();
    ofPopMatrix();
        ofPushMatrix();
            ofTranslate(0 , 15);
        franchiseBig.drawString(ofToString(mmenu.litrosAhorrados),0,50);
        franchise.drawString("litros petroleo",0,80);
        franchise.drawString("ahorrados con",0,110);
        franchise.drawString( ofToString((nsolares*100.0)/(nnormales+nsolares) )+"% de viajes",0,140);
        franchise.drawString("solares  anuales" ,0,170);
        ofPopMatrix();
        ofPopStyle();
    ofPopMatrix();


    //marcador
    ofPushMatrix();
    ofPushStyle();
        ofTranslate(960, 480);
        franchiseBig.drawString("1000",20,150);
        franchise.drawString("litros petroleo",20,190);
        franchise.drawString("ahorrados",20,230);
    ofPopStyle();
    ofPopMatrix();

    //ISLZPUZLE
    ofPushMatrix();
    ofPushStyle();
              glEnable(GL_DEPTH_TEST);
    ofTranslate(0, 480);
    ofSetColor(0,127,127);
    //ofRect(0,0,islapuzle_w, islapuzle_h);
//    cam.dolly(dolly);
   // cout << px <<endl;
    cam.setPosition(px, py, pz);
    cam.begin( ofRectangle(0,0,islapuzle_w, islapuzle_h) );

    cam.roll(  30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
    
    mislapuzle.draw();
    
    cam.roll(  -30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
    cam.end();
   // ofSetColor(255);
   // franchise.drawString("CLIMATIC",20,50);
   // franchise.drawString("CHANGE?",20,90);
            glDisable(GL_DEPTH_TEST);
    ofPopStyle();
    ofPopMatrix();
    
    
    mapping->unbind();
    
    
    //-------- mapping of the towers/shapes
    ofSetColor(255, 255, 255, 255);
    ofFill();
    ofDisableAlphaBlending();
    mapping->draw();

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='A'){
        mmenu.start(_100);
    }
    if(key=='S'){
        mmenu.start(_80);
    }
    if(key=='D'){
        mmenu.start(_60);
    }
    if(key=='F'){
        mmenu.start(_40);
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
