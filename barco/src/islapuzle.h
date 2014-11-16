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

class islapuzle{
public:
    int w_width=islapuzle_w;
    int h_height=islapuzle_h;
    //--------------------------------------------------------------
    void setup(){
        light.setPosition(100,500, 100);
        //    light.setDiffuseColor(ofColor::blue);
        light.setAmbientColor(ofColor::green);
        light.setSpecularColor(ofColor::green);
        ofImage background;
        background.loadImage("fondo.png");
        
        bounce.setTexture(background.getTextureReference(), 1);
        
        squirrelModel.loadModel("tortoise/tortoise.3ds", 100);
        
        //you can create as many rotations as you want
        //choose which axis you want it to effect
        //you can update these rotations later on
        squirrelModel.setRotation(0, 90, 1, 0, 0);
        squirrelModel.setRotation(1, 270, 0, 0, 1);
        squirrelModel.setScale(0.9, 0.9, 0.9);
        //squirrelModel.setPosition(w_width/2, h_height/2, 0);
        
        franchise.loadFont("Franchise-Bold-hinted.ttf",40,true,true);
        franchise.setEncoding(OF_ENCODING_UTF8);
        fboIsla.allocate(w_width, h_height);
        
        makeTissue(60, w_width*0.8, h_height*0.8, 10);
        numCells=50;
        rip.allocate(w_width,h_height);
        bounce.allocate(w_width,h_height);

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
        
       //     voro::wall_cone cone(0,0,min(_width*0.5, _height*0.5),0,0,-1,atan(0.5));
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
        
        ofSetWindowTitle(ofToString(ofGetFrameRate()));
        
        rip.begin();
        ofFill();
        ofSetColor(ofNoise( ofGetFrameNum() ) * 255 * 5, 255);
        if(ofGetFrameNum()%200==0)
            ofEllipse(ofRandom(0,w_width),ofRandom(0,h_height), 20,20);
        rip.end();
        rip.update();
        
        bounce << rip;
        
    }
    
    void updateResult(int solar, int normal){
        float ratio=solar/normal;
        cout << "update updateResult isla Puzle" << endl ;
        
    }
    void start(){
        
    }
    void end(){
        
    }
    
    //--------------------------------------------------------------
    void draw(){

      //  fboIsla.begin();
       
 //       ofDrawBitmapString("ofxBounce", 640+15,15);
            bounce.draw(0,0);
        light.enable();
        ofPushMatrix();
        ofEnableLighting();
        glEnable(GL_DEPTH_TEST);

        
        /* for (int i = 0; i < cellCentroids.size(); i++){
         ofSetColor(0);
         ofSphere(cellCentroids[i], cellRadius[i]*0.15);
         }*/
        
        for(int i = 0; i < numCells; i++){
            ofSetColor(100,240);
            cellMeshes[i].drawFaces();
            ofPushStyle();
            ofSetLineWidth(3);
            ofSetColor(100);
            // cellMeshWireframes[i].draw();
            //        cellMeshWireframes[i].drawFaces();
            cellMeshWireframes[i].ofMesh::draw( OF_MESH_POINTS);
            ofPopStyle();
        }
        
        //tortuga
        glPushMatrix();
            glTranslatef(cellMeshWireframes[0].getVertex(0).x,
                         cellMeshWireframes[0].getVertex(0).y+10,
                         cellMeshWireframes[0].getVertex(0).z);
            
            ofSetColor(255, 255, 255, 255);
            squirrelModel.draw();
        
        glPopMatrix();
        
        
        glDisable(GL_DEPTH_TEST);
        ofDisableLighting();
        light.disable();

        ofPopMatrix();

        //fboIsla.end();
        //fboIsla.draw(0,0,w_width,h_height);
        
    }
    
    //--------------------------------------------------------------
    void keyPressed(int key){
        if ( key == ' '){
            makeTissue(50, w_width*0.8, h_height*0.8,20);
        } else     if ( key == '+'){
            if(numCells<cellMeshes.size())numCells++;
        }else     if ( key == '-'){
            if(numCells>0)numCells--;
        }
        else  if (key == OF_KEY_UP){
            rip.damping += 0.01;
        } else if ( key == OF_KEY_DOWN){
            rip.damping -= 0.01;
        }
    }

private:
    

    ofLight     light;
    
    vector<ofPoint> cellCentroids;
    vector<float>   cellRadius;
    vector<ofVboMesh>  cellMeshes;
    vector<ofVboMesh>  cellMeshWireframes;
    int numCells;
    
    bool direction;
    ofxRipples  rip;
    ofxBounce   bounce;
    
    ofx3DModelLoader squirrelModel;
    ofTrueTypeFont franchise;
    ofFbo fboIsla;
};


#endif
