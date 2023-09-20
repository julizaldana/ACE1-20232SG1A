#include <EEPROM.h>
#include <LiquidCrystal.h>

LiquidCrystal pantalla(8, 9, 10, 11, 12, 13);

#define INICIALIZAR_TECLADO char tecla = ' '
#define TECLA_PRESIONADA \
  tecla = leerTecla(); \
  switch (tecla)
#define LOOP while (true)
#define LINEA_VACIA "                "

char teclas[4][3] = { { '1', '2', '3' },
                      { '4', '5', '6' },
                      { '7', '8', '9' },
                      { '*', '0', '#' } };

char letras[] = "ABCDEFGHIJKL";
String estado = "Normal";

//FUNCION PARA LEER UNA TECLA
char leerTecla() {
  for (int i = 14; i <= 16; i++) {
    digitalWrite(i, HIGH);
    for (int j = 17; j <= 20; j++) {
      if (digitalRead(j) == HIGH) {
        digitalWrite(i, LOW);
        return teclas[j - 17][i - 14];
      }
    }
    digitalWrite(i, LOW);
  }
  return ' ';
}

//ESTRUCTURA PARA EL USUARIO
struct usuario {
  char nombre[20];
  char password[10];
};

void borrarEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

INICIALIZAR_TECLADO;
char nombre_temp[20];
char password_temp[10];
char nombre_vacio[20];

void setup() {
  Serial.begin(9600);  // INICIALIZAR PUERTO SERIAL
  pantalla.begin(16, 4);
  for (int j = 17; j <= 20; j++) {
    pinMode(j, INPUT);
  }
  for (int j = 14; j <= 16; j++) {
    pinMode(j, OUTPUT);
  }
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  //borrarEEPROM();

  /*
  //CARGAR EL USUARIO DEL ADMIN
  memset(nombre_temp, 0, 20);
  memset(password_temp, 0, 10);
  String user = "A1801C";
  String pass = "331016";
  for(int i = 0; i < user.length(); i++){
    char carac = user.charAt(i);
    nombre_temp[i] = carac;
  }
  for(int i = 0; i < pass.length(); i++){
    char carac = pass.charAt(i);
    password_temp[i] = carac;
  }

  struct usuario nuevo_usuario;
  memcpy(nuevo_usuario.nombre, nombre_temp, 20);
  memcpy(nuevo_usuario.password, password_temp, 10);
  EEPROM.put(0,nuevo_usuario);
  */

  /* //INICIALIZAR ESTRUCTURAS EN LA EEPROM
  struct usuario nuevo_usuario;
  memset(nombre_temp, 0, 20);
  memset(password_temp, 0, 10);

  memcpy(nuevo_usuario.nombre, nombre_temp, 20);
  memcpy(nuevo_usuario.password, password_temp, 10);
  for (int i =0; i<20; i++){    
    EEPROM.put(i * sizeof(struct usuario),nuevo_usuario);
  }
  */
}

enum estados {
  ESPERANDO,
  MENU,
  CRUD,
  ESTADO, //aqui va lo de la temperatura
  PASS,
  DELETE,
  MOD,
  USUARIO //cuando se loguea un usuario
} anterior_estado,
  estado_actual = ESPERANDO, siguiente_estado = MENU;

//EL MENU SELECCIONADO
byte opcion_menu = 0;
byte opcion_crud = 0;

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

void limpiarBuffer() {
  int t0 = millis();
  int t1 = millis();

  LOOP {
    t1 = millis();
    while (Serial.available()) {
      Serial.read();
    }
    if ((t1 - t0 >= 1000) && !Serial.available()) break;
  }
}

void imprimirAsteriscos(char* cadena) {
  for (; *cadena; cadena++) {
    pantalla.write('*');
  }
}

