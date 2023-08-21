#include <LiquidCrystal.h>

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
//
LiquidCrystal lcd(40,38,36,34,32,30);
void setup() {
 lcd.begin(16,2);
 pinMode(btn_izq, INPUT);
 pinMode(btn_der, INPUT);
}

void mensajes(){
  if(mostrado==false)
    mensaje_inicial();
  menu();

}
void menu(){
  if(selecciono==false){
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
        delay(1000);
        opcion=1;
      }else if (opcion==1) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("->Nuevo Juego");
        lcd.setCursor(0,1);
        lcd.print("Puntajes Altos");
        delay(1000);
        opcion=0;
      }
    
    }else if(boton==1){
      if(opcion==0){
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ustede selecciono:");
        lcd.setCursor(0, 1);
        lcd.print("*Nuevo Juego*");
        selecciono=true;
        //codigo para nuevo juego.
      }else{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ustede selecciono:");
        lcd.setCursor(0, 1);
        lcd.print("*Puntajes Altos");
        selecciono=true;
        //codigo para puntajes altos
      }
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

int contador=0;
void loop() {
  mensajes();

}
