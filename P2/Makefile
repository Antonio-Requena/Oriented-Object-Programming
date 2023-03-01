# $Id: Makefile 399 2017-05-17 17:32:04Z gerardo $
# Makefile para los casos de uso 1, 2, 3 y 4 de la LIBRERÍA
# ©2010-20 los profesores de POO, para P2, P3 y P4
# ©2021 Gerardo - La Gran Unificación

## Variables, macros, más macros y más variables, que es lo mismo. ##
.EXPORT_ALL_VARIABLES:

# AP1_AP2_N es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado P<n>, siendo <n> el número de práctica: P0, P1,
# P2, P3 y P4. La variable P recoge este nombre de directorio Pn.
# AP1_AP2_N debe ser de la forma: Apellido1_Apellido2_Nombre_de_pila
# Sin tildes ni diéresis, y cambiando ñ por nn.
# Ejemplo: Para Pánfilo Pancracio Povedilla Putiérrez sería:
# Povedilla_Putierrez_PanfiloPancracio, y debajo de ese directorio estarían
# P0, P1, P2, P3 y P4, y los directorios Tests-auto y dsl-comprobaciones,
# más luhn.cpp. Véanse las instrucciones de entrega en el enunciado.
NA = $(shell dirname ${PWD})
AP1_AP2_N = $(notdir ${NA})
P := $(shell basename ${PWD})

# DIRFECHCAD es el directorio donde están las cabeceras, fuentes o módulos
# objeto de las clases Cadena y Fecha de P1, y su Makefile.
DFC = P1
DIRFECHCAD = ../${DFC}

# Esto debe dejarse así para que funcionen los tests automáticos.
# DIRTESTS es el directorio donde están los ficheros del programa de pruebas
# unitarias automáticas.
DIRTESTS = ../Tests-auto
INCLUDES = -I${DIRFECHCAD} -I${DIRTESTS} -I.

# DIRLUHN es el directorio donde está el fichero luhn.cpp con la función luhn
DIRLUHN = ..

# --- Parte configurable ---
# Compilador de C++ preferido: el del sistema (c++), el de LLVM (clang++),
# el de GNU (g++), el mismo en la versión x (g++-x), el de Intel (icpc)...
CXX = clang++

# ¿Qué estándar seguir?
# c++98 o c++03 (-ansi): estándar de 1998, corregido en 2003. NO USAR YA.
# c++11: estándar de 2011 - Versión mínima necesaria.
# c++14: estándar de 2014 - OK.
# c++17: estándar de 2017 - Recomendado si su compilador lo admite.
# c++20: estándar de 2020 - OK si el compilador lo admite.
# Si se deja en blanco, el valor predeterminado depende de ${CXX} y su versión.
STD = -std=c++17

# Opciones para el preprocesador. No las quite.
# -Idirec : directorio donde buscar cabeceras adicionales (#include "...")
# -Dmacro : define una macro del preprocesador, como #define
CPPFLAGS = ${INCLUDES} -D$P

# Opciones para el compilador. Añada o quite las que quiera.
# Recomendado: déjelo como está.
# ${STD}     : el estándar de C++ a utilizar (V. comentarios anteriores)
# -g         : para poder depurar, si hay que hacerlo
# -O         : optimizador
# -pedantic  : para que se ajuste al estándar empleado sin desviarse
# -Wall      : para que dé todo tipo de avisos, no solo los normales
# -pg        : genera código para escribir información de perfilado
# -fprofile-arcs : genera código para analizar llamadas a funciones
# -ftest-coverage: cobertura de pruebas
CXXFLAGS = ${STD} -g -pedantic -Wall

# Opciones para el enlazador. Recomendado: ninguna.
# -pg            : para poder perfilar el programa con gprof
# -fprofile-arcs : V. antes; implica -lgcov
LDFLAGS =

# --- Fin parte configurable

LOCALLIBS = ${DIRFECHCAD}/cadena.o ${DIRFECHCAD}/fecha.o ${DIRLUHN}/luhn.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}

# Estos son los ficheros que tiene que hacer el alumno. El resto se le da.
OWN_SRCS  = usuario.cpp tarjeta.cpp articulo.cpp
ifneq ($P, P2)
OWN_SRCS += pedido-articulo.cpp pedido.cpp usuario-pedido.cpp
endif
OWN_HDRS  = $(OWN_SRCS:.cpp=.hpp)

OWN_OBJS  = $(OWN_SRCS:.cpp=.o)

MAIN_SRCS = test-consola.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = ${MAIN_SRCS:.cpp=}

TEST_SRCS = ${DIRTESTS}/test-caso0-cadena-auto.cpp \
	    ${DIRTESTS}/test-caso0-fecha-auto.cpp  \
	    ${DIRTESTS}/test-caso1-2-auto.cpp ${DIRTESTS}/test-auto.cpp
