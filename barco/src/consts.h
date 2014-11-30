//
//  consts.h
//  barco
//
//  Created by Sergio Galan on 11/15/14.
//
//

#ifndef barco_consts_h
#define barco_consts_h

#define islapuzle_w  320
#define islapuzle_h  240

#define isla_w 480
#define isla_h 480


#define ratioPanelizaArriba 1
#define ratioPanelizaAbajo 70/60
#define ratioPanelDereArriba 69/69
#define ratioPanelLargo 120/21

#define pajaros_w   480*0.93

#define pajaros_h   520*0.93

#define ratioPetroleo 1.2
#define petroleo_h (768-pajaros_h)
#define petroleo_w petroleo_h*ratioPetroleo


#define trayectosRealesBarco 100
#define LITROSPETROLEOANUALES 10000

extern ofTrueTypeFont franchise;
extern int statusGlobal;

enum statuses{PRE,RUN,POST};
#endif
