/* $Id: test-P1-consola.cpp 407 2018-03-17 20:19:10Z gerardo $
  Programa para probar (no demasiado exhaustivamente) 
  las clases Fecha y Cadena de P0 y P1.
  V. "fecha.hpp" y "cadena.hpp" para más información.
  ©2000-2012 `El Equipo C'
  ©2013 Los profesores de POO
  ©2015 Gerardo - diferencia de fechas, iteradores de Cadena
  ©2016 Gerardo - unión de pruebas de Fecha y Cadena
  ©2020 Gerardo - pragma para evitar aviso en clang++ de autoasignación
  ©2021 Gerardo - La Gran Unificación
*/

/* La macro P0 o la macro P1, según se esté en la práctica 0 o 1 
   respectivamente, debe estar definida.
   Si se define la macro FECHA o la macro CADENA, se compila solamente 
   la parte de la clase Fecha o de la clase Cadena, respectivamente.
   Si no se definen FECHA ni CADENA, se compila todo el programa.
   Si se definen ambas, el programa queda vacío y no sirve para nada. :-|
*/

#if !defined P0 && !defined P1
#error Debe definir P0 o P1 (ej.: c++ -DP0 -c ...). Vea el Makefile.
#endif
#if defined P0 && defined P1
#error Solo uno de P0 o P1 debe estar definido, no ambos.
#endif
#if defined FECHA && defined CADENA
#warning Definir FECHA y CADENA es inútil. Defina solo 1 de los 2.
#endif

#include <cstddef>		// size_t
#include <iostream>		// cin, cout, endl, <<, >>
#include <stdexcept>		// out_of_range
#ifndef CADENA
#include "fecha.hpp"		// Fecha
#endif
#ifndef FECHA
#include "cadena.hpp"		// Cadena
#endif

using namespace std;

