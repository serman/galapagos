import oscP5.*;
import netP5.*;
  
OscP5 oscP5;
NetAddress myRemoteLocation;
String  IPEnvio = "localhost";
int     puertoEscucha = 9001;

void setupOSC() {
  oscP5 = new OscP5(this,puertoEscucha);
//EM 
 oscP5.plug(this,"updateMarcador","/marcador"); 
 oscP5.plug(this,"start","/start");
 
 oscP5.plug(this,"startWait","/startWait");
 oscP5.plug(this,"end","/end");
}

void updateMarcador(int nsolar, int nnormal){
//  print("update marcador ");
//  print(nsolar + " ::::: ");
//  println(nnormal);  
  barcosSolares=nsolar;
  barcosNormales=nnormal;
}

void start(){
  barcosSolares=0;
  barcosNormales=0;
  status=2;
}
void end(){
  status=3;
}

void startWait(){
  status=1;
  barcosSolares=0;
  barcosNormales=0;
}
