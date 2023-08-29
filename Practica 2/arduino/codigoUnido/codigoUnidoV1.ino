//Libreria para manejar pantalla LCD
#include <LiquidCrystal.h>

//Libreria para manejar la comunicacion I2C
#include <Wire.h>

//variable de mensaje inicio
bool mostrado=false;
//pines de botones
int btn_izq=13;
int btn_der=12;
//variables para el menu
int opcion=0;
bool entre=false;
int boton=3;
bool selecciono =false;
bool configJuego = true;
bool paletas = false;

//Arreglo de top 10 puntajes
int top[10]={0,0,0,0,0,0,0,0,0,0};
int contador_puntaje=0;
//Se configura la pantalla LCD
LiquidCrystal lcd(40,38,36,34,32,30);
//Se crean caracteres que representan las vidas
const byte customCharVida[8] = {
  B00000,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110,
  B00000,
  B00000
};
const byte customCharNoVida[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01110,
  B00000,
  B00000
};
//CONFIGURACIÓN PALETAS CON MOTORES DC 12V Y L298N
//Declaración de Pines - L298N
//MOTOR A - MOTOR PALETA IZQUIERDA  
int In1 = 11; //Cable Negro Motor 1 Bajar
int In2 = 10; //Cable Blanco Motro 1 Subir
//MOTOR B - MOTOR PALETA - DERECHA
int In3 = 9; //Cable Blanco Motor 2 Bajar
int In4 = 8; //Cable Negro Motor 2 Subir
//Cable Negro Motor 1  y 2 Abajo
bool paletas = false;

void setup() {
  Wire.begin(); //Se inicia la comunicacion I2C como maestro
  Serial.begin(9600);
  lcd.begin(16,2);
  pinMode(btn_izq, INPUT);
  pinMode(btn_der, INPUT);
  randomSeed(analogRead(A0));
  lcd.createChar(0,customCharVida);
  lcd.createChar(1,customCharNoVida);
  
  // Se deben de inicializar los pines digitales desde el L298N en Arduino
  //Pines Modulo Puente H
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  //pines de botones
  pinMode(btn_izq, INPUT_PULLUP);
  pinMode(btn_der, INPUT_PULLUP);
  //Estado Inicial
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
 
}

int estado_anterior_btn_Izquierdo = HIGH;    
bool cambio_detectado_btn_Izquierdo = false;

boolean pulsacionBtnIzquierdo(){
  int estado_actual = digitalRead(btn_izq);
  if (estado_actual != estado_anterior_btn_Izquierdo) {
    if (estado_actual == LOW) {
      cambio_detectado_btn_Izquierdo = true;
      estado_anterior_btn_Izquierdo = estado_actual;
      delay(1);
    }else if(estado_actual == HIGH && cambio_detectado_btn_Izquierdo == true){  
      cambio_detectado_btn_Izquierdo = false;
      estado_anterior_btn_Izquierdo = estado_actual;
      delay(1);
      return true; //Pulsacion Detectada
    }
  }
  return false; //Pulsacion No Detectada
} 

int estado_anterior_btn_Derecho = HIGH;    
bool cambio_detectado_btn_Derecho = false;

boolean pulsacionBtnDerecho(){
  int estado_actual = digitalRead(btn_der);
  if (estado_actual != estado_anterior_btn_Derecho) {
    if (estado_actual == LOW) {
      cambio_detectado_btn_Derecho = true;
      estado_anterior_btn_Derecho = estado_actual;
      delay(1);
    }else if(estado_actual == HIGH && cambio_detectado_btn_Derecho == true){  
      cambio_detectado_btn_Derecho = false;
      estado_anterior_btn_Derecho = estado_actual;
      delay(1);
      return true; //Pulsacion Detectada
    }
  }
  return false; //Pulsacion No Detectada
}