int main()
{
#ifndef CADENA
  /******* PRUEBAS DE LA CLASE Fecha **********/
  // No podemos sobrecargarlas porque tienen la misma signatura.
  Fecha obtener_fecha_v1(void), obtener_fecha_v2(void);
  
  // Pruebas de constructores
  Fecha hoy, copia_hoy(hoy);	// Predeterminado, de copia
  Fecha mi_nacimiento(29, 12, 1958);
  Fecha mannana = ++hoy;	// pre-incremento
  Fecha ayer = --copia_hoy;	// pre-decremento

  // P0 - Operador de conversión Fecha -> const char*
  // P1 - Impresión en un flujo de salida, operador de inserción
  // Nota: Hay que hacerlo en sentencias separadas.
  
  cout << "Hoy es " << --hoy;	// Impresión, operador de inserción
  cout << "\nAyer fue " << ayer;
  cout << ", y mañana será " << mannana << '.' << endl;

  hoy += 7;			// Prueba de suma con asignación
  cout << "Dentro de una semana será: " << hoy << endl;
  hoy += 365 * 3;
  cout << "Dentro de 3 años y 1 semana será: " << hoy << endl;
  hoy -= 365 * 3 + 7;
  cout << "Volvemos a hoy: " << hoy << endl;

  // Pruebas de excepciones
  try {
    Fecha("20/1/2000");
    Fecha("31/2/2000");
  } catch(const Fecha::Invalida &e)
    {
      cerr << "EXCEPCIÓN: " << e.por_que() << endl;
    }

  cout << "Yo nací: " << mi_nacimiento;
  cout << "\nDentro de una semana será: " << hoy + 7;
  cout << "\nHoy: " << hoy;
  cout << "\nHace 2 semanas fue: " << hoy - 14

       << "\nEl día después del 28 de febrero de este año es: ";
  Fecha f(28, 2);		// prueba de constructor de 2 parámetros
  cout << ++f
       << "\nY el de después del 28 de febrero de 2000 fue: ";
  f = Fecha(28, 2, 2000);	// prueba de asignación
  cout << ++f
       << "\nTras Año Viejo viene: ";
  Fecha av(31,12);
  cout << ++av << "\nY Año Viejo es: ";
  cout << --av

  // Prueba de constructor "cadena de caracteres"
       << "\n20/1/2000 está mejor dicho como " << Fecha("20/1/2000") << endl;

  /* Pruebas de excepciones  */

  Fecha f1 = obtener_fecha_v1(), f2 = obtener_fecha_v2();
  cout << "La 1ª fecha fue: \"" << f1;
  cout << "\", y la 2ª: \"" << f2 << "\"." << endl;
#endif  // ifndef CADENA

#ifndef FECHA
/*****************************************************************************/
/*************** PRUEBAS DE LA CLASE Cadena **********************************/

  // Prueba de constructores
  Cadena s1(20, '['), s2(20, ']'),
    c1(" !Bravo "), c2("a "), c3("todos "),
    s = s1 + c1;		// prueba de concatenación
  s += c2;			// pruebas de concatenación con asignación
  s += c3;
  s += "los ";
  s += "alumnos! ";
  s += s2;
  s += "\n";
  // P0: Conversión Cadena -> const char*
  // P1: Inserción en flujo de salida
  cout << "\n" << s;
  Cadena t("Por haber hecho el esfuerzo de teclear este programa. Repito:\n");
  Cadena u;			// constructor predeterminado
  u = t + s;			// pruebas de asignación, concatenación
#ifdef __clang__
# pragma GCC diagnostic ignored "-Wself-assign-overloaded"
#endif
  u = u;
  cout << u;
  Cadena v;
  v = "Hola";			
  cout << v << endl;
  
  // Pruebas de índices
  size_t i = 87;
  cout << "El elemento " << i << " de la cadena es: " << u[i] << endl;
  u[94u] = u[54u] = 'p';
  cout << "Y tras modificar algunos caracteres, la cadena queda:\n" << u;
  try {
    cout << u.at(2000);		// Fuera de rango
  } catch(out_of_range& e) {
    cerr << "ERROR CAPTURADO. Mensaje: \"" << e.what() << "\"" << endl;
  }
  
  // Prueba de subcadena
  Cadena grande("Nihil novum sub solem"); // Nada nuevo bajo el Sol
  Cadena nuevo = grande.substr(6, 5);  // nuevo <- "novum"
  cout << "substr(6, 5) de " << grande << ": \"" << nuevo << "\"" << endl;
#ifdef P0
  if (Cadena("novum") != nuevo)
#else
  if ("novum" != nuevo)
#endif
    cerr << "*** ERROR *** Debería haber impreso \"novum\"" << endl;
  
  // Prueba de comparaciones
  cout << "Cadena a = \"novum\", b = \"Nihil novum sub solem\";\n a < b: " 
       << boolalpha << (nuevo < grande) << "\n a > b: " << (nuevo > grande)
       << "\n a <= b: " << (nuevo <= grande) << "\n a >= b: " 
       << (nuevo >= grande) << "\n a == b: " << (nuevo == grande)
       << "\n a != b: " << (nuevo != grande) << endl;
  // Prueba de longitud
  cout << "La cadena a tiene  5 caracteres: " << (nuevo.length() == 5)
       << "\nLa cadena b tiene 21 caracteres: " << (grande.length() == 21)
       << endl;
#ifdef P1
  // P1 - Pruebas de E/S
  Cadena c;
  cout << "Escribe un par de palabras, por favor: ";
  cin >> c;
  cout << "Palabra 1: " << c << endl;
  cout << "Carácter actual: '" << static_cast<char>(cin.peek())
       << "'" << endl;
  cin >> c;
  cout << "Palabra 2: " << c << endl;
  
  // P1 - Pruebas de iteradores
  c = "No te digo trigo por no llamarte Rodrigo";
  for (auto i : c)
    cout << i;
  cout << endl;
  for (Cadena::const_reverse_iterator r = c.rbegin(); r != c.rend(); ++r)
    cout << *r;
  cout << endl;
#endif // P1
#endif // ifndef FECHA
} // ~

#ifndef CADENA
// Funciones auxiliares de pruebas de excepciones de Fecha
Fecha obtener_fecha_v1()
{
  while (true)
    try {
      cout << "Introduzca una fecha en el formato DD/MM/AAAA, por favor: ";
#ifdef P0
      char linea[11];
      cin.getline(linea, 11);
      Fecha f(linea);
#else // P1
      Fecha f(12, 12, 2012);
      cin >> f;			// operador de extracción
#endif
      return f;      // Fecha correcta: salimos.
    } catch(const Fecha::Invalida& e) {
      cerr << e.por_que() 
	   << "\aInténtelo de nuevo.\n" << endl;
      cin.clear();
    } // Fin while
}

Fecha obtener_fecha_v2() // Otra alternativa. Tomamos la fecha de hoy
  try {
#ifdef P0
    cout << "Introduzca una fecha. Primero el día del mes: ";
    int d;
    cin >> d;
    cout << "Ahora el mes (numérico): ";
    int m;
    cin >> m;
    cout << "Y por último el año (4 cifras): ";
    int a;
    cin >> a;
    Fecha f(d, m, a);
#else  // P1
    cout << "Introduzca una fecha en el formato DD/MM/AAAA, por favor: ";
    Fecha f(12, 12, 2012);
    cin >> f;
#endif
    return f;
  }
  catch(const Fecha::Invalida& e) {
    cerr << e.por_que() << "Tom\aamos la fecha de «hoy»." << endl;
    cin.clear();
    return Fecha();
  }
#endif // ifndef CADENA

