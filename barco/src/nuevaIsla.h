//
//  nuevaIsla.h
//  barco
//
//  Created by Sergio Galan on 11/13/14.
//
//

#ifndef barco_nuevaIsla_h
#define barco_nuevaIsla_h
#include "consts.h"

class nuevaIsla{
    
public:
    vector<Particle> particles;
    vector<ofPoint> imgPoint;
    ofMesh mesh;
    int density=1;
    int islaSize;
    float zoomRatio=1.333;
    void setup(){
        mapa.loadImage("mapa.png");
        imageIsla.loadImage("isla.png");
        for ( int y = 0 ; y < imageIsla.height;  y+=1 ){
            for ( int x = 0 ; x < imageIsla.width; x+=1 ){
                if(imageIsla.getColor(x,y).getBrightness()>20)
                    imgPoint.push_back(ofPoint(x,y));
            }
        }
        
        //inicializo imagen isla
        for ( int y = 0 ; y < imageIsla.height;  y+=1 ){
            for ( int x = 0 ; x < imageIsla.width; x+=1 ){
                Particle mparticle=Particle(ofVec3f(x-1000,y-1000,0),
                                            ofVec3f(0,ofRandom(-400,0),ofRandom(-400)),
                                            ofColor(255,255,255) ,x,y);
                particles.push_back(mparticle);
            }
        }
        setSize(1);
    }
    
    
    void update(){
        mesh.clear();
        for ( int i = 0 ; i < islaSize;  i+=1 ){
            ofVec3f p=ofVec3f( imgPoint[i] );
            particles[i].steer(p,true,2,5);
            particles[i].update();
            mesh.addVertex(particles[i].position);
            mesh.addColor(ofColor(247,244,236));
        }
        for ( int i = islaSize ; i < particles.size();  i+=1 ){
            ofVec3f p=ofVec3f( 400,400 );
            particles[i].steer(p,true,2,5);
            particles[i].update();
            mesh.addVertex(particles[i].position);
            mesh.addColor(ofColor(247,244,236));
        }
    }
    
    void updateResult(int solar, int normal){
        float ratio=solar/normal;
        cout << "update updateResult nueva isla" << endl ;
        
    }
    
    void draw(){
        mesh.setMode(OF_PRIMITIVE_POINTS);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(1);
        mapa.draw(0,0,640/zoomRatio, 640/zoomRatio);
        ofPushMatrix();
            ofTranslate(354/zoomRatio,194/zoomRatio,0);
            mesh.draw();
        ofPopMatrix();
    }
    
    void setSize(int _size){
        islaSize=_size;
    }
    
    void setSizeTon(float tons){
        islaSize=  round( ((556.2*tons)/0.5) *(0.88/zoomRatio));
        cout <<islaSize << "\n";
    }
    void start(){
        
    }
    void end(){
        
    }
    
    
private:
    ofImage mapa;
    ofImage imageIsla;
    
};


#endif
