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
class petrol{
    public:
    
        void setup() {
           
            
            box2d.init();
            box2d.setGravity(0, 10);
            box2d.setFPS(30.0);
            
            box2d.registerGrabbing();
            box2d.createBounds(0,0, petroleo_w, petroleo_h);
            
            particles.setup(box2d.getWorld(), 10000, 0.0, 2.0, 2.0, ofColor::black);
            
            for (int i = 0; i < 500; i++) {
                ofVec2f position = ofVec2f(ofRandom(100),
                                           ofRandom(ofGetHeight()));
                ofVec2f velocity = ofVec2f(0, 0);
                particles.createParticle(position, velocity);
            }
            
            ofEnableAlphaBlending();
            ofSetVerticalSync(true);
            ofEnableSmoothing();
            
        }
        void addParticles(){
            for (int i = 0; i < 400; i++) {
                ofVec2f position = ofVec2f(ofRandom(ofGetWidth()),
                                           ofRandom(ofGetHeight()-4,ofGetHeight()));
                ofVec2f velocity = ofVec2f(0, 0);
                particles.createParticle(position, velocity);
            }
            
        }

        //--------------------------------------------------------------
        void update() {
            box2d.update();
            ofSetWindowTitle(ofToString(ofGetFrameRate()));
        }


        //--------------------------------------------------------------
        void draw() {
            ofSetColor(0,191,255);
            ofRect(0,0,petroleo_w,petroleo_h);
            ofSetColor(255);
            particles.draw();
        }
private:
    ofxBox2d box2d;
    vector <ofPtr<ofxBox2dCircle> >	circles;		  //	default box2d circles
    vector <ofPtr<ofxBox2dRect> > boxes;			  //	defalut box2d rects
    ofxBox2dParticleSystem particles;			      //    LiquidFun particle system
    

    
};
#endif
