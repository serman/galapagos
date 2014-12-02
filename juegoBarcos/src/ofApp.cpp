#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(25);
    mapa.loadImage("mapa.png");
    creditos.loadImage("creditos.png");
    intro.loadImage("intro.png");
    mbarcos.setup();
    mtracking.setup();
    gui=new ofxUICanvas(0,0,200,150);
    gui->addSlider("threshold", 1, 255, &(mtracking.threshold));
        gui->addSlider("min Rad", 1, 50, &(mtracking.minRadius));
        gui->addSlider("max Rad", 10, 200, &(mtracking.maxRadius));
    ofSetVerticalSync(true);
   // openCameras();
    helvetica1.loadFont("Helvetica-Bold.otf", 11,true,true);
        helvetica1.setEncoding(OF_ENCODING_UTF8);
    letraGrande.loadFont("GOTHMBCD.TTF",30,true,true);
        letraGrande.setEncoding(OF_ENCODING_UTF8);
    cheapComm *myComm;
    myComm=cheapComm::getInstance();
    myComm->setup();
    gameStatus=JUGANDO;
    myComm->sendStart();
    loadSettings();
    gui->disable();
}

//--------------------------------------------------------------
void ofApp::update(){
    //ofSetWindowTitle("juego barco. fps:" + ofToString(ofGetFrameRate()));
    if(gameStatus==JUGANDO){
        mbarcos.update();
       // mbarcos.checkColision((int)mtracking.loc.x,(int)mtracking.loc.y);
        mtracking.update();
        mtracking.checkCollisions(mbarcos.barcos);
        if(ofGetFrameNum()%5)
            cheapComm::getInstance()->sendMarcador(mbarcos.nbarcoSolar, mbarcos.nbarcoNormal);
        
        if(mbarcos.nbarcoSolar+ mbarcos.nbarcoNormal>TOTAL_BARCOS ){
            gameStatus=FIN;
            timeChangeStatus=ofGetElapsedTimeMillis()+18000;
            cheapComm::getInstance()->sendEnd();
        }
    }else if(gameStatus==FIN){
        /*helvetica1.drawString("JUEGO TERMINADO",0,300);
        helvetica1.drawString("Proyecto desarrollado con alumnos de bellas artes de la U.C. del ecuador",0,350);
        helvetica1.drawString("Dario Rafael Puco Zapata,Santiago Cárdenas Haro,Paola Arévalo Moncayo,\n Luis Alberto Zabala Vaca,Diana Clavijo",0,400);
        helvetica1.drawString("Programación: Sergio Galán. Coordinación Beatriz Rivela (Iner) ",0,500);
//        helvetica1.drawString("Darío Rafael Puco Zapata",400,400);*/        
        if(ofGetElapsedTimeMillis()>timeChangeStatus){
            gameStatus=SINJUGADOR;
            cheapComm::getInstance()->sendStartWait();
            timeChangeStatus=ofGetElapsedTimeMillis()+3000;
        }
    }else if(gameStatus==SINJUGADOR  ){
        //TODO

        mtracking.update();
        if(mtracking.checkPointers()==true && ofGetElapsedTimeMillis()>timeChangeStatus){
            restart();
            cheapComm::getInstance()->sendStart();
            gameStatus=JUGANDO;
        }
        


        
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
        //mtracking.drawMatrixVideo();
        mtracking.draw();
        drawMarcador();
    } else if(gameStatus==FIN){
//        helvetica1.drawString("JUEGO TERMINADO",400,300);
        ofSetColor(255);
        creditos.draw(0, 0);
        ofTranslate(288,255);
        ofSetHexColor(0x4ECDC4);
        helvetica1.drawString("PUNTUACIÓN", 0, 0);
        letraGrande.drawString("Trayectos de barcaza solar: " + ofToString(mbarcos.nbarcoSolar*ratioBarcosReales) +" ("+
                              ofToString(mbarcos.nbarcoSolar)+")",0,40);
        
        letraGrande.drawString("Trayectos de barcaza diesel: "+ ofToString(mbarcos.nbarcoNormal*ratioBarcosReales) +" ("+
                              ofToString(mbarcos.nbarcoNormal)+")",0,90);
        
        
    }
    else if(gameStatus==SINJUGADOR){
        ofSetColor(255);
        intro.draw(0,0);
        
        mtracking.draw();
    }
    

}

