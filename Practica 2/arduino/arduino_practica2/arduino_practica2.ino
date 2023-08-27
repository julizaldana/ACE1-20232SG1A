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
//Arreglo de top 10 puntajes
int top[10]={0,0,0,0,0,0,0,0,0,0};
int contador_puntaje=0;
LiquidCrystal lcd(40,38,36,34,32,30);

void setup() {
 lcd.begin(16,2);
 pinMode(btn_izq, INPUT);
 pinMode(btn_der, INPUT);
randomSeed(analogRead(A0));
 
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
        int numeroAleatorio = random(0, 100);
        agregar_puntaje(numeroAleatorio);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Puntaje agregado:");
        lcd.setCursor(0, 1);
        lcd.print(numeroAleatorio);
        delay(500);
        lcd.clear();
        //*************** CODIGO PARA JUEGO NUEVO******************
        //EL CODIGO ANTERIOR ES DE PRUEBA PARA INGRESAR NUMEROS RANDOM 
        //Y PROBAR EL ORDENAMIENTO Y LA MUESTRA DEL TOP.
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


void loop() {
  mensajes();
  
  
}
