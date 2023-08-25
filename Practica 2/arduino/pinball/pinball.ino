

byte secuencia[4][4] = { 
                          {1,1,0,0}, //Paso1
                          {0,1,1,0}, //Paso2
                          {0,0,1,1}, //Paso3
                          {1,0,0,1}, //Paso4
                       };

void setup() {
  //pinMode(13, INPUT_PULLUP); 
  //pinMode(12, INPUT_PULLUP);
  //pinMode(6,OUTPUT);
  pinMode(11, OUTPUT); //IN1
  pinMode(10, OUTPUT); //IN2
  pinMode(9, OUTPUT);  //IN3
  pinMode(8, OUTPUT);  //IN4
}

void loop() {
  for (byte paso =0; paso<4; paso++) {
    for (byte bobina=0; bobina<4; bobina++) {
      digitalWrite(11-bobina,secuencia[paso][bobina]);
    }
    delay(2);
  }
}
