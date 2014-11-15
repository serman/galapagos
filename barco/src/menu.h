//
//  menu.h
//  kinectExample
//
//  Created by Sergio Galan on 9/29/14.
//
//

#ifndef kinectExample_menu_h
#define kinectExample_menu_h
//#include "consts.h"
#include <ofMain.h>
#include <math.h>
#include "Particle.h"
#include "consts.h"

enum  {EM, NUCLEAR_DEBIL, NUCLEAR_FUERTE, GRAVEDAD, MENU,TESTING};
class menu{
public:
    vector<Particle> particles;
    ofMesh mesh;
    ofImage *currentImg;
    //Vectores de puntos donde hay letra en la imagen
    vector<ofPoint> emImgWP,weakImgWP,strongImgWP,gravityImgWP,flabImgWP;
    vector<ofPoint> *currentvector;
    ofImage texture1;
    int density=4;
    void setup(){
        emImg.loadImage("barco.png");
        weakImg.loadImage("barco2.png");
        strongImg.loadImage("barco3.png");
        gravityImg.loadImage("nobarco.png");
        flabImg.loadImage("barco.png");
        texture1.loadImage("barco.png");
        
        start(MENU);
        for ( int y = 0 ; y < emImg.height;  y+=density ){
            for ( int x = 0 ; x < emImg.width; x+=density ){
                Particle mparticle=Particle(ofVec3f(x-1000,y-1000,0),
                                            ofVec3f(0,ofRandom(-400,0),ofRandom(-400)),
                                            ofColor(255,255,255) ,x,y);
                particles.push_back(mparticle);
            }
        }
        analyzeImg();
        currentvector=&emImgWP;
        start(MENU);
    }
    
    void start(int _state){
        initTime=ofGetElapsedTimeMillis();
        state=_state;
        
    }
    
    void reset(){
        for ( int i = 0 ; i < particles.size();  i++ ){
            particles[i].position=ofVec3f(-1,i%emImg.width,0);
            particles[i].update();
        }
    }
    
    void analyzeImg( ){
        for ( int y = 0 ; y < emImg.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < emImg.width; x+=density/1.6 ){
                if(emImg.getColor(x,y).getBrightness()>100)
                    emImgWP.push_back(ofPoint(x,y));
            }
        }
        
        for ( int y = 0 ; y < emImg.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < emImg.width; x+=density/1.6 ){
                if(weakImg.getColor(x,y).getBrightness()>100)
                    weakImgWP.push_back(ofPoint(x,y));
            }
        }
        
        for ( int y = 0 ; y < emImg.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < emImg.width; x+=density/1.6 ){
                if(strongImg.getColor(x,y).getBrightness()>100)
                    strongImgWP.push_back(ofPoint(x,y));
            }
        }
        
        for ( int y = 0 ; y < emImg.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < emImg.width; x+=density/1.6 ){
                if(gravityImg.getColor(x,y).getBrightness()>100)
                    gravityImgWP.push_back(ofPoint(x,y));
            }
        }
        
        for ( int y = 0 ; y < emImg.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < emImg.width; x+=density/1.6 ){
                if(flabImg.getColor(x,y).getBrightness()>100)
                    flabImgWP.push_back(ofPoint(x,y));
            }
        }
        
    }
    
    
    
    void update(){
        switch(state){
            case EM:
                //emImg.draw(0,0,emImg.width,emImg.height);
                //ofDrawBitmapString (ofToString(ofGetElapsedTimeMillis()-initTime),500,500);
                currentImg=&emImg;
                currentvector=&emImgWP;
                
                break;
            case NUCLEAR_DEBIL:
                //weakImg.draw(0,0,emImg.width,emImg.height);
                currentImg=&weakImg;
                currentvector=&weakImgWP;
                break;
            case NUCLEAR_FUERTE:
                // strongImg.draw(0,0,emImg.width,emImg.height);
                currentImg=&strongImg;
                currentvector=&strongImgWP;
                break;
                
            case GRAVEDAD:
                //gravityImg.draw(0,0,emImg.width,emImg.height);
                currentImg=&gravityImg;
                currentvector=&gravityImgWP;
                break;
                
            case MENU:
                //flabImg.draw(0,0,emImg.width,emImg.height);
                currentImg=&flabImg;
                currentvector=&flabImgWP;
                break;
        }
        //ofDisableAlphaBlending();
       // ofPopStyle();
        mesh.clear();
        for ( int i = 0 ; i < particles.size();  i+=1 ){
            int index=i%currentvector->size();
            if( ((float)(  i/currentvector->size()) )>1) continue;
            ofVec3f p=ofVec3f( (*currentvector)[index] );
            particles[i].steer(p,true,2,5);
            particles[i].update();
            mesh.addVertex(particles[i].position);
            mesh.addColor(ofColor(0,192));
        }
    }
    
    void draw(){
        ofPushStyle();
        ofEnableAlphaBlending();
        
        ofSetColor(255/*,min( (int)(ofGetElapsedTimeMillis()-initTime)/2,255) */) ;
        
        mesh.setMode(OF_PRIMITIVE_POINTS);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(2);
        //texture1.bind();
        //ofEnableDepthTest();
        mesh.draw();
        //ofDisableDepthTest();
        //texture1.unbind();
        
    }
    
private:
    ofImage emImg, weakImg,strongImg,gravityImg,flabImg;
    long initTime;
    int state;
    
    
};

#endif
