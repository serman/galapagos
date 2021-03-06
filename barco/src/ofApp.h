#pragma once

#include "ofMain.h"
#include "menu.h"
#include "nuevaIsla.h"
#include "islapuzle.h"
#include "ofxMtlMapping2D.h"
#include "consts.h"
#include "ofxCameraSaveLoad.h"
#include "ofxSyphon.h"
#include "cheapCommRcv.h"
#include "ofxUI.h"
#include "petrol.h"

class cheapCommRcv;
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        menu mmenu;
    
        nuevaIsla isla;
        ofxMtlMapping2D *mapping;
        islapuzle mislapuzle;
        ofEasyCam   cam;
        ofxSyphonClient mClient;
        cheapCommRcv *myOSCrcv;
        void updateResult(int solar, int normal);
        void reset();
        void start();
        void end();
        void gui2Event(ofxUIEventArgs &e);
        petrol mpetrol;
        void toTransicion();
    
        /**** magnitudes ***/
    
    
    
private:
    
    //ofTrueTypeFont franchiseBig;
    ofxUICanvas *gui;

    
};
