## Universidad de San Carlos de Guatemala
## Escuela de Ciencias y Sistemas, Facultad de Ingeniería
## Arquitectura de Computadoras y Ensambladores 1, 2DO semestre 2023
-----
# PRACTICA2 - LAB ARQUITECTURA DE COMPUTADORAS Y ENSAMBLADORES 1 - SECCION A
-----
# MANUAL TÉCNICO 
-----

**Resumen**

En la práctica No. 2 correspondiente al curso de Arquitectura de Computadoras y Ensambladores 1, se desarrolló un prototipo/maqueta que emula al juego de Pinball. Todo fue trabajado con la utilización de microcontroaldores Arduino, y la utilización de electrónica básica, uso de motores para accionar las paletas del juego. Utilización de una pantalla LCD para poder mostrar mensajes, y todo conectado con las entradas/salidas del Arduino, cargado el programa desde la computadora.

**Explicación del funcionamiento del programa**

En general en esta práctica, se utiliza el IDE de Arduino para poder programar la lógica del juego Pinball para luego cargarlo por medio de cables conectados directamente a los microcontroladores, esto para poder accionar todos los componentes como los motores, botones, pantallas LCD, luces leds, sensores ultrasonicos etc.

Todas las funciones, métodos de las modalidades se crearon directamente con base en el lenguaje de programación C++. Y todo fue conectado de manera física, utilizando:

1. Arduino Uno
2. Arduino Mega

Donde luego se haría una conexión I2C para poder comunicarlos entre los 2, para recibir serialmente las instancias de acciones para poder ejecutar diferentes funciones específicas del juego.

**Metodos más importantes**

1. Función moverPaletas(): Esta función es importante porque con ella se puede accionar y hacer que se muevan los motores DC de 12 Voltios que se utilizaron con su controlado L298N
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/e40491bf-ea3c-483d-9d60-1d1d82e27797)

2. Función mostrar_puntajes(): Para mostrar los puntajes como lista en la pantalla LCD.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f0a5ab79-99ec-4957-964d-3fc9c5c904f5)

3. Función juego(): Donde se engloban a todas las funciones y se llaman para poder hacer que el juego funcione como conjunto.

 ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/c4ac31dc-002b-4945-b77f-6d93ac4af47b)


**Descripción de herramientas utilizadas**

1. Arduino IDE: Se utilizó este IDE especial para poder programar y así cargar el mismo a los Arduinos de forma física con cables, para poder ejecutar esos métodos y poder accionar el juego como tal.
2. Librería LiquidCristal: Se utilizó esta librería para poder accionar y utilizar la pantalla LCD.
3. Librería Wire: Para poder hacer la comunicación entre los Arduinos (I2C)


**Conclusiones**

1. Es importante conocer el microcontrolador Arduino, entender cuales son las partes, pines, salidas y entradas que tiene, porque son muy utiles al hacer cualquier tipo de proyecto, funcionamiento, aplicación en cualquier área que se requiera.
2. Es importante tener conocimiento sobre la comunicación entre Arduinos, como la comunicación I2C, ya que es muy útil.
