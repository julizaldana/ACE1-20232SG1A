## Universidad de San Carlos de Guatemala
## Escuela de Ciencias y Sistemas, Facultad de Ingeniería
## Arquitectura de Computadoras y Ensambladores 1, 2DO semestre 2023
-----
# PROYECTO 1 - LAB ARQUITECTURA DE COMPUTADORAS Y ENSAMBLADORES 1 - SECCION A
-----
# MANUAL TÉCNICO 
-----

**Resumen**

En el proyecto No. 1 correspondiente al curso de Arquitectura de Computadoras y Ensambladores 1, se desarrolló una aplicación móvil que representa el control de diseño de productos de una empresa de paquetería. 
Todo la simulación de este sistema de empaques y diseño de productos fue elaborado en Proteus, y funcional vía conexión Bluetooth, donde es conectado con la aplicación móvil, elaborada con MIT App inventor.

**Explicación del funcionamiento de la simulación y de la aplicación móvil**

Para la elaboración del proyecto, se utilizó el Arduino Mega, este por su variedad de pines tanto digitales como análogos, que fueron utiles para el funcionamiento correcto de los diversos componentes, necesarios
para la interconexión y el funcionamiento del sistema. 

**Metodos y Funcionalidades más importantes**

*1. enum Estados:* Se enumeran y se enlistan los estados, que guiarán para poder avanzar y ejecutar los distintos funcionamientos, como el menú para el registro de usuarios, manejo del crud, el funcionamiento de la simulación del sistema de paquetes

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/17e38569-614e-43f5-9b9b-d4a7d56ea626)


*2. Función limpiarBuffer():* Esta función es importante, ya que permite ir limpiando y borrando el registro del Buffer, para que no se llene y no se existan problemas por ejemplo al cambiar de funcionamiento, por ejemplo al mostrar las estaciones, es muy funcional, para que cambie de diseño.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/0b80f15f-2b78-45ac-b8f1-590adbb039f1)


3. Definición del teclado: Se define el teclado, en el cual, se podrá manejar la pantalla LCD, donde se visualiza el menú de la simulación del sistema.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/f1fd4f1e-997a-44d2-ab3b-053bb7fe3a55)


*4. Case MENU:* Es un estado donde se definen algunas teclas, para que exista el funcionamiento correcto del teclado con el registro de usuarios.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/bd456310-6996-4a9b-8425-c700ec3ffdf4)


**Funciones de funcionamiento del sistema de paquetes**

*5. Definición de arrays/vectores para las matrices:* Se definen estos conjuntos de arrays de bytes, para poder manejar lo que son las matrices, donde se presentarán los productos del diseño del sistema de paquetes.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/bbb415ae-432c-47d8-9b6f-5d7ad06ac480)


*6. Función voidEstación1,2,3():*  Muestra como es que se imprimen los diseños en las matrices correspondientes.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/3b36dd19-4341-41c3-9b66-caf4e8912b7f)



*8. Función void estación_inicial():* Aquí engloban todas las estaciones y como se inicializa la matriz principal, para luego ir trabjando cada una de las matrices.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/fa3d343e-016e-403f-8fe6-5438f14006a7)

*9. Función mover_motores():* Esta función es impotante para hacer que se muevan los motores stepper para la simulación de la banda transportadora.

![image](https://github.com/julizaldana/ACE1-20232SG1A/assets/98117383/42f664e2-ca4d-4afe-8325-fc798f420c2f)



**Descripción de herramientas utilizadas**

1. Arduino IDE: Se utilizó este IDE especial para poder programar y así cargar el mismo a los Arduinos de forma física con cables, para poder ejecutar todos los métodos y poder accionar el juego como tal.
2. Librería LiquidCristal: Se utilizó esta librería para poder ejecutar y utilizar la pantalla LCD.
3. Librería Stepper.h: Se utilizó para el correcto funcionamiento de los motores Stepper dentro de la simulación
4. Utilización de Memoria EEPROM: Para el registro de usuarios, contraseñas, manejo del login del programa de simulación, y app.
   

   
**Conclusiones**

1. Es importante conocer los alcances de los microcontorladores Arduino, ya que estos tienen muchos pines, y componentes que lo hacen muy útil para poder conectarlo con diferentes componentes, como motores, botones, luces, pantallas LEDs etc.
2. Es importante destacar la utilización de una memoria EEPROM, y saber la utilización correcta del mismo, ya que se pueden almacenar datos de forma segura.
3. Tener en cuenta el funcionamiento y la configuración de un componente Bluetooth, entender como configurarlo para hacer que funcione correctamente.


