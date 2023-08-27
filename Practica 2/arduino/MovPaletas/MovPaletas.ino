//CONFIGURACIÓN PALETAS CON MOTORES DC 12V Y L298N


//pines de botones
int btn_izq=26;
int btn_der=28;

//Declaración de Pines - L298N
//MOTOR A - MOTOR PALETA IZQUIERDA 
int ENA = 9; 
int In1 = 8;
int In2 = 7;
//MOTOR B - MOTOR PALETA - DERECHA
int In3 = 5;
int In4 = 4;
int ENB = 3; 

int SPEED = 210;
bool paletas = false;

void setup() {
  // Se debe de inicializar los pines digitales en Arduino
  pinMode(ENA, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);

  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  pinMode(ENB, OUTPUT)

  //pines de botones
  pinMode(btn_izq, INPUT);
  pinMode(btn_der, INPUT);


  //Aquí se setea la velocidad; puede ser de 0 a 255 para motores DC
  analogWrite(ENA,SPEED);
  analogWrite(ENB,SPEED)  
}

void moverPaletas() {
  //Leer los botones
  bool btnIzqPresionado = digitalRead(btn_izq) == LOW;
  bool btnDerPresionado = digitalRead(btn_der) == LOW;

  //Si el botón izquierdo es presionado
  if (btnIzqPresionado) {
    digitalWrite(In1, LOW);
    digitalWrite(In2, HIGH);
    delay(1000); //Se puede ajustar el delay, dependiendo de la cantidad de tiempo del giro de la paleta
    digitalWrite(In1, HIGH);
    digitalWrite(In2, LOW);
  }

  //Si el botón derecho es presionado
  if (btnDerPresionado) {
    digitalWrite(In3, LOW);
    digitalWrite(In4, HIGH);
    delay(1000);
    digitalWrite(In3, HIGH);
    digitalWrite(In4, LOW);
  }

}



void loop() {
  // put your main code here, to run repeatedly:
  moverPaletas();
}




