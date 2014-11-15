import codeanticode.syphon.*;
import gifAnimation.*;
import de.looksgood.ani.*;
PGraphics canvas;
SyphonServer server;

PImage[] animation;
ArrayList<pajaro> pajaros;
Gif nonLoopingGif;
boolean pause = false;
PImage arbol;
public void setup() {
  size(480, 521,P3D);
  canvas = createGraphics(480, 521, P3D);
  frameRate(25);
  //pajaro paj1=new pajaro();
  pajaros=new ArrayList<pajaro>();
  arbol=loadImage("arbol.png");
  Ani.init(this);
  for (int i=0; i<6; i++) {
    pajaro paj= new pajaro();
    int j=i+1;
    paj.setup(i, this, "pajaro"+j+".gif");
    pajaros.add(paj);
  }
  pajaros.get(0).setDestination(394, 332);
  pajaros.get(1).setDestination(486, 239);
  pajaros.get(2).setDestination(348, 264); //359.302
  pajaros.get(3).setDestination(359, 127);
  pajaros.get(4).setDestination(218, 227);
  pajaros.get(5).setDestination(196, 309);
  server = new SyphonServer(this, "pajaros");
}

void draw() {
 
   background(255);
   image(arbol, 0, 0);
  //image(pajaro1, 10, height / 2 - pajaro1.height / 2);

  for (int i=0; i< pajaros.size (); i++) {
    pajaros.get(i).draw();
  }
  
 // image(canvas, 0, 0);
  server.sendScreen();
}

void mousePressed() {

  //paj1.startEvent();
}

void keyPressed() {
  if (key=='1' || key=='2' ||key=='3' ||key=='0' ||key=='4' ||key=='5') {
    int code=int(key-48);
    pajaros.get(code).startEvent();
  }
  if(key>=97 && key <104){
    pajaros.get(key-97).dieEvent();
  }
}

