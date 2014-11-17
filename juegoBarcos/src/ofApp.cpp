#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    mapa.loadImage("mapa.png");
    mbarcos.setup();
    mtracking.setup();
    gui=new ofxUICanvas(1150,0,200,150);
    gui->addSlider("threshold", 180, 255, &(mtracking.threshold));
    ofSetVerticalSync(true);
   // openCameras();
    helvetica1.loadFont("Helvetica-Bold.otf", 11);
    
    cheapComm *myComm;
    myComm=cheapComm::getInstance();
    myComm->setup();
    gameStatus=JUGANDO;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle("juego barco. fps:" + ofToString(ofGetFrameRate()));
    if(gameStatus==JUGANDO){
        mbarcos.update();
       // mbarcos.checkColision((int)mtracking.loc.x,(int)mtracking.loc.y);
        mtracking.update();
        mtracking.checkCollisions(mbarcos.barcos);
        if(ofGetFrameNum()%5)
            cheapComm::getInstance()->sendMarcador(mbarcos.nbarcoSolar, mbarcos.nbarcoNormal);
        
        if(mbarcos.nbarcoSolar+ mbarcos.nbarcoNormal>TOTAL_BARCOS ){
            gameStatus=FIN;
            timeChangeStatus=ofGetElapsedTimeMillis()+2000;
            cheapComm::getInstance()->sendEnd();
        }
    }else if(gameStatus==FIN){
        helvetica1.drawString("JUEGO TERMINADO",400,300);
        if(ofGetElapsedTimeMillis()>timeChangeStatus)
            gameStatus=SINJUGADOR;
    }else if(gameStatus==SINJUGADOR){
        //TODO
        gameStatus=JUGANDO;
        cheapComm::getInstance()->sendStart();
    }
    
    
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    if(gameStatus==JUGANDO){
        mapa.draw(0,0,1024,768);
        mbarcos.draw();
        mtracking.drawMatrixVideo();
        mtracking.draw();
        drawMarcador();
    } else if(gameStatus==FIN){
        helvetica1.drawString("JUEGO TERMINADO",400,300);
    }
    

}

void ofApp::drawMarcador(){
    helvetica1.drawString("barcos solares:" + ofToString(mbarcos.nbarcoSolar), 300, 40);
    helvetica1.drawString("barcos convencionales" + ofToString(mbarcos.nbarcoNormal), 500, 40);
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
