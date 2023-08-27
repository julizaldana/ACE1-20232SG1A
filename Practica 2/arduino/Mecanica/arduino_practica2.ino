//Libreria para manejar pantalla LCD
#include <LiquidCrystal.h>

//Libreria para manejar la comunicacion I2C
#include <Wire.h>

//variable de mensaje inicio
bool mostrado=false;

//pines de botones
int btn_izq=26;
int btn_der=28;

//variables para el menu
int opcion=0;
bool entre=false;
int boton=3;
bool selecciono =false;
bool configJuego = true;
bool paletas = false;



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

//Configuracion inicial
void setup() {
  Wire.begin(); //Se inicia la comunicacion I2C como maestro
  Serial.begin(9600);
  lcd.begin(16,2); //Se inicializa la pantalla LCD
  pinMode(btn_izq, INPUT);
  pinMode(btn_der, INPUT); 
  lcd.createChar(0,customCharVida);
  lcd.createChar(1,customCharNoVida);
}

//Funcion mostrar primero mensaje y despues el menu
void mensajes(){
  if(mostrado==false)
    mensaje_inicial();
  menu();

}

//Funcion mostrar el menu
void menu(){
  if(selecciono==false){
    if(entre==false){
      //Primera entrada del menu
      lcd.setCursor(0,0);
      lcd.print("->Nuevo Juego");
      lcd.setCursor(0,1);
      lcd.print("Puntajes Altos");
      entre=true;
    }

    // Se analiza si hay un cambio en el boton que selecciona
    while(digitalRead(btn_izq)==LOW || digitalRead(btn_der)==LOW){  
      if (digitalRead(btn_izq)==HIGH) {
        boton=0; //Cambio de seleccion
        break;       
      }else if( digitalRead(btn_der)==HIGH){
        boton=1; //Entra a la opcion
        break;     
      }
    }
    //Cambie la opcion
    if(boton==0){
      if (opcion==0) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Nuevo Juego");
        lcd.setCursor(0,1);
        lcd.print("->Puntajes Altos");
        opcion=1;
        delay(500);
      }else if (opcion==1) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("->Nuevo Juego");
        lcd.setCursor(0,1);
        lcd.print("Puntajes Altos");
        opcion=0;
        delay(500);
      }
    //Entre a la opcion
    }else if(boton==1){
      if(opcion==0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Comenzando juego:");
        selecciono=true;
        delay(1000);
        config_juego();
        //codigo para nuevo juego.
      }else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Usted selecciono:");
        lcd.setCursor(0, 1);
        lcd.print("*Puntajes Altos");
        selecciono=true;
        //codigo para puntajes altos
      }
    }
  }
}

//Configuracion de pantalla para el mensaje inicial
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

    }
    //AQUI SE GUARDA EL PUNTAJE FINAL
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

int contador=0;
void loop() {
  mensajes();
  juego();

}
