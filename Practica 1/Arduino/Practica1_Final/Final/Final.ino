#include "LedControl.h"

//------------------------------------------------------------------------------------------------------
int cambioDeModo = false; 
unsigned long tiempoInicio3Segundos= 0;
bool botonPresionado = false;
int velocidad = 1; //Velocidad Elegida Por el Usuario
int potenciometro = 0;
LedControl matriz = LedControl(13,11,12,2); //Matriz con driver
int tamMensajeX = 168;
int tamMensajeY = 8;
byte mensaje[8][168] = {{0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0 },
                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
                        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
                        {0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0 },
                        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0 },
                        {0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
                        {0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 },
                        {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0 } };

int offset = 0;
void pintarLed(int x, int y) {
	if (x >= 0 && x <= 7)
		matriz.setLed(0, y, x, true); // manipulo matriz sin driver
	else if (x >= 8 && x <= 15)
		matriz.setLed(1, y, x-8, true); //  " " con driver
}

void borrarLed(int x, int y) {
  if(x >= 0 && x <= 7)
    matriz.setLed(0,y,x,false);
	else if (x >= 8 && x <= 15)
		matriz.setLed(1, y, x - 8, false); //  " " con driver
}

byte estado[8][16] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, \
                       { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, };
//------------------------------------------------------------------------------------------------------

struct nodoSnake{  //Nodo que conformara el cuerpo de la serpiente
  byte column;
  byte fila;
  nodoSnake* sig;
};

int velocidadJuego = 500; //Velocidad Juego 



unsigned long tiempoInicio;
unsigned long tiempoActual;


//unsigned long tiempoActual3Segundos;


int puntaje = 0;



int columna_comida =random(0,16);
int fila_comida=random(0,8);

nodoSnake* snake = nullptr; //Serpiente

//LedControl matriz = LedControl(13,11,12,2); //Matriz con driver

char direccionMov = 'R';

boolean murio = false;
boolean pausa = false;

void presiono3Segundo(){
  if (digitalRead(10) == HIGH) {
    if (!botonPresionado) {
      tiempoInicio3Segundos = millis();  // Iniciar el temporizador al presionar el botón
      botonPresionado = true;
    }

    if (millis() - tiempoInicio3Segundos >= 1500) {
      // Realizar las acciones que desees aquí cuando el botón está presionado el tiempo deseado
      cambioDeModo = true;
      botonPresionado = false;
    }
  } else {
    botonPresionado = false;  // Reiniciar el estado del botón si se suelta
  }
}
void mostrarMensajeMatriz() {
  cambioDeModo = false;
  while(!cambioDeModo){
    if (digitalRead(53) == LOW) {
      for (int i = 0; i < tamMensajeY; i++)
        for (int j = 0; j < tamMensajeX; j++) {
          if (mensaje[i][j] == 1) {
            int residuo = (j + offset) % tamMensajeX;
            pintarLed(residuo < 0 ? residuo + tamMensajeX : residuo, i);
          }
        }
      //                   vv
      // analogRead(A0);
      // 0  - 1023 -- entrada análoga
      // 1  -   15 -- velocidad
      //                   ||
      //                   ||
      //                   vv
      potenciometro = analogRead(A0);
      velocidad = map(potenciometro, 0, 1024, 1, 15);    
      for (int i = 0; i <= 10 + (2 * velocidad); i++) {
        delay(15);
      }
      if (digitalRead(52) == LOW)
        offset++;
      else
        offset--;    
      
      matriz.clearDisplay(0);
      matriz.clearDisplay(1);      
      presiono3Segundo();
      if(cambioDeModo)
          return;
    } else if (digitalRead(53) == HIGH) {
      for (int k = 0; k < 28 && k >= 0;) {
        if (digitalRead(52) == HIGH) {
          if (k < 28)
            k++;
          else k=0;
        } else {
          if (k > 0)
            k--;
          else k=27;
        }
        for (int i = 0; i < 8; i++) {
          for (int j = 6 * k; j < (6 * k) + 6; j++) {
            if (mensaje[i][j] == 1) {
              pintarLed((j % 6) + 8, i);
            }
          }
        }
        potenciometro = analogRead(A0);
        velocidad = map(potenciometro, 0, 1024, 1, 15);
        for (int i = 0; i <= 10 + (2 * velocidad); i++) {
          delay(15);
        }
        if (digitalRead(53) == LOW )
          break;
        matriz.clearDisplay(0);
        matriz.clearDisplay(1);        
        presiono3Segundo();
        if(cambioDeModo)
          return;
      }
    }
  }
}
//-------------------------------------Acciones Serpiente-------------------------------------------------


