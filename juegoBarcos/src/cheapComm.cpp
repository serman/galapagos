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
    int serverRecvPortData2 = 9001;
    myOscData.setup(dst,serverRecvPortData);
    myOscData2.setup(dst,serverRecvPortData2);
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
    myOscData2.sendMessage(m);
}

void cheapComm::sendEnd( ){
    ofxOscMessage m;
    m.setAddress("/end");
    myOscData.sendMessage(m);
    myOscData2.sendMessage(m);
}

void cheapComm::sendStart( ){
    ofxOscMessage m;
    m.setAddress("/start");
    myOscData.sendMessage(m);
    myOscData2.sendMessage(m);
}

void cheapComm::sendStartWait( ){
    ofxOscMessage m;
    m.setAddress("/startWait");
    myOscData.sendMessage(m);
    myOscData2.sendMessage(m);
}
