## Universidad de San Carlos de Guatemala
## Escuela de Ciencias y Sistemas, Facultad de Ingeniería
## Arquitectura de Computadoras y Ensambladores 1, 2DO semestre 2023
-----
# PROYECTO 1 - LAB ARQUITECTURA DE COMPUTADORAS Y ENSAMBLADORES 1 - SECCION A
-----
# MANUAL DE USUARIO
-----

**Propósito**

Se realizó el presente manual para tener a disposición un mejor manejo de la aplicación móvil que se creó, para la simulación del sistema de diseño de paquetes.

**Descripción**

Como se detalló anteriormente, el prototipo elaborado de forma simulada con Proteus, incluyendo varios componentes: Como una pantalla LCD para presentar, el menú de la simulación, un teclado, para manejarse dentro de ese menú, 
al igual que matrices de LEDs 8x8, para presentar los diseños de productos que se podrán crear dentro de la app móvil, al igual que visualizar un contador de tiempo con displays de 7 seg, al igual que un sensor de temperatura que se utiliza con representación de leds.

**Utilización de app móvil**

NOTA: Tener instalado un editor de texto / IDE que soporte a Arduino, para que este pueda ser conectado con los cables de conexión entre la computadora donde se tenga el archivo con la lógica del juego, con los dispositivos Arduino.

Tener en cuenta también que se debe de configurar bien el Bluetooth dentro de la computadora del usuario.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/a2a870d4-4a04-4abe-bcc7-f7e1cab494af)

Al igual que tenga emparejado el móvil, en donde se utilizará la aplicación web.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/890f6df9-2fcc-42bc-b7c2-13b3b7dc747b)


**DISEÑO SIMULACIÓN DEL SISTEMA DE PAQUETES**

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/9ec0c2fe-2ba4-443d-90ca-906c78258d73)

1. Pantalla LCD, para la presentación del menú, donde se verificará todo el registro de los usuarios, del administrador, y para poder verificar credenciales y ejecutar la simulación de los diseños de productos.
2. Área de Matrices y Banda transportadora: Para la presentación de los diseños de productos.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/6e97f22b-89e7-4023-b5b1-3b2d6f421e5e)

4. Área de sistema de temperatura:
5. Área de contador de tiempo:

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/3a260412-c2f3-412c-b80f-a7b4f2c066c2)


--------

**DISEÑO DE APP**

1. Login de un usuario ya registrado:

![login](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/25fc197b-8a2b-4cdb-905e-a8121d8cb79b)


2. Diseño de producto, matriz dentro de la app:
   
![Captura de pantalla 2023-09-23 222557](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/7301c3eb-e509-48da-8086-8b2131695e03)

Se puede realizar cualquier diseño, dentro de la matriz de 8x8; luego dar en continuar:

![Captura de pantalla 2023-09-23 222606](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/2106fd82-05dd-421b-89cb-17fda65d3b24)


**ÁREA DE ENSAMBLAJE** 

Para poder visualizar, en la simulación, el diseño del producto en las estaciones, se debe de configurar ya dentro del área de ensamblaje, se debe de introducir, el orden de los números de las estaciones, en
donde se irán presentando luego en la simulación de Proteus:

![Captura de pantalla 2023-09-23 221639](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/cbf0de73-b32b-4a7b-8336-93448788f26d)


![Captura de pantalla 2023-09-23 222642](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/adf6774b-2f58-44cd-a7d4-a945f65d3f52)


4.  Temperatura:

Tener en cuenta que se tienen tres tipos de LEDS que marcaran los estados de temperatura:

1. Verde: La temperatura marcada es <37°
2. Amarillo: La temperatura marcada es >36° Y <46° 
3. Rojo: La temperatura marcada es >45°

Se registra en la simulación 

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/1e51bc29-a936-4aff-b021-4eb3f37f1b15)

Y luego dentro de la app móvil, también tomar en cuenta que se va tomando el tiempo y se actualiza en la app móvil. 

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/1ee63209-c25f-4972-a767-c22d01f0ef46)






