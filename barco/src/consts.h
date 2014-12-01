//
//  consts.h
//  barco
//
//  Created by Sergio Galan on 11/15/14.
//
//
// Cada barcaza convencional consume entre 35 y 60 L diarios de diésel (ojo: no es gasolina), en promedio el dato que se maneja es de 22.000L/año por barco
//En Galápagos hay unas 90 barcas de diferente tipo y tamaño circulando; el suministro de combustible se hace en buques cargueros, cuya capacidad es de aprox. 800.000 L. Para que te hagas una idea, llega uno o dos buques al mes para hacer este suministro.
//trayectos 5 barcas 5 i y 5 v 50 trayectos completos de 1.4 km

// 1 barca: 10 trayetos diarios = 6 km

// ahorro  6.842 toneladas de co2 al año por barco
// emisiones 8.85 toneladas de deo2


// 42 pasajeros por trayecto

#ifndef barco_consts_h
#define barco_consts_h

#define islapuzle_w  320
#define islapuzle_h  240

#define isla_w 480
#define isla_h 480


#define ratioPanelizaArriba 1
#define ratioPanelizaAbajo 70/60
#define ratioPanelDereArriba 69/69
#define ratioPanelLargo (120/21)

#define pajaros_w   480*0.93

#define pajaros_h   520*0.93

#define ratioPetroleo 1.2
#define petroleo_h (768-pajaros_h)
#define petroleo_w petroleo_h*ratioPetroleo

#define textos_w (1024-petroleo_w-islapuzle_w)
#define textos_h (2*textos_w/ratioPanelLargo)


#define trayectosRealesBarco 100
#define LITROSPETROLEOANUALES 10000

extern ofTrueTypeFont franchise;
extern int statusGlobal;
extern long timeLastChange;

enum statuses{PRE,RUN,POST};
#endif
