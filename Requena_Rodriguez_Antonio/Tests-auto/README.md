-*-text-*-
$Id:$

Estos son los programas de pruebas automáticas para todas
las prácticas de la asignatura «Programación Orientada a Objetos»
(POO). Están hechos mediante un marco de pruebas para C y C++ llamado
FCTX (Fast C Tests Xunit), hecho por Ian Brumel, con una licencia
libre basada en la de BSD.

Para usarlos, descomprima el archivo en un directorio al mismo nivel
que los de las prácticas, quedando la estructura:

Apellido1_Apellido2_Nombre
	Tests-auto
	P0
	P1
	P2
	P3
	P4

En los Makefile de cada práctica, debe definir en la variable o macro
que representa las opciones para el preprocesador de C++ (CPPFLAGS; o,
alternativamente, pero no recomendado, CXXFLAGS):

-DPn   siendo n el número de la práctica correspondiente, de 0 a 4.
-I../Tests-auto -I.

La primera opción define para el preprocesador la macro Pn, siendo n
el número de la práctica correspondiente, de 0 a 4; por ejemplo, para
la práctica 3, la opción sería -DP3.

La segunda indica al preprocesador dónde buscar los ficheros de
cabecera de los tests automáticos. Hay que repetir la opción
especificando el directorio actual (.) para que los tests automáticos
encuentren el directorio donde están los ficheros de cabecera de cada
práctica.

El programa ejecutable de los tests automáticos se genera en el
directorio de cada práctica.
