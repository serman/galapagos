import codeanticode.syphon.*;
import gifAnimation.*;
import de.looksgood.ani.*;
import controlP5.*;

PGraphics canvas;
SyphonServer server;
ControlP5 cp5;
PImage[] animation;
ArrayList<pajaro> pajaros;
int pajarosActivos=0;
Gif nonLoopingGif;
boolean pause = false;
PImage arbol;
int barcosSolares, barcosNormales=1;
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
  pajaros.get(0).setDestination(289, 268);
  pajaros.get(1).setDestination(409, 180);
  pajaros.get(2).setDestination(263, 189); //359.302
  pajaros.get(3).setDestination(284, 90);
  pajaros.get(4).setDestination(168, 168);
  pajaros.get(5).setDestination(154, 250);
  server = new SyphonServer(this, "pajaros");
  setupOSC();
  
  cp5 = new ControlP5(this);
  
  // add a horizontal sliders, the value of this slider will be linked
  // to variable 'sliderValue' 
  cp5.addSlider("barcosSolares")
     .setPosition(width-100,height-50)
     .setRange(1,200)
     ;
     
  cp5.addSlider("barcosNormales")
     .setPosition(width-100,height-20)
     .setRange(1,200)
     ;

}


void updateViz(){
 // println(barcosSolares);
 // println(barcosNormales);
  int nuevoNumeroPajaros=round( (pajaros.size()-1)* ((float)barcosSolares/(float)(barcosNormales+barcosSolares)));
  println(pajarosActivos + ":::: "+ nuevoNumeroPajaros);
  if (nuevoNumeroPajaros>pajarosActivos){
     for(int i=pajarosActivos; i<nuevoNumeroPajaros; i++){
      pajaros.get(i).startEvent();
     } 
  }else if (nuevoNumeroPajaros<pajarosActivos){
     for(int i=pajarosActivos; i>=nuevoNumeroPajaros; i--){
      pajaros.get(i).dieEvent();
     } 
  }
  pajarosActivos=nuevoNumeroPajaros;
    
    
  
  
}
void draw() {
 updateViz();
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

