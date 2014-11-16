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
#define filas 30
#define columnas 30
static int camWidth = 640;
static int camHeight = 480;
static int tileWidth = (int)(camWidth / columnas);
static int tileHeight = (int)(camHeight / filas);
static float ratiow=1024.0/camWidth;
static float ratioh=768.0/camHeight;

static int imgWidth = camWidth;
static int imgHeight = camHeight;


class barcos;
class barco;
class tracking{
public:
    float matrix [filas][columnas]; //[filas][columnas];
    int maxPuntos = 10;
    int minPuntos= 1;
    ofPoint loc;
    float threshold;
    
    void openCameras(){
        if( USE_LIVE_VIDEO){
            camera.listDevices();
            camera.setDeviceID(0);
            camera.setDesiredFrameRate(30);
            camera.initGrabber(camWidth,camHeight);
        }else{
            player.loadMovie("muncyt-test-intermedio.mov");
            player.play();
        }
    }
    
    void setup(){
        //matrix=new float [filas][columnas];
        openCameras();
        threshold=200;
        // opencv.startBackgroundSubtraction(5, 3, 0.5);
        sourceImg.allocate(imgWidth,imgHeight);
        grayImg.allocate(imgWidth,imgHeight);
      //  grayImgBg.allocate(imgWidth,imgHeight);
      //  grayImgDiff.allocate(imgWidth,imgHeight);
    //    grayImgW.allocate(imgWidth,imgHeight);
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
                sourceImg.setFromPixels(camera.getPixels(), camWidth,camHeight);
            else
                sourceImg.setFromPixels(player.getPixels(), camWidth,camHeight);
            
            sourceImg.mirror(false, true);
        }
        
        grayImg = sourceImg;
        grayImgT=grayImg;
        grayImgT.threshold(threshold);

        if(ofGetFrameNum()%2==0){
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    if (matrix[i][j] >0) {
                        matrix[i][j] -=1; //amountActivity;
                    }
                }
            }
        }
        detect();
    }
    
    void draw() {
//        strokeWeight(4);
        ofNoFill();
        ofEllipse(loc.x, loc.y, 10, 10);
        ofPushMatrix();
            ofSetColor(255);
            ofTranslate(1024,0);
            drawMatrix();
            ofSetColor(255);
            grayImg.draw(0 ,200,320,240);
            grayImgT.draw(0,450,320,240);
        ofPopMatrix();
       // camera.draw(0,0);
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
    
    void checkCollisions(vector<barco> &mbarcos){
        int tileW=round(tileWidth*ratiow);
        int tileH=round(tileHeight*ratioh);
        for (int i = 0; i < columnas; i++) {
			for (int j = 0; j < filas; j++) {
                int amountActivity=matrix[i][j];
				if (amountActivity > 1) {
                        //buscar colisiones
                    for(int z=0; z<mbarcos.size(); z++){
                        if( mbarcos[z].intersects(ofRectangle(
                                                              round(i * tileW), round( j* tileH) , (int)tileW, (int)tileH
                                                              )
                                                  ) ){
                            mbarcos.at(z).type=1;
                        }
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
                        ofSetLineWidth(1);
                        ofFill();
                        ofSetColor(0, 205, 0, 255);
                        ofPushMatrix();
                        //TODO 
                        //glTranslated(40, 40 + 32, 0); 
                        ofRect(i * 5, j * 5, 5, 5);
                    ofPopMatrix();
                    ofPopStyle();
                }
                else{
                    ofPushMatrix();
                        
             //         setLineWidth(0);
                        ofSetLineWidth(1);
                        ofFill();
                        ofSetColor(30);
                        ofRect(i * 5, j * 5, 5, 5);
                    ofPopMatrix();
                }
            } 
        } 
    }
    
    void drawMatrixVideo(){

        int tileW=round(tileWidth*ratiow);
        int tileH=round(tileHeight*ratioh);
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if(matrix[i][j] > 1) {
                    ofPushStyle();
                    int energy = ofMap(matrix[i][j], 0, 10, 0, 100);
                    ofSetLineWidth(1);
                    ofFill();
                    ofSetColor(0, 205, 0, energy);
                    ofPushMatrix();
                    //TODO
                    //glTranslated(40, 40 + 32, 0);
                    ofRect(i * tileW, j * tileH, tileW, tileH);
                    ofPopMatrix();
                    ofPopStyle();
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
