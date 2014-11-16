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
const int width=1024;
const int height=768;
class barco: public ofRectangle{
public:
    int type; //0 normal 1 solar
    float speed;
    
    barco(int _x, int _y, int _w, int _h):ofRectangle(_x, _y, _w, _h) {
//        ofRectangle::ofRectangle(_x, _y, _w, _h);
        type=0;
        speed=1;
    }
    
    barco(int _x, int _y, int _w, int _h, float _speed): ofRectangle(_x, _y, _w, _h) {

        type=0;
        speed=_speed;
    }
    
    void setSpeed(float _speed){
        speed=_speed;
    }
    
    void updatePosition(){
        x+=speed;
    }
};


class barcosManager{
    
public:
    
    void setup() {
       // barcos=new ArrayList<barco>();
        barcoSolar.loadImage("barcosolar.png");
        barcoNormal.loadImage("barconormal.png");
    }
    
    void update() {
        if (ofGetElapsedTimeMillis()>timeNextBoat) {
            barco mbarco(0, (int)ofRandom(0, 768), 120, 120, ofRandom(2,5));
            barcos.push_back(mbarco);
            timeNextBoat=ofGetElapsedTimeMillis()+2500;
        }
        for (int i=0; i<barcos.size (); i++) {
            barcos[i].updatePosition();
        }
        for (int i=0; i<barcos.size(); i++) {
            if(barcos[i].x>width){
                if(barcos[i].type==0)  nbarcoNormal++;
                else nbarcoSolar++;
                barcos.erase(barcos.begin()+i) ;
                break;
            }
        }
        
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
                barcoNormal.draw (barcos[i].x, barcos[i].y, 120, 120);
            } else {
                ofSetColor(255, 255, 255, 255);
                    barcoSolar.draw(barcos[i].x, barcos[i].y, 120, 120);
            }
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

};




#endif