void generarPosicionAleatoriaComida(){
  //randomSeed(millis());
  columna_comida = random(0,16);
  fila_comida = random(0,8);
  while (validadPosicionComidaYSnake()) {
    columna_comida = random(0,16);
    fila_comida = random(0,8);
  } 
}

bool validadPosicionComidaYSnake(){
  nodoSnake* aux = snake;
  while (aux != nullptr) {
    if (columna_comida == aux->column && fila_comida == aux->fila) {
      return true;
    }
    aux = aux->sig;
  }
  return false;
}

void pintarComida(int fila,int columna){
  pintarMatriz8x16(fila, columna);
}

int estadoPresente = LOW;  
int estadoPasado = LOW;     

void detectarpausa(){
  estadoPresente = digitalRead(10);
  if(estadoPresente == HIGH && estadoPasado == LOW ){
    estadoPasado = estadoPresente;
    return;
  }
  if(estadoPresente== LOW && estadoPasado == HIGH){
    estadoPasado = estadoPresente;
    if(pausa == false){
      int decena = puntaje /10;
      int unidad = puntaje %10;
      int mensaje[] = {decena,-1,unidad};
      mostrarMensaje(2,1,mensaje,3,0,0);
      pausa = true;
    }else{
      tiempoInicio = tiempoActual;
      pintarSnake();
      pausa = false;
    }
  }
}

void estasMuerto(){
  if (snake->fila < 0 || snake->fila > 7 || snake->column < 0 || snake->column > 15) {
    murio = true;
    return;
  }
  nodoSnake* aux = snake->sig;
  while (aux != nullptr) {
    if (aux->fila == snake->fila && aux->column == snake->column) {
      murio = true;
      return;
    }
    aux = aux->sig;
  }
  murio = false;
  return false;
}

int colInicialRandom(){
  int colRandom = random(0,2);
  return (colRandom == 0) ? 8 : 0;
}

int filaInicialRandom(){
  return random(0,8);
}

void juegoSnake(){
  while (true) {
    cambioDeModo = false;
    elegirVelocidad(); 
    puntaje = 0;
    generarPosicionAleatoriaComida();
    snake = nullptr;
    direccionMov = 'R';
    randomSeed(millis()); 
    int colInicialSnake = colInicialRandom();
    int filaInicialSnake = filaInicialRandom();
    agregarSnake(filaInicialSnake, colInicialSnake);
    agregarSnake(filaInicialSnake, colInicialSnake+1);
    velocidadJuego = map(velocidad, 1, 4, 500, 50);
    pintarSnake();
    tiempoInicio = millis();
    murio = false;
    delay(650);
    while (!murio) {
      presiono3Segundo();
      if (cambioDeModo) {
        return;
      }
      detectarpausa();
      if (pausa) {
        continue;
      }
      detectarMov();
      tiempoActual = millis();
      if (tiempoActual - tiempoInicio >= velocidadJuego) {
        moverSnake();
        estasMuerto();
        pintarSnake();
        tiempoInicio = tiempoActual;
      } 
    }
    int decena = puntaje /10;
    int unidad = puntaje %10;
                  // G  A  M  E     O  V  E  R     0 0     Longitud 12
    int mensaje[] = {10,11,12,13,-1,14,15,13,16,17,decena,unidad};
    mostrarMensaje(2,0,mensaje,12,700,100);
  }
}

