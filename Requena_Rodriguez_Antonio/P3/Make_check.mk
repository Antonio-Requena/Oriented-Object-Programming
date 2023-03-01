# $Id: Make_check.mk 416 2018-04-23 08:38:49Z u44965478 $
# Comprobaciones de código para P4
# ©2015 Pedro Delgado, para POO
# ©2017 - Simplificación - Gerardo
# ©2020 - usuario-pedido.cpp (no hpp) - Gerardo
# ©2021 Gerardo - La Gran Unificación

# V. comentario en Makefile
ifndef P
P = $(shell basename ${PWD})
endif

# Directorio donde está el código compartido del DSL
DIR=../dsl-comprobaciones/

# Obligatorio Clang, versión 3.9 al menos.
CXX         := clang++
CPPFLAGS    := -I${DIR} -D$P $(shell llvm-config --cppflags)
CXXFLAGS    := -std=c++14
# Añadir -static en la siguiente línea para obtener un ejecutable enlazado 
# estáticamente muy grande y pesado pero que se puede distribuir al 
# alumnado para que no tengan que instalarse todos los paquetes de 
# desarrollo de LLVM/CLang.
LDFLAGS     := $(shell llvm-config --libs) # -static
COMMONSRCS  := $(DIR)caclibrary.cpp $(DIR)execute.cpp $(DIR)matchers.cpp
OWNSOURCE   := libreria_check.cpp
SOURCES     := $(OWNSOURCE) ${COMMONSRCS}
COMMONHDRS  := $(COMMONSRCS:.cpp=.h) $(DIR)info.h
COMMONOBJS  := $(COMMONSRCS:.cpp=.o)
OBJECT      := $(OWNSOURCE:.cpp=.o)
EXE         := $(OWNSOURCE:.cpp=)
VERIFYSRCS   = articulo.cpp tarjeta.cpp usuario.cpp
ifneq ($P, P2)
VERIFYSRCS  += pedido.cpp pedido-articulo.cpp usuario-pedido.cpp
endif
CLANGLIBS   := -lclangFrontend -lclangSerialization -lclangDriver      \
		-lclangTooling -lclangParse -lclangSema -lclangAnalysis \
		-lclangEdit -lclangAST -lclangASTMatchers -lclangLex     \
		-lclangBasic -lclangRewrite

.PHONY: clean all allclean check

all: $(EXE)

${EXE}: $(OBJECT) $(COMMONOBJS)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CLANGLIBS)

${COMMONOBJS}: ${COMMONHDRS}
	${MAKE} --file=$(DIR)Makefile --directory=${DIR}

$(OWNSOURCE): ${COMMONOBJS} $(COMMONHDRS)

check: ${EXE}
	@echo Verificando los fuentes ...
	./${EXE} -extra-arg-before="-I../P1" -extra-arg="-std=c++14" \
          ${VERIFYSRCS} -- -D$P

clean:
	${RM} ${RMFLAGS} $(EXE) $(OBJECT)

allclean: clean
	${RM} ${RMFLAGS} ${COMMONOBJS}
