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

Para la práctica se tienen a los siguientes archivos donde se trabajó toda la lógica y la programación.

**Archivo .pdsprj de Proteus -  Con todo el diseño del juego, incluyendo todos los componentes que se trabajaron*

![imagen archivos2](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/b60aaf07-3ea8-49a1-b0d9-e17021f42749)

**Archivos Final.ino que contiene todo el código y la programación del juego y el archivo compilado del mismo; Final.ino.hex, que se usa en Proteus para que funcione correctamente el programa en general*

![imagen archivos](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/04f4ecf2-af74-41ef-8868-940b150e3090)

**Metodos más importantes**

1. **mostrarMensajeMatriz():** Esta función es muy importante ya que se muestra el modo mensaje
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/b59981b4-4720-4dda-aa58-2f438e5efa1f)

Se utilizan pequeñas funciones para poder pintar las leds y borrarlas, para que se muestre el mensaje de forma correcta. Al igual que se tiene una matriz, llamada mensaje, donde se contiene todo el mensaje, de <PRAC1 - GRUPO1 - SECCIÓN A>
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/a460bf1e-64b1-4534-8a50-56ad554f7500)

2. **juegoSnake():** Esta función es fundamental ya que se inicializa, lo que son todas las funciones secundarias para poder hacer que el juego trabaje.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/789da61f-3297-469c-8eed-dd27b2f7159c)

3. **elegirVelocidad():** Esta función es determinante al momento de poder seleccionar y configurar la velocidad que tendrá la serpiente dentro del juego. 

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/5c7c3a1b-a6c5-41cb-ba32-a8aaeb396746)

4. **detectarMov(): y moverSnake()** Función básica e importante, ya que se incializan y así se funcionan los botones de movimiento del programa.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/73241d53-9d1a-4a3d-8648-a37e5665c9d3)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/279eebf3-6e4a-4660-949d-750ece3309b3)

5. **detectarPausa():** Importante para pausar el juego, y mostrar la puntuación

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/62602634-770c-49c3-b753-e9c141bda98d)

6. Funciónes para mostrar y generar la comida:

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/8381dc22-6ed4-4cff-80ef-881510126ed8)


**Descripción de herramientas utilizadas**

1. Arduino IDE: Se utilizó este IDE especial para poder simular la utilización de un puerto, para la conexión del código con el microcontrolador Arduino de forma simulada en Proteus. 
2. Librería LedControl: Se utilizó esta librería que permite utilizar los drivers MAX7219 y MAX7221 para el funcionamiento correcto de las matrices de LEDs.
3. Proteus: Software de diseño electrónico, fundamental para poder trabajar el programa, ya que se utilizó electrónica básica para poder hacer conexiones entre el MAX7219, el microcontrolador Arduino, y el manejador de los botones para el movimiento, el potenciometro para graduar la velocidad del modo mensaje entre otros.
4. Librería Arduino Proteus: Se utilizó una librería que importa los microcontroladores Arduino para utilizarlos en Proteus.


**Conclusiones**

1. Es importante conocer el microcontrolador Arduino, entender cuales son las partes, pines, salidas y entradas que tiene, porque son muy utiles al hacer cualquier tipo de proyecto, funcionamiento, aplicación en cualquier área que se requiera.
2. Es importante tener conocimiento previos sobre el lenguaje C, C++ para poder basarse, y que se amucho más fácil poder realizar un programa cómo el que se realizó. Teniendo un conocimiento previo de como manejar variables, matrices, funciones, es muy útil.
3. Conocer el funcionamiento básico de los puertos y salidas seriales del microcontrolador Arduino, es muy útil ya que se acostumbra uno a utilizar un componente tan funcional en muchas áreas.