//Funcion para mover paletas con motores DC
void moverPaletas() {
  //Si el botón izquierdo es presionado
  if (pulsacionBtnIzquierdo()) {
    //Mover Hacia Arriba
    digitalWrite(In1, LOW);   //Cable Negro
    digitalWrite(In2, HIGH);  //Cable Blanco
    delay(20); //Tiempo Prendido
    digitalWrite(In1, LOW);  
    digitalWrite(In2, LOW);
    delay(400);
    //Mover Hacia Abajo
    digitalWrite(In1, HIGH);   //Cable Negro
    digitalWrite(In2, LOW);  //Cable Blanco
    delay(5); //Tiempo Prendido
    digitalWrite(In1, LOW);  
    digitalWrite(In2, LOW);
  }

  
  //Si el botón derecho es presionado
  if (pulsacionBtnDerecho()) {
    //Mover Hacia Arriba
    digitalWrite(In3, LOW);   //Cable Negro
    digitalWrite(In4, HIGH);  //Cable Blanco
    delay(25); //Tiempo Prendido
    digitalWrite(In3, LOW);  
    digitalWrite(In4, LOW);
    delay(400);
    //Mover Hacia Abajo
    digitalWrite(In3, HIGH);   //Cable Negro
    digitalWrite(In4, LOW);  //Cable Blanco
    delay(7); //Tiempo Prendido
    digitalWrite(In3, LOW);  
    digitalWrite(In4, LOW);
  }
}

void actualizar_puntajes(int puntaje){
  int posicionMinimo = 0; 

  for (int i = 1; i < 10; i++) {
    if (top[i] < top[posicionMinimo]) {
      posicionMinimo = i;
    }
  }
  top[posicionMinimo]=puntaje;

}

void ordenar_puntajes(){
  for (int i = 0; i < 10 - 1; i++) {
    for (int j = 0; j < 10 - i - 1; j++) {
      if (top[j] < top[j + 1]) {
        // Intercambiar los valores
        int temp = top[j];
        top[j] = top[j + 1];
        top[j + 1] = temp;
      }
    }
  }
}