void pintarSnake(){
  matriz.clearDisplay(0);
  matriz.clearDisplay(1);
  pintarComida(fila_comida,columna_comida);
  nodoSnake* aux = snake;
  while (aux!= nullptr) {
    pintarMatriz8x16(aux->fila, aux->column);
    aux = aux->sig;
  }
}


void agregarSnake(byte fila, byte column){ //Agregar un punto de led de longitud a la serpiente
  nodoSnake* nuevoNodo = new nodoSnake;
  nuevoNodo -> column = column;
  nuevoNodo -> fila = fila;
  nuevoNodo -> sig = snake;
  snake = nuevoNodo;
  nuevoNodo = nullptr;
}

void moverSnake(){
  byte tempFila = snake ->fila;
  byte tempColumn = snake ->column;
  switch (direccionMov) {
    case 'R':
      snake ->column++;
      break;
    case 'D':
      snake ->fila++; 
      break;
    case 'L':
      snake ->column--;
      break;
    case 'U':
      snake ->fila--;
      break;
  }
  if (snake->fila == fila_comida && snake->column == columna_comida) {
    snake->fila = tempFila;
    snake->column = tempColumn;
    agregarSnake(fila_comida, columna_comida);
    generarPosicionAleatoriaComida();
    puntaje++;
    velocidadJuego = velocidadJuego -25;
    if (velocidadJuego < 0) {
      velocidadJuego = 0;
    }
    return;
  }
  byte tempFila2;
  byte tempColumn2;
  nodoSnake* aux = snake;
  while (aux ->sig !=  nullptr) {
    tempFila2 = aux->sig->fila;
    tempColumn2 = aux->sig->column;
    aux->sig->fila = tempFila;
    aux->sig->column = tempColumn;
    tempFila = tempFila2;
    tempColumn = tempColumn2;
    aux = aux ->sig;
  }
}

void detectarMov(){           //Detecta el Movimiento de los controles
  if (digitalRead(23) == HIGH) {
    //Codigo Para Arriba
    if (direccionMov == 'U') {
      return;
    }
    direccionMov = 'U';
  }else if (digitalRead(25) == HIGH) {
    //Codigo Abajo
    if (direccionMov == 'D') {
      return;
    }
    direccionMov = 'D';
  }else if (digitalRead(28) == HIGH) {
    //Codigo Izquierda
    if (direccionMov == 'L') {
      return;
    }
    direccionMov = 'L';
  }else if (digitalRead(30) == HIGH) {
    //Codigo Derecha
    if (direccionMov == 'R') {
      return;
    }
    direccionMov = 'R';
  }else{
    return;
  }
  moverSnake();
  estasMuerto();
  pintarSnake();
  tiempoInicio = millis();
}
//-----------------------------------------------------------------------------------------------------------

//---------------------------------------PINTAR MATRICES-------------------------------------------------------
void pintarMatriz8x16(int fila, int column){
  if (!(fila >= 0 && fila <8)) {
    return;
  }
  if (column >= 0 && column <8) {
    matriz.setLed(0,fila, column, true);
  }else if(column > 7 && column < 16){
    matriz.setLed(1,fila, column-8 ,true);
  }
}
//----------------------------------------------------------------------------------------------------------------

