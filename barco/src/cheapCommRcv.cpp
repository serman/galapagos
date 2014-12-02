//
//  cheapComm.cpp
//  panel1_tracking
//
//  Created by Sergio Galan on 5/7/14.
//
//

#include "cheapCommRcv.h"


cheapCommRcv::cheapCommRcv(){

}
void cheapCommRcv::setup(){
    int serverRecvPort = 9000;
	myosc.setup(serverRecvPort);

	remotePosition=0;
	remoteSpeed=0;
}

void cheapCommRcv::update(){
	while(myosc.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		myosc.getNextMessage(&m);
		// check for mouse moved message
        //cout << m.getAddress()<<endl;
        if(m.getAddress()=="/marcador"){
           // ((ofApp*)ofGetAppPtr())->mislapuzle.updateResult(m.getArgAsInt32(0),m.getArgAsInt32(1));
            ((ofApp*)ofGetAppPtr())->updateResult(m.getArgAsInt32(0),m.getArgAsInt32(1));
            //((ofApp*)ofGetAppPtr())->isla.updateResult(m.getArgAsInt32(0),m.getArgAsInt32(1));
            //((ofApp*)ofGetAppPtr())->mmenu.updateResult(m.getArgAsInt32(0),m.getArgAsInt32(1));
           // ((ofApp*)ofGetAppPtr())->mpetrol.updateResult(m.getArgAsInt32(0),m.getArgAsInt32(1));
        }
        else if(m.getAddress()=="/end"){
         //   ((ofApp*)ofGetAppPtr())->mislapuzle.end();
            ((ofApp*)ofGetAppPtr())->end();
         //   ((ofApp*)ofGetAppPtr())->isla.end();
         //   ((ofApp*)ofGetAppPtr())->mmenu.end();

        }
        else if(m.getAddress()=="/start"){
            ((ofApp*)ofGetAppPtr())->start();
        }
        else if(m.getAddress()=="/startWait"){
            ((ofApp*)ofGetAppPtr())->toTransicion();
        }
       
    }
}