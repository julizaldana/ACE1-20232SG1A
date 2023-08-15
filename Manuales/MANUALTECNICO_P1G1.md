## Universidad de San Carlos de Guatemala
## Escuela de Ciencias y Sistemas, Facultad de Ingeniería
## Arquitectura de Computadoras y Ensambladores 1, 2DO semestre 2023
-----
# PRACTICA1 - LAB ARQUITECTURA DE COMPUTADORAS Y ENSAMBLADORES 1 - SECCION A
-----
# MANUAL TÉCNICO 
-----

**Resumen**

En la práctica No. 1 correspondiente al curso de Arquitectura de Computadoras y Ensambladores 1. Se desarrolló un programa que consiste en dos modalidades principales: Las cuales son un modo mensaje y una modalidad de juego, que antes de este se puede configurar la velocidad que tendrá en este caso el usuario por medio de una serpiente que se movilizará, en dos matrices de LED de 8x8, que simularán al tablero o área del juego. Todo con el objetivo de simular al famoso juego de "Snake" donde el jugador podrá adquirir comida que se genera aleatoriamente en el tablero, y podrá comersela y aumentar la longitud de su cola. Siempre con la posibilidad de morir al tocar las paredes del tablero, o bien al chocarse con su propia cola.

**Explicación del funcionamiento del programa**

En general en esta práctica, se utiliza el IDE de Arduino para poder programar y generar el código que se conectará con su archivo compilado .hex al prototipo de "Arduino Simulino Mega" con la librería de Arduino de Proteus. Esto con el fin de simular el funcionamiento del programa en Proteus.

Todas las funciones, métodos de las modalidades se crearon directamente con base en el lenguaje de programación C++. Y todo fue conectado y probado con el software de diseño electrónico Proteus. 

**Explicación Archivos**



**Metodos más importantes**





**Descripción de herramientas utilizadas**


1. Arduino IDE: Se utilizó este IDE especial para poder simular la utilización de un puerto, para la conexión del código con el microcontrolador Arduino de forma simulada en Proteus. 
2. Librería LedControl: Se utilizó esta librería que permite utilizar los drivers MAX7219 y MAX7221 para el funcionamiento correcto de las matrices de LEDs.
3. Proteus: Software de diseño electrónico, fundamental para poder trabajar el programa, ya que se utilizó electrónica básica para poder hacer conexiones entre el MAX7219, el microcontrolador Arduino, y el manejador de los botones para el movimiento, el potenciometro para graduar la velocidad del modo mensaje entre otros.
4. Librería Arduino Proteus: Se utilizó una librería que importa los microcontroladores Arduino para utilizarlos en Proteus.


**Conclusiones**

1. 
2.
3. 