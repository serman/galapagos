import codeanticode.syphon.*;
import gifAnimation.*;
import de.looksgood.ani.*;
import controlP5.*;
PFont myFont;
PGraphics canvas;
SyphonServer server;
ControlP5 cp5;
PImage[] animation;
ArrayList<pajaro> pajaros;
int pajarosActivos=0;
Gif nonLoopingGif;
boolean pause = false;
PImage arbol;
int totalPajaros=9;
int barcosSolares, barcosNormales=1;
int status=3;
public void setup() {
  size(480, 521,P3D);
  canvas = createGraphics(480, 521, P3D);
  frameRate(25);
  myFont = loadFont("Gotham-Bold-30.vlw");
  textFont(myFont, 30);
  //pajaro paj1=new pajaro();
  pajaros=new ArrayList<pajaro>();
  arbol=loadImage("arbol.png");
  Ani.init(this);
  for (int i=0; i<totalPajaros; i++) {
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
  pajaros.get(6).setDestination(74, 160);
  pajaros.get(7).setDestination(61, 86);
  pajaros.get(8).setDestination(175, 8);
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
  cp5.hide();

}


void updateViz(){
 // println(barcosSolares);
 // println(barcosNormales);
 int nuevoNumeroPajaros=4;
 if((barcosSolares+barcosNormales) < 10){
    nuevoNumeroPajaros=4;
 }
 else{
  nuevoNumeroPajaros=round( (pajaros.size()  )* ((float)barcosSolares/(float)(barcosNormales+barcosSolares)));
 }
 // println(pajarosActivos + ":::: "+ nuevoNumeroPajaros);
  if (nuevoNumeroPajaros>pajarosActivos){
     for(int i=pajarosActivos; i<nuevoNumeroPajaros; i++){
      pajaros.get(i).startEvent();
     } 
  }else if (nuevoNumeroPajaros<pajarosActivos){
     for(int i=pajarosActivos-1; i>=nuevoNumeroPajaros; i--){
      pajaros.get(i).dieEvent();
     } 
  }
  pajarosActivos=nuevoNumeroPajaros;
    
    
  
  
}
void draw() {
 updateViz();
   background(198,229,217);
   image(arbol, 0, 0);
  //image(pajaro1, 10, height / 2 - pajaro1.height / 2);

  for (int i=0; i< pajaros.size (); i++) {
    pajaros.get(i).draw();
  }
  if(status==1){
    fill(255);
    text("Los pinzones \nde Darwin",20,460);
  }
  
  if(status==3){
    fill(255);
    text("Las emisiones generadas por \ncombustibles fósiles \nprovocan la pérdida de \nbiodiversidad",20,400);
  }
 // image(canvas, 0, 0);
  server.sendScreen();
}

void mousePressed() {

  //paj1.startEvent();
}

void keyPressed() {
  if (key=='1' || key=='2' ||key=='3') {
    status=int(key-48);
  }
  /*if(key>=97 && key <104){
    pajaros.get(key-97).dieEvent();
  }*/
  if(key=='g'){
    if(cp5.isVisible()) 
      cp5.hide();
    else cp5.show();
  }
}

