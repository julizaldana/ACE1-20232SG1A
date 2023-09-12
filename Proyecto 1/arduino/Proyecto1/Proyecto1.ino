//Proyecto1 - Arqui1 - Lab Sección A - GRUPO 1

#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal pantalla(8, 9, 10, 11, 12, 13);

#define INICIALIZAR_TECLADO char tecla = ' '
#define TECLA_PRESIONADA tecla = leerTecla(); \
                         switch(tecla)
#define LOOP while(true)
#define LINEA_VACIA "                "
#define OFFSET_USUARIOS 1

char teclas[4][3] = { { '1', '2', '3' }, \
                      { '4', '5', '6' }, \
                      { '7', '8', '9' }, \
                      { '*', '0', '#' } };

char letras[] = "ABCDEFGHIJKL";

char leerTecla() {
    for (int i = 14; i <= 16; i++) {
        digitalWrite(i, HIGH);
        for (int j = 17; j <= 20; j++) {
            if (digitalRead(j) == HIGH) {
                digitalWrite(i, LOW);
                return teclas[j-17][i-14];
            }
        }
        digitalWrite(i, LOW);
    }
    return ' ';
}

struct usuario {
    char nombre[11];
    char contra[11];
    char numero[9] ;
};

void borrarEEPROM() {
    for (int i = 0; i < EEPROM.length(); i++)
        EEPROM.write(i, 0);
}

INICIALIZAR_TECLADO;
void setup() {
    Serial.begin(9600);  // INICIALIZAR PUERTO SERIAL
    pantalla.begin(16,4);
    for (int j = 17; j <= 20; j++) {
        pinMode(j, INPUT);
    }
    for (int j = 14; j <= 16; j++) {
        pinMode(j, OUTPUT);
    }
    pinMode(4, INPUT);
    pinMode(3, INPUT);
    //borrarEEPROM();
}

enum estados {
    MENU,
    REGISTRO,
    ESPERANDO,
    LOGIN,
    LOGS
} siguiente_estado, estado_actual = MENU;

byte opcion_menu = 0;
char nombre_temp[11];
char contra_temp[11];
char numero_temp[9] ;

boolean entradaAceptada() {
    LOOP {
        if (digitalRead(4)) {
	    delay(210);
	    return true;
	}
        if (digitalRead(3)) {
	    delay(210);
	    return false;
	}
    }
} 

void enviarConfirmar(char* cadena) {
    Serial.println(cadena);
    bool hayAlgo = false;
    char recibidos[3];
    LOOP {
        while(Serial.available()) {
	    Serial.readBytes(recibidos, 2);
            hayAlgo = true;
        }
        if (hayAlgo && !Serial.available()) break;
    }
}

void limpiarBuffer() {
    int t0 = millis();
    int t1 = millis();
    LOOP {
        t1 = millis();
        while(Serial.available()) {
	    Serial.read();
        }
        if ((t1 - t0 >= 1000) && !Serial.available()) break;
    }
}

void imprimirAsteriscos(char* cadena) {
    for (; *cadena; cadena++)
        pantalla.write('*');
}

