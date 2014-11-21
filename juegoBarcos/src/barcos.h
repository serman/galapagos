//
//  barcos.h
//  juegoBarcos
//
//  Created by Sergio Galan on 11/14/14.
//
//
#include "ofMain.h"
#ifndef juegoBarcos_barcos_h
#define juegoBarcos_barcos_h
const int game_width=1024;
const int game_height=768;
const int barco_w=60;
const int barco_h=60;

class barco: public ofRectangle{
public:
    int type; //0 normal 1 solar
    float speed;
    bool done;
    bool direccion; // 0 izquierda derecha 1 derecha izquierda
    ofColor c_normal;
    ofColor c_solar;
    float xInit, yInit, x1, y1,  xEnd, yEnd;
    ofImage paletaFria;
    ofImage paletaCaliente;
    barco(int _x, int _y, int _w, int _h):ofRectangle(_x, _y, _w, _h) {
//        ofRectangle::ofRectangle(_x, _y, _w, _h);
        type=0;
        speed=1;
    }
    
    barco(int _x, int _y, int _w, int _h, float _speed): ofRectangle(_x, _y, _w, _h) {
        type=0;
        speed=_speed;
    }
    
    void setup(){
        done=false;
        paletaFria.loadImage("paleta_fria.png");//izquierda a derecha
        paletaCaliente.loadImage("paleta_caliente.png");//izquierda a derecha
        if(ofRandom(0,1)>0.5){
            xInit=ofRandom(0,20);
            xEnd=ofRandom(game_width,game_width-20);
            yInit=ofRandom(0,game_height);
            yEnd=ofRandom(yInit-100,yInit+100);
            x1=xInit; y1=yInit;
            c_normal=paletaFria.getColor((int)ofRandom(0,paletaFria.width), (int)ofRandom(0,paletaFria.height));
            c_solar=paletaCaliente.getColor((int)ofRandom(0,paletaCaliente.width), (int)ofRandom(0,paletaCaliente.height));
            direccion=false;
        }
        else{ //derecha a izquierda
            xEnd=ofRandom(0,20);
            xInit=ofRandom(game_width,game_width-20);
            yInit=ofRandom(0,game_height);
            yEnd=ofRandom(yInit-100,yInit+100);
            x1=xInit; y1=yInit;
            c_normal=paletaFria.getColor((int)ofRandom(0,paletaFria.width), (int)ofRandom(0,paletaFria.height));
            c_solar=paletaCaliente.getColor((int)ofRandom(0,paletaCaliente.width), (int)ofRandom(0,paletaCaliente.height));

            direccion=true;
        }
        x=x1;
        y=y1;
        
        
    }
    void setSpeed(float _speed){
        speed=_speed;
    }
    
    void updatePosition(){
        x+=speed;
    }
    void draw(){
        if(type==0)
            ofSetColor(c_normal);
        if(type==1)
            ofSetColor(c_solar);
        
        ofSetLineWidth(3);
     //   setLineSmoothing(true);
        ofEnableSmoothing();
        if(direccion==true)// derecha izq
            ofLine(xInit,yInit+barco_h/2,x1+barco_w,y1+barco_h/2);
        else
          ofLine(xInit, yInit+barco_h/2, x1-barco_w/2, y1+barco_h/2);
        
        if(done==false){
            if(direccion==false){
                if(x1<(xEnd-speed)) x1+=speed;
                else done=true;
                if(y1!=xEnd) {
                    y1+=(yEnd-yInit)/ ((xEnd-xInit) /speed);
                }
            }
            else{
                if(xEnd<(x1-speed)) x1-=speed;
                else done=true;
                if(y1!=xEnd) {
                    y1+=(yEnd-yInit)/ ((xEnd-xInit) /speed);
                }     
            }
            x=x1;
            y=y1;
        }
    }

};


class barcosManager{
    
public:
    
    void setup() {
       // barcos=new ArrayList<barco>();
        barcoSolar.loadImage("barcosolar.png");
        barcoNormal.loadImage("barconormal.png");
        barcoSolarInv.loadImage("barcosolar.png");
        barcoSolarInv.mirror(false,true);
        barcoNormalInv.loadImage("barconormal.png");
        barcoNormalInv.mirror(false,true);
    }
    
    void update() {
        //crear nuevo barco
        if (ofGetElapsedTimeMillis()>timeNextBoat) {
            addNew();
            timeNextBoat=ofGetElapsedTimeMillis()+1000;
        }
        for (int i=0; i<barcos.size (); i++) {
            barcos[i].updatePosition();
        }
        for (int i=0; i<barcos.size(); i++) {
            if(barcos[i].x>game_width){
                if(barcos[i].type==0)  nbarcoNormal++;
                else nbarcoSolar++;
                    barcos.erase(barcos.begin()+i) ;
                break;
            }
        }
    }
    
    void addNew(){
        barco mbarco(0, (int)ofRandom(0, 768), 60, 60, ofRandom(4,10));
        mbarco.setup();
        barcos.push_back(mbarco);

        
    }
    
    void reset(){
        nbarcoSolar=0;
        nbarcoNormal=0;
    }
    
    void draw() {
        for (int i=0; i<barcos.size (); i++) {
            if (barcos[i].type==0) {
                ofSetColor(255, 255, 0, 255);
                       // cout << barcos[i].y << endl;
                if(barcos[i].direccion){ //derecha a izquierda
                    barcoNormalInv.draw (barcos[i].x1, barcos[i].y1, 60, 60);
                }
                else //izquierda a derecha
                    barcoNormal.draw (barcos[i].x1, barcos[i].y1, 60, 60);
            } else {
                    ofSetColor(255, 255, 255, 255);
                    if(barcos[i].direccion)
                        barcoSolarInv.draw(barcos[i].x1, barcos[i].y1, 60, 60);
                    else
                        barcoSolar.draw(barcos[i].x1, barcos[i].y1, 60, 60);
            }
            barcos[i].draw();
        }
        ofSetColor(255);
    }
    
    void checkColision(int x1, int y1) {
        for (int i=0; i<barcos.size (); i++) {
            if(barcos[i].inside(x1,y1)){
                barcos[i].type=1;
            }
        }
    }
    
    
    


    vector <barco> barcos;
        int nbarcoSolar, nbarcoNormal;
private:

    long timeNextBoat;
    ofImage barcoSolar;
    ofImage barcoNormal;
    ofImage barcoSolarInv;
    ofImage barcoNormalInv;

};




#endif