void mostrar_puntajes(){
  
  int posicion=1;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Presione un");
  lcd.setCursor(0,1);
  lcd.print("boton.");
 
  for(int i=0;i<10;i++){

    //esperar a que se presione un boton
    while(digitalRead(btn_izq)==LOW || digitalRead(btn_der)==LOW){  
      if (digitalRead(btn_izq)==HIGH) {
        boton=0; 
        break;       
      }else if( digitalRead(btn_der)==HIGH){
        boton=1;   
        break;     
      }
    }
    //anti rebote
    while (digitalRead(btn_izq)==HIGH || digitalRead(btn_der)==HIGH ){
     
    }

    if (boton==0){
      if(top[i]!=0){
        int puntaje=top[i];
        if(posicion==1){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("PRIMER LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==2){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SEGUNDO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==3){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("TERCER LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==4){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("CUARTO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==5){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("QUINTO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==6){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SEXTO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==7){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("SEPTIMO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==8){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("OCTAVO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==9){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("NOVENO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
        }
        else if(posicion==10){
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("DECIMO LUGAR");
          lcd.setCursor(0,1);
          lcd.print(puntaje);
          posicion++;
          delay(2000);
        }
      
      }else{
        break;
      }
    }else if(boton==1){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("saliendo...");
      delay(250);
      lcd.clear();
      break;
    }

    
  }

}

void agregar_puntaje(int valor){
  if (contador_puntaje < 10) { 
    top[contador_puntaje] = valor; // Agregar el valor al arreglo
    contador_puntaje++; // Incrementar el contador
  } else {
    actualizar_puntajes(valor);
  }
}

void mensajes(){
  if(mostrado==false)
    mensaje_inicial();
  menu();

}
void menu(){
  
    if(entre==false){
      lcd.setCursor(0,0);
      lcd.print("->Nuevo Juego");
      lcd.setCursor(0,1);
      lcd.print("Puntajes Altos");
      entre=true;
    }
  
    while(digitalRead(btn_izq)==LOW || digitalRead(btn_der)==LOW){  
      if (digitalRead(btn_izq)==HIGH) {
        boton=0; 
        break;       
      }else if( digitalRead(btn_der)==HIGH){
        boton=1;   
        break;     
      }
    }
    while (digitalRead(btn_izq)==HIGH || digitalRead(btn_der)==HIGH ){
     
    }

    if(boton==0){
      if (opcion==0) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Nuevo Juego");
        lcd.setCursor(0,1);
        lcd.print("->Puntajes Altos");
        
        opcion=1;
      }else if (opcion==1) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("->Nuevo Juego");
        lcd.setCursor(0,1);
        lcd.print("Puntajes Altos");
        
        opcion=0;
      }
    
    }else if(boton==1){
      if(opcion==0){
        //*************** CODIGO PARA JUEGO NUEVO******************
        juego();              
        //*************** CODIGO PARA JUEGO NUEVO******************
        entre=false;
        boton=3;
        opcion=0;
        menu();
      }else{
        
        ordenar_puntajes();
        mostrar_puntajes();
        entre=false;
        boton=3;
        opcion=0;
        menu();
      }
    }
  
}

void mensaje_inicial(){
  //(columna,fila)
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Grupo #1");
 lcd.setCursor(0,1);
 lcd.print("Sergio Ralda");
 delay(1000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Grupo #1");
 lcd.setCursor(0,1);
 lcd.print("Jose Panaza"); 
 delay(1000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Grupo #1");
 lcd.setCursor(0,1);
 lcd.print("Julio Zaldana"); 
 delay(1000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Grupo #1");
 lcd.setCursor(0,1);
 lcd.print("Paulo Merida"); 
 delay(1000);
 lcd.clear();
 mostrado=true;
}

void config_juego(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Preparando");
    lcd.setCursor(0,1);
    lcd.print("Software..."); 

    //Se manda cadena para inicio de secuencia de LEDS
    Wire.beginTransmission(8); // Se inicia la comunicacion con el esclavo
    Wire.write("INICIO");
    Wire.endTransmission();
    delay(1000);
    //Se recibe la señal cuando la pelota pasa por primera vez
    while(configJuego){
      Wire.requestFrom(8,6);
      String receivedData = "";

      while(Wire.available()){
        char c = Wire.read();
        receivedData += c;
      }

      //Cuando ya coincida la cadena 
      if(receivedData == "INICIO"){
        configJuego = false;
      }
      configJuego = false; //solo para probar, esto se quita
    }
    paletas = true;


}

//Variable para el Juego
int nivel = 1;
long puntaje = 0;
int vidas = 3;


void juego(){
  if(configJuego == false ){
    while(vidas > 0){
      vidas -= 1;
      //Verifico y actualizo los datos
      actualizar_datos();
      lcd.clear();
      //Se imprime en la primera fila: NIVEL #NUM #VIDAS
      lcd.setCursor(0,0);
      lcd.print("NIVEL ");
      lcd.print(String(nivel));
      lcd.print("    ");
      for (int i=0; i<vidas;i++){
        lcd.write(byte(0));
        lcd.print(" ");
      }
      for(int i=0;i<3-vidas;i++){
        lcd.write(byte(1));
        lcd.print(" ");
      }
      
      //Se imprime en la segunda fila:          #PUNTAJE
      lcd.setCursor(8,1);
      if(puntaje < 10){
        lcd.print("0000000");
      }
      else if(puntaje < 100){
        lcd.print("000000");
      }
      else if(puntaje < 1000){
        lcd.print("00000");
      }
      else if(puntaje < 10000){
        lcd.print("0000");
      }
      else if(puntaje < 100000){
        lcd.print("000");
      }
      else if(puntaje < 1000000){
        lcd.print("00");
      }
      else if(puntaje < 10000000){
        lcd.print("0");
      }
      lcd.print(String(puntaje));
      delay(500);
      //funcion para escuchar botones que mueven motores
      moverPaletas();

    }

    
    agregar_puntaje(puntaje);  
    delay(1000);
    //Aqui ya perdio el jugador
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GAME");
    lcd.setCursor(7,1);
    lcd.print("OVER!");

    //Inicializar variables para mostrar el mensaje
    selecciono = false;
    entre = false;
    configJuego = true;

    //Inicializar variables de juego
    nivel = 1;
    puntaje = 0;
    vidas = 3;
    delay(2000);
  }
}

void actualizar_datos(){
  // CAMBIO NIVEL: MASNIV
  // MAS PTS:      MASPTS
  // PIERDE VIDA:  PIVIDA

  Wire.requestFrom(8,6);
  String receivedData = "";

  while(Wire.available()){
    char c = Wire.read();
    receivedData += c;
  }

  //Cuando ya coincida la cadena 
  if(receivedData == "MASNIV"){
    nivel += 1;
  }
  else if(receivedData == "MASPTS"){
    int sum = nivel * 10;
    puntaje += sum;
  }
  else if(receivedData == "PIVIDA"){
    vidas -= 1;
  }

}

void loop() {
  mensajes();
  
  
}