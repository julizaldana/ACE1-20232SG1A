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

En general en esta práctica, se utiliza el IDE de Arduino para poder programar la lógica del juego Pinball para luego cargarlo por medio de cables conectados directamente a los microcontroladores Arduino, esto para poder accionar todos los componentes como los motores DC de 12 V, botones, pantalla LCD 16x2, luces leds, sensores ultrasonicos etc.

Todas las funciones y métodos de las modalidades se crearon directamente con base en el lenguaje de programación C++. Y todo fue conectado de manera física, utilizando dos diferentes tipos de Arduino:

1. Arduino Uno
2. Arduino Mega

Donde luego se utilizaría el protocolo de comunicación I2C para hacer que los Arduinos se comunicaran entre sí, para así recibir serialmente las instancias de acciones para poder ejecutar diferentes funciones específicas del juego.

**Metodos más importantes**

*1. Función moverPaletas():* Esta función es importante porque con ella se puede accionar y hacer que se muevan los motores DC de 12 Voltios que se utilizaron con un driver/puente H L298N.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/e40491bf-ea3c-483d-9d60-1d1d82e27797)

Este puente H fue de ayuda para poder conectar los dos motores DC, y así mismo, poder mandar señales digitales a las conexiones que van al puente H, desde el Arduino.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/741583a9-efb8-4527-8b48-479e7a2a87c2)

*2. Función mostrar_puntajes():* Esta función es importante, ya que ayuda para mostrar los puntajes más altos, como si fuera una lista, esto la pantalla LCD.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f0a5ab79-99ec-4957-964d-3fc9c5c904f5)

3. Funciones para actualizar y ordenar la lista de puntajes: Se trabaja como un algoritmo de ordenamiento, donde se va insertando el puntaje, y se va analizando si es mas alto con los actuales o si es menor con los actuales guardados.

 ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/e0cca7de-904c-4771-991e-93ff8d3a6188)


*4. Función menu():* Con esta función se podrá escribir y mostrar inicialmente en la pantalla el menú de opciones. 

 ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/40aa4b56-087f-4341-a99c-76a1ea83ad89)
 
 ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/59788793-ef5f-4056-8f28-0f04e0fb477c)

**Funciones para comunicación I2C:**

*5. Función config_juego():* Esta función es importante para poder realizar esa comunicación serial entre ambos arduinos, cómo están en diferente posición, se hace esto. Y se comunica, uno con el otro, mandando una señal que el juego comenzó.

  ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/5d34bc68-4b76-4f36-a8d3-695baaf7cb63)

*6. Función actualizar_datos():* Para poder verificar, cuando es que se cambia de nivel, o se pierde, o se van agregando más puntos. Esto se recibe como señal de un Arduino con otro.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f596795a-a9ef-4b93-8d3c-32851c6a57da)


*8. Función juego():* Donde se engloban a todas las funciones y se llaman para poder hacer que el juego funcione como conjunto.

 ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/c4ac31dc-002b-4945-b77f-6d93ac4af47b)



**Descripción de herramientas utilizadas**

1. Arduino IDE: Se utilizó este IDE especial para poder programar y así cargar el mismo a los Arduinos de forma física con cables, para poder ejecutar todos los métodos y poder accionar el juego como tal.
2. Librería LiquidCristal: Se utilizó esta librería para poder ejecutar y utilizar la pantalla LCD.
3. Librería Wire: Para poder utilizar el protocolo de comunicación entre los Arduinos (I2C), donde se mandarían y recibirían señales.

   
**Conclusiones**

1. Es importante conocer los alcances de los microcontorladores Arduino, ya que estos tienen muchos pines, y componentes que lo hacen muy útil para poder conectarlo con diferentes componentes, como motores, botones, luces, pantallas LEDs etc.
2. Es importante tener conocimiento sobre la comunicación entre Arduinos, como el protocolo de comunicación I2C, ya que es muy útil al momento de mandar y recibir señales digitales entre 2 dispositivos distintos.
3. Hay que tener en cuenta la utilización de ciertas librerías, que fueron de utilidad para poder ejecutar ciertos componentes con éxito. Como las librerías LiquidCristal para encender y escribir en la Pantalla LCD 16x2, o bien la libería Wire para realizar con efectividad la comunicación I2C.
4. Recordarse sobre componentes que se asemejan en funcionamientos, hablando del área de motores. Para la práctica se utilizaron motores DC de 12 V. Ya que haciendo pruebas, con Motores Stepper BYJ-48 que se habían adquirido, no fueron utilizados ya que no empujaban la pelota como se requería. Así que tener en cuenta un margen de motores, es de gran ayuda para cumplir con el funcionamiento requerido en la práctica.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/d1433e43-ab00-486f-b612-baf975995d06)