ifeq ($P, P3)
TEST_SRCS += ${DIRTESTS}/test-caso3-auto.cpp
endif
ifeq ($P, P4)
TEST_SRCS += ${DIRTESTS}/test-caso3-auto.cpp ${DIRTESTS}/test-caso4-auto.cpp
endif
TEST_HDRS = ${DIRTESTS}/test-auto.hpp ${DIRTESTS}/fct.h
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-$P-auto

CHECK_SRC = libreria_check.cpp
CHECK_OBJ = ${CHECK_SRC:.cpp=.o}
CHECK_EXE = ${CHECK_SRC:.cpp=}

SRCS      = ${OWN_SRCS} $(MAIN_SRCS) ${TEST_SRCS} $(CHECK_SRC) \
            Makefile Make_check.mk
HDRS      = $(OWN_HDRS) $(TEST_HDRS)

NOMBRETAR = ../../${AP1_AP2_N}.tar.gz
D = ${AP1_AP2_N}/$P

## OBJETIVOS PRINCIPALES ## 

# Construye los programas de prueba
all: ${MAIN_EXE} ${TEST_EXE}
	@echo "Prueba 'make help' para más objetivos interesantes"

# Ejecuta los programas de prueba
tests: test-noauto test-auto

# Construye el test de consola y lo ejecuta
test-noauto: ${MAIN_EXE}
	./$<

# Construye el test automático y lo ejecuta
test-auto: ${TEST_EXE}
	./$<

# Hace comprobaciones en el código fuente
check:  ${OWN_SRCS} ${CHECK_SRC}
	${MAKE} --file=Make_check.mk $@

# Ejecuta los tests comprobando que no haya fugas de memoria
# - valgrind: http://valgrind.org
valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind --quiet ./${MAIN_EXE}
	valgrind --quiet ./${TEST_EXE} --logger=minimal

## Compilación ## 

