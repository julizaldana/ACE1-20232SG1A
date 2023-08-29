## Universidad de San Carlos de Guatemala
## Escuela de Ciencias y Sistemas, Facultad de Ingeniería
## Arquitectura de Computadoras y Ensambladores 1, 2DO semestre 2023
-----
# PRACTICA2 - LAB ARQUITECTURA DE COMPUTADORAS Y ENSAMBLADORES 1 - SECCION A
-----
# MANUAL DE USUARIO
-----

**Propósito**

Se realizó el presente manual para tener a disposición un mejor manejo del prototipo que se elaboró para la simulación respectiva del famoso juego "Pinball". En donde se trabajó una maqueta/tablero de juego, con los componentes básicos que emulan la mecánica del juego.

**Descripción**

Como se detalló anteriormente, el prototipo elaborado de forma física, tiene como objetivo emular al juego "Pinball", teniendo varios funcionamientos interactivos, como el mostrar los integrantes del grupo, el puntaje y los niveles del jugador actual, todo mediante una pantalla LCD (Posicionada en la parte superior al centro del tablero de juego).
Al igual que con la mecánica del juego, donde las paletas serán accionadas por dos botones (Posicionados en la parte inferior del tablero) Todo con el fin de empujar una pelota que ingresará al tablero, para conseguir puntos, e ir subiendo de nivel. 

**Utilización del prototipo Pinball**

NOTA: Tener instalado un editor de texto / IDE que soporte a Arduino, para que este pueda ser conectado con los cables de conexión entre la computadora donde se tenga el archivo con la lógica del juego, con los dispositivos Arduino.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/cbcb99a4-edeb-4e2c-97b5-cffd4a15d17a)

Por ejemplo teniendo Arduino IDE, se puede abrir el archivo mostrado, y cargar el respectivo archivo a los Arduinos que se encuentran con la maqueta del juego Pinball.

**EXPLICACION DEL TABLERO**

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/bd7e555e-6e77-4dc2-9d32-8453e0681d1b)

1. Área de Pantalla y LEDS de puntajes y niveles: En la pantalla es donde se muestra al principio los integrantes que elaboraron el prototipo del juego, de igual manera aquí es donde se toma en cuenta y se muestra el puntaje y la subida de niveles que tendrá el jugador durante el juego, esto medido cuando la pelota da un giro sobre el área superior, medido por las LEDS. O bien si pierde, se termina el juego regresando al nivel 1, y comenzando la partida de nuevo.
2. Área de Botones y Paletas: Aquí se encuentran los botones que accionaran a las paletas del juego, al igual que serán de utilidad para navegar dentro del menú de la pantalla del juego, para comenzar partidas, o ver un historial de puntajes.
3. Área de carga de pelotas: Un área para poder ingresar pelotas y poder impulsarlas y poder comenzar un juego nuevo.

--------

**LISTA DE COMPONENTES PARA JUGAR**

1. Botones y paletas:

**FUNCIONAMIENTO DE PALETAS**

Se accionaran principalmente por el uso de los botones. Tanto para el de la izquierda como el de la derecha. Aquí se tiene un ejemplo de cómo se acciona.

![Movimiento de Paletas](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/d373835c-3141-42c2-94af-9342d6fcd6a7)

También será util para navegar dentro del menú que se muestra al principio, para poder escoger si comenzar partida o ver lista de puntajes.

1. Boton Izquierdo - Para navegar entre las opciones
2. Boton Derecho - Para aceptar la opción

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f71e8775-74c7-493f-bdb1-cd934bbe5f4c)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/0b539086-1bab-4ee8-8c42-91f1e0f13514)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/afd73917-a968-48d4-8e87-81df07cfe931)


2. Pelotas:

Útiles para poder hacer que el juego funcione.

   ![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/74978a34-a7d4-4f2e-9d5a-7480aac2d4a1)


**OBJETIVO DEL JUEGO**

El objetivo primordial del juego es poder hacer y empujar la pelota, con las paletas hasta la parte superior del tablero. Que gire sobre el cilindro superior, donde se encuentra la pantalla. 

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/aed02f33-5b87-4a2c-9873-487814812465)

Cada vez que gire el cilindro, se sumarán 10 pts si se encuentra en el nivel 1 y se enciende una luz led. (Se deben de encender lsa 6 luces LEDS para poder pasar de nivel.)

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/06db7ec7-329f-4d1a-9dfe-8132ab760f2c)

Si se pasa de nivel, en el nivel 2, se sumarán 20 pts por cada vuelta que haga la pelota.
   
**GAME OVER**

Cuando la pelota cae en el espacio entre las paletas, el juego termina. 

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f0b52e49-6cad-40d4-89a2-2c75cecd472a)

Y se muestra el mensaje en la pantalla:

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/ece93ac7-5e8e-439f-a978-b2f25ed2bf82)


**IMAGENES DE DISTINTAS VERSIONES DEL PROTOTIPO**

![WhatsApp Image 2023-08-28 at 11 21 42 PM (2)](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/500defd7-b103-41c7-a994-45bc0ea47bcd)


![WhatsApp Image 2023-08-28 at 11 21 43 PM (1)](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/2e3f50c3-fe16-4b49-b97a-7e9cc03387a2)