void loop() {
    switch (estado_actual) {
        case ESPERANDO: {
	    limpiarBuffer();
	    pantalla.clear();
	    pantalla.print(" Esperando  una ");
	    pantalla.setCursor(0, 1);
	    pantalla.print("   conexion...  ");
	    bool alguienPorAhi = false;
            char recibidos[3];
	    LOOP {
	        while(Serial.available()) {
		    Serial.readBytes(recibidos, 2);
		    alguienPorAhi = true;
		}
		if (alguienPorAhi && !Serial.available()) break;
	    }
	    estado_actual = siguiente_estado;
	    break;
        }
        case MENU: {
            pantalla.clear();
            pantalla.setCursor(0, 0);
            pantalla.print("  LOGIN");  
            pantalla.setCursor(0, 1);
            pantalla.print("  REGISTRO");  
            pantalla.setCursor(0, 2);
            pantalla.print("  LOGS");  
            pantalla.setCursor(0, opcion_menu);
            pantalla.print(">");
            LOOP {
                bool salir = false;
                TECLA_PRESIONADA {
                    case '2': {
                        delay(210);
                        opcion_menu--;
                        if (opcion_menu < 0) opcion_menu = 0;
                        salir = true;
                        break;
                    }
                    case '8': {
                        delay(210);
                        opcion_menu++;
                        if (opcion_menu > 2) opcion_menu = 2;
                        salir = true;
                        break;
                    }
                    case '5': {
                        delay(210);
                        switch (opcion_menu) {
                            case 0: estado_actual = ESPERANDO;
                                    siguiente_estado = LOGIN;
                                    break;
                            case 1: estado_actual = ESPERANDO;
                                    siguiente_estado = REGISTRO;
                                    break;
                            case 2: estado_actual = ESPERANDO;
                                    break;
                        }
                        opcion_menu = 0;
                        salir = true;
                        break;
                    }
                }
                if (salir) break;
            }
            break;
        }
        case LOGIN: {
            memset(nombre_temp, 0, 11);    
            memset(contra_temp, 0, 11);    
            memset(numero_temp, 0,  9);    
            struct usuario nuevo_usuario;
	    LOOP {
	        limpiarBuffer();
	        enviarConfirmar("Nombre:");
            	memset(nombre_temp, 0, 11);    
                pantalla.clear();
                pantalla.print("L O G I N");
                pantalla.setCursor(0, 1);
                pantalla.print(" - NOMBRE:");
                pantalla.setCursor(0, 2);
                // OBTENER CADENA DE APLICACIÓN -- Nombre
                bool seEnvioAlgo = false;
                int indiceNombre = 0;
                long int t0 = millis();
                long int t1 = millis();
	        limpiarBuffer();
                LOOP {
                    // SI YA SE ENVIO ALGO DESDE LA APLICACION
                    while (Serial.available()) {
                        seEnvioAlgo = true;
                    //   RECIBIRLO
                        nombre_temp[indiceNombre++] = Serial.read();
                    }
                    // CONTROLAR CUANTO HA PASADO DESDE QUE COME...
                    if (seEnvioAlgo) {
                        t1 = millis();
                        if (t1 - t0 >= 500) break;
                    } else {
                        t0 = millis();
                        t1 = millis();
                    }
                }
                pantalla.print(nombre_temp);
                pantalla.setCursor(0, 3);
                pantalla.print("Correcto?       ");
                delay(500);
    	        if (entradaAceptada()) break;
		pantalla.setCursor(0, 2);
		pantalla.print(LINEA_VACIA);
		pantalla.setCursor(0, 3);
		pantalla.print(LINEA_VACIA);
            }
	    LOOP {
	        limpiarBuffer();
	        enviarConfirmar("Contras:");
            	memset(contra_temp, 0, 11);    
                pantalla.clear();
                pantalla.print("L O G I N");
                pantalla.setCursor(0, 1);
                pantalla.print(" - Contras:");
                pantalla.setCursor(0, 2);
                // OBTENER CADENA DE APLICACIÓN -- Nombre
                bool seEnvioAlgo = false;
                int indiceContra = 0;
                long int t0 = millis();
                long int t1 = millis();
	        limpiarBuffer();
                LOOP {
                    // SI YA SE ENVIO ALGO DESDE LA APLICACION
                    while (Serial.available()) {
                        seEnvioAlgo = true;
                    //   RECIBIRLO
                        contra_temp[indiceContra++] = Serial.read();
                    }
                    // CONTROLAR CUANTO HA PASADO DESDE QUE COME...
                    if (seEnvioAlgo) {
                        t1 = millis();
                        if (t1 - t0 >= 500) break;
                    } else {
                        t0 = millis();
                        t1 = millis();
                    }
                }
		imprimirAsteriscos(contra_temp);
                pantalla.setCursor(0, 3);
                pantalla.print("Correcto?       ");
                delay(500);
    	        if (entradaAceptada()) break;
		pantalla.setCursor(0, 2);
		pantalla.print(LINEA_VACIA);
		pantalla.setCursor(0, 3);
		pantalla.print(LINEA_VACIA);
            }
	    enviarConfirmar("NADA");
	    // LEER EEPROM
	    byte usuarios = 0;
	    EEPROM.get(0, usuarios);
	    int siguiente_direccion = OFFSET_USUARIOS;
	    bool encontrado = false;
	    for (int i = 0; i < usuarios; i++) {
	        struct usuario usuario_existente;
		EEPROM.get(siguiente_direccion, usuario_existente);
		if (strcmp(nombre_temp, usuario_existente.nombre) == 0 && \
		    strcmp(contra_temp, usuario_existente.contra) == 0) {
		    encontrado = true;
		}
	        siguiente_direccion += sizeof(struct usuario);
	    }
	    pantalla.clear();
	    if (encontrado) pantalla.print("ENCONTRADO");
	    else pantalla.print("NO ENCONTRADO");
	    siguiente_estado = MENU;
	    delay(2000);
            break;
        }
        case REGISTRO: {
            memset(nombre_temp, 0, 11);    
            memset(contra_temp, 0, 11);    
            memset(numero_temp, 0,  9);    
            struct usuario nuevo_usuario;
	    LOOP {
	        limpiarBuffer();
	        enviarConfirmar("Nombre:");
            	memset(nombre_temp, 0, 11);    
                pantalla.clear();
                pantalla.print("R E G I S T R O");
                pantalla.setCursor(0, 1);
                pantalla.print(" - NOMBRE:");
                pantalla.setCursor(0, 2);
                // OBTENER CADENA DE APLICACIÓN -- Nombre
                bool seEnvioAlgo = false;
                int indiceNombre = 0;
                long int t0 = millis();
                long int t1 = millis();
	        limpiarBuffer();
                LOOP {
                    // SI YA SE ENVIO ALGO DESDE LA APLICACION
                    while (Serial.available()) {
                        seEnvioAlgo = true;
                    //   RECIBIRLO
                        nombre_temp[indiceNombre++] = Serial.read();
                    }
                    // CONTROLAR CUANTO HA PASADO DESDE QUE COME...
                    if (seEnvioAlgo) {
                        t1 = millis();
                        if (t1 - t0 >= 500) break;
                    } else {
                        t0 = millis();
                        t1 = millis();
                    }
                }
                pantalla.print(nombre_temp);
                pantalla.setCursor(0, 3);
                pantalla.print("Correcto?       ");
                delay(500);
    	        if (entradaAceptada()) break;
		pantalla.setCursor(0, 2);
		pantalla.print(LINEA_VACIA);
		pantalla.setCursor(0, 3);
		pantalla.print(LINEA_VACIA);
            }
	    LOOP {
	        limpiarBuffer();
	        enviarConfirmar("Celular:");
            	memset(numero_temp, 0, 9);    
                pantalla.clear();
                pantalla.print("R E G I S T R O");
                pantalla.setCursor(0, 1);
                pantalla.print(" - Celular:");
                pantalla.setCursor(0, 2);
                // OBTENER CADENA DE APLICACIÓN -- Nombre
                bool seEnvioAlgo = false;
                int indiceNumero = 0;
                long int t0 = millis();
                long int t1 = millis();
	        limpiarBuffer();
                LOOP {
                    // SI YA SE ENVIO ALGO DESDE LA APLICACION
                    while (Serial.available()) {
                        seEnvioAlgo = true;
                    //   RECIBIRLO
                        numero_temp[indiceNumero++] = Serial.read();
                    }
                    // CONTROLAR CUANTO HA PASADO DESDE QUE COME...
                    if (seEnvioAlgo) {
                        t1 = millis();
                        if (t1 - t0 >= 500) break;
                    } else {
                        t0 = millis();
                        t1 = millis();
                    }
                }
                pantalla.print(numero_temp);
                pantalla.setCursor(0, 3);
                pantalla.print("Correcto?       ");
                delay(500);
    	        if (entradaAceptada()) break;
		pantalla.setCursor(0, 2);
		pantalla.print(LINEA_VACIA);
		pantalla.setCursor(0, 3);
		pantalla.print(LINEA_VACIA);
            }
	    LOOP {
	        limpiarBuffer();
	        enviarConfirmar("Contras:");
            	memset(contra_temp, 0, 11);    
                pantalla.clear();
                pantalla.print("R E G I S T R O");
                pantalla.setCursor(0, 1);
                pantalla.print(" - Contras:");
                pantalla.setCursor(0, 2);
                // OBTENER CADENA DE APLICACIÓN -- Nombre
                bool seEnvioAlgo = false;
                int indiceContra = 0;
                long int t0 = millis();
                long int t1 = millis();
	        limpiarBuffer();
                LOOP {
                    // SI YA SE ENVIO ALGO DESDE LA APLICACION
                    while (Serial.available()) {
                        seEnvioAlgo = true;
                    //   RECIBIRLO
                        contra_temp[indiceContra++] = Serial.read();
                    }
                    // CONTROLAR CUANTO HA PASADO DESDE QUE COME...
                    if (seEnvioAlgo) {
                        t1 = millis();
                        if (t1 - t0 >= 500) break;
                    } else {
                        t0 = millis();
                        t1 = millis();
                    }
                }
		imprimirAsteriscos(contra_temp);
                pantalla.setCursor(0, 3);
                pantalla.print("Correcto?       ");
                delay(500);
    	        if (entradaAceptada()) break;
		pantalla.setCursor(0, 2);
		pantalla.print(LINEA_VACIA);
		pantalla.setCursor(0, 3);
		pantalla.print(LINEA_VACIA);
            }
	    enviarConfirmar("NADA");
	    //
	    memcpy(nuevo_usuario.nombre, nombre_temp, 11);
	    memcpy(nuevo_usuario.numero, numero_temp, 9);
	    memcpy(nuevo_usuario.contra, contra_temp, 11);
	    // LEER EEPROM
	    byte usuarios = 0;
	    EEPROM.get(0, usuarios);
	    int siguiente_direccion = OFFSET_USUARIOS;
	    for (int i = 0; i < usuarios; i++) {
	        siguiente_direccion += sizeof(struct usuario);
	    }
	    EEPROM.put(siguiente_direccion, nuevo_usuario);
	    usuarios++;
	    EEPROM.put(0, usuarios);
            estado_actual = MENU;
	    pantalla.clear();
            break;                         
        }                                  
        case LOGS: {
            pantalla.clear();
            pantalla.print("L  O  G  S");
            break;
        }
    }
    delay(10);
}