void loop() {
  switch (estado_actual) {
    //CASO DONDE ESPERAN LAS CREEDENCIALES
    case ESPERANDO:
      {
        memset(nombre_temp, 0, 20);
        memset(password_temp, 0, 10);
        memset(nombre_vacio, 0, 20);
        struct usuario nuevo_usuario;
        limpiarBuffer();
        pantalla.clear();
        pantalla.print("Esperando ");
        pantalla.setCursor(0, 1);
        pantalla.print("credenciales...  ");
        bool seEnvioAlgo = false;
        long int t0 = millis();
        long int t1 = millis();
        String data[2];
        int indicedata = 0;
        LOOP {
          while (Serial.available()) {
            seEnvioAlgo = true;
            data[indicedata++] = Serial.readStringUntil('&');
          }
          // Controlar el tiempo que pasa desde que se lee
          if (seEnvioAlgo) {
            t1 = millis();
            if (t1 - t0 >= 500) break;
          } else {
            t0 = millis();
            t1 = millis();
          }
        }

        //Se evaluan si los datos cumplan con la longitud
        if (data[0].length() >= 20) {
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("Ocurrio un error:");
          pantalla.setCursor(0, 1);
          pantalla.print("Usuario excede");
          pantalla.setCursor(0, 2);
          pantalla.print("numero de bytes");
          estado_actual = ESPERANDO;
          break;
        }
        if (data[1].length() >= 10) {
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("Ocurrio un error:");
          pantalla.setCursor(0, 1);
          pantalla.print("Passw excede");
          pantalla.setCursor(0, 2);
          pantalla.print("numero de bytes");
          estado_actual = ESPERANDO;
          break;
        }

        //Si la longitud es aceptada, llena los temporales para despues ser comparados en la eeprom
        for (int i = 0; i < data[0].length(); i++) {
          nombre_temp[i] = data[0][i];
        }
        for (int i = 0; i < data[1].length(); i++) {
          password_temp[i] = data[1][i];
        }
        int siguiente_dir = 0;
        bool encontrado = false;
        for (int i = 0; i < 20; i++) {
          struct usuario usuario_existente;
          EEPROM.get(siguiente_dir, usuario_existente);
          //se verifica si viene vacio
          if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
            break;
          }
          if (strcmp(nombre_temp, usuario_existente.nombre) == 0 && strcmp(password_temp, usuario_existente.password) == 0) {
            encontrado = true;
            break;
          }
          siguiente_dir += sizeof(struct usuario);
        }
        pantalla.clear();
        if (encontrado) {
          //Se verifica si es el administrador
          if (data[0] == "A1801C") {
            pantalla.clear();
            pantalla.setCursor(0, 0);
            pantalla.print("Bienvenido");
            pantalla.setCursor(0, 1);
            pantalla.print("Administrador...");
            estado_actual = MENU;
            delay(300);
            limpiarBuffer();
            break;
            //ES EL ADMIN, SE MANDA AL CRUD
          }
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("Bienvenido");
          pantalla.setCursor(0, 1);
          pantalla.print(data[0] + "...");
          estado_actual = USUARIO;
          delay(300);
          limpiarBuffer();
          break;

        } else {
          pantalla.clear();
          pantalla.print("NO ENCONTRADO");
          estado_actual = ESPERANDO;
          Serial.print("ERR&");
          delay(300);
          limpiarBuffer();
          break;
        }
      }

    //CASO DONDE ESTE EL MENU
    case MENU:
      {
        pantalla.clear();
        pantalla.setCursor(0, 0);
        pantalla.print("  Estado: " + estado);
        pantalla.setCursor(0, 1);
        pantalla.print("  CRUD");
        pantalla.setCursor(0, opcion_menu);
        pantalla.print(">");
        LOOP {
          bool salir = false;
          TECLA_PRESIONADA {
            case '2':
              {
                delay(210);
                if (opcion_menu == 0) opcion_menu = 1;
                else opcion_menu--;
                salir = true;
                break;
              }
            case '8':
              {
                delay(210);
                if (opcion_menu == 1) opcion_menu = 0;
                else opcion_menu++;
                salir = true;
                break;
              }
            case '*':
              {
                delay(210);
                switch (opcion_menu) {
                  case 0:
                    estado_actual = ESTADO;
                    anterior_estado = MENU;
                    break;
                  case 1:
                    estado_actual = CRUD;
                    anterior_estado = MENU;
                    break;
                }
                opcion_menu = 0;
                salir = true;
                break;
              }
            case '#':
              {
                delay(210);
                anterior_estado = ESPERANDO;
                estado_actual = anterior_estado;
                siguiente_estado = estado_actual;
                opcion_menu = 0;
                salir = true;
                break;
              }
          }
          if (salir) break;
        }
        break;
      }
    //CASO DEL CRUD
    case CRUD:
      {
        pantalla.clear();
        pantalla.setCursor(0, 0);
        pantalla.print("  Ingresar pass");
        pantalla.setCursor(0, 1);
        pantalla.print("  Elimina user");
        pantalla.setCursor(0, 2);
        pantalla.print("  Mod user");
        pantalla.setCursor(0, opcion_crud);
        pantalla.print(">");
        LOOP {
          bool salir = false;
          TECLA_PRESIONADA {
            case '2':
              {
                delay(210);
                if (opcion_crud == 0) opcion_crud = 2;
                else opcion_crud--;
                salir = true;
                break;
              }
            case '8':
              {
                delay(210);
                if (opcion_crud == 2) opcion_crud = 0;
                else opcion_crud++;
                salir = true;
                break;
              }
            case '*':
              {
                delay(210);
                switch (opcion_crud) {
                  case 0:
                    estado_actual = PASS;
                    anterior_estado = CRUD;
                    break;
                  case 1:
                    estado_actual = DELETE;
                    anterior_estado = CRUD;
                    break;
                  case 2:
                    estado_actual = MOD;
                    anterior_estado = CRUD;
                    break;
                }
                opcion_crud = 0;
                salir = true;
                break;
              }
            case '#':
              {
                delay(210);
                anterior_estado = MENU;
                estado_actual = anterior_estado;
                siguiente_estado = estado_actual;
                opcion_crud = 0;
                salir = true;
                break;
              }
          }
          if (salir) break;
        }
        break;
      }
    //CASO PARA INTRODUCIR CONTRASEÑAS
    case PASS:
      {
        //struct usuario nuevo_usuario;
        LOOP {
          memset(nombre_temp, 0, 20);
          memset(password_temp, 0, 10);
          memset(nombre_vacio, 0, 20);
          limpiarBuffer();
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("R E G I S T R O");
          pantalla.setCursor(0, 1);
          pantalla.print("-User:");
          pantalla.setCursor(6, 1);
          Serial.print("ADM&");

          // Se obtiene el usuario de la aplicacion
          bool seEnvioAlgo = false;
          long int t0 = millis();
          long int t1 = millis();
          String usern;
          String contraC = "";
          int letra = 0;
          bool ret = false;
          LOOP {
            while (Serial.available()) {
              seEnvioAlgo = true;
              usern = Serial.readStringUntil('&');
            }
            // Controlar el tiempo que pasa desde que se lee
            if (seEnvioAlgo) {
              t1 = millis();
              if (t1 - t0 >= 500) break;
            } else {
              t0 = millis();
              t1 = millis();
            }
            TECLA_PRESIONADA {
              case '#':
                delay(210);
                ret = true;
                estado_actual = CRUD;
                anterior_estado = MENU;
                break;
            }
            if (ret) break;
          }
          if (ret) break;
          //Se evaluan si los datos cumplan con la longitud
          if (usern.length() >= 20) {
            pantalla.clear();
            pantalla.setCursor(0, 0);
            pantalla.print("Ocurrio un error:");
            pantalla.setCursor(0, 1);
            pantalla.print("Usuario excede");
            pantalla.setCursor(0, 2);
            pantalla.print("numero de bytes");
            break;
          }
          //Se llena el usuario
          for (int i = 0; i < usern.length(); i++) {
            nombre_temp[i] = usern[i];
          }
          //Se verifica que el usuario no exista
          int siguiente_dir = 0;
          bool encontrado = false;
          for (int i = 0; i < 20; i++) {
            struct usuario usuario_existente;
            EEPROM.get(siguiente_dir, usuario_existente);
            //se verifica si viene vacio
            if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
              break;
            }
            if (strcmp(nombre_temp, usuario_existente.nombre) == 0) {
              encontrado = true;
              break;
            }
            siguiente_dir += sizeof(struct usuario);
          }

          if (encontrado) {
            pantalla.clear();
            pantalla.setCursor(0, 0);
            pantalla.print("Ocurrio un error:");
            pantalla.setCursor(0, 1);
            pantalla.print("Usuario ya");
            pantalla.setCursor(0, 2);
            pantalla.print("esta registrado");
            break;
          }

          //Se muestra la contrasena
          pantalla.print(nombre_temp);
          pantalla.setCursor(0, 2);
          pantalla.print("-Pass:");
          String car = "";
          bool regresar = false;
          LOOP {
            pantalla.setCursor(5 + letra, 2);
            if (car != "") pantalla.print(car);
            bool salir = false;
            TECLA_PRESIONADA {
              case '0':
                delay(210);
                contraC += "0";
                car = "0";
                letra++;
                break;
              case '1':
                delay(210);
                contraC += "1";
                car = "1";
                letra++;
                break;
              case '2':
                delay(210);
                contraC += "2";
                car = "2";
                letra++;
                break;
              case '3':
                delay(210);
                contraC += "3";
                car = "3";
                letra++;
                break;
              case '4':
                delay(210);
                contraC += "4";
                car = "4";
                letra++;
                break;
              case '5':
                delay(210);
                contraC += "5";
                car = "5";
                letra++;
                break;
              case '6':
                delay(210);
                contraC += "6";
                car = "6";
                letra++;
                break;
              case '7':
                delay(210);
                contraC += "7";
                car = "7";
                letra++;
                break;
              case '8':
                delay(210);
                contraC += "8";
                car = "8";
                letra++;
                break;
              case '9':
                delay(210);
                contraC += "9";
                car = "9";
                letra++;
                break;
              case '*':
                delay(210);
                salir = true;
                break;
              case '#':
                delay(210);
                regresar = true;
                estado_actual = CRUD;
                anterior_estado = MENU;
                break;
            }
            if (regresar) break;
            if (salir) {
              if (contraC.length() > 10) {
                pantalla.clear();
                pantalla.setCursor(0, 0);
                pantalla.print("Ocurrio un error:");
                pantalla.setCursor(0, 1);
                pantalla.print("Passw excede");
                pantalla.setCursor(0, 2);
                pantalla.print("numero de bytes");
              } else {
                break;
              }
            };
          }
          if (regresar) break;

          for (int i = 0; i < contraC.length(); i++) {
            password_temp[i] = contraC[i];
          }
          //Se copian los usuarios
          struct usuario nuevo_usuario;
          memcpy(nuevo_usuario.nombre, nombre_temp, 20);
          memcpy(nuevo_usuario.password, password_temp, 10);

          siguiente_dir = 0;
          for (int i = 0; i < 20; i++) {
            struct usuario usuario_existente;
            EEPROM.get(siguiente_dir, usuario_existente);
            //se verifica si viene vacio
            if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
              break;
            }
            siguiente_dir += sizeof(struct usuario);
          }
          EEPROM.put(siguiente_dir, nuevo_usuario);
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("Usuario se ha");
          pantalla.setCursor(0, 1);
          pantalla.print("creado");
          pantalla.setCursor(0, 2);
          pantalla.print("correctamente");
          delay(1000);
        }
        break;
      }
    //CASO PARA ELIMINAR UN USUARIO
    case DELETE:
      {
        memset(nombre_vacio, 0, 20);
        pantalla.clear();
        pantalla.setCursor(0, 0);
        pantalla.print("Eliminar ");
        pantalla.setCursor(0, 1);
        pantalla.print("   Usuario...");
        int cont = 0;
        int siguiente_dir = 0;
        for (int i = 0; i < 20; i++) {
          struct usuario usuario_existente;
          EEPROM.get(siguiente_dir, usuario_existente);
          //se verifica si viene vacio
          siguiente_dir += sizeof(struct usuario);
          if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
            continue;
          }
          cont++;
        }
        usuario list_user[cont];
        siguiente_dir = 0;
        int indexl = 0;
        for (int i = 0; i < 20; i++) {
          struct usuario usuario_existente;
          EEPROM.get(siguiente_dir, usuario_existente);
          //se verifica si viene vacio
          siguiente_dir += sizeof(struct usuario);
          if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
            continue;
          }
          list_user[indexl] = usuario_existente;
          indexl++;
        }
        int index = 0;
        bool regresar = false;
        LOOP {
          if (index >= sizeof(list_user)) break;
          pantalla.setCursor(0, 2);
          pantalla.print(list_user[index].nombre);
          bool salir = false;
          TECLA_PRESIONADA {
            case '2':
              {
                delay(210);
                if (index == 0) index = cont - 1;
                else index--;
                pantalla.setCursor(0, 2);
                pantalla.print("              ");
                break;
              }
            case '8':
              {
                delay(210);
                if (index == cont - 1) index = 0;
                else index++;
                pantalla.setCursor(0, 2);
                pantalla.print("              ");
                break;
              }
            case '*':
              {
                delay(210);
                salir = true;
                break;
              }
            case '#':
              {
                delay(210);
                anterior_estado = MENU;
                estado_actual = CRUD;
                siguiente_estado = estado_actual;
                salir = true;
                regresar = true;
                break;
              }
          }
          if (salir) break;
        }
        if (regresar) break;
        if (index == 0) {
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("Ocurrio un error:");
          pantalla.setCursor(0, 1);
          pantalla.print("No se puede");
          pantalla.setCursor(0, 2);
          pantalla.print("eliminar admin");
          delay(1000);
          break;
        }
        memset(nombre_temp, 0, 20);
        memset(password_temp, 0, 10);
        struct usuario nuevo_usuario;
        memcpy(nuevo_usuario.nombre, nombre_temp, 20);
        memcpy(nuevo_usuario.password, password_temp, 10);
        //Se carga segun el index el dato vacio
        EEPROM.put(index * sizeof(struct usuario), nuevo_usuario);
        pantalla.clear();
        pantalla.setCursor(0, 0);
        pantalla.print("Usuario se ha");
        pantalla.setCursor(0, 1);
        pantalla.print("eliminado");
        pantalla.setCursor(0, 2);
        pantalla.print("correctamente");
        delay(1000);
        break;
      }
    case MOD:
      {
        memset(nombre_temp, 0, 20);
        memset(password_temp, 0, 10);
        memset(nombre_vacio, 0, 20);
        pantalla.clear();
        pantalla.setCursor(0, 0);
        pantalla.print("Modificar passwd");
        pantalla.setCursor(0, 1);
        pantalla.print("   Usuario...");
        int cont = 0;
        int siguiente_dir = 0;
        for (int i = 0; i < 20; i++) {
          struct usuario usuario_existente;
          EEPROM.get(siguiente_dir, usuario_existente);
          //se verifica si viene vacio
          siguiente_dir += sizeof(struct usuario);
          if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
            continue;
          }
          cont++;
        }
        usuario list_user[cont];
        siguiente_dir = 0;
        int indexl = 0;
        for (int i = 0; i < 20; i++) {
          struct usuario usuario_existente;
          EEPROM.get(siguiente_dir, usuario_existente);
          //se verifica si viene vacio
          siguiente_dir += sizeof(struct usuario);
          if (strcmp(nombre_vacio, usuario_existente.nombre) == 0) {
            continue;
          }
          list_user[indexl] = usuario_existente;
          indexl++;
        }
        int index = 0;
        bool regresar = false;
        LOOP {
          if (index >= sizeof(list_user)) break;
          pantalla.setCursor(0, 2);
          pantalla.print(list_user[index].nombre);
          bool salir = false;
          TECLA_PRESIONADA {
            case '2':
              {
                delay(210);
                if (index == 0) index = cont - 1;
                else index--;
                pantalla.setCursor(0, 2);
                pantalla.print("              ");
                break;
              }
            case '8':
              {
                delay(210);
                if (index == cont - 1) index = 0;
                else index++;
                pantalla.setCursor(0, 2);
                pantalla.print("              ");
                break;
              }
            case '*':
              {
                delay(210);
                salir = true;
                break;
              }
            case '#':
              {
                delay(210);
                anterior_estado = MENU;
                estado_actual = CRUD;
                siguiente_estado = estado_actual;
                salir = true;
                regresar = true;
                break;
              }
          }
          if (salir) break;
        }
        if (regresar) break;
        //Se muestra la contrasena
        pantalla.clear();
        pantalla.setCursor(0, 0);
        pantalla.print("M O D  P A S S");
        pantalla.setCursor(0, 1);
        pantalla.print("-User:");
        pantalla.print(list_user[index].nombre);
        pantalla.setCursor(0, 2);
        pantalla.print("-Pass:");
        String car = "";
        regresar = false;
        int letra = 0;
        String contraC = "";
        LOOP {
          pantalla.setCursor(5 + letra, 2);
          if (car != "") pantalla.print(car);
          bool salir = false;
          TECLA_PRESIONADA {
            case '0':
              delay(210);
              contraC += "0";
              car = "0";
              letra++;
              break;
            case '1':
              delay(210);
              contraC += "1";
              car = "1";
              letra++;
              break;
            case '2':
              delay(210);
              contraC += "2";
              car = "2";
              letra++;
              break;
            case '3':
              delay(210);
              contraC += "3";
              car = "3";
              letra++;
              break;
            case '4':
              delay(210);
              contraC += "4";
              car = "4";
              letra++;
              break;
            case '5':
              delay(210);
              contraC += "5";
              car = "5";
              letra++;
              break;
            case '6':
              delay(210);
              contraC += "6";
              car = "6";
              letra++;
              break;
            case '7':
              delay(210);
              contraC += "7";
              car = "7";
              letra++;
              break;
            case '8':
              delay(210);
              contraC += "8";
              car = "8";
              letra++;
              break;
            case '9':
              delay(210);
              contraC += "9";
              car = "9";
              letra++;
              break;
            case '*':
              delay(210);
              salir = true;
              break;
            case '#':
              delay(210);
              regresar = true;
              estado_actual = MOD;
              anterior_estado = CRUD;
              break;
          }
          if (regresar) break;
          if (salir) {
            if (contraC.length() > 10) {
              pantalla.clear();
              pantalla.setCursor(0, 0);
              pantalla.print("Ocurrio un error:");
              pantalla.setCursor(0, 1);
              pantalla.print("Passw excede");
              pantalla.setCursor(0, 2);
              pantalla.print("numero de bytes");
            } else {
              break;
            }
          };
        }
        if (regresar) break;

        for (int i = 0; i < contraC.length(); i++) {
          password_temp[i] = contraC[i];
        }
        //se adjunta a un nuevo usuario la informacion
        struct usuario nuevo_usuario;
        memcpy(nuevo_usuario.nombre, list_user[index].nombre, 20);
        memcpy(nuevo_usuario.password, password_temp, 10);

        //Despues de tener el usuario completo con sus creedencial, se busca su pocicion segun el nombre y se modifica
        int indexmod = 0;
        siguiente_dir = 0;
        bool encontrado = false;
        for (int i = 0; i < 20; i++) {
          struct usuario user_const;
          EEPROM.get(siguiente_dir, user_const);
          //se verifica si viene vacio
          siguiente_dir += sizeof(struct usuario);
          if (strcmp(nombre_vacio, user_const.nombre) == 0) {
            indexmod++;
            continue;
          }
          //si encuentra el nombre se sale
          if (strcmp(nuevo_usuario.nombre, user_const.nombre) == 0) {
            encontrado = true;
            break;
          }
          indexmod++;
        }
        if (encontrado) {
          EEPROM.put(indexmod * sizeof(struct usuario), nuevo_usuario);
          pantalla.clear();
          pantalla.setCursor(0, 0);
          pantalla.print("Passwd se ha");
          pantalla.setCursor(0, 1);
          pantalla.print("modificado");
          pantalla.setCursor(0, 2);
          pantalla.print("correctamente");
          delay(1000);
          break;
        }
      }
  }
}