#include "LedControl.h"
LedControl matriz = LedControl(13,11,12,2); 

int columna_snake;
int fila_snake;
int columna_comida;
int fila_comida;
int conteo_velocidad;

const int boton_abajo=21;
const int boton_arriba=20;

void setup() {

  conteo_velocidad=0;
  // generar la posicion inicial de la serpiente
  randomSeed(analogRead(A0));
  
  //botones de subir y bajar
  pinMode(boton_abajo,INPUT);
  pinMode(boton_arriba,INPUT);

  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);

	//  INICIALIZAR MATRIZ CON DRIVER
	matriz.shutdown(0, false);
	matriz.setIntensity(0, 8); 
  matriz.shutdown(1, false);
	matriz.setIntensity(1, 8); 

}

void encenderLed(int x, int y) {
	digitalWrite(y, LOW);
	digitalWrite(14 + x, HIGH);
 
}

void pintarLed(int x, int y) {
	if (x >= 0 && x <= 7)
		matriz.setLed(0, y, x, true);
	else if (x >= 8 && x <= 15)
		matriz.setLed(1, y, x-8, true);
    
}

void borrarLed(int x, int y) {
	if (x >= 0 && x <= 7)
		matriz.setLed(0, y, x, false);
	else if (x >= 8 && x <= 15)
		matriz.setLed(1, y, x-8, false);
}

void establecer_posicion(){
  // definir la posicion de la serpiente
  columna_snake= random(0,2);
  fila_snake=random(0,8);
  if(columna_snake==1)
    columna_snake=8;
  pintarLed(columna_snake, fila_snake);
}

void pintar_velocidad(){
  
 

  byte cero[8]={
      B00111000,
      B01000100,
      B01000100,
      B01000100,
      B01000100,
      B01000100,
      B01000100,
      B00111000
    };

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

    byte cuatro[8]={
      B00001000,
      B00011000,
      B00101000,
      B01001000,
      B01001000,
      B01111100,
      B00001000,
      B00001000
    };
  if (conteo_velocidad==0){

    for(int i=0;i<8;i++){
      matriz.setRow(0,i,cero[i]);
      matriz.setRow(1,i,uno[i]);
    } 
  }else if(conteo_velocidad==1){
    for(int i=0;i<8;i++){
      matriz.setRow(0,i,cero[i]);
      matriz.setRow(1,i,dos[i]);
    } 
  
  }else if(conteo_velocidad==2){
    for(int i=0;i<8;i++){
      matriz.setRow(0,i,cero[i]);
      matriz.setRow(1,i,tres[i]);
    }
  }else if(conteo_velocidad==3){
    for(int i=0;i<8;i++){
      matriz.setRow(0,i,cero[i]);
      matriz.setRow(1,i,cuatro[i]);
    }
  }
}
void limpiar_matrices(){
  matriz.clearDisplay(0);
  matriz.clearDisplay(1);
}

void verificar_velocidad(){
  if(digitalRead(boton_abajo)==HIGH ){
      if(conteo_velocidad!=0){
        conteo_velocidad-=1; 
          
      }         
    }
    
    if(digitalRead(boton_arriba)==HIGH ){
      if(conteo_velocidad!=3){
        conteo_velocidad+=1; 
          
        }       
    } 
}


bool repetido =false;

void posicion_comida(){
  columna_comida= random(0,16);
  fila_comida=random(0,8);

  if(columna_comida == columna_snake && fila_snake == fila_comida){
    repetido=true;
    posicion_comida();
  }else{
    repetido=false;
  }
  if (repetido==false)
      pintarLed(columna_comida, fila_comida);
  
}

void loop() {
  //pintar_velocidad();
  //while(digitalRead(boton_arriba) == LOW && digitalRead(boton_abajo) == LOW){ 	// espera infinitamente hasta que se presione el pulsador
  //}
  
  //verificar_velocidad();

  //while(digitalRead(boton_arriba) == HIGH || digitalRead(boton_abajo) == HIGH ){ 	// espera como funcion antirebote simple
 // }
  establecer_posicion();
  delay(300);
  posicion_comida();
  delay(300);
  borrarLed(columna_comida, fila_comida);
  borrarLed(columna_snake, fila_snake);
  delay(300);
}
