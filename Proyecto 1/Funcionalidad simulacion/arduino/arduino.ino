#include "LedControl.h"
#include <LiquidCrystal.h>
#include <Stepper.h>
LedControl matriz = LedControl(13,11,12,4); //Matriz con driver

//pines de motores
int a1=52;
int a2=50;
int b1=48;
int b2=46;

const int stepsPerRevolution = 360;  // Número de pasos por revolución del motor
Stepper myStepper(stepsPerRevolution, a1,a2,b1,b2);  // Crea un objeto Stepper
byte datos[64];
String diseno="";
byte uno[8]={
      B00010000,
      B00110000,
      B00010000,
      B00010000,
      B00010000,
      B00010000,
      B00010000,
      B00111000
    };

byte dos[8]={
      B00111000,
      B01000100,
      B00000100,
      B00000100,
      B00001000,
      B00010000,
      B00100000,
      B01111100
    };
byte tres[8]={
      B00111000,
      B01000100,
      B00000100,
      B00011000,
      B00000100,
      B00000100,
      B01000100,
      B00111000
    };

byte mensaje2[8][57]={{  0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0 },
                       { 0,0,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0 },
                       { 0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
                       { 0,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,1,0,0,0,0 },
                       { 0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0 },
                       { 0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0,0,0 },
                       { 0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,0 },
                       { 0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0 }};
                       

    
void setup() {
  matriz.shutdown(0,false); //Modo normal
  matriz.shutdown(1,false); 
  matriz.shutdown(2,false); 
   matriz.shutdown(3,false); 
  matriz.setIntensity(0,15);  //Intensidad
  matriz.setIntensity(1,15);
  matriz.setIntensity(2,15);
  matriz.setIntensity(3,15);
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(a1,OUTPUT);
  pinMode(a2,OUTPUT);
  pinMode(b1,OUTPUT);
  pinMode(b2,OUTPUT);
  myStepper.setSpeed(65); 
  Serial.begin(9600);
}


void esperar_imagen() {
    while(!Serial.available());
    
}

void esperar_dato() {
    while(!Serial.available());
    
}

void esperar_estacion(int estacion){
   while(!Serial.available()){
     mensaje_espera(estacion);
   }
}

void leer_imagen() {
    diseno=Serial.readStringUntil('&');
    for (int i = 0; i < 64; i++) {
    if (diseno[i] == '0') {
      datos[i] = 0;
    } else if (diseno[i] == '1') {
      datos[i] = 1;
    } 
    }
 }

int currentBlockRow = 0;
int currentBlockCol = 0;
void mensaje_espera(int estacion){
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      byte valor = mensaje2[row][currentBlockCol + col];
      if (valor == 1) {
        matriz.setLed(estacion, row, col, true);
        
      } else {
        matriz.setLed(estacion, row, col, false);
      }
    }
  }
  delay(150);  // Mostrar cada bloque durante 1 segundo
  matriz.clearDisplay(estacion); // Apagar todos los LEDs antes de mostrar el siguiente bloque

  // Avanzar al siguiente bloque
  currentBlockCol += 2;
  if(currentBlockCol==54){
    currentBlockCol=0;
  }
}

void estacion_1(){
    matriz.clearDisplay(0);  
    int cont = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 3; j++) {
            matriz.setLed(0, i, j, datos[cont] ? true : false);
            cont++;
        }
        cont+=5;
    }
}

void estacion_2(){
  matriz.clearDisplay(1);
  
    int cont = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 6; j++) {
            matriz.setLed(1, i, j, datos[cont] ? true : false);
            cont++;
        }
        cont+=2;
    }
}

void estacion_3(){
  matriz.clearDisplay(2);
  
    int cont = 0;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            matriz.setLed(2, i, j, datos[cont] ? true : false);
            cont++;
        }        
    }
}

void mover_motores(){
 
  while(!Serial.available()){
   String inst=Serial.readStringUntil('&');
   if(inst=="detener"){
     myStepper.step(0); 
     break;
   }
    myStepper.step(stepsPerRevolution); 
    
  }
    delay(1000);
}

boolean bandera=true;
int contador=0;
void estacion_inicial(boolean ensamblando){
  //esperando diseño
  esperar_imagen();
  leer_imagen();
  boolean use_estacion1=false;
  boolean use_estacion2=false;
  boolean use_estacion3=false;
  int estacion_espera=0;
  while(ensamblando ==true || contador!=3){
  
  
    //esperando estacion
    esperar_estacion(estacion_espera);
    currentBlockRow = 0;
    currentBlockCol = 0;
    String estacion=Serial.readStringUntil('&');
    if(estacion=="1"){
      matriz.clearDisplay(3);
      for(int i=0;i<8;i++){        
        matriz.setRow(3,i,uno[i]);      
      }
      contador++;
      estacion_1();
      use_estacion1=true;
    }else if(estacion=="2"){
      matriz.clearDisplay(3);
      for(int i=0;i<8;i++){        
        matriz.setRow(3,i,dos[i]);      
      }
      contador++;
      estacion_2();
      use_estacion2=true;
    }else if(estacion=="3"){
      matriz.clearDisplay(3);
      for(int i=0;i<8;i++){        
        matriz.setRow(3,i,tres[i]);      
      }
      contador++;
      estacion_3();
      use_estacion3=true;
    }else if(estacion=="termino" || contador==3){
      ensamblando=false;
      bandera=false;
      delay(1000);
      matriz.clearDisplay(3); 
      break;     
    }
    if(use_estacion1==false){
      estacion_espera=0;
    }else if( use_estacion2==false){
      estacion_espera=1;
    }else if(use_estacion3==false){
      estacion_espera=2;
    }
  }

  if(ensamblando==false || contador==3){
    
    pintar_imagen();
    String instruccion="";
    while(instruccion != "barra"){
      esperar_dato();
      instruccion=Serial.readStringUntil('&');
      if(instruccion=="barra"){
        mover_motores();
      }
    }
    
  }

}

void pintar_imagen() {
    int cont = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            matriz.setLed(3, i, j, datos[cont] ? true : false);
            cont++;
        }
}


void loop() {
      
  estacion_inicial(bandera);

  
  
  
  
  
}
