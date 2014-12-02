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
    helvetica1.loadFont("Helvetica-Bold.otf", 11,true,true);
    letraGrande.loadFont("GOTHMBCD.TTF",30,true,true);
    
    cheapComm *myComm;
    myComm=cheapComm::getInstance();
    myComm->setup();
    gameStatus=JUGANDO;
    loadSettings();
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
            timeChangeStatus=ofGetElapsedTimeMillis()+10000;
            cheapComm::getInstance()->sendEnd();
        }
    }else if(gameStatus==FIN){
        /*helvetica1.drawString("JUEGO TERMINADO",0,300);
        helvetica1.drawString("Proyecto desarrollado con alumnos de bellas artes de la U.C. del ecuador",0,350);
        helvetica1.drawString("Dario Rafael Puco Zapata,Santiago C�rdenas Haro,Paola Ar�valo Moncayo,\n Luis Alberto Zabala Vaca,Diana Clavijo",0,400);
        helvetica1.drawString("Programaci�n: Sergio Gal�n. Coordinaci�n Beatriz Rivela (Iner) ",0,500);
//        helvetica1.drawString("Dar�o Rafael Puco Zapata",400,400);*/        
        if(ofGetElapsedTimeMillis()>timeChangeStatus){
            gameStatus=SINJUGADOR;
            cheapComm::getInstance()->sendStartWait();
            timeChangeStatus=ofGetElapsedTimeMillis()+3000;
        }
    }else if(gameStatus==SINJUGADOR && ofGetElapsedTimeMillis()>timeChangeStatus ){
        //TODO
        helvetica1.drawString("Apunta a los barcos",0,350);
        mtracking.update();
        if(mtracking.checkPointers()==true){
            restart();
            cheapComm::getInstance()->sendStart();
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
        mtracking.drawMatrixVideo();
        mtracking.draw();
        drawMarcador();
    } else if(gameStatus==FIN){
//        helvetica1.drawString("JUEGO TERMINADO",400,300);
        creditos.draw(0, 0);
        ofTranslate(55,182);
        
        helvetica1.drawString("Trayectos en barcaza solar:" + ofToString(mbarcos.nbarcoSolar*ratioBarcosReales) +"("+
                              ofToString(mbarcos.nbarcoSolar)+")",0,0);
        
        helvetica1.drawString("Trayectos en barcaza diesel: "+ ofToString(mbarcos.nbarcoNormal*ratioBarcosReales) +"("+
                              ofToString(mbarcos.nbarcoNormal)+")",0,30);
        
        
    }
    

}

void ofApp::drawMarcador(){
    ofSetColor(200);
    helvetica1.drawString("Trayectos en barcazas solares", 150, 40);
    letraGrande.drawString(ofToString(mbarcos.nbarcoSolar*ratioBarcosReales), 450, 45);
    
    helvetica1.drawString("Trayectos en barcazas convencionales", 650, 40);
    letraGrande.drawString(ofToString(mbarcos.nbarcoNormal*ratioBarcosReales), 550, 45);

    letraGrande.drawString("DIA " + ofToString(round(( mbarcos.nbarcoNormal + mbarcos.nbarcoSolar ) * DIAS_BARCO)) + " de 365", 50, 730);
    helvetica1.drawString("1 trayecto del juego son " + ofToString(ratioBarcosReales)  + " trayectos reales", 600, 730);
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
