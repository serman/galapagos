//
//  cameraTracking.h
//  juegoBarcos
//
//  Created by Sergio Galan on 11/14/14.
//
//

#ifndef juegoBarcos_cameraTracking_h
#define juegoBarcos_cameraTracking_h
#include "ofxCV.h"
#include "ofxOpenCv.h"
#include "ofxUI.h"

static bool USE_LIVE_VIDEO =true;
static int filas=20;
static int columnas=20;
static int camWidth = 320;
static int camHeight = 240;
static int tileWidth = (int)(camWidth / columnas);
static int tileHeight = (int)(240 / filas);


static int imgWidth = 320;
static int imgHeight = 240;
class tracking{
public:
    float matrix [20][20]; //[filas][columnas];
    //import org.opencv.core.countNonZero;
    int maxPuntos = 10;
    int minPuntos= 1;
    ofPoint loc;
    float threshold;

    
    void openCameras(){
        if( USE_LIVE_VIDEO){
            camera.listDevices();
            camera.setDeviceID(0);
            //camera.setDesiredFrameRate(30);
            camera.initGrabber(camWidth,camHeight);
        }else{
            player.loadMovie("muncyt-test-intermedio.mov");
            player.play();
        }

        
    }
    
    void setup(){
        //matrix=new float [filas][columnas];

        openCameras();
       // video.start();
        threshold=200;
        // opencv.startBackgroundSubtraction(5, 3, 0.5);
        sourceImg.allocate(imgWidth,imgHeight);
        grayImg.allocate(imgWidth,imgHeight);
        grayImgBg.allocate(imgWidth,imgHeight);
        grayImgDiff.allocate(imgWidth,imgHeight);
        grayImgW.allocate(imgWidth,imgHeight);
        grayImgT.allocate(imgWidth,imgHeight);
    }
    
    void update(){
        bool bNewFrame = false;
        
        if(USE_LIVE_VIDEO){
            camera.update();
            bNewFrame = camera.isFrameNew();}
        else{
            player.update();
            bNewFrame = player.isFrameNew();}

        
        if (bNewFrame){
            
        if(USE_LIVE_VIDEO)
            sourceImg.setFromPixels(camera.getPixels(), 320,240);
        else
            sourceImg.setFromPixels(player.getPixels(), 320,240);
        }
        grayImg = sourceImg;
            grayImgT=grayImg;
        grayImgT.threshold(threshold);
        
        
        
/*        for (int i = 0; i < columnas; i++) {
            for (int j = 0; j < filas; j++) {
                    if (matrix[i][j] > 0) matrix[i][j] -= 1; //amountActivity;
                    
                }				
            }*/
        
        if(ofGetFrameNum()%2==0){
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    if (matrix[i][j] >0) {
                        matrix[i][j] -=1; //amountActivity;
                    }
                }
            }
        }
        

    }
    
    void draw() {
        ofSetColor(255, 0, 0);
//        strokeWeight(4);
        ofNoFill();
        ofEllipse(loc.x, loc.y, 10, 10);
        detect();
        drawMatrix();

        ofSetColor(255);
        grayImg.draw(400,400);
        grayImgT.draw(780,400);
    }
    
    void detect(){
 		for (int i = 0; i < columnas; i++) {
			for (int j = 0; j < filas; j++) {
				float amountActivity = grayImgT.countNonZeroInRegion(i * tileWidth, j * tileHeight, tileWidth, tileHeight);
				if (amountActivity > 1) {
                   // if (amountActivity>maxPuntos && amountActivity>minPuntos)    continue;
					if (matrix[i][j] < 15) {
						matrix[i][j] += 1; //amountActivity;
					}
				}
			}
		}
    }
    
    void drawMatrix(){
        float energy=0;
        //strokeWeight(1);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if(matrix[i][j] > 1) {
                    int qi = i;
                    int qj = j;
                    ofPushStyle();
                    energy = ofMap(matrix[i][j], 0, 10, 0, 255);
               //     setLineWidth(0);
                    ofFill();
                    ofSetColor(0, 205, 0, 255);
                    ofPushMatrix();
                    ofTranslate(700,0);
                    //TODO 
                    //glTranslated(40, 40 + 32, 0); 
                    ofRect(i * 5, j * 5,5, 5);
                    ofPopMatrix();
                    ofPopStyle();
                }
                else{
                    ofPushMatrix();
                    ofTranslate(700,0);
           //         setLineWidth(0);
                    ofFill();
                    ofSetColor(30);
                    ofRect(i * 5, j * 5, 5, 5);
                    ofPopMatrix();
                }
            } 
        } 
    }
    
    void resetMatrix() {     
        //matriz de luz reset
        for (int i = 0; i < columnas; i++) {
            for (int j = 0; j < filas; j++) {
                matrix[i][j] = 0; //amountActivity; 
            }
        }
    }
    
private:
    ofVideoGrabber camera;
    ofVideoPlayer player;
    ofxCvColorImage		sourceImg;
	
	ofxCvGrayscaleImage 	grayImg;
	ofxCvGrayscaleImage 	grayImgBg;
	ofxCvGrayscaleImage 	grayImgDiff;
	
	ofxCvGrayscaleImage 	grayImgT;
	ofxCvGrayscaleImage 	grayImgW;


    };




#endif