//--------------------------------------------MENSAJE-------------------------------------------------------------
byte letras[18][5][5] = { \
                                /*Numeros "0"*/
                                { {0,1,1,1,0},\
                                  {1,0,0,1,1},\
                                  {1,0,1,0,1},\
                                  {1,1,0,0,1},\
                                  {0,1,1,1,0} },\
                                 /*Numeros "1"*/
                                { {0,1,1,0,0},\
                                  {0,0,1,0,0},\
                                  {0,0,1,0,0},\
                                  {0,0,1,0,0},\
                                  {0,1,1,1,0} },\
                                 /*Numeros "2"*/
                                { {1,1,1,1,0},\
                                  {0,0,0,0,1},\
                                  {0,1,1,1,0},\
                                  {1,0,0,0,0},\
                                  {1,1,1,1,1} },\
                                 /*Numeros "3"*/
                                { {1,1,1,1,0},\
                                  {0,0,0,0,1},\
                                  {0,0,1,1,0},\
                                  {0,0,0,0,1},\
                                  {1,1,1,1,0} },\
                                 /*Numeros "4"*/
                                { {0,0,1,1,0},\
                                  {0,1,0,1,0},\
                                  {1,0,0,1,0},\
                                  {1,1,1,1,1},\
                                  {0,0,0,1,0} },\
                                 /*Numeros "5"*/
                                { {1,1,1,1,1},\
                                  {1,0,0,0,0},\
                                  {1,1,1,1,0},\
                                  {0,0,0,0,1},\
                                  {1,1,1,1,0} },\
                                 /*Numeros "6"*/
                                { {0,1,1,1,1},\
                                  {1,0,0,0,0},\
                                  {1,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {0,1,1,1,0} },\
                                 /*Numeros "7"*/
                                { {1,1,1,1,1},\
                                  {0,0,0,0,1},\
                                  {0,0,0,1,0},\
                                  {0,0,1,0,0},\
                                  {0,1,0,0,0} },\
                                 /*Numeros "8"*/
                                { {0,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {0,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {0,1,1,1,0} },\
                                 /*Numeros "9"*/
                                { {0,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {0,1,1,1,1},\
                                  {0,0,0,0,1},\
                                  {1,1,1,1,0} },\
                                 /*Letra "G"*/
                                { {0,1,1,1,1},\
                                  {1,0,0,0,0},\
                                  {1,0,0,1,1},\
                                  {1,0,0,0,1},\
                                  {0,1,1,1,1} },\
                                 /*Letra "A"*/
                                { {0,0,1,0,0},\
                                  {0,1,0,1,0},\
                                  {1,0,0,0,1},\
                                  {1,1,1,1,1},\
                                  {1,0,0,0,1} },\
                                 /*Letra "M"*/
                                { {1,0,0,0,1},\
                                  {1,1,0,1,1},\
                                  {1,0,1,0,1},\
                                  {1,0,0,0,1},\
                                  {1,0,0,0,1} },\
                                 /*Letra "E"*/
                                { {1,1,1,1,1},\
                                  {1,0,0,0,0},\
                                  {1,1,1,0,0},\
                                  {1,0,0,0,0},\
                                  {1,1,1,1,1} },\
                                 /*Letra "O"*/
                                { {0,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {1,0,0,0,1},\
                                  {1,0,0,0,1},\
                                  {0,1,1,1,0} },\
                                 /*Letra "V"*/
                                { {1,0,0,0,1},\
                                  {1,0,0,0,1},\
                                  {1,0,0,0,1},\
                                  {0,1,0,1,0},\
                                  {0,0,1,0,0} },\
                                 /*Letra "R"*/
                                { {1,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {1,1,1,1,0},\
                                  {1,0,0,0,1},\
                                  {1,0,0,0,1} },\
                                /*Guion -*/
                                { {0,0,0,0,0},\
                                  {0,0,0,0,0},\
                                  {0,1,1,1,0},\
                                  {0,0,0,0,0},\
                                  {0,0,0,0,0} },\
                       };

bool actualizarMensaje(int filaInicial,int columnInicial,int mensaje[],int longitud,int desplazamiento){
  matriz.clearDisplay(0);
  matriz.clearDisplay(1);
  for (int l = 0; l<longitud; l++) {
    if( mensaje[l] == -1 ){
      columnInicial = columnInicial+2;
      continue;
    }
    if ((columnInicial-desplazamiento) > 15) {
      return false;
    }
    for (int fila =0; fila <5 ; fila++) {
      for (int column =0; column <5; column++) {
        int colAbsoluta = (column + columnInicial) - desplazamiento;
        if ( colAbsoluta > 15 ) {
          continue;
        }
        if ( colAbsoluta < 0 ) {
          continue;
        }
        byte led = letras[mensaje[l]][fila][column]; 
        if( led == 0 ){
          continue;
        }
        pintarMatriz8x16(fila+filaInicial, colAbsoluta);
      }
    }
    if ((columnInicial-desplazamiento+4) <= 15 && l == longitud-1) {
        return true;
    }
    columnInicial = columnInicial + 6;
  }
  return false;
}

void mostrarMensaje(int filaInicial,int colInicial,int mensaje[],int longitud,int retrasoFinal,int velocidadMov){
  boolean terminoMensaje = actualizarMensaje(filaInicial, colInicial, mensaje, longitud, 0);
  int desplazamiento = 0;
  while (!terminoMensaje) {
    tiempoActual = millis();
    if (tiempoActual - tiempoInicio >= velocidadMov) {
      terminoMensaje = actualizarMensaje(filaInicial, colInicial, mensaje, longitud, desplazamiento);
      tiempoInicio = tiempoActual;
      desplazamiento++;
    }
  }
  delay(retrasoFinal);
}
//------------------------------------------------------------------------------------------------------------
//-------------------------------------------Elegir Velocidad-------------------------------------------------
void elegirVelocidad(){
  tiempoInicio = millis();
  int mensajeVelocidad[3] = {0,-1,1};
  mostrarMensaje(2,1,mensajeVelocidad,3,0,100);
  //boolean aceptar = false;
  velocidad = 1;
  while (true) {
    presiono3Segundo();
    if(cambioDeModo){
      cambioDeModo = false;
      return;
    }
    tiempoActual = millis();
    if (tiempoActual - tiempoInicio < 300) {
      continue;
    }
    if (digitalRead(23) == HIGH) {
      //Codigo Para Arriba
      velocidad++;
      if (velocidad > 4) {
        velocidad = 1;
      }
    }else if (digitalRead(25) == HIGH) {
      //Codigo Abajo
      velocidad--;
      if (velocidad < 1) {
        velocidad = 4;
      }
    }else{
      continue;
    }
    tiempoInicio = tiempoActual;
    int decenas = velocidad / 10;
    int unidades = velocidad % 10;
    mensajeVelocidad[0] = decenas;
    mensajeVelocidad[2] = unidades;
    mostrarMensaje(2,1,mensajeVelocidad,3,0,100);
  }
}
//------------------------------------------------------------------------------------------------------------
void setup() {
  int pines_Control[] = {23,25,28,30,10}; // Pines de control de Movimiento
  for (int i = 0; i < 5 ; i++) {
    pinMode(pines_Control[i],INPUT);
  }
  matriz.shutdown(0,false); //Modo normal
  matriz.shutdown(1,false); 
  matriz.setIntensity(0,15);  //Intensidad
  matriz.setIntensity(1,15);  //Intensidad
  for (int i = 0; i <= 7; i++ ) {
    pinMode(i, OUTPUT);
  }
  for (int i = 14; i <= 21; i++ ) {
    pinMode(i, OUTPUT);
  }
  for (int i = 0; i <= 7; i++ ) {
    digitalWrite(i, LOW);
  }
  for (int i = 14; i <= 21; i++ ) {
    digitalWrite(i, HIGH);
  }
  pinMode(53,INPUT);
  pinMode(52,INPUT);
  pinMode(10,INPUT);
}

void loop() {
  mostrarMensajeMatriz();
  juegoSnake();
}
