## Universidad de San Carlos de Guatemala
## Escuela de Ciencias y Sistemas, Facultad de Ingeniería
## Arquitectura de Computadoras y Ensambladores 1, 2DO semestre 2023
-----
# PRACTICA1 - LAB ARQUITECTURA DE COMPUTADORAS Y ENSAMBLADORES 1 - SECCION A
-----
# MANUAL DE USUARIO
-----

**Propósito**

Se realizó el presente manual para tener a disposición un mejor manejo del programa "Juego de Snake" con una modalidad de mensaje y una modalidad del propio juego como tal.  

**Descripción**

Como se detalló anteriormente, el programa en su conjunto consiste en mostrar un modo de mensaje donde se indica el número de grupo y la sección del laboratorio del curso. 

"<"PRAC1 - GRUPO1 - SECCIÓN A">"

Y por otro lado se puede acceder mediante el botón Start, para poder acceder a la modalidad de configuración de velocidad del usuario, que es importante para poder seleccionar la velocidad en el que la serpiente (jugador) se moverá dentro del tablero de juego (matrices de LEDs 8x8).

**Navegabilidad y Utilización del programa**

NOTA: Tener instalado el software de diseño electrónico; Proteus para poder abrir el archivo del juego, al igual que tener el archivo Final.ino.hex para el funcionamiento correcto del juego.


![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/334a87ca-1447-4945-8c97-13352c09dadc)


Verificar si se encuentra la carpeta y el archivo Final.ino.hex de forma correcta (Este será primordial ya que contiene la lógica del programa)


![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/3292f428-c703-4938-a35e-d256d1fa00e2)


1. Al estar en Proteus, darle a Play para poder inicializar y comenzar la simulación del juego.
   
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/3ea43ccb-d9a4-43ed-8f40-f32f82c2c13b)

**CONTROLES Y BOTONES:**

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/83cdcbd6-b984-437c-bc3a-2f944ef3a608)

Se compone como en la imagen elaborada:

1. Tablero del juego "Snake" compuesta por dos Matrices de Leds 8x8.
2. Botones de movimiento: Arriba, Abajo, Derecha e Izquierda que servirán para poder mover a la serpiente dentro del tablero, al igual que con los botones de Arriba y Abajo servirán para poder configurar la velocidad de la serpiente ya dentro del juego.
3. Botón Start - Aceptar: Al presionar 3 segundos, se podrá cambiar de modo de juego, al igual que se podrá realizar una pausa, donde mostrará el puntaje, de igual manera se podrá aceptar la configuración de velocidad para entrar al modo de juego.
4. Tablero con un switch para poder cambiar y configurar la forma en que se despliega un mensaje con la información del grupo que elaboró el programa.


--------

**MODO MENSAJE**

Al haber iniciado la simulación, se comienza mostrando el mensaje con información del grupo. Existen unas formas en las que se puede visualizar el mensaje, en el tablero de configuración de mensaje:

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/885fd1b4-15ee-48b7-8828-45442f9f1ba0)

1. Se puede cambiar la velocidad en la que se visualiza el mensaje, esto se puede ajustar con el potenciometro de velocidad.
2. Se puede cambiar la forma o el modo de visualización; ya sea que se visualice el mensaje en movimiento o bien solo letra por letra.
3. Se puede cambiar la dirección del mensaje, ya sea que se quiera que venga por la derecha o bien que venga por la izquierda.

**COMBINACIONES PARA MENSAJE EJEMPLOS**

Entre algunos ejemplos se puede tener:

- Movimiento a la derecha

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/edf6cbed-4840-4dd3-85ef-d9d00348c77e)

- Movimiento a la izquierda
  
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/3040de8e-f716-41a5-8550-9107d39ad399)

- Letra por letra a la derecha: Se lee la frase al revés
- Letra por letra a la izquierda: Se lee la frase normalmente
  
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/8ffb92a0-608b-4250-acae-a97a97e5a052)

--------

**ENTRAR AL MODO DE CONFIGURACIÓN DE VELOCIDAD DEL JUEGO**

Para entrar al juego, primero se debe de configurar la velocidad, para eso si se está en el modo mensaje, se presiona el botón de Aceptar o Start por 3 segundos, para entrar al modo de configuración de velocidad.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/37b6709a-5f82-44c3-8445-652443560e97)

Después de presionar aparece la opción de configurar la velocidad de juego.

**La velocidad del juego se determina de 01-02-03-04 de más bajo al más alto*
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/b163fd6b-2db6-4882-9be5-e2608c7437f6)

Para cambiar de velocidad, se presionan los botones de arriba y abajo.
![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/99488065-5690-40ba-9c5c-a836103f69b3)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/c6e2e2ff-aba7-46a7-92aa-c4097e689f3b)

Luego se presiona el botón de Aceptar o "Start" para comenzar el juego de Snake.

---------

**JUEGO SNAKE**

El juego cumple con ciertas reglas básicas e importantes para cumplir con el funcionamiento. El jugador aparecerá en la primera columna del tablero, aleatoriamente (su personaje es una serpiente; dos puntos en las matrices)

FUNCIONAMIENTO:

El objetivo es conseguir la máxima cantidad de puntos. En todo el tablero se presentará aleatoriamente comida, que el jugador debe procurar de comersela al dirigirse hacia ella. Con esto cada comida es 1 Punto. Y esto también significa que aumentará la cola y el cuerpo del jugador (serpiente, aumentará 1 punto de luz). 

El movimiento de la serpiente, se puede manejar directamente con sus controles de movimiento. 

FORMAS DE MORIR EN SNAKE: 

- El jugador debe de tener cuidado ya que conforme se come comida, se irá aumentando un poco la velocidad de la serpiente, así que evitar:
1. Toparse con las paredes del tablero de juego, para no morir. Ya que terminará el juego.
2. Al haber comido mucho, la serpiente será muy larga, así que tener cuidado de no chocarse con la propia serpiente porque esto implica perder el juego de igual manera.

**CAPTURAS DEL JUEGO**

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/96265431-8754-488b-9053-2583a4ca5e66)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/31cd9e67-3e25-446c-b4de-1f3ad2e76bcb)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/fee63ae6-e0c9-4a92-a2ca-843f03db72de)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/162db0bf-88d0-41d4-a8ab-eebf7b6c5080)

**PAUSAR EL JUEGO**

Al presionar el botón de Aceptar / "Start" esto lo que hará es pausar el juego y mostrará la puntuación del jugador que se encuentra actualmente jugando. Al presionar de nuevo el botón, se saldrá del modo de pausa y regresará 
el jugador a la posición en la que se encontraba.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/dbb006cb-c2a2-46e6-afd0-15c6a952c69f)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/73d10fd1-6c1d-4247-adf5-16b5da9da1bc)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f34807dc-4c57-4ced-9f8a-5e199ac48cd6)

**GAME OVER**

Al haber morir en Snake, se presentará el mensaje de GAME OVER - y la puntuación del jugador que alcanzó en su partida jugada. Después regresará al modo de configuración de velocidad para comenzar un juego nuevo.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/3d6a681b-f0b7-4f8a-87f1-8a78c05fd40d)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/fce4037a-2933-4626-9484-75ccb9bd817e)




