//
//  isla.h
//  barco
//
//  Created by Sergio Galan on 11/14/14.
//
//

#ifndef barco_isla_h
#define barco_isla_h
#include "ofxVoro.h"

#include "ofxRipples.h"
#include "ofxBounce.h"
#include "ofx3DModelLoader.h"
#include "consts.h"
#define TOTALCELLS 60
extern float ratio;
extern int nsolares;
extern int nnormales;

class islapuzle{
public:
    int w_width=islapuzle_w;
    int h_height=islapuzle_h;
    float px, py, pz,zoom;
    //--------------------------------------------------------------
    void setup(){
        light.setPosition(100,500, 100);
        //    light.setDiffuseColor(ofColor::blue);
        //light.setAmbientColor(ofColor::brown);
//        light.setSpecularColor(ofColor::green);
        rip.allocate(islapuzle_w,islapuzle_h);
        bounce.allocate(islapuzle_w,islapuzle_h);
        ofImage background;
        background.loadImage("fondo.png");
        
        bounce.setTexture(background.getTextureReference(), 1);
        
        squirrelModel.loadModel("tortoise/tortoise.3ds", 100);
        
        //you can create as many rotations as you want
        //choose which axis you want it to effect
        //you can update these rotations later on
 //       squirrelModel.setRotation(0, 90, 1, 0, 0);
//        squirrelModel.setRotation(1, 300, 0, 0, 1);
        squirrelModel.setScale(0.4, 0.4, 0.4);
        //squirrelModel.setPosition(w_width/2, h_height/2, 0);
        
        fboIsla.allocate(islapuzle_w, islapuzle_h);
        
        makeTissue(TOTALCELLS, islapuzle_w*0.8, islapuzle_h*0.8, 10);
        numCellsActual=50;
        
        px=0;
        py=-180;
        pz=0;
        zoom=1.0;

    }
    
    void makeTissue(int _nCells, int _width, int _height, int _deep){
        
        //  Fresh begining
        //
        cellMeshes.clear();
        cellCentroids.clear();
        cellRadius.clear();
        
        //  Define a container
        //
        voro::container con(-_width*0.5,_width*0.5,
                            -_height*0.5,_height*0.5,
                            -_deep*0.5,_deep*0.5,
                            1,1,1,
                            true,true,true,
                            8);
        
        //  Add walls (un comment one pair if you like to shape the container)
        //
        //  voro::wall_cylinder cyl(0,0,0,0,0,20, min(_width*0.5, _height*0.5));
        //  con.add_wall(cyl);
        
        //   voro::wall_sphere sph(0, 0, 0, min(_width*0.5, _height*0.5) );
        //  con.add_wall(sph);
        
        //    voro::wall_cone cone(0,0,min(_width*0.5, _height*0.5),0,0,-1,atan(0.5));
        //    con.add_wall(cone);
        
        //  Add the cell seed to the container
        //
        for(int i = 0; i < _nCells;i++){
            ofPoint newCell = ofPoint(ofRandom(-_width*0.5,_width*0.5),
                                      ofRandom(-_height*0.5,_height*0.5),
                                      0);
            
            addCellSeed(con, newCell, i, true);
        }
        
        cellMeshes = getCellsFromContainer(con,0.0);
        cellMeshWireframes = getCellsFromContainer(con,0.0,true);
        cellRadius = getCellsRadius(con);
        cellCentroids = getCellsCentroids(con);
    }
    
    //--------------------------------------------------------------
    void update(){
        
        rip.begin();
        ofFill();
        ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
        //generamos nueva onda
        if(ofGetFrameNum()%100==0)
            ofEllipse(ofRandom(0,islapuzle_w),ofRandom(0,islapuzle_h), 20,20);
        rip.end();
        rip.update();
        updateResult();
        
        bounce << rip;
        if(ofGetFrameNum()%5==0){
            if(numCellsActual< numCellsDestino){
                numCellsActual++;
            }
            if(numCellsActual> numCellsDestino){
                numCellsActual--;
            }
        }
        updateResult();
    }
    
