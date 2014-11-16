//
//  cheapComm.cpp
//  panel1_tracking
//
//  Created by Sergio Galan on 5/7/14.
//
//

#include "cheapComm.h"

cheapComm* cheapComm::m_pInstance = NULL;

cheapComm::cheapComm(){

}

void cheapComm::setup(){
    string dst="127.0.0.1";
    int serverRecvPortData = 9000;
    myOscData.setup(dst,serverRecvPortData);
	int maxServerMessages = 38;
	ofLogNotice("> >> >>> >> > >> >>> >> > >> >>> >> > >> cheapComm::setup()");
	
		
}

void cheapComm::sendMarcador(int nsol, int nnormal ){
    if(nsol==0)     nsol=1;
    if(nnormal==0)  nnormal=1;
    ofxOscMessage m;
    m.setAddress("/marcador");
    m.addIntArg(nsol);
    m.addIntArg(nnormal);
    myOscData.sendMessage(m);
}

void cheapComm::sendEnd( ){
    ofxOscMessage m;
    m.setAddress("/end");
    myOscData.sendMessage(m);
}

void cheapComm::sendStart( ){
    ofxOscMessage m;
    m.setAddress("/start");
    myOscData.sendMessage(m);
}


