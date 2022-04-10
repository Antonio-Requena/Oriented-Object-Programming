/* 
 * libreria_check.cpp - Comprobación estática de código fuente
 * para las clases del SGL. Hacen uso de un DSL.  
 * ©2020 POO - Pedro, Inma, Fidel, Gerardo
 * ©2021 Gerardo - La Gran Unificación
 */

/* Debe estar definida P2, P3 o P4, pero P2 es incompatible con
 * "caclibrary.h", porque incluye a su vez "llvm/ADT/STLExtras.h",
 * donde se usan P1 y P2 como parámetros de plantilla.
 * En este programa no usamos la macro P2, así que simplemente la anulamos.
 */
#undef P2

#include "caclibrary.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, const char **argv)
{
  checkCode c1(argc, argv, "articulo.cpp",
	       "Modo de empleo: ./libreria_check *.cpp --"
	       " -std=c++14 -I../P1 -DPx  # x es 2, 3 o 4");
  //	       " articulo.cpp tarjeta.cpp usuario.cpp pedido.cpp"
  //	       " pedido-articulo.cpp usuario-pedido.cpp -- -std=c++14"
  //	       " -I../P1");
  string headerName = "cstring";
  vector<string> functionNames = {"strlen", "strcat", "memset", 
				  "strcpy", "strcmp"};
#ifndef P4
  c1.setCorrectMessage("Verificación correcta de la clase Artículo.");
  c1.setIncorrectMessage("REVISA LOS POSIBLES ERRORES DE Articulo.");

  if(c1.findClass({"Articulo"})){
    llvm::outs() << "* articulo.cpp:\n";
    c1.invocationsFromHeaders(functionNames, headerName, true,
			      "Revisa de dónde son tomadas las funciones de la"
			      " biblioteca estándar como strlen, strcpy...");
    c1.allPrivateVariableMember("Articulo","Revisa el acceso a los atributos.");
    c1.notFriendMember("Articulo", "Revisa si es necesario incluir 'friend'.");
    c1.guardClauses("articulo.hpp","Recuerda añadir las guardas de inclusión.");
    c1.check();
  }
  else
    llvm::outs()<<"No se ha encontrado la clase 'Articulo'"<<"\n";

#else
  // P4
  c1.setCorrectMessage
    ("Verificación correcta de la clase Articulo y sus derivadas.");
  c1.setIncorrectMessage("REVISA LA CLASE Articulo Y SUS DERIVADAS.");

  if(c1.findClass({"Articulo", "ArticuloAlmacenable", "Autor",
            "Libro","Cederron","LibroDigital"})) {
    llvm::outs() << "* articulo.cpp:\n";

    c1.allPrivateVariableMember("Articulo","Revisa el acceso a los atributos.");
    c1.notFriendMember("Articulo", "Revisa si es necesario incluir 'friend'.");
    c1.guardClauses("articulo.hpp","Recuerda añadir las guardas de inclusión.");
    c1.memberVariable("Articulo", {"stock_"}, {"?"}, {false}, 
		      "Revisa el enunciado respecto a los atributos"
		      " que deben estar en cada clase (¿Articulo::stock_?).");
    c1.memberVariable("ArticuloAlmacenable", {"stock_"}, {"noconst"}, 
		      {true}, "Revisa el enunciado respecto a los atributos"
		      " que deben estar en cada clase"
		      " (ArticuloAlmacenable::stock_).");
    c1.virtualMethod({"~Articulo"},{{}},"Articulo", {"noconst"}, 
		     "Contempla crear un destructor apropiado para esta clase."
		     );
    c1.functionWithReferencedMethod({"operator<<"},{{
	  "class std::basic_ostream<char> &","const class Articulo &"}},
      {"impresion_especifica"},{{"class std::basic_ostream<char> &"}},
      "Articulo",{"const"},
      "¿No llamas a impresion_especifica en el operador de inserción?");
    c1.methodWithReferencedMemberVariable({"impresion_especifica"}, {{
	  "class std::basic_ostream<char> &"}}, "Libro", {"const"}, 
      {"n_pag_"}, "Revisa qué debe imprimir la definición"
      " del método impresion_especifica en cada clase.");
    c1.methodWithReferencedMemberVariable({"impresion_especifica"}, {{
	  "class std::basic_ostream<char> &"}}, "Libro", {"const"}, 
      {"stock_"},"Revisa qué debe imprimir la definición"
      " del método impresion_especifica en cada clase.");
    c1.methodWithReferencedMemberVariable({"impresion_especifica"}, {{
	  "class std::basic_ostream<char> &"}}, "Cederron", {"const"}, 
      {"tam_"},"Revisa qué debe imprimir la definición"
      " del método impresion_especifica en cada clase.");
    c1.methodWithReferencedMemberVariable({"impresion_especifica"}, {{
	  "class std::basic_ostream<char> &"}}, "Cederron", {"const"}, 
      {"stock_"},"Revisa qué debe imprimir la definición"
      " del método impresion_especifica en cada clase.");
    c1.methodWithReferencedMemberVariable({"impresion_especifica"}, {{
	  "class std::basic_ostream<char> &"}}, "LibroDigital", {"const"},
      {"f_expir_"},"Revisa qué debe imprimir la definición"
      " del método impresion_especifica en cada clase.");
    c1.method({"nombre","apellidos","direccion"}, {{},{},{}}, "Autor",
	      {"const","const","const"}, 
	      "Revisa el uso de métodos constantes (Autor).");
    c1.noExceptMethod({"nombre","apellidos","direccion"},{{},{},{}}, 
		      "Autor", {"const","const","const"}, 
		      "Revisa el enunciado respecto a las excepciones (Autor)."
		      );
    c1.check();
  }
  else
    llvm::outs() << "No se han encontrado las clases 'Articulo',"
      " 'ArticuloAlmacenable', 'Autor', 'Libro', 'Cederron' o 'LibroDigital'\n";
#endif // P4
  
  checkCode c2(argc, argv, "tarjeta.cpp", "");
  c2.setCorrectMessage("Verificación correcta de la clase Tarjeta.");
  c2.setIncorrectMessage("REVISA LA CLASE Tarjeta.");
  
  if(c2.findClass({"Tarjeta"})) {        
    llvm::outs() << "* tarjeta.cpp:\n";
    
    c2.invocationsFromHeaders(functionNames, headerName, true, 
			      "Revisa de dónde son tomadas las funciones de"
			      " la biblioteca estándar de C, como strcmp...");	
    c2.allPrivateVariableMember("Tarjeta", "Revisa el acceso a los atributos.");

    //Constructor de copia y operador de asignación
    c2.deletedMethod({"Tarjeta", "operator="}, {{
	  "const class Tarjeta &"}, {"const class Tarjeta &"}}, "Tarjeta", 
      {"noconst", "noconst"}, 
      "Revisa el enunciado respecto a la copia de objetos.");
    c2.guardClauses("tarjeta.hpp", "Recuerda añadir las guardas de inclusión.");

    vector<string> methodNames = {"numero", "caducidad", "activa"};
    vector<vector<string>> parametersMethods = {{},{},{}};
    c2.inlineMethod(methodNames, parametersMethods, "Tarjeta", 
		    { "const", "const", "const" }, 
		    "Sugerencia: incluir marca 'inline' a aquellos métodos"
		    " con pocas instrucciones, como 'numero()', 'caducidad()'"
		    " o 'activa()'.");
		    
    c2.friendClass("Tarjeta", {"Usuario"}, "Recuerda: solo la clase Usuario debe poder llamar al método anula_titular de Tarjeta.");
    		    
    c2.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Tarjeta'.\n";
  
  checkCode c3(argc, argv,"usuario.cpp", "");
  c3.setCorrectMessage("Verificación correcta de la clase Usuario.");
  c3.setIncorrectMessage("REVISA LA CLASE Usuario.");

  if(c3.findClass({"Usuario"})) {
    llvm::outs() << "* usuario.cpp:\n";

    c3.invocationsFromHeaders(functionNames, headerName, true, 
            "Revisa de dónde son tomadas las funciones"
            " de la biblioteca estándar de C, como strlen, strcmp...");
    c3.allPrivateVariableMember("Usuario", "Revisa el acceso a los atributos.");
	
    //Constructor de copia y operador de asignación
    c3.deletedMethod({"Usuario", "operator="}, 
		     {{"const class Usuario &"}, {"const class Usuario &"}}, 
		     "Usuario", {"noconst", "noconst"}, 
		     "Revisa el enunciado respecto a la copia de objetos.");	
    c3.numberOfConstructors("Usuario", 1, false,
       "Revisa el enunciado respecto a los constructores en esta clase.");
    c3.friendFunction({"operator<<"}, {{"?"}}, "Usuario", 
		      "Revisa si existen funciones que deben ser marcadas"
		      " como amigas de la clase.");
    vector<string> methodNames = {"id", "nombre", "apellidos"};
    vector<vector<string>> parametersMethods = {{},{},{}};
    c3.inlineMethod(methodNames, parametersMethods, "Usuario",
		    {"const", "const", "const"},
		    "Sugerencia: incluir marca 'inline'"
		    " a aquellos métodos con pocas instrucciones, como"
		    " 'id()', 'nombre()' o 'apellidos()'.");
    c3.guardClauses("usuario.hpp", "Recuerda añadir las guardas de inclusión.");
    c3.check();
  }
  else
    llvm::outs()<<"No se ha encontrado la clase 'Usuario'.\n";

#if defined P3 || defined P4
  checkCode c4(argc, argv,"pedido.cpp", "");
  c4.setCorrectMessage("Verificación correcta de la clase Pedido.");
  c4.setIncorrectMessage("REVISA LA CLASE Pedido.");

  if(c4.findClass({"Pedido"})) {
    llvm::outs() << "* pedido.cpp:\n";

    c4.allPrivateVariableMember("Pedido", "Revisa el acceso a los atributos.");
    c4.numberOfConstructors("Pedido", 1, false, 
       "Revisa el enunciado respecto al n.º de constructores de Pedido");
    c4.defaultArgumentsInMethod({"Pedido"}, {{"?"}}, "Pedido", 
				{"?"}, {1}, {{"Fecha()"}}, 
            "Revisa el enunciado respecto a la construcción de un Pedido.");    
    /* Ponemos "?" como lista de parámetros porque solo debe haber un
       constructor. La regla funcionará cualquiera que sea el orden en
       el que se pongan los inicializadores en el constructor.
    */
    c4.listInitializerConstructor("Pedido", {"?"}, {"int", 
	  "const class Tarjeta *", "class Fecha", "double"}, 
      "Revisa la lista de inicialización del constructor."); 
    c4.function({"operator<<"},
		{{"class std::basic_ostream<char> &", "const class Pedido &"}}, 
		"Revisa el enunciado respecto al operador de inserción.");
    c4.memberVariable("Pedido", {"tarjeta_"}, {"const"}, {true}, 
		      "Revisa el enunciado respecto al atributo de la tarjeta."
		      );
    c4.guardClauses("pedido.hpp", "Recuerda añadir las guardas de inclusión");
#ifdef P4
    c4.methodWithDynamicCast("Pedido", {}, "Pedido", "noconst", 
			     "class Articulo *", "class ArticuloAlmacenable *", 
			     "Es necesario que emplees el operador de molde "
			     "apropiado en el constructor de la clase"
			     " (Articulo* -> ArticuloAlmacenable*).\n");
    c4.methodWithDynamicCast("Pedido", {}, "Pedido", "noconst", 
			     "class Articulo *", "class LibroDigital *", 
			     "Es necesario que emplees el operador de molde "
			     "apropiado en el constructor de la clase"
			     " (Articulo* -> LibroDigital*).\n");
#endif // P4 solo
        c4.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Pedido'.\n";

  checkCode c5(argc, argv,"pedido-articulo.cpp", "");
  c5.setCorrectMessage("Verificación correcta de la clase Pedido_Articulo.");
  c5.setIncorrectMessage("REVISA LA CLASE Pedido_Articulo.");

  if(c5.findClass({"Pedido_Articulo", "LineaPedido"})) {
    llvm::outs() << "* pedido-articulo.cpp:\n";

    c5.numberOfConstructors("Pedido_Articulo", 0, false, 
			    "Revisa la necesidad de definir constructores"
			    " de Pedido_Articulo.");
    c5.numberOfConstructors("LineaPedido", 1, false, 
			    "Revisa el enunciado respecto al n.º de "
			    "constructores de LineaPedido.");
    vector<string> params = { "double", "unsigned int" };
    vector<vector<string>> methodsParams = { params };
    c5.defaultArgumentsInMethod({"LineaPedido"}, methodsParams, 
				"LineaPedido", {"?"}, {1}, {{"1"}}, 
				"Revisa el enunciado respecto al "
				"constructor de LineaPedido.");
    c5.explicitSpecifiedConstructor("LineaPedido", params, 
       "Revisa el enunciado respecto a conversiones implícitas.");
    c5.function({"operator<<"}, {{"class std::basic_ostream<char> &",
	    "const class LineaPedido &"}}, 
      "Revisa el lugar de la declaración de los operadores.");
    /* 
       'pedir' sobrecargado puede hacerse mediante la búsqueda de
       dos métodos con diferentes parametros. 
    */
    c5.method({"pedir","pedir"},{{"class Pedido &", 
	    "class Articulo &", "double", "unsigned int"},
	  {"class Articulo &", "class Pedido &", "double", 
	      "unsigned int"}}, "Pedido_Articulo", {"noconst","noconst"},
      "Se sugiere la sobrecarga del método 'pedir'.");
    c5.guardClauses("pedido-articulo.hpp",
		    "Recuerda añadir las guardas de inclusión");
		    
    c5.methodWithReferencedMethod({"mostrarDetallePedidos", "mostrarVentasArticulos"}, 
    {{"?"}, {"?"}}, "Pedido_Articulo", {"?", "?"},
      {"detalle", "ventas"}, {{"?"}, {"?"}}, "Pedido_Articulo", {"const", "const"},
      "Revisa la posibilidad de reutilizar los métodos detalle y ventas en los métodos mostrarDetallePedidos y mostrarVentasArticulos.");    		    
    c5.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Pedido_Articulo'.\n";

  checkCode c6(argc, argv,"usuario-pedido.cpp", "");
  c6.setCorrectMessage("Verificación correcta de la clase Usuario_Pedido.");
  c6.setIncorrectMessage("REVISA LA CLASE Usuario_Pedido.");

  if(c6.findClass({"Usuario_Pedido"})) {
    llvm::outs() << "* usuario-pedido.cpp:\n";
        
    c6.allPrivateVariableMember("Usuario_Pedido", 
				"Revisa el acceso a los atributos.");
    c6.guardClauses("usuario-pedido.hpp", 
		    "Recuerda añadir las guardas de inclusión múltiple.");
    c6.notFriendMember("Usuario_Pedido",
		       "Revisa si es necesario incluir friend.");
    c6.check();
  }
  else
    llvm::outs() << "No se ha encontrado la clase 'Usuario_Pedido'.\n";
#endif  // P3 y P4
}
