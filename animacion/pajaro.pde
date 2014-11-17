class pajaro{
 Gif pajaro1;
 float x1,y1;
 float xend,yend;
 Ani xani;
 Ani caeAni;
 PApplet parent;
 int tipo;
 float rotateDie;
 String filename;
 void setup(int _tipo, PApplet p,String _filename){
   filename=_filename;
   println(filename);
   parent=p;
   pajaro1 = new Gif(parent , filename);
  pajaro1.ignoreRepeat();
  tipo=_tipo;
  rotateDie=0;
  if(tipo>=0 && tipo<4){ //derecha
    x1=700;
    y1=100;
  }
  if(tipo>=4){ //izquierda
    x1=-100;
    y1=-100;
  }
  
 }
 
 void setDestination(int _x, int _y){
   xend=_x;
   yend=_y;
 }
 
 void startEvent(){
   xani = new Ani(this, 1.0, "x1", xend, Ani.SINE_OUT, "onStart:itsStarted, onEnd:llegadaARama");
   Ani.to(this, 1.0, "y1", yend, Ani.SINE_OUT);
 }
 
 void dieEvent(){
   caeAni = new Ani(this, 1.0, "y1", yend+500, Ani.SINE_IN, "onStart:itsStarted, onEnd:restartValues");
   //Ani.to(this, 1.0, "y1", yend+500, Ani.SINE_IN);
   rotateDie=0.01;
 }
 
 
 
 void draw(){   
    pushMatrix();
    translate(x1,y1);
    rotate(rotateDie);
   if(rotateDie!=0) rotateDie+=0.09;
    image(pajaro1, 0,0,
         pajaro1.width/1.5,
         pajaro1.height/1.5);
    popMatrix();
 }
  
  void itsStarted() {
    //println("diameterAni started");
  }

  // called onEnd of diameterAni animation
  void llegadaARama(Ani theAni) {
    pajaro1.play();
  }
  
  void restartValues(){
    println("restaurando " + filename);
        x1=700;
        y1=100;
        rotateDie=0;
        pajaro1.stop();
  }
  
}
