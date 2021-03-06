#pragma once

#include "ofMain.h"
#include "barcos.h"
#include "cameraTracking.h"
#include "cheapComm.h"
#define TOTAL_BARCOS 182
#define ratioBarcosReales 100
#define DIAS_BARCO (365.0/TOTAL_BARCOS)
//#define TOTAL_BARCOS 200
class ofApp : public ofBaseApp{
    enum statuses{SINJUGADOR, JUGANDO,FIN};
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
        barcosManager mbarcos;
        tracking mtracking;
    
        ofTrueTypeFont helvetica1;
        ofTrueTypeFont letraGrande;
        ofImage mapa;
            ofImage intro;
        ofxUICanvas *gui;
        int gameStatus;
        float timeChangeStatus;
        void drawMarcador();
        void drawIntroMsg();
        void restart();
        ofImage creditos;
    void loadSettings();
    		void saveSettings(); 
    		ofxXmlSettings XML;

    
};
