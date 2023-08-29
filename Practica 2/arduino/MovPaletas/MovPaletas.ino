//CONFIGURACIÓN PALETAS CON MOTORES DC 12V Y L298N


//pines de botones
int btn_izq=13;
int btn_der=12;

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

void loop() {
  moverPaletas();
}