# Construye el programa de prueba de consola
${MAIN_EXE}: ${MAIN_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de pruebas unitarias automáticas
${TEST_EXE}: ${TEST_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de comprobaciones sobre el código fuente
${CHECK_EXE}: ${CHECK_SRC}
	${MAKE} --file=Make_check.mk $@

# Detección automática de dependencias en código fuente C++ #
%.d: %.cpp
	@$(CXX) -MM -MF $@ ${CPPFLAGS} $(CXXFLAGS) $<
	@sed --regexp-extended --in-place 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(OWN_SRCS:.cpp=.d) $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d)

# Porque Cadena y Fecha aún son susceptibles de cambios...
# ¡Ojo! Se usan los Makefile del alumno en ${DIRFECHCAD}.
cadena.o: ${DIRFECHCAD}/cadena.hpp
	${MAKE} --directory=${DIRFECHCAD} --file=${DIRFECHCAD}/Makefile $@
fecha.o : ${DIRFECHCAD}/fecha.hpp
	${MAKE} --directory=${DIRFECHCAD} --file=${DIRFECHCAD}/Makefile $@

# Por si se cambia algo en los tests automáticos
${TESTS_OBJS}: ${TESTS_SRCS} ${TESTS_HDRS}

## Limpieza
#  normal...
clean:
	${RM} ${RMFLAGS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} \
	      ${TEST_OBJS} ${DIRTESTS}/*.d ${OWN_OBJS} ${CHECK_EXE} \
              *.d *~ \#* *.gcno *.{aux,log,dvi,toc} core
	${MAKE} --makefile=Make_check.mk $@
	${MAKE} --directory=${DIRFECHCAD} --file=${DIRFECHCAD}/Makefile $@

# ... más profunda ...
allclean: clean
	${RM} ${RMFLAGS} ${LOCALLIBS}
	${MAKE} --makefile=Make_check.mk $@

# ... y del archivo a entregar.
distclean: allclean
	${RM} ${RMFLAGS} ${NOMBRETAR}

## Empaquetado para entrega

# Esto lo debería usar el alumnado a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre de las prácticas
# tras borrar lo sobrante.
dist: distclean ${NOMBRETAR}

FICHEROS_ENTREGA = $D/usuario.hpp  $D/usuario.cpp  \
		$D/articulo.hpp $D/articulo.cpp \
		$D/tarjeta.hpp  $D/tarjeta.cpp  \
		${AP1_AP2_N}/${DFC}/cadena.hpp ${AP1_AP2_N}/${DFC}/cadena.cpp \
		${AP1_AP2_N}/${DFC}/fecha.hpp  ${AP1_AP2_N}/${DFC}/fecha.cpp  \
		${AP1_AP2_N}/${DFC}/Makefile
ifneq ($P, P2)
FICHEROS_ENTREGA += $D/pedido.hpp   $D/pedido.cpp   \
		$D/pedido-articulo.hpp $D/pedido-articulo.cpp \
		$D/usuario-pedido.hpp  $D/usuario-pedido.cpp
endif


${NOMBRETAR}: ${OWN_SRCS} ${OWN_HDRS}
ifeq ($(strip $(AP1_AP2_N)),)
	@echo ""
	@echo "ATENCIÓN: En el Makefile debe estar definida la variable"
	@echo " AP1_AP2_N con el nombre del directorio superior a este."
	@echo "Vea las instrucciones de entrega de las prácticas."
else
	@echo "Creando archivo en ${NOMBRETAR} con el siguiente contenido:"
	tar --create --verbose --gzip --file=${NOMBRETAR} --directory=../.. \
            ${FICHEROS_ENTREGA}
endif

# Ayuda
help:
	echo "make [all]          -- Construye los programas de prueba"
	echo "make tests          -- Construye y ejecuta los programas de prueba"
	echo "make test-noauto    -- Construye y ejecuta el programa de prueba «de consola»"
	echo "make test-auto      -- Construye y ejecuta el programa de pruebas automáticas"
	echo "make check          -- Construye y ejecuta el programa de comprobaciones estáticas de código fuente"
	echo "make valgrind       -- Construye y ejecuta con valgrind los programas de prueba"
	echo "make ${MAIN_EXE}   -- Construye el programa de prueba «de consola»"
	echo "make ${TEST_EXE}   -- Construye el programa de pruebas automáticas"
	echo "make ${CHECK_EXE} -- Construye el programa de comprobaciones estáticas de código fuente"
	echo "make clean          -- Borra los programas de pruebas y comprobaciones, y los módulos objeto"
	echo "make allclean       -- Borra como 'clean' más los módulos objeto de P1 y comprobaciones estáticas de código fuente"
	echo "make distclean      -- Borra como 'allclean' más el archivo de entregas"
	echo "make dist           -- Borra como 'distclean' y crea el archivo de entrega en ${NOMBRETAR}"
	echo "make help           -- Muestra esta ayuda"
	echo "make variables      -- Muestra las variables más importantes definidas en este Makefile"

variables:
	echo "---- Principales variables o macros definidas en el Makefile ----"
	echo "--- Lugares (directorios)"
	echo "AP1_AP2_N = \"$(AP1_AP2_N)\" -- Directorio donde están las prácticas de POO"
	echo "P = \"$P\" -- Nombre de esta práctica y su directorio"
	echo "D = \"$D\" -- Ídem, desde el directorio padre de las prácticas de POO"
	echo "DIRFECHCAD = \"$(DIRFECHCAD)\" -- Directorio de la práctica 1 donde están las clases Fecha y Cadena"
	echo "DIRTESTS = \"$(DIRTESTS)\" -- Directorio de los programas de pruebas automáticas"
	echo "DIRLUHN = \"$(DIRLUHN)\" -- Directorio donde está el fichero con el algoritmo de Luhn"
	echo "--- Traducción (preprocesado, compilación, enlazado)"
	echo "CXX = \"$(CXX)\" -- El \"compilador\""
	echo "CPPFLAGS = \"$(CPPFLAGS)\" -- Opciones para el preprocesador"
	echo "CXXFLAGS = \"$(CXXFLAGS)\" -- Opciones para el compilador"
	echo "LDFLAGS = \"$(LDFLAGS)\" -- Opciones para el enlazador"
	echo "LIBS = \"$(LIBS)\" -- Bibliotecas con las que hay que enlazar"
	echo "--- Ficheros"
	echo "OWN_SRCS = \"$(OWN_SRCS)\" -- Fuentes en C++ que hay que hacer"
	echo "OWN_HDRS = \"$(OWN_HDRS)\" -- Cabeceras en C++ que hay que hacer"
	echo "SRCS = \"$(SRCS)\" -- Todos los ficheros fuente en C++"
	echo "HDRS = \"$(HDRS)\" -- Todos los ficheros de cabecera en C++"
	echo "MAIN_SRCS = \"$(MAIN_SRCS)\" -- Fuente C++ del programa de prueba"
	echo "MAIN_EXE = \"$(MAIN_EXE)\" -- El programa de prueba"
	echo "TEST_SRCS = \"$(TEST_SRCS)\" -- Fuentes C++ del programa de pruebas unitarias automáticas"
	echo "TEST_HDRS = \"$(TEST_HDRS)\" -- Cabeceras C++ del programa de pruebas automáticas"
	echo "TEST_EXE = \"$(TEST_EXE)\" -- Programa de pruebas unitarias automáticas"
	echo "CHECK_SRC = \"$(CHECK_SRC)\" -- Fuente C++ del programa de comprobaciones estáticas de código fuente C++"
	echo "CHECK_EXE = \"$(CHECK_EXE)\" -- Programa de comprobaciones estáticas de código fuente"
	echo "NOMBRETAR = \"$(NOMBRETAR)\" -- El archivo comprimido con lo que hay que entregar"
	echo "FICHEROS_ENTREGA = \"$(FICHEROS_ENTREGA)\" -- Los ficheros que están en el archivo \"$(NOMBRETAR)\""

# Objetivos falsos
.PHONY: all clean allclean distclean dist check valgrind \
        tests test-noauto test-auto help
# Objetivos silenciosos
.SILENT: help variables
