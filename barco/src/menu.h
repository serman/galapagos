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

enum  {_0, _20, _40, _60, _80,_100};
class menu{
public:
    vector<Particle> particles;
    ofMesh mesh;
    ofImage *currentImg;
    //Vectores de puntos donde hay letra en la imagen
    vector<ofPoint> _0WP,_20WP,_40WP,_60WP,_80WP,_100WP;
    vector<ofPoint> *currentvector;
    ofImage texture1;
    int density=6;
    void setup(){
        _0Img.loadImage("nobarco.png");
        _20Img.loadImage("barco_20.png");
        _40Img.loadImage("barco_40.png");
        _60Img.loadImage("barco_60.png");
        _80Img.loadImage("barco_80.png");
        _100Img.loadImage("barco_100.png");
        
        texture1.loadImage("barco.png");
        
        start(_100);
        for ( int y = 0 ; y < _100Img.height;  y+=density ){
            for ( int x = 0 ; x < _100Img.width; x+=density ){
                Particle mparticle=Particle(ofVec3f(x-1000,y-1000,0),
                                            ofVec3f(0,ofRandom(-400,0),ofRandom(-400)),
                                            ofColor(255,255,255) ,x,y);
                particles.push_back(mparticle);
            }
        }
        analyzeImg();
        currentvector=&_20WP;
        start(_100);
        litrosAhorrados=0;
    }
    
    void start(int _state){
        initTime=ofGetElapsedTimeMillis();
        state=_state;
        
    }
    
    void reset(){
        for ( int i = 0 ; i < particles.size();  i++ ){
            particles[i].position=ofVec3f(-1,i%_100Img.width,0);
            particles[i].update();
        }
    }
    
    void analyzeImg( ){
      //100
        for ( int y = 0 ; y < _100Img.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < _100Img.width; x+=density/1.6 ){
                if(_100Img.getColor(x,y).getBrightness()>100)
                    _100WP.push_back(ofPoint(x,y));
            }
        }
//80
        for ( int y = 0 ; y < _100Img.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < _100Img.width; x+=density/1.6 ){
                if(_80Img.getColor(x,y).getBrightness()>100)
                    _80WP.push_back(ofPoint(x,y));
            }
        }
//60
        for ( int y = 0 ; y < _100Img.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < _100Img.width; x+=density/1.6 ){
                if(_60Img.getColor(x,y).getBrightness()>100)
                    _60WP.push_back(ofPoint(x,y));
            }
        }
//40
        for ( int y = 0 ; y < _100Img.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < _100Img.width; x+=density/1.6 ){
                if(_40Img.getColor(x,y).getBrightness()>100)
                    _40WP.push_back(ofPoint(x,y));
            }
        }
//20
        for ( int y = 0 ; y < _100Img.height;  y+=density/1.6 ){
            for ( int x = 0 ; x < _100Img.width; x+=density/1.6 ){
                if(_20Img.getColor(x,y).getBrightness()>100)
                    _20WP.push_back(ofPoint(x,y));
            }
        }
        
    }
    
    
    
    void update(){
        switch(state){
            case _100:
                //_100Img.draw(0,0,_100Img.width,_100Img.height);
                //ofDrawBitmapString (ofToString(ofGetElapsedTimeMillis()-initTime),500,500);
                currentImg=&_100Img;
                currentvector=&_100WP;
                
                break;
            case _80:
                //weakImg.draw(0,0,_100Img.width,_100Img.height);
                currentImg=&_80Img;
                currentvector=&_80WP;
                break;
                
            case _60:
                // strongImg.draw(0,0,_100Img.width,_100Img.height);
                currentImg=&_60Img;
                currentvector=&_60WP;
                break;
                
            case _40:
                //gravityImg.draw(0,0,_100Img.width,_100Img.height);
                currentImg=&_40Img;
                currentvector=&_40WP;
                break;
                
            case _20:
                //flabImg.draw(0,0,_100Img.width,_100Img.height);
                currentImg=&_20Img;
                currentvector=&_20WP;
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
    
    void updateResult(int solar, int normal){
        float ratio=(float)solar/(float)(normal+solar);
        litrosAhorrados=round(ratio*LITROSPETROLEOANUALES);
        //cout << "update updateResult menu" << endl ;
        
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
    
    void start(){
        
    }
    void end(){
        
    }
        float litrosAhorrados;
    
private:
    ofImage _0Img, _20Img,_40Img,_60Img,_80Img,_100Img;
    long initTime;
    int state;

    
    
};

#endif
