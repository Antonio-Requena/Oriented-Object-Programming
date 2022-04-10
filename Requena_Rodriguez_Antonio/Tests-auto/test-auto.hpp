/* -*-c++-*-
 * $Id: test-auto.hpp 344 2016-04-29 20:20:13Z gerardo $
 *
 * Fichero de cabecera para todos los tests unitarios automáticos
 * de todas las prácticas.
 * Debe estar definida la macro Px, siendo x | 0 ≤ x ≤ 4 el n.º de la práctica.
 *
 * ©2014 Antonio G.ª Dguez.
 * ©2015-18 el resto de profesores de POO
 */

#ifndef TEST_AUTO_HPP_
#define TEST_AUTO_HPP_

#if !defined(P0) && !defined(P1) && !defined(P2) && !defined(P3) && !defined(P4)
#error Debe definir Px siendo x [0..4] el núm. de la práctica a probar
#endif

#include <ctime>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <memory>
#include <type_traits>
#include <locale>
/**
   Lamentablemente, <regex>, de la biblioteca estándar de C++11,
   no funcionaba bien en algunas versiones antiguas: muy mal en GCC C++ 4.8 y 
   algo menos, pero no bien, en GCC C++ 4.9. A partir de la versión 5 ya
   funciona bien. En cuanto a CLang, usa la misma biblioteca que GCC de
   forma predeterminada. El problema no es tanto del compilador como de
   la versión de la biblioteca estándar de C++ (en GNU/Linux, libstdc++).
*/
#if __GLIBCXX__ >= 20160301
# define CPP11REGEX 1
# include <regex>
#else
# include <regex.h>
#endif

#include "fct.h"

#include "fecha.hpp"
#include "cadena.hpp"
#if defined(P2) || defined(P3) || defined(P4)
# include "articulo.hpp"
# include "tarjeta.hpp"
# include "usuario.hpp"
#endif
#if defined(P3) || defined(P4)
# include "pedido.hpp"
# include "pedido-articulo.hpp"
# include "usuario-pedido.hpp"
#endif

/*********************** COMPROBACIONES *********************/

#define chk_incl_str(haystack, needle)                       \
  fct_xchk(strstr(haystack.c_str(), needle.c_str()) != NULL, \
           "failed chk_incl_str:\n'%s' not in '%s'",         \
           needle.c_str(), haystack.c_str())

#define chk_incl_cstr(haystack, needle)                      \
  fct_xchk(strstr(haystack.c_str(), needle) != NULL,         \
           "failed chk_incl_cstr:\n'%s' not in '%s'",        \
           (const char*)needle, haystack.c_str())

#define chk_eq_str(haystack, needle)                         \
  fct_xchk(strcmp(haystack.c_str(), needle.c_str()) == 0,    \
           "failed chk_eq_str:\n'%s' != '%s'",               \
           needle.c_str(), haystack.c_str())

#define chk_eq_cstr(haystack, needle)                        \
  fct_xchk(strcmp(haystack.c_str(), needle) == 0,            \
           "failed chk_eq_cstr:\n'%s' != '%s'",              \
	   (const char*)needle, haystack.c_str())

/************************ CLASES ****************************/
#ifndef CPP11REGEX
/**
   Clase de excepción para expresiones regulares no válidas.
*/
class BadRegex : public std::exception {
public:
  BadRegex(const char* regex) : regex_(regex) {}
  const char* regex() const { return regex_; }
private:
  const char* regex_;
};
#endif

/************************ UTILIDADES **********************/

#if !defined(P0) && !defined(P1)
/**
   Comprueba que dos números de tarjeta son iguales. El enunciado solo
   pide <, y no ==, por lo que emulamos == mediante <. Se aplica la
   siguiente equivalencia:

   a == b ssi < es orden total y !(a < b) y !(b < a)
*/
inline bool operator ==(const Numero& a, const Numero& b) 
{
  return !(a < b) && !(b < a);
}
#endif

/**
   Elimina el separador de decimales, porque da problemas con
   algunas localizaciones españolas, que incorrectamente ponen el ".". 
   También, de paso, fijamos el separador de decimales a la coma.
*/
struct sin_separador : std::numpunct<char> {
protected:
  virtual string_type do_grouping     () const { return "\000"; }
  virtual char_type   do_decimal_point() const { return ','   ; }
};

/**
   Plantilla de función de utilidad para convertir algo a cadena (string), 
   aprovechando su operador de inserción en flujo.
*/
template <typename T>
std::string toString(const T& o) 
{
  std::ostringstream os;
  os.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
  os << o;
  return os.str();
}

/**
   Convierte una cantidad a euros, con su '€' y todo.
 */
std::string toEuros(double cantidad);

#ifdef P4
/**
   Crea un conjunto de autores con un solo autor. Útil cuando solo
   podemos contar con un bloque namespace donde inicializarlo todo.
   Autor[es] solo se definen en P4.
 */
Articulo::Autores crea_autores(Autor& autor);
#endif

#ifndef CPP11REGEX
/**
   Función que busca una expresión regular dentro de una cadena y
   devuelve la posición del comienzo de la primera coincidencia. 
   Devuelve -1 cuando no encuentra ninguna. Lanza la excepción 
   BadRegex cuando la expresion regular no es válida.
*/
regoff_t find_regex(const char* regex, const char* text) noexcept(false);
#endif

#endif
