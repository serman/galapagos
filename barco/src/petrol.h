//
//  petrol.h
//  vizs
//
//  Created by Sergio Galan on 11/22/14.
//
//

#ifndef vizs_petrol_h
#define vizs_petrol_h
#include "ofxLiquidFun.h"
#include "consts.h"
#define MAXBALLS 10000
#define MAXSAVING 20000*5

extern float litros_petroleo_ahorrado;


class petrol{
    public:
        void setup() {
            box2d.init();
            box2d.setGravity(0, 10);
            box2d.setFPS(60.0);
            
            box2d.registerGrabbing();
            box2d.createBounds(0,0, petroleo_w, petroleo_h-10);
                    particles.setup(box2d.getWorld(), 10000, 0.0, 2.0, 2.0, ofColor::black);
            
            
            ofEnableAlphaBlending();
            ofSetVerticalSync(true);
            ofEnableSmoothing();
            restart();
          //  addParticles(200);
            
        }
    
        void addParticles(int nparticles){
            for (int i = 0; i < nparticles; i++) {
                ofVec2f position = ofVec2f(ofRandom(400),
                                           ofRandom(ofGetHeight()));
                ofVec2f velocity = ofVec2f(0, 0);
                particles.createParticle(position, velocity);
            }
        }

        //--------------------------------------------------------------
        void update() {
            box2d.update();
            ofSetWindowTitle(ofToString(ofGetFrameRate()));
            if(statusGlobal==RUN){
                setSizeTon(litros_petroleo_ahorrado);
            }
        }


        //--------------------------------------------------------------
        void draw() {
            if(statusGlobal==RUN){
                drawNormal();
            }
            else if(statusGlobal==PRE){
                drawPre();
            }
            else if(statusGlobal==POST){
                drawPost();
            }
        }
    
    void drawNormal(){
        ofSetColor(197,224,220);
        ofRect(0,0,petroleo_w,petroleo_h);
        ofSetColor(255);
        particles.draw();
        franchise.drawString("DIÉSEL AHORRADO",20,60);

    }
    

    
    void drawPre(){
        ofSetColor(0,0,0);
        //ofRect(0, 0, 640/zoomRatio, 640/zoomRatio);
        ofSetColor(255, 255, 255);
        franchise.drawString("drawPre: ",20,30);
    }
    
    void drawPost(){
        ofSetColor(0, 0, 0);
        //ofRect(0, 0, 640/zoomRatio, 640/zoomRatio);
       // ofSetColor(255, 255, 255);
        franchise.drawString("Densidad Co2: ",20,30);
        //franchise.drawString("altura de la isla: 0.5m",20,60);
    }
    
    void setSizeTon(float tons){
        if(currentPetrol<tons){
            int newBalls=ofMap(tons,0,MAXSAVING,0,MAXBALLS);
            newBalls=ofClamp(newBalls,0,MAXBALLS);
            if(newBalls>currentBalls){
                addParticles(newBalls-currentBalls);
            }
            currentBalls=newBalls;
            currentPetrol=tons;
        }
    }
    
    void restart(){
        currentPetrol=0;
        currentBalls=0;
        particles.destroy();
        particles.setup(box2d.getWorld(), 10000, 0.0, 5.0, 3.0, ofColor::black);
    }
    
    void start(){
        restart();
    }
    void end(){
        
    }
    
/*    void updateResult(int solar, int normal){
  //1 barco= 100 trayectos
        //float toneladas_Petroleo_100_trayectos= 0.1;
        setSizeTon(solar*toneladas_Petroleo_100_trayectos);
        
        cout << "update updateResult nueva isla" << endl ;
        
    }*/

private:
    ofxBox2d box2d;
    vector <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    vector <ofPtr<ofxBox2dRect> > boxes;			  //	defalut box2d rects
    ofxBox2dParticleSystem particles;			      //    LiquidFun particle system
    int currentPetrol;
    int currentBalls;

    
};
#endif