void ofApp::drawMarcador(){
    ofSetColor(150);
    helvetica1.drawString("Trayectos en barcazas solares", 150, 40);
    letraGrande.drawString(ofToString(mbarcos.nbarcoSolar*ratioBarcosReales), 450, 45);
    
    helvetica1.drawString("Trayectos en barcazas convencionales", 650, 40);
    letraGrande.drawString(ofToString(mbarcos.nbarcoNormal*ratioBarcosReales), 550, 45);

    letraGrande.drawString("Día " + ofToString(round(( mbarcos.nbarcoNormal + mbarcos.nbarcoSolar ) * DIAS_BARCO)) + " de 365", 50, 750);
    helvetica1.drawString("1 trayecto del juego son " + ofToString(ratioBarcosReales)  + " trayectos reales", 600, 750);
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
    if(key== 's'){
        saveSettings();
        gui->saveSettings("gui_settings.xml");
    }
    if(key=='r'){
        mbarcos.nbarcoSolar=TOTAL_BARCOS    ;
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
    mtracking.boxInputMatrix.adjustHandle(x, y);
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

void ofApp::loadSettings() {
    
    gui->loadSettings("gui_settings.xml");
    if( XML.loadFile("mySettings.xml") ){
        //message = "mySettings.xml loaded!";
        
        mtracking.boxInputMatrix.setTopLeftX(XML.getValue("CAPTUREREGION:r11:X", 0));
        mtracking.boxInputMatrix.setTopLeftY(XML.getValue("CAPTUREREGION:r11:Y", 0));
        
        mtracking.boxInputMatrix.setBottomLeftX(XML.getValue("CAPTUREREGION:r12:X", 0));
        mtracking.boxInputMatrix.setBottomLeftY(XML.getValue("CAPTUREREGION:r12:Y", imgWidth));
        
        mtracking.boxInputMatrix.setTopRightX(XML.getValue("CAPTUREREGION:r21:X", 0));
        mtracking.boxInputMatrix.setTopRightY(XML.getValue("CAPTUREREGION:r21:Y", imgHeight));
        
        mtracking.boxInputMatrix.setBottomRightX(XML.getValue("CAPTUREREGION:r22:X", imgWidth));
        mtracking.boxInputMatrix.setBottomRightY(XML.getValue("CAPTUREREGION:r22:Y", imgHeight));        
        
    }else{
        
        //message = "unable to load mySettings.xml check data/ folder";
    }
    
    
}

void ofApp::saveSettings() {
	
	XML.clear();
	XML.setValue("CAPTUREREGION:r11:X", mtracking.boxInputMatrix.getTopLeftX());
	XML.setValue("CAPTUREREGION:r11:Y", mtracking.boxInputMatrix.getTopLeftY());
	
	XML.setValue("CAPTUREREGION:r12:X", mtracking.boxInputMatrix.getBottomLeftX());
	XML.setValue("CAPTUREREGION:r12:Y", mtracking.boxInputMatrix.getBottomLeftY());
	
	XML.setValue("CAPTUREREGION:r21:X", mtracking.boxInputMatrix.getTopRightX());
	XML.setValue("CAPTUREREGION:r21:Y", mtracking.boxInputMatrix.getTopRightY());
	
	XML.setValue("CAPTUREREGION:r22:X", mtracking.boxInputMatrix.getBottomRightX());
	XML.setValue("CAPTUREREGION:r22:Y", mtracking.boxInputMatrix.getBottomRightY());
	   
	XML.saveFile("mySettings.xml");
	
}
