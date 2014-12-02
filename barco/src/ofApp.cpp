#include "ofApp.h"

ofTrueTypeFont franchise;
ofTrueTypeFont franchiseBig;
int statusGlobal;
long timeLastChange;

//MAGNITUDES variables globales
float litros_petroleo_ahorrado, litros_petroleo_consumido, ton_co2_ahorrado, ton_co2_consumido;
int nsolares;
int nnormales;
float ratio;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
   // mmenu.setup();
    mpetrol.setup();
    
    franchise.loadFont("GOTHMBCD.TTF",20,true,true);
    franchise.setEncoding(OF_ENCODING_UTF8);
    franchiseBig.loadFont("GOTHMBCD.TTF",40,true,true);
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

    
    gui=new ofxUICanvas(700,0,200,350);
    gui->addSlider("x", -200, 200, &(mislapuzle.px));
    gui->addSlider("y", -200, 200, &(mislapuzle.py));
    gui->addSlider("z", -200, 200, &(mislapuzle.pz));
    gui->addSlider("zoom", 0.1, 1, &(mislapuzle.zoom));

    gui->addSlider("tortugaX", -200, 200, &(mislapuzle.tortugaX));
    gui->addSlider("tortugay", -200, 200, &(mislapuzle.tortugaY));
    gui->addSlider("tortugaz", -200, 200, &(mislapuzle.tortugaZ));

//    gui->addSlider("toneladasPetroleo", 0, 30, &(ton_petroleo_ahorrado) );
    gui->addIntSlider("statusGlobal", 0, 2, &(statusGlobal));
    gui->addIntSlider("barcos solares", 0, 300, &(nsolares) );
    gui->addIntSlider("barcos normales", 0, 300, &(nnormales) );
    
    ofAddListener(gui->newGUIEvent,this,&ofApp::gui2Event);
    gui->loadSettings("settings.xml");
    gui->disable();
    reset();
    timeLastChange=0;
   // cam.enableMouseInput();
    
//    ofAddListener( ofEvents().update , this, &ofEasyCam::update);
}

void ofApp::gui2Event(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    updateResult(nsolares,nnormales);
    if(name == "Adaptative") {
        
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
    
    float litros_Petroleo_N_trayectos=  100* (22000/(10*365)) ;  //DIESEL
    float toneladas_CO2_consumido_N_trayectos= 100 * (8.85 / (10*365));  //CO2 EMITIDO por cada barco del juego que representa N trayectos
    float toneladas_CO2_ahorrado_N_trayectos= 100 * (6.842 / (10*365));  //CO2 EMITIDO por cada barco del juego que representa N trayectos
    
    litros_petroleo_ahorrado=nsolares*litros_Petroleo_N_trayectos;
    litros_petroleo_consumido=nnormales*litros_Petroleo_N_trayectos;
    ton_co2_consumido=nnormales*toneladas_CO2_consumido_N_trayectos;
    ton_co2_ahorrado=nsolares*toneladas_CO2_ahorrado_N_trayectos;

    if(normal>0 || solar>0)
        ratio=(float)solar/(float)(solar+normal);
    else ratio=0;

  //  cout << "update updateResult ofApp" << endl ;
}




//--------------------------------------------------------------
void ofApp::draw(){
    mapping->bind();


    ofBackground (0,0,0) ;
    ofNoFill();
    
    ofRect(0,0,1024,768);
    ofFill();
//ISLA CO2
    ofPushMatrix();
        ofPushStyle();
        ofSetColor(255);
        isla.draw();
        ofPopStyle();
    ofPopMatrix();

//PAJAROS
    mClient.draw(480, 0,pajaros_w,pajaros_h);

//Petroleo
    ofPushMatrix();
        ofPushStyle();
        ofTranslate(islapuzle_w+10, pajaros_h);
       // ofScale(0.5, 0.5);
       // mmenu.draw();
        mpetrol.draw();
        ofPopStyle();
    ofPopMatrix();


//*********marcador********
    ofPushMatrix();
    ofPushStyle();
    if(statusGlobal==RUN || statusGlobal==POST){
        ofEnableAlphaBlending();
        ofTranslate(islapuzle_w+petroleo_w+20, 500);
        ofSetColor(255,ofClamp((ofGetElapsedTimeMillis()-timeLastChange )/10.0,0,255));
        ofRect(0, 0, textos_w, textos_h);
        //ofNoFill();
        //ofSetHexColor(0x9DE0AD);
        //ofSetLineWidth(3);
        //    ofRect(0, 0, textos_w, textos_h);
        ofFill();
            ofSetColor(0);
        
        //En el juego
     //       franchise.drawString(ofToString((nsolares*100.0)/(nnormales+nsolares) )+"% de viajes solares",0,0);
     //       franchise.drawString("1 Trayectos en el juego \n = X Trayectos Reales",0,90);

        // en la pantalla alargada
            franchise.drawString(ofToString(ton_co2_ahorrado) + " ton CO2 Ahorrado",10,30);
            franchise.drawString(ofToString(ton_co2_consumido) +" ton CO2 Emitido",10,60);

            franchise.drawString(ofToString(litros_petroleo_ahorrado) + " Litros de Diésel ahorrado",10,90);
            franchise.drawString(ofToString(litros_petroleo_consumido) + " Litros de Diésel consumidos",10,120);
        ofDisableAlphaBlending();
        
        //ESte dato moverlo a la pantalla de juego, cuando termina.
      //      franchise.drawString("Pasajeros Barca solar ",0,160);
      //      franchise.drawString("Pasajeros Barca gasolina ",0,190);
    }
    ofPopStyle();
    ofPopMatrix();

//********************ISLZPUZLE*********
    ofPushMatrix();
        ofPushStyle();
        // glEnable(GL_DEPTH_TEST);
        ofTranslate(0, 480);
        
        
        //ofSetColor(0,191,255);
       // ofRect(0, 0, islapuzle_w, islapuzle_h);
        ofPushMatrix();
 
            //cam.roll(  30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
            mislapuzle.draw();
           // cam.roll(  -30*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );

    
        ofPopMatrix();
        

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
    litros_petroleo_ahorrado=0;
    litros_petroleo_consumido=0;
    ton_co2_ahorrado=0;
    ton_co2_consumido=0;
}

void ofApp::start(){
    statusGlobal=RUN; //-> MODO JUEGO
    reset();
    timeLastChange=ofGetElapsedTimeMillis();
    mpetrol.start();
    isla.start();
    mislapuzle.start();
}

void ofApp::end(){ //-> MODO TRANSICION
    statusGlobal=POST;
    timeLastChange=ofGetElapsedTimeMillis();
    mpetrol.end();
    isla.end();
    mislapuzle.end();
}

void ofApp::toTransicion(){ //-> MODO TRANSICION
    timeLastChange=ofGetElapsedTimeMillis();
    statusGlobal=PRE;

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
    if(key=='S'){
        gui->saveSettings("settings.xml");
    }
    if(key=='1'){
        toTransicion();
        statusGlobal=PRE;
        timeLastChange=ofGetElapsedTimeMillis();
    }
    if(key=='2'){
        start();
        statusGlobal=RUN;
                timeLastChange=ofGetElapsedTimeMillis();
    }
    if(key=='3'){
        end();
        statusGlobal=POST;
                timeLastChange=ofGetElapsedTimeMillis();
       // cout << timeLastChange <<endl;
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
