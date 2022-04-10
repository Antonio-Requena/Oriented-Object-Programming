#	$Id: Make_check.mk 411 2018-04-04 16:04:49Z u44965478 $
# Makefile para las comprobaciones estáticas de código fuente
# de cadena.cpp y fecha.cpp, clases Cadena y Fecha, de la P1
# ©2017 Los profesores de POO de la ESI de la UCA
# ©2021 Gerardo - La Gran Unificación

# V. comentario en Makefile
ifndef P
P = $(shell basename ${PWD})
endif

# Directorio donde está el código compartido del DSL
DIR=../dsl-comprobaciones/

# Obligatorio Clang, versión 9 al menos
CXX         := clang++
CPPFLAGS    := -I${DIR} -D$P $(shell llvm-config --cppflags)
CXXFLAGS    := -std=c++17
# Añadir -static en la siguiente línea para obtener un ejecutable enlazado 
# estáticamente muy grande y pesado pero que se puede distribuir al 
# alumnado para que no tengan que instalarse todos los paquetes de 
# desarrollo de LLVM/CLang.
LDFLAGS     := $(shell llvm-config --libs) #-static
COMMONSRCS  := $(DIR)caclibrary.cpp $(DIR)execute.cpp $(DIR)matchers.cpp
OWNSOURCE   := fecha_cadena_check.cpp
SOURCES     := ${OWNSOURCE} ${COMMONSRCS}
COMMONHDRS  := $(COMMONSRCS:.cpp=.h) $(DIR)info.h
COMMONOBJS  := $(COMMONSRCS:.cpp=.o)
OBJECT      := $(OWNSOURCE:.cpp=.o)
EXE         := $(OWNSOURCE:.cpp=)
CLANGLIBS   := -lclangFrontend -lclangSerialization -lclangDriver \
		-lclangTooling -lclangParse -lclangSema -lclangAnalysis \
		-lclangEdit -lclangAST -lclangASTMatchers -lclangLex \
		-lclangBasic -lclangRewrite

.PHONY: clean all check
all: $(EXE)

${EXE}: ${OBJECT} $(COMMONOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CLANGLIBS)

${COMMONOBJS}: ${COMMONHDRS} ${COMMONSRCS}
	${MAKE} --file=$(DIR)Makefile --directory=${DIR}

check: ${EXE}
	@echo Verificando fecha.cpp y cadena.cpp ...
	./fecha_cadena_check -extra-arg-before="-D$P" -extra-arg="-std=c++11" \
	fecha.cpp cadena.cpp --

clean:
	@echo "Limpiando."
	${RM} ${RMFLAGS} $(EXE) $(OBJECT)

allclean: clean
	${MAKE} --file=$(DIR)Makefile --directory=$(DIR) clean
