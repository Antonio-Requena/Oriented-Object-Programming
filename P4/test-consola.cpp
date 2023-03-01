/* $Id: test-consola.cpp 396 2017-05-12 18:54:19Z gerardo $
 * Prueba del SGL, casos de uso 1, 2, 3 y 4 (P2, P3 y P4)
 *
 * LIBRERÍA
 * ©2009-20 los profesores de POO
 * ©2021 Gerardo - La Gran Unificación
 */

#include <iostream>
#include "fecha.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#ifndef P2
#include "cadena.hpp"
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#endif

using std::cout;
using std::cerr;
using std::endl;

#define AZUL   "\033[0m\033[01;34m"
#define VERDE  "\033[0m\033[01;32m"
#define NORMAL "\033[0m"

void numero_incorrecto(Numero::Incorrecto);

/**
   Elimina el separador de decimales, porque da problemas con
   algunas localizaciones españolas, que incorrectamente 
   (según la RAE) ponen el ".". Debe ser un espacio "fino", salvo
   para los años...
   También, de paso, fijamos el separador de decimales a la coma.
*/
struct sin_separador : std::numpunct<char> {
protected:
  virtual string_type do_grouping     () const { return "\0"; }
  virtual char_type   do_decimal_point() const { return ',' ; }
};

int main()
{
  cout.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
  
  /******** USUARIOS ************/
  // Constructor de usuario: id, nombre, apellidos, dirección, clave
  Usuario 
    lucas("lucas", "Lucas", "Grijander", 
	  "Avda. del Atún, 654 (Barbate)", "vaeg0Quo"),
    krispin("krispin", "Crispin", "Klander", 
	    "Calle del Jurel, 876 (Cerdanyola del Vallès)", "Pheaj9li"),
    yoshua("yoshua", "Yoshua", "Romegosa", 
	   "Callejón del Algarrobo, s/n (Mondragón)", "ahxo2Aht"),
    yessi("yessi", "Yesica", "Minglanilla",
	  "Calle del Almendro, 345 (Corrubedo)", "Roh9aa5v");

  /******** TARJETAS *************/
  // Constructor de Tarjeta: Numero, Usuario, fecha de caducidad
  // Para evitar problemas con las fechas y sus caducidades, ponemos año 0
  // (el actual) y sumamos uno o más años.
  Tarjeta
    visa1(Numero("4539 4512 0398 7356"), lucas, Fecha(31,12,0) + 3*365),
    american_express(Numero("378282246310005"), yoshua, Fecha(30,11,0) + 4*365),
    dinners_club(Numero("30569309025904"), yessi, Fecha(31,7) + 5*365),
    mastercard(Numero("555555555555 4444  "), krispin, Fecha(31,1) + 3*365),
    australian_bank_card(Numero("5610591081018250"), krispin, Fecha(28,2)+ 365),
    jcb(Numero("3530111333300000"), yessi, Fecha("31/7/0") + 2*365),
    visa2(Numero(" 4222222222222"), lucas, Fecha("28/2/0") + 365);

  // Pruebas de titularidad de tarjeta
  yessi.no_es_titular_de(jcb);	// Se le quita la Tarjeta jcb a Yessi.
  lucas.es_titular_de(jcb);	// No debe hacer nada.
  yessi.es_titular_de(jcb);	// Tampoco hace nada ya, solo se puede
				// asignar una Tarjeta de forma válida
				// cuando se crea.

  // Prueba de impresión de usuarios
  cout << lucas << '\n' << krispin << '\n' << yoshua << '\n' << yessi << '\n';

  // Pruebas de excepciones
  try {
    Usuario aitor("aitor", "Aitor", "Tilla de Papas", "C/ del Pez", "ok");
    // Clave corta (¿solo la clave?)
  }
  catch(Clave::Incorrecta &e) {
    switch (e.razon()) {
    case Clave::CORTA:
      cerr << "La contraseña es demasiado corta. "
	"Debe tener al menos 5 caracteres." << endl;
      break;
    case Clave::ERROR_CRYPT: // Esto no va a ocurrir
      cerr << "crypt(): ERROR." << endl;
   }
  }
  Clave c2("TeDaKuén");	  // Prueba de verificación de clave
  if (!c2.verifica("TeDaCuén")) // Deberá imprimir el mensaje de error
    cerr << "Error de verificación de clave: "
	      << "\"TeDaKuén\" != \"TeDaCuén\"." << endl;
  if (c2.verifica("TeDaKuén"))
    cerr << "OK, clave \"TeDaKuén\" verificada." << endl;
  else			// Esto no debe ocurrir, no imprimirá nada
    cerr << "Error de verificación de clave: "
	      << "\"TeDaKuén\" != \"TeDaKuén\". (\?\?\?)" << endl;
  try {		 // O938 en vez de 0938 ;-) (era una O, no un cero)
    Tarjeta falsa(Numero("4539 4512 O398 7356"), lucas, "31/12/2020");
  }
  catch(Numero::Incorrecto& e) {
    numero_incorrecto(e);
  }
  try {
    Tarjeta judas(Numero("1234567890123456"), lucas, "31/12/2020");
  }
  catch(Numero::Incorrecto& e) {
    numero_incorrecto(e);
  }
  try {
    Tarjeta mala(Numero("123"), lucas, "31/12/2021");
  }
  catch(Numero::Incorrecto& e) {
    numero_incorrecto(e);
  }
  try {
    Tarjeta caduca(Numero("4222222222222"), lucas, "30/04/2002");
  }
  catch(Tarjeta::Caducada &e) {
    cerr << "Error: Tarjeta caducada desde el " << e.cuando() << endl;
  }
  try { 			// En la fecha, O = letra O, no cero (O-0)
    Tarjeta rota(Numero(" 4222222222222 "), lucas, "1O/O4/2O2O");
  }
  catch(Fecha::Invalida &e) {
    cerr << "Error: Fecha de caducidad inválida. " << e.por_que() << endl;
  }


#ifdef P4
  /********* AUTORES ********/
  // Constructor de Autor: nombre, apellidos, dirección
  Autor 
    Esteban("Esteban", "Rey", "Portland, Maine (US)"),
    Rolling("JK", "Rolling", "Yate, Gloucestershire (UK)"),
    Humberto("Humberto", "Echo", "Alessandria, Piamonte (Italia)"),
    Goria("Goria", "Fuertes", "Madriz (Españia)");
  
  Articulo::Autores autores { &Rolling };

  /******** ARTÍCULOS ***************/
  //----------- Libros
  // Constructor de Libro: autores, referencia, título, fecha publicación,
  //                       precio, páginas, stock
  Libro enrique_alfarero(autores, "100", // autor = Rolling
     "Enrique Alfarero y el fistro de fuego", "1/8/2000", 32.50, 245, 5); 
  autores.insert(&Goria);
  Libro manualidades1(autores,	// autores = Rolling y Goria
     "110", "Mi primer libro de manualidades", "20/6/1998)", 35.95, 650, 100); 
  autores.clear();
  autores.insert(&Esteban);
  Libro salem(autores,		// autor = Esteban
     "111", "Las brujas de Salem", "17/10/1975", 42.10, 150, 300);
  autores.insert(&Humberto);
  Libro bracula(autores,	// autores = Esteban y Humberto
     "103", "Brácula, el no vivo", "1/1/1902", 39.95, 455, 4);

  //------------- Libros digitales
  // Constructor de LibroDigital: autores, referencia, título,
  //                              fecha publicación, precio, fecha expiración
  LibroDigital nombre(autores,	// autores = Esteban y Humberto
     "034", "El nombre de La Cosa", "15/1/2009", 6., "1/7/2009");
  autores.clear();
  autores.insert(&Goria);
  LibroDigital tonto(autores,	// autor = Goria
      "035", "Eres mu tonto", "20/3/2009)", 9., Fecha("20/6/00") + 365 * 4),
    pasquin(autores, "036", "55 días en Pasquín",
	    "1/10/2007", 12., "30/9/2008"); // expirado

  //-------------- Cederrones
  // Constructor de Cederron: autores, referencia, título, fecha publicación,
  //                          precio, megas, stock
  Cederron camela(autores,	// autor = Goria
      "210", "Biografía de Camela", "1/8/2000", 32.50, 245, 40);
  autores.insert(&Rolling);
  Cederron adenda(autores,	// autores = Goria y Rolling
      "211", "Adenda a las asignaturas del GII", "20/6/1998", 35.95, 650, 50);
  autores.insert(&Esteban);
  Cederron cppref(autores,	// autores = Goria, Rolling y Esteban
      "220", "Referencia de C++", "9/9/2020", 12.90, 547, 30);
#else
  // Constructor de Articulo genérico: referencia, título,
  // fecha de publicación, precio, stock
  Articulo
    enrique_alfarero("100", "Enrique Alfarero y el fistro de fuego",
		     "1/8/2000", 32.50, 5), 
    manualidades1("110", "Mi primer libro de manualidades",
		  "20/6/1998)", 35.95, 100),
    salem("111", "Las brujas de Salem", "17/10/1975", 42.10, 300),
    bracula("103", "Brácula, el no vivo", "1/1/1902", 39.95, 4),
    nombre("034", "El nombre de La Cosa", "15/1/2009", 6., 10),
    tonto("035", "Eres mu tonto", "20/3/2009)", 9., 3),
    pasquin("036", "55 días en Pasquín", "1/10/2007", 12., 55),
    camela("210", "Biografía de Camela", "1/8/2000", 32.50, 40),
    adenda("211", "Adenda a las asignaturas del GII", "20/6/1998", 35.95, 550),
    cppref("220", "Referencia de C++", "9/9/2020", 12.90, 30),
    poo("100", "Programación Orientada a Objetos", "1/8/2000", 32.50, 5),
    cpp("110", "Fundamentos de C++", "20/6/1998", 35.95, 10),
    stl("111", "The Standard Template Library", "5/10/2002", 42.10, 3),
    ada("103", "Análisis y Diseño de Algoritmos", "1/2/2001", 39.95, 2);
#endif
  cout << "\n" AZUL "---------------INVENTARIO DE EXISTENCIAS-----------\n"
    NORMAL
#ifdef P4
    "LIBROS:"
#endif
       << '\n' << enrique_alfarero << '\n' << manualidades1 << '\n' 
       << salem << '\n' << bracula << '\n'
#ifdef P4
       << "LIBROS DIGITALES:" 
#endif
       << '\n' << nombre << '\n' << tonto << '\n' << pasquin << '\n'
#ifdef P4
       << "CEDERRONES:"
#endif
       << '\n' << camela << '\n' << adenda << '\n' << cppref << endl;

  // Añadir y quitar artículos al carrito y ver el carrito
  // Comprar: Articulo, Cantidad (1 por omisión, 0 elimina el artículo)
#ifndef P2
  // Factura: Usuario_Pedido, Pedido_Articulo, Usuario, Tarjeta, Fecha [hoy]
  Usuario_Pedido usuario_ped;
  Pedido_Articulo pedido_art;
#endif
  cout << "\n\nCARRITOS VACÍOS\n\n";
  mostrar_carro(cout, lucas);
  mostrar_carro(cout, krispin);
  mostrar_carro(cout, yoshua);
  mostrar_carro(cout, yessi);
  cout << VERDE "\n*** Lucas compra 4 artículos.\n" NORMAL;
  
  lucas.compra(manualidades1, 3);
  lucas.compra(salem, 1);
  lucas.compra(nombre, 2);
  lucas.compra(adenda, 1);
  mostrar_carro(cout, lucas);
#ifndef P2
  Pedido p1(usuario_ped, pedido_art, lucas, visa1, Fecha(10, 3));
#endif
  cout << VERDE "*** Cambio de precio de \"Mi primer libro de manualidades\", "
    "\"Las brujas de Salem\", \"El nombre de la Cosa\" y"
    " \"Biografía de Camela\".\n\n" NORMAL;
  manualidades1.precio() = 29.95;	// cambiar precios
  salem.precio() = 44.50; 
  nombre.precio() = 5.50;
  camela.precio() = 24.05;

  cout << VERDE "*** Krispín compra 2 artículos.\n" NORMAL;
  krispin.compra(manualidades1, 2);
  krispin.compra(salem, 2);
  mostrar_carro(cout, krispin);
  cout << VERDE "\n*** Krispín devuelve \"Las brujas de Salem\" y compra"
    " \"Enrique Alfarero y el fistro de fuego\" y \"Referencia de C++\".\n"
    NORMAL;
  krispin.compra(salem, 0); // quita salem del carrito
  krispin.compra(enrique_alfarero);    // un ejemplar
  krispin.compra(cppref);
  mostrar_carro(cout, krispin);
  cout << VERDE "\n*** No se comprueban existencias\n"
    "*** existencias de \"Brácula, el no vivo\" = " << bracula.stock()
       << NORMAL << endl;
  yoshua.compra(bracula, 6);	// no se comprueban las existencias
#ifdef P4
  cout << VERDE "\n*** No se comprueba la fecha de expiración\n"
    "*** fecha expir. \"55 días en Pasquín\" = " << pasquin.f_expir()
       << NORMAL "\n\n";
#endif
  yoshua.compra(pasquin, 2); // no se comprueba la fecha de expiración
  mostrar_carro(cout, yoshua);
  cout << VERDE "\n*** Yoshua devuelve 4 ejemplares de \"Brácula\"\n" NORMAL;
  yoshua.compra(bracula, 2);	// quita 4 del carrito
  mostrar_carro(cout, yoshua);
#ifndef P2
  Pedido p2(usuario_ped, pedido_art, yoshua, american_express, 
	    --Fecha());	// pedido ayer
  Pedido p3(usuario_ped, pedido_art, krispin, mastercard, "5/4/2010");
#endif
  cout << VERDE "*** Cambio de precios de "
    "\"Enrique Alfarero y el fistro de fuego\","
    " \"Brácula el no vivo\" y \"Eres mu tonto\"\n\n" NORMAL;
  enrique_alfarero.precio() = 35.20;	// cambiar precios
  bracula.precio() = 34.9; 
  tonto.precio() -= 6.; // 6 € menos

  cout << VERDE "*** Yessi compra 3 artículos.\n" NORMAL;
  yessi.compra(cppref, 2);
  yessi.compra(tonto, 3);
  yessi.compra(salem);
  yessi.compra(adenda, 0); // no hace nada, adenda no está en el carro
  mostrar_carro(cout, yessi);
#ifndef P2
  try {
    Pedido p4(usuario_ped, pedido_art, yessi, jcb, "5/4/2010");
  }
  catch(Pedido::Impostor) {
    cout << "Yessi ha intentado pagar con una tarjeta que ya no tiene." << endl;
  }
  Pedido p4(usuario_ped, pedido_art, yessi, dinners_club, "5/4/2010");  
  cout << AZUL "\n---------------------PEDIDOS-----------------------\n"
    NORMAL << p1 << endl << p2 << endl << p3 << endl << p4;
#endif
  cout << VERDE "\nSe reciben más cantidades de los artículos existentes.\n\n"
    NORMAL;
  // Recepción de mercancías
  enrique_alfarero.stock() += 5; 
  manualidades1.stock() *= 4; 
  salem.stock() += 2; 
  bracula.stock() += 2;
#ifndef P2
  cout << VERDE "*** Yessi compra 2 libros más";
  yessi.compra(salem);
  yessi.compra(bracula);
  cout <<  " y hace un pedido.\n" NORMAL;
  Pedido p5(usuario_ped, pedido_art, yessi, dinners_club); // pedido hoy

  cout << VERDE "*** Yessi compra 3 ejemplares de "
    "\"Mi primerer libro de manualidades\""; 
  yessi.compra(manualidades1, 3);
  cout << " y hace otro pedido.\n" NORMAL;
  Pedido p6(usuario_ped, pedido_art, yessi, dinners_club); // pedido hoy
  cout << VERDE "*** Krispín compra 3 artículos";
  krispin.compra(bracula); 
  krispin.compra(salem); 
  krispin.compra(enrique_alfarero, 3);
  cout << " y hace su pedido.\n" NORMAL;
  Pedido p7(usuario_ped, pedido_art, krispin, australian_bank_card, "5/4/2010");
  cout << VERDE "*** Yoshua compra 2 artículos";
  yoshua.compra(enrique_alfarero, 2); 
  yoshua.compra(manualidades1);
  cout << " y hace su pedido.\n" NORMAL;
  Pedido p8(usuario_ped, pedido_art, yoshua, american_express, "5/4/2010");
  
  cout << p5 << endl << p6 << endl << p7 << endl << p8 << endl
    
       << "\n" AZUL "-------------------DETALLE DE PEDIDOS--------------"
    NORMAL "\n";
  pedido_art.mostrarDetallePedidos(cout);
  cout << "\n" AZUL "------------------VENTAS DE ARTÍCULOS--------------"
    NORMAL "\n";
  pedido_art.mostrarVentasArticulos(cout);
  
  cerr << "\n" AZUL "---------PRUEBAS DE EXCEPCIONES DE PEDIDOS---------"
    NORMAL "\n";
  try {
    Pedido nulo(usuario_ped, pedido_art, lucas, visa2);
  }
  catch(Pedido::Vacio& e) {
    cerr << "Error de pedido: el carrito de " << e.usuario().id() 
	      << " está vacío. " << endl;
  }
  try {
    krispin.compra(manualidades1);
    Pedido farsante(usuario_ped, pedido_art, krispin, visa2);
  }
  catch(Pedido::Impostor& e) {
    cerr << "Error de pedido: la tarjeta de pago no es de " 
	      << e.usuario().id() << endl;
  }
  try {
    yessi.compra(enrique_alfarero, 2); 
    yessi.compra(salem, 4); 
    yessi.compra(bracula, 5);
    Pedido no_disponible(usuario_ped, pedido_art, yessi, dinners_club);
  }
  catch(Pedido::SinStock& e) {
    cerr << "Error de pedido: no hay existencias del artículo [" 
	      << e.articulo().referencia() << "]" << endl;
  }
  try {
    // Creamos una tarjeta que caducó ayer. ¿Qué pasa? ¡No somos un
    // maldito banco, esto es una prueba!
    Tarjeta caduca(Numero("4222222222222"), lucas, Fecha() - 1); 
    lucas.compra(enrique_alfarero, 2);
    Pedido no_pagado(usuario_ped, pedido_art, lucas, caduca); // pedido hoy
  }
  catch(Tarjeta::Caducada& e) {
    cerr << "Error de pedido: tarjeta caducada el " << e.cuando()
	      << endl;
  }
#endif // P3 o P4
#ifdef P4
  try {
    Articulo::Autores a;
    Libro anonimo(a, "133", "El Necronomicón", 
		  "10/3/2009", 35.00, 210, 4);
  }
  catch(Articulo::Autores_vacios) {
    cerr << "Error de artículo: No se puede crear uno anónimo.\n";
  }
#endif
#ifndef P2
  // Por último: impresión del número total de pedidos.
  cout << "\nNúmero total de pedidos: " 
       << Pedido::n_total_pedidos() << '\n' << endl;
#endif
}

// Función llamada desde los catch(Numero::Incorrecto) que comprueba
// la razón y muestra un mensaje apropiado.
void numero_incorrecto(Numero::Incorrecto e)
{
  cerr << "Error: El número de la tarjeta ";
  switch (e.razon()) {
  case Numero::DIGITOS:
    cerr << "tiene caracteres no numéricos ni blancos" << endl;
    break;
  case Numero::NO_VALIDO:
    cerr << "no es válido, error de CRC." << endl;
    break;
  case Numero::LONGITUD:
    cerr << "es de una longitud incorrecta." << endl;
    break;
  default:
    cerr << "tiene un error desconocido." << endl;
  }
}
