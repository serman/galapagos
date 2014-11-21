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
        //particulas que forman parte de la isla
        for ( int i = 0 ; i < islaSize;  i+=1 ){
            ofVec3f p=ofVec3f( imgPoint[i] );
            particles[i].steer(p,true,2,5);
            particles[i].update();
            mesh.addVertex(particles[i].position);
            //mesh.addColor(ofColor(247,244,236));
            mesh.addColor(ofColor(0,0,0));
        }
        //particulas en espera
        for ( int i = islaSize ; i < particles.size();  i+=1 ){
            ofVec3f p=ofVec3f( 200,200 );
            particles[i].steer(p,true,2,5);
            particles[i].update();
            mesh.addVertex(particles[i].position);
            mesh.addColor(ofColor(247,244,236,0));
        }
    }
    
    void updateResult(int solar, int normal){
        float ratio=solar/normal;
        //cada barco supone 100 trayectos
        //
        float toneladas_100_trayectos= 100 * (8.85 / (50*365));
        setSizeTon(normal*toneladas_100_trayectos);
        
        cout << "update updateResult nueva isla" << endl ;
        
    }
    
    void draw(){
        if(statusGlobal==PRE) drawPre();
        if(statusGlobal==POST) drawPost();
        else if(statusGlobal==RUN){
            ofSetColor(255, 255, 255, 255);
            ofSetLineWidth(0);
            mesh.setMode(OF_PRIMITIVE_POINTS);
            glEnable(GL_POINT_SMOOTH);
            glPointSize(1);
            mapa.draw(0,0,640/zoomRatio, 640/zoomRatio);
            ofEnableAlphaBlending();
            ofPushMatrix();
                ofTranslate(354/zoomRatio,194/zoomRatio,0);
                mesh.draw();
            ofPopMatrix();
            ofDisableAlphaBlending();
            ofSetColor(85,98,112);
            franchise.drawString("Tendríamos una isla de " +ofToString(islaSize/0.8) + "m^2",20,30);
            franchise.drawString("con el co2 emitido por",20,60);
            franchise.drawString("" + ofToString(normal * trayectosRealesBarco) + " trayectos de barcos de gasoil",20,90);
        }
        
    }
    
    void drawPre(){
        ofSetColor(0,0,0);
        ofRect(0, 0, 640/zoomRatio, 640/zoomRatio);
        ofSetColor(255, 255, 255);
        franchise.drawString("drawPre: ",20,30);
    }

    void drawPost(){
        ofSetColor(0, 0, 0);
        ofRect(0, 0, 640/zoomRatio, 640/zoomRatio);
        ofSetColor(255, 255, 255);
        franchise.drawString("Densidad Co2: ",20,30);
        franchise.drawString("altura de la isla: 0.5m",20,60);


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