    void updateResult(){
        if((nnormales+nsolares)>10){
            numCellsDestino=ofMap(ratio,0,1,0,TOTALCELLS);
            numCellsDestino=ofClamp(numCellsDestino,0,TOTALCELLS);
        }
        else{
            numCellsDestino=TOTALCELLS/2;
        }
    }
    void start(){
        numCellsDestino=TOTALCELLS/2;
    }
    void end(){
        
    }
    void draw(){
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
    
    void drawPre(){
        drawNormal();
    }
    
    void drawPost(){
                bounce.draw(0,0,islapuzle_w,islapuzle_h);
        ofSetColor(255);
        franchise.drawString("Si no se reducen las emisiones \nque provocan el cambio climático \nel aumento del nivel del mar \nprovocará la inundación \nde los hábitats costeros",20,40);
    }
    
    //--------------------------------------------------------------
    void drawNormal(){

      //  fboIsla.begin();
       
 //       ofDrawBitmapString("ofxBounce", 640+15,15);
        
        
        ofPushMatrix();
        ofEnableAlphaBlending();
        ofSetColor(255,255);
        bounce.draw(0,0,islapuzle_w,islapuzle_h);
        ofDisableAlphaBlending();
        
        light.enable();
        ofEnableLighting();       
        /* for (int i = 0; i < cellCentroids.size(); i++){
         ofSetColor(0);
         ofSphere(cellCentroids[i], cellRadius[i]*0.15);
         }*/
              light.setAmbientColor(ofColor(207,240,158));
        ofTranslate(160, 120);
        ofSetColor(0,127,127);
        ofRotateX(px);
        ofRotateY(py);
        ofRotateZ(pz);
        ofScale(zoom, zoom);
        
        ofRotateX(  3*sin( ofGetElapsedTimeMillis()/ (400*PI) ) );
        ofEnableDepthTest();
        for(int i = 0; i < numCellsActual; i++){
            ofSetColor(100,240);
            cellMeshes[i].drawFaces();
            ofPushStyle();
            ofSetLineWidth(3);
            ofSetColor(100);
            // cellMeshWireframes[i].draw();
            //        cellMeshWireframes[i].drawFaces();
            
            //TODO try y catch para la excepcion de bad Access
            cellMeshWireframes[i].ofMesh::draw( OF_MESH_POINTS);
            ofPopStyle();
        }
        ofDisableDepthTest();
        
        //tortuga
        if(numCellsActual>0){
            glPushMatrix();
            glTranslatef(cellMeshWireframes[0].getVertex(0).x,
                             cellMeshWireframes[0].getVertex(0).y,
                             cellMeshWireframes[0].getVertex(0).z);

            squirrelModel.setRotation(0, tortugaX, 1, 0, 0);
            squirrelModel.setRotation(1, tortugaY, 0, 1, 0);
            squirrelModel.setRotation(2, tortugaZ, 0, 0, 1);
                          light.setAmbientColor(ofColor(121,189,154));
                ofSetColor(255, 255, 255, 255);
                squirrelModel.draw();
            
            glPopMatrix();
        
        }

        ofDisableLighting();
        light.disable();

        ofPopMatrix();
                  ofSetColor(255, 255, 255, 255);
        franchise.drawString("CAMBIO CLIMÁTICO",20,40);
        glDisable(GL_DEPTH_TEST);

        ofSetColor(255);

        //fboIsla.end();
        //fboIsla.draw(0,0,w_width,h_height);
        
    }
    
    //--------------------------------------------------------------
    void keyPressed(int key){
        if ( key == ' '){
            makeTissue(50, w_width*0.8, h_height*0.8,20);
        } else     if ( key == '+'){
            if(numCellsActual<cellMeshes.size())numCellsActual++;
        }else     if ( key == '-'){
            if(numCellsActual>0)numCellsActual--;
        }
        else  if (key == OF_KEY_UP){
            rip.damping += 0.01;
        } else if ( key == OF_KEY_DOWN){
            rip.damping -= 0.01;
        }
    }
    vector<ofPoint> cellCentroids;
        ofxBounce   bounce;
        float tortugaX,tortugaY,tortugaZ;
    
private:
    

    ofLight     light;
    

    vector<float>   cellRadius;
    vector<ofVboMesh>  cellMeshes;
    vector<ofVboMesh>  cellMeshWireframes;
    int numCellsActual;
    int numCellsDestino;
    
    bool direction;
    ofxRipples  rip;


    ofx3DModelLoader squirrelModel;
   // ofTrueTypeFont franchise;
    ofFbo fboIsla;
};


#endif
