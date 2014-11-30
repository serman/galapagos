#include "ofApp.h"

ofTrueTypeFont franchise;
int statusGlobal;

//MAGNITUDES variables globales
float ton_petroleo_ahorrado, ton_petroleo_consumido, ton_co2_ahorrado, ton_co2_consumido;
int nsolares;
int nnormales;
float ratio;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
   // mmenu.setup();
    mpetrol.setup();
    
    franchise.loadFont("Franchise-Bold-hinted.ttf",25);
    franchiseBig.loadFont("Franchise-Bold-hinted.ttf",65);
    statusGlobal=RUN;
    
    isla.setup();

    ofxLoadCamera(cam, "ofEasyCamSettings");
    //cam.move(150, 0, 0);

    mapping = new ofxMtlMapping2D();
    mapping->init(ofGetWidth(), ofGetHeight(), "mapping/xml/shapes.xml", "mapping/controls/mapping.xml");
    mislapuzle.setup();
  	mClient.setup();
    mClient.set("pajaros","animacion");
    
    cam.lookAt(mislapuzle.cellCentroids[0]);
    cam.setAutoDistance(true);
    myOSCrcv=new cheapCommRcv();
    myOSCrcv->setup();
    px=0;
    py=-180;
    pz=0;
    zoom=1.0;
    
    gui=new ofxUICanvas(700,0,200,350);
    gui->addSlider("x", -200, 200, &px);
    gui->addSlider("y", -200, 200, &py);
    gui->addSlider("z", -200, 200, &pz);
    gui->addSlider("zoom", 0.1, 1, &zoom);

    gui->addSlider("tortugaX", -200, 200, &(mislapuzle.tortugaX));
    gui->addSlider("tortugay", -200, 200, &(mislapuzle.tortugaY));
    gui->addSlider("tortugaz", -200, 200, &(mislapuzle.tortugaZ));

//    gui->addSlider("toneladasPetroleo", 0, 30, &(ton_petroleo_ahorrado) );
    gui->addIntSlider("barcos solares", 0, 300, &(nsolares) );
    gui->addIntSlider("barcos normales", 0, 300, &(nnormales) );
    
    ofAddListener(gui->newGUIEvent,this,&ofApp::gui2Event);
    gui->loadSettings("settings.xml");
    reset();

   // cam.enableMouseInput();
    
//    ofAddListener( ofEvents().update , this, &ofEasyCam::update);
}

void ofApp::gui2Event(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    updateResult(nsolares,nnormales);
    if(name == "Adaptative")
    {
        
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle("visualizaciones fps:" + ofToString(ofGetFrameRate()));

   // mmenu.update();
    mpetrol.update();
        isla.update();
    mapping->update();
        mislapuzle.update();

    myOSCrcv->update();
}

void ofApp::updateResult(int solar, int normal){
    nsolares=solar;
    nnormales=normal;
    
    float toneladas_Petroleo_N_trayectos= 0.1; //TODO ESTO FALTA
    float toneladas_CO2_consumido_N_trayectos= 100 * (8.85 / (50*365));
    ton_petroleo_ahorrado=nsolares*toneladas_Petroleo_N_trayectos;
    if(normal>0)
        ratio=solar/normal;
    else ratio=0;
    ton_co2_consumido=normal*toneladas_CO2_consumido_N_trayectos;

    cout << "update updateResult ofApp" << endl ;
}




//--------------------------------------------------------------
void ofApp::draw(){
    mapping->bind();
    
    ofBackground (0,0,0) ;
//ISLA CO2
    ofPushMatrix();
        ofPushStyle();
        ofSetColor(255);
        isla.draw();
        ofPopStyle();
    ofPopMatrix();

//PAJAROS
    mClient.draw(480, 0,pajaros_w,pajaros_h);

//BUQUE
    ofPushMatrix();
        ofPushStyle();
        ofTranslate(islapuzle_w+10, pajaros_h);
        ofPushMatrix();
       // ofScale(0.5, 0.5);
       // mmenu.draw();
        mpetrol.draw();
        ofPopMatrix();
        ofPopStyle();
    ofPopMatrix();


    //marcador
    ofPushMatrix();
    ofPushStyle();
        ofTranslate(islapuzle_w+petroleo_w, 500);
        franchise.drawString(ofToString((nsolares*100.0)/(nnormales+nsolares) )+"% de viajes solares",0,0);
        franchise.drawString("X Co2 Ahorrado",0,30);
        franchise.drawString("X Co2 Emitido",0,60);
        franchise.drawString("1 Barcos en el juego \n = X barcos Reales",0,90);
        franchise.drawString("Pasajeros Barca solar ",0,160);
        franchise.drawString("Pasajeros Barca gasolina ",0,190);
    ofPopStyle();
    ofPopMatrix();

//********************ISLZPUZLE*********
    ofPushMatrix();
        ofPushStyle();
        // glEnable(GL_DEPTH_TEST);
        ofTranslate(0, 480);
        
        
        ofSetColor(0,191,255);
        ofRect(0, 0, islapuzle_w, islapuzle_h);
        ofPushMatrix();
            ofTranslate(160, 120);
            ofSetColor(0,127,127);
            ofRotateX(px);
            ofRotateY(py);
            ofRotateZ(pz);
            ofScale(zoom, zoom);
            //cam.roll(  30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
           // mislapuzle.draw();
           // cam.roll(  -30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
            ofSetColor(255);
    
        ofPopMatrix();
        
        franchise.drawString("CLIMATIC",20,50);
        franchise.drawString("CHANGE?",20,90);
        glDisable(GL_DEPTH_TEST);
        mislapuzle.bounce.draw(0,0);
    ofPopStyle();
    ofPopMatrix();
    mapping->unbind();
    
    
    //-------- mapping of the towers/shapes
    ofSetColor(255, 255, 255, 255);
    ofFill();
    ofDisableAlphaBlending();
    mapping->draw();
}

void ofApp::reset(){
    nnormales=1;
    nsolares=0;
    ratio=0;
    ton_co2_consumido=0;    
}

void ofApp::start(){
    mpetrol.start();
    isla.start();
    mislapuzle.start();
}

void ofApp::end(){
    mpetrol.end();
    isla.end();
    mislapuzle.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
 /*   if(key=='A'){
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
    } */
    if(key=='O'){
        isla.setSize(isla.islaSize+30);
    }
    if(key=='L'){
        isla.setSize(isla.islaSize-30);
    }
    if(key=='T'){
        isla.setSizeTon(6.8);
    }if(key=='g'){
        if(gui->isEnabled())
            gui->disable();
        else gui->enable();
    }
    if(key=='L'){
        gui->saveSettings("settings.xml");
    }
    if(key=='1'){
        statusGlobal=PRE;
    }
    if(key=='2'){
        statusGlobal=RUN;
    }
    if(key=='3'){
        statusGlobal=POST;
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
