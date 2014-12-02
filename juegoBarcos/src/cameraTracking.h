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
#include "ofxPS3EyeGrabber.h"
#include "boxAlign.h"
#define EYETOY 1
static bool USE_LIVE_VIDEO =true;
#define filas 25
#define columnas 25
static int camWidth = 320;
static int camHeight = 240;
static int tileWidth = (int)(camWidth / columnas);
static int tileHeight = (int)(camHeight / filas);
static float ratiow=1024.0/camWidth;
static float ratioh=768.0/camHeight;
static float screen_w = 1024.0;
static float screen_h = 768.0;

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
    float minRadius;
    float maxRadius;
    
    
    void openCameras(){
        if( USE_LIVE_VIDEO){
            
#ifdef EYETOY
            camera.setGrabber(ofPtr<ofxPS3EyeGrabber>(new ofxPS3EyeGrabber()));
                camera.setPixelFormat(OF_PIXELS_MONO);
#else   
            camera.listDevices();
            camera.setDeviceID(0);
            camera.setDesiredFrameRate(30);
#endif
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
        grayImgW.allocate(imgWidth,imgHeight);
        background.setLearningTime(900);

        thresholded.allocate(imgWidth,imgHeight,OF_IMAGE_GRAYSCALE);
        //contourFinder.setMinAreaRadius(minRadius);
        //contourFinder.setMaxAreaRadius(maxRadius);
                    thresholded.setImageType(OF_IMAGE_GRAYSCALE);
        bdrawDebug=false;
        	boxInputMatrix.setup( 0, 200, imgWidth, imgHeight);

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
            if(USE_LIVE_VIDEO){
                background.setThresholdValue(threshold);
                #ifdef EYETOY
                    sourceImgImage.setFromPixels(camera.getPixelsRef());
                                background.update(sourceImgImage, thresholded);
                                thresholded.update();
                #else
                    sourceImg.setFromPixels(camera.getPixels(), camWidth,camHeight);
                    background.update(sourceImg, thresholded);
                    thresholded.update();
                #endif
                
                //sourceImg.setFromPixels(camera.getPixels(), camWidth,camHeight);


            }
            else{
                sourceImg.setFromPixels(player.getPixels(), camWidth,camHeight);
                background.update(player, thresholded);
                thresholded.update();
            }
            
            //sourceImg.mirror(false, true);
        }
        #ifdef EYETOY
            ofxCv::convertColor(sourceImgImage.getPixelsRef(), grayImg.getPixelsRef(), CV_RGBA2GRAY);
            grayImg.flagImageChanged();
        #else
            grayImg = sourceImg;
                    grayImg.flagImageChanged();
        #endif
        if(!enableBGS){
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
        else{
            //grayImgT=thresholded;
            ofPoint dstPts[4] = {
                ofPoint(0, imgHeight, 0),
                ofPoint(imgWidth, imgHeight, 0),
                ofPoint(imgWidth, 0, 0),
                ofPoint(0, 0, 0)
            };
            grayImgT.setFromPixels(thresholded.getPixels(),thresholded.getWidth(), thresholded.getHeight());
            grayImgW.warpIntoMe(grayImgT, boxInputMatrix.fHandles, dstPts );
            
            //grayImgT.mirror(false, false);
             grayImgW.erode_3x3();
            grayImgW.dilate_3x3();
             contourFinder.findContours(grayImgW, minRadius, maxRadius, 10, false, true);
        }            
    }
    
    void draw() {
//        strokeWeight(4);
        ofNoFill();
        ofEllipse(loc.x, loc.y, 10, 10);
        if(bdrawDebug){
            
            
            ofPushMatrix();
            ofSetColor(255);
            //dibujo las esquinas
            ofSetLineWidth(4);
            ofRect(0,0,screen_w,screen_h);
            
            ofFill();
                        ofSetLineWidth(0);
            ofRect(-10,-10,20,20);
            ofRect(screen_w-10,-10,20,20);
            ofRect(screen_w-10,screen_h-10,20,20);
            ofRect(0,screen_h-10,20,20);
            
//                ofTranslate(50,0);
            if(!enableBGS){
                drawMatrix();
            }
            ofSetColor(255);
            grayImg.draw(0 ,200,320,240); // entrada
            
            if(!enableBGS){
                grayImgT.draw(0,450,320,240); //
            }else{

                grayImgT.draw(0,450);
                grayImgW.draw(325,450);
                boxInputMatrix.draw(0 ,200);
                
            }
        }
        ofPopMatrix();
        if(enableBGS){
            ofPushMatrix();
            ofScale(ratiow, ratioh);
            contourFinder.draw();
            ofPopMatrix();
            
        }
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
        if(!enableBGS){
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
        else{
            for(int i=0; i< contourFinder.nBlobs; i++){
                for(int z=0; z<mbarcos.size(); z++){
                    ofRectangle r=contourFinder.blobs[i].boundingRect;
                    r.x*=ratiow;
                    r.y*=ratioh;
                    if( mbarcos[z].intersects(r)){
                        mbarcos.at(z).type=1;
                    }
                }
            }
        }
    }
    
    bool checkPointers(){
        if(contourFinder.nBlobs>0)
            return true;
        else return false;
        
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
        ofxCv::RunningBackground background;
    bool    bdrawDebug;
    	CBoxAligner         boxInputMatrix;
private:
    ofVideoGrabber camera;
    ofVideoPlayer player;
    ofImage sourceImgImage;
    ofxCvColorImage		sourceImg;
	
	ofxCvGrayscaleImage 	grayImg;
	ofxCvGrayscaleImage 	grayImgBg;
	ofxCvGrayscaleImage 	grayImgDiff;
	
	ofxCvGrayscaleImage 	grayImgT;
	ofxCvGrayscaleImage 	grayImgW;
    bool enableBGS=true;

    ofImage thresholded;
    ofxCvContourFinder contourFinder;
    };




#endif
