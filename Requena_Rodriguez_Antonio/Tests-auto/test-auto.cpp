/* $Id: test-auto.cpp 344 2016-04-29 20:20:13Z gerardo $
 * Pruebas automáticas para el S. G. L., P0..P4
 * Prácticas de POO
 * ©2014-18 Antonio G.ª Domínguez y el resto de profesores de POO
 */

#include "test-auto.hpp"

/**
  UN FICHERO PARA GOBERNARLOS A TODOS, UN FICHERO PARA ENCONTRARLOS,
  UN FICHERO PARA ATRAERLOS A TODOS... y ejecutarlos de una vez, que
  resulta más cómodo.

  Incluye también varias funciones de utilidad para las pruebas.
  V. comentarios sobre las funciones en test-auto.hpp .
*/
using namespace std;		// Esto también resulta más cómodo.

#ifdef P4
Articulo::Autores crea_autores(Autor& autor) {
  Articulo::Autores autores { &autor };
  return autores;
}
#endif

/**
   Convierte un número de coma flotante de doble precisión a una
   cantidad de euros, con dos dígitos decimales.
*/
string toEuros(double cantidad) {
  ostringstream os;
  os.imbue(locale(locale("es_ES.UTF-8"), new sin_separador()));
  os << fixed << setprecision(2) << cantidad << " €";
  return os.str();
}

#ifndef CPP11REGEX
regoff_t find_regex(const char* regex, const char* text) noexcept(false) {
  regex_t reg;
  if (regcomp(&reg, regex, REG_EXTENDED) != 0)
    throw BadRegex(regex);
  regmatch_t matches[1] = {{-1, -1}};
  regexec(&reg, text, 1, matches, 0);
  regfree(&reg);

  return matches[0].rm_so;
}
#endif

/***** CUERPO PRINCIPAL *****/

FCT_BGN() {

  /**
     Establecemos la localización por omisión a la española de España
     con UTF-8, para asegurarnos de que las pruebas funcionen como
     deben. Si no, se mezclarán los separadores decimales ingleses
     ('.') y españoles (',').
  */
  try {
    locale::global(locale("es_ES.UTF-8"));
  }
  catch(const runtime_error& e) {
    cerr << "Parece que no tienes la localización española "
      "\"es_ES.UTF-8\". Instálala antes. El mensaje de error es:\n"
	 << e.what() << "\nFin del programa" << endl;
    return 1;
  }
  // Establecemos la zona horaria a UTC para evitar cosas raras
  setenv("TZ", "", 1);
  tzset();

  /**
     No sirve para nada: simplemente callamos a GCC C++ para que no
     incordie al compilar con avisos de funciones no usadas con FCTX.
     Anulado porque ya no hace falta con las últimas versiones de GCC.
  */
#if 0
  FCT_SUITE_BGN(Callar avisos de GCC) {
    FCT_TEST_BGN(callar avisos de GCC) {
      fct_chk(true);
    } FCT_TEST_END();
  }
  FCT_SUITE_END();
#endif
  /**
     Los tests de Fecha y Cadena ("caso 0", práctica preliminar P0 y P1) se 
     hacen en todas las prácticas, de P0 a P4. Los de P2 (casos 1 y 2) se hacen
     en P2 a P4. Los de P3 (caso 3: clases e informes) se hacen en P3 y P4, 
     y los de P4 (caso 4), obviamente solo en P4, de forma que cada práctica
     arrastra los tests de las anteriores, teniendo en cuenta las pequeñas 
     modificaciones de las partes comunes.
*/
  FCTMF_SUITE_CALL(test_fecha);
  FCTMF_SUITE_CALL(test_cadena);
#if defined(P2) || defined(P3) || defined(P4)
  FCTMF_SUITE_CALL(test_p2);
#endif
#if defined(P3) || defined(P4)
  FCTMF_SUITE_CALL(test_p3_clases);
  FCTMF_SUITE_CALL(test_p3_informes);
#endif
#ifdef P4
  FCTMF_SUITE_CALL(test_p4);
#endif

  cerr << endl;
}
FCT_END()
