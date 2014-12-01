#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(25);
    mapa.loadImage("mapa.png");
    creditos.loadImage("creditos.png");
    mbarcos.setup();
    mtracking.setup();
    gui=new ofxUICanvas(0,0,200,150);
    gui->addSlider("threshold", 1, 255, &(mtracking.threshold));
        gui->addSlider("min Rad", 1, 50, &(mtracking.minRadius));
        gui->addSlider("max Rad", 10, 200, &(mtracking.maxRadius));
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
            timeChangeStatus=ofGetElapsedTimeMillis()+10000;
            cheapComm::getInstance()->sendEnd();
        }
    }else if(gameStatus==FIN){
        /*helvetica1.drawString("JUEGO TERMINADO",0,300);
        helvetica1.drawString("Proyecto desarrollado con alumnos de bellas artes de la U.C. del ecuador",0,350);
        helvetica1.drawString("Dario Rafael Puco Zapata,Santiago C‡rdenas Haro,Paola ArŽvalo Moncayo,\n Luis Alberto Zabala Vaca,Diana Clavijo",0,400);
        helvetica1.drawString("Programaci—n: Sergio Gal‡n. Coordinaci—n Beatriz Rivela (Iner) ",0,500);
//        helvetica1.drawString("Dar’o Rafael Puco Zapata",400,400);*/        
        if(ofGetElapsedTimeMillis()>timeChangeStatus){
            gameStatus=SINJUGADOR;
            cheapComm::getInstance()->sendStartWait();
        }
    }else if(gameStatus==SINJUGADOR){
        //TODO

        restart();
        cheapComm::getInstance()->sendStart();
    }
}
void ofApp::restart(){
    mbarcos.nbarcoSolar=0;
    mbarcos.nbarcoNormal=0;
    gameStatus=JUGANDO;
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
//        helvetica1.drawString("JUEGO TERMINADO",400,300);
        creditos.draw(0, 0);
    }
    

}

void ofApp::drawMarcador(){
    helvetica1.drawString("barcos solares:" + ofToString(mbarcos.nbarcoSolar), 300, 40);
    helvetica1.drawString("barcos convencionales" + ofToString(mbarcos.nbarcoNormal), 500, 40);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
		mtracking.background.reset();
	}
    if(key== 'd'){
        mtracking.bdrawDebug=!mtracking.bdrawDebug;
    }
    if(key== 'g'){
        if(gui->isEnabled()) gui->disable();
        else gui->enable();
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
