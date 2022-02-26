/*
 * fecha_cadena_check.cpp - Análisis estático de código fuente 
 * para las clases Fecha y Cadena de P0 y P1.
 * ©2020 Los profesores de POO
 * ©2021 Gerardo - La Gran Unificación
 */

/* Debe estar definido P0 o P1, pero P1 es incompatible con
 * caclibrary.h que incluye a su vez llvm/ADT/STLExtras.h donde se
 * usan P1 y P2 como parámetros de plantilla.
 */
#ifdef P1
#define PRACTICA1
#undef P1
#endif
#include "caclibrary.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
  
int main(int argc, const char **argv) {

  /***************** Fecha *************************************/
  checkCode cf(argc, argv, "fecha.cpp",
      "Modo de empleo: ./fecha_check fecha.cpp cadena.cpp -- -std=c++11");
  cf.setCorrectMessage("Verificación correcta de la clase Fecha.");
  cf.setIncorrectMessage("REVISA LA CLASE Fecha.");
  
  if(cf.findClass({"Fecha"})) {
    cf.staticVariable("Fecha", {"AnnoMaximo", "AnnoMinimo"}, {"const", "const"},
		     "Revisa el enunciado respecto a AnnoMinimo y AnnoMaximo.");
    cf.defaultConstructor("Fecha", true,
	      "Revisa el enunciado respecto a la construcción de objetos.");
    vector<string> parameters = {"int", "int", "int"};
    cf.explicitSpecifiedConstructor("Fecha", parameters,
		"Revisa el enunciado respecto a conversiones implícitas.");
    vector<string> initializationList = {"int", "int", "int"};
    cf.listInitializerConstructor("Fecha", initializationList,
				 initializationList,
				 "Revisa la inicialización de los atributos.");
    cf.copyConstructor("Fecha", false,
		      "Revisa el enunciado respecto al constructor de copia.");
    vector<string> consts = {"?", "?", "?", "?", "?"};
    vector<vector<string>> params = {{"?"}, {"?"}, {"?"}, {"?"}, {"?"}};
    cf.methodWithReferencedMethod({"operator-=", "operator+",
				  "operator-", "operator++", "operator--"},
      params, "Fecha", consts,
      {"operator+=", "operator+=", "operator+=", "operator+=", "operator+="},
      params, "Fecha", consts,
      "Revisa los consejos sobre los operadores aritméticos.");
    params = {{"?"}, {"?"}, {"?"}, {"?"} };
    cf.functionWithReferencedFunction({"operator!=", "operator>",
				      "operator<=", "operator>="}, params,   
      {"operator==", "operator<", "operator<", "operator<"}, params,
      "Revisa los consejos sobre los operadores de comparación.");
    params = {{"?"}};
    cf.inlineMethod({"dia"}, params, "Fecha", {"const"}, 
		   "Sugerencia: incluir marca 'inline' a aquellos métodos"
		   " con pocas instrucciones, como 'dia()'."); 
    cf.noExceptMethod({"dia"}, params, "Fecha", {"const"}, 
		     "Sugerencia: incluir marca 'noexcept' "
		     "a aquellos métodos que no lancen excepciones."); 		
    vector<string> functionNames = {"ssprintf", "sscanf"};
    string headerName = "cstdio";
    cf.fileIncludedHeader(headerName, {"fecha.cpp", "fecha.hpp"},
			 "Revisa dónde se declaran las funciones"
			 " ssprintf y sscanf.");
    cf.guardClauses("fecha.hpp", "Recuerda incluir las guardas de inclusión.");
    cf.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Fecha'\n";

  /*************** Cadena *************************/
  
  checkCode cc(argc, argv, "cadena.cpp");
  cc.setCorrectMessage("Verificación correcta de la clase Cadena.");
  cc.setIncorrectMessage("REVISA LA CLASE Cadena.");

  if(cc.findClass({"Cadena"})) {
    cc.defaultConstructor("Cadena",
       "Revisa el enunciado respecto a la construcción de objetos.");
    vector<string> params = {"?", "char"};
    cc.explicitSpecifiedConstructor("Cadena", params,
       "Revisa el enunciado respecto a conversiones implícitas.");
    vector<string> initializationList = {"?"};
    vector<string> parameters = {"?"};
    cc.listInitializerConstructor("Cadena", parameters, initializationList,
				  "Revisa la inicialización de los atributos.");
    cc.numberOfConstructors("Cadena", 3, true,
			    "Número de constructores incorrecto.");
    vector<string> memoryFunctionNames = {"malloc","calloc", "realloc", "free"};
    string memoryHeaderName = "stdlib";
    cc.invocationsFromHeaders(memoryFunctionNames, memoryHeaderName, false,
       "Revisa la asignación y destrucción de memoria de variables.");
    cc.takeException({"out_of_range"},
       "Revisa las excepciones que se han de lanzar en el programa.");
    cc.fileIncludedHeader("stdexcept", {"cadena.cpp", "cadena.hpp"},
       "Comprueba haber incluido las cabeceras adecuadas en tus ficheros.");
    vector<string> standardFunctionNames = {"strlen","strcat",
					    "memset", "strcpy"};
    string standardHeaderName = "cstring";
    cc.invocationsFromHeaders(standardFunctionNames, standardHeaderName, true,
			      "Revisa de dónde son tomadas las funciones de la"
			      " biblioteca estándar como strlen, strcpy...");
    cc.destructorDeleteMember("Cadena", {"s_"},
			      "Revisa el destructor de la clase.");
    cc.releaseVariable("Revisa la asignación y liberación de memoria.");
    vector<string> methodNames = {"length"};
    vector<vector<string> > parametersMethods = {{"?"}};
    cc.inlineMethod(methodNames, parametersMethods, "Cadena", {"?"},
		    "Sugerencia: incluir marca 'inline' a aquellos"
		    " métodos con pocas instrucciones, como 'length()'.");
    cc.noExceptMethod(methodNames, parametersMethods, "Cadena", {"?"},
		      "Sugerencia: incluir marca 'noexcept' a aquellos"
		      " métodos que no lancen excepciones, como 'length()'");
    cc.guardClauses("cadena.hpp", "Recuerda incluir las guardas de inclusión.");
#ifdef PRACTICA1
    cc.moveConstructor("Cadena",
		       "Revisa el enunciado respecto a los constructores.");
#endif
    cc.notFriendMember("Cadena", "Revisa si es necesario declarar 'friend'.");
    cc.function({
#ifdef PRACTICA1
		 "operator<<", "operator>>",
#endif
		 "operator>", "operator<", "operator>=", "operator<=",
		 "operator==", "operator!=", "operator+"},
      {
#ifdef PRACTICA1
       {"?"}, {"?"},
#endif
       {"?"}, {"?"}, {"?"}, {"?"}, {"?"}, {"?"}, {"?"}},
      "Revisa el lugar de la declaración de los operadores.");
#ifdef PRACTICA1
    vector<vector<string> > parametros = {{"?"}, {"?"}, {"?"}, {"?"} };
    cc.methodWithReferencedMethod({"rbegin", "crbegin", "rend", "crend"},
				  parametros, "Cadena", {"?", "?", "?", "?"},
				  {"end", "end", "begin", "begin"},
				  parametros, "Cadena", {"?", "?", "?", "?"},
       "Emplea la reutilización en las funciones sobre iteradores.");
#endif
    cc.check();
  }
  else
    llvm::outs()<<"No se ha encontrado la clase 'Cadena'.\n";
}
