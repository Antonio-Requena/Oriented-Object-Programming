/* $Id: test-caso1-2-auto.cpp 347 2016-05-06 19:20:38Z gerardo $
 * Pruebas unitarias automáticas para los casos de uso 1 y 2 del S. G. L.: P2
 * ©2014 Antonio G.ª Dguez.
 * ©2015-16 el resto de profesores de POO
 */

#include "test-auto.hpp"

using namespace std;

// Variables para el siguiente conjunto de casos de prueba. ¡No tocar!
namespace {
  const Cadena referencia("1234XYZ");
  const Cadena titulo("Prueba");
  const Fecha  fecha(10, 10, 2000);
  const Cadena sId("pperez");
  const Cadena sNombre("Perico");
  const Cadena sApellidos("Perez Palotes");
  const Cadena sDireccion("13 Rue del Percebe");
  const Clave  clave("pedrofueacomprarpan");
  const Numero nTarjeta("4164 2959 2196 7832");
  const Numero nTarjeta2("3138799837441258");
  const Numero nTarjeta3("5544313153232185");
  const Fecha  fHoy;
  const Fecha  fUnaSemana = fHoy + 7;
  const Fecha  fSiguienteAnno(1, 1, fHoy.anno() + 1);

#ifdef P4
  Autor autor("Harry", "Potter", "Hogwarts");
  Articulo::Autores autores = crea_autores(autor);

  Libro articulo1(autores, "111", "The Standard Template Library",
                  fHoy, 42.10, 200, 50);
  Cederron articulo2(autores, "110", "Fundamentos de C++",
                     fHoy, 35.95, 100, 50);
#else
  Articulo articulo1("111", "The Standard Template Library", fHoy, 42.10, 200),
    articulo2("110", "Fundamentos de C++", fHoy, 35.95, 100);
#endif
  Usuario* pU { nullptr };

  using TIPO = Tarjeta::Tipo;

  bool bPrimera = true;
}

FCTMF_FIXTURE_SUITE_BGN(test_p2) {

  if (bPrimera) {
    bPrimera = false;
    cerr << "\n---------- PRÁCTICA 2 ----------\n" << endl;
  }

  FCT_SETUP_BGN() {
    pU = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    if (pU) {
      delete pU;
      pU = nullptr;
    }
  }
  FCT_TEARDOWN_END();

  // --- Pruebas de la clase Clave

  FCT_TEST_BGN(Clave - Ctor.: demasiado corta) {
    try {
      Clave c("");
      fct_chk(!"Se esperaba una excepción Clave::Incorrecta(CORTA)");
    } catch (const Clave::Incorrecta& ex) {
      fct_chk_eq_int(ex.razon(), Clave::CORTA);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Clave - observador y cifrado DES) {
    const Clave c("!.:xA?");
    fct_chk_neq_str(c.clave().c_str(), "!.:xA?");
    fct_chk_eq_int(c.clave().length(), 13);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Clave - copia y observador y sal aleatoria) {
    // La copia da 2 exactamente iguales, obviamente
    const Clave c("Sherlock"), d(c), e("Sherlock");
    fct_chk_eq_str(c.clave().c_str(), d.clave().c_str());
    // Las 2 contraseñas iguales cifradas deberían ser distintas. La
    // probabilidad de que sean iguales es MUY pequeña.
    fct_chk_neq_str(c.clave().c_str(), e.clave().c_str());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Clave - verificacion: coincide) {
    const Clave c("buenas");
    fct_chk(c.verifica("buenas"));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Clave - verificacion: no coincide) {
    const Clave c("password");
    fct_chk(!c.verifica("eres mu tonto"));
  }
  FCT_TEST_END();

  // --- Pruebas de la clase Numero

  FCT_TEST_BGN(Numero - validacion: muy corto) {
    try {
      Numero n("");
      fct_chk(!"Se esperaba una excepción Numero::Incorrecto(LONGITUD)");
    } catch (const Numero::Incorrecto& ex) {
      fct_chk_eq_int(ex.razon(), Numero::LONGITUD);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Numero - validacion: muy largo) {
    try {
      Numero n("01234567890123456789");
      fct_chk(!"Se esperaba una excepción Numero::Incorrecto(LONGIUD)");
    } catch (const Numero::Incorrecto& ex) {
      fct_chk_eq_int(ex.razon(), Numero::LONGITUD);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Numero - validacion: con caracteres no numericos) {
    try {
      Numero n("0123456789abcd");
      fct_chk(!"Se esperaba una excepción Numero::Incorrecto(DIGITOS)");
    } catch (const Numero::Incorrecto& ex) {
      fct_chk_eq_int(ex.razon(), Numero::DIGITOS);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Numero - validacion: todo espacios) {
    try {
      Numero n(" \t\v  \n \f ");
      fct_chk(!"Se esperaba una excepción Numero::Incorrecto(LONGITUD)");
    } catch (const Numero::Incorrecto& ex) {
      fct_chk_eq_int(ex.razon(), Numero::LONGITUD);
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Numero - validacion: cifra de comprobacion no valida) {
    try {
      // La cifra de comprobación correcta es 8, no 2
      Numero n("01234 56789 012 2");
      fct_chk(!"Se esperaba una excepción Numero::Incorrecto(NO_VALIDO");
    } catch (const Numero::Incorrecto& ex) {
      fct_chk_eq_int(ex.razon(), Numero::NO_VALIDO);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Numero - conversion implicita a cadena) {
    const Numero n("01234 56789 012   8");
    fct_chk(strcmp(n, "01234567890128") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Numero - operador menor que: solo cambios en espacios) {
    const Numero n1("01234\v5\r6 789\t012\f8"), n2("01234567890128");
    fct_chk(!(n1 < n2));
    fct_chk(!(n2 < n1));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Numero - operador menor que: numeros distintos) {
    const Numero n1("01234 56789 012 8"), n2("11234567890126");
    fct_chk(n1 < n2);
    fct_chk(!(n2 < n1));
  }
  FCT_TEST_END();

  // --- Pruebas de la clase Usuario

  FCT_TEST_BGN(Usuario - no es copiable) {
    fct_chk(!is_copy_constructible<Usuario>::value);
    fct_chk(!is_copy_assignable   <Usuario>::value);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario - observadores) {
    const Usuario& rU = *pU;
    fct_chk(rU.id       () == sId                );
    fct_chk(rU.nombre   () == sNombre            );
    fct_chk(rU.apellidos() == sApellidos         );
    fct_chk(rU.direccion() == sDireccion         );
    fct_chk(rU.tarjetas () == Usuario::Tarjetas());
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Usuario - Articulos es unordered_map) {
    fct_chk(pU->compra().bucket_count());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario - identificador repetido) {
    try {
      Usuario u(sId,
                "otro nombre", "otros apellidos", "otra dirección",
                Clave("otraclave"));
      fct_chk(!"Se esperaba una excepción Usuario::Id_duplicado");
    } catch (const Usuario::Id_duplicado& ex) {
      fct_chk(ex.idd() == sId);
    }
  }
  FCT_TEST_END();

  // --- Pruebas de la clase Tarjeta

  FCT_TEST_BGN(Tarjeta - no es copiable) {
    fct_chk(!is_copy_constructible<Tarjeta>::value);
    fct_chk(!is_copy_assignable   <Tarjeta>::value);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Tarjeta - caducada) {
    const Fecha ayer { fHoy - 1 };
    try {
      Tarjeta tarjeta(nTarjeta, *pU, ayer);
      fct_chk(!"Se esperaba una excepción Tarjeta::Caducada");
    } catch (const Tarjeta::Caducada& ex) {
      fct_chk(ex.cuando() == ayer);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Tarjeta - desactivada) {
    Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    bool a = tarjeta.activa(false);
    fct_chk(!a);
    fct_chk_ex(Tarjeta::Desactivada, if (!a) throw Tarjeta::Desactivada());
    a = tarjeta.activa();
    fct_chk(a);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Tarjeta - duplicada) {
    Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    try {
      Tarjeta tarjeta2(nTarjeta, *pU, fSiguienteAnno);
    } catch(const Tarjeta::Num_duplicado& ex) {
      fct_chk(ex.que() == nTarjeta);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Tarjeta - observadores) {
    const Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    fct_chk(tarjeta.tipo     () == Tarjeta::Tipo::VISA );
    fct_chk(tarjeta.numero   () == nTarjeta             );
    fct_chk(tarjeta.caducidad() == fUnaSemana           );
    fct_chk(tarjeta.titular  () == pU                   );
    fct_chk(tarjeta.activa   () == true                 );
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Tarjeta - comparacion) {
    const Tarjeta tarjeta1(nTarjeta, *pU, fUnaSemana),
      tarjeta2(nTarjeta2, *pU, fUnaSemana),
      tarjeta3(nTarjeta3, *pU, fUnaSemana);
    fct_chk(!(tarjeta1 < tarjeta2));
    fct_chk(  tarjeta2 < tarjeta1 );
    fct_chk(  tarjeta1 < tarjeta3 );
    fct_chk(!(tarjeta3 < tarjeta1));
    fct_chk(  tarjeta2 < tarjeta3 );
    fct_chk(!(tarjeta3 < tarjeta2));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Tarjeta - insercion en flujo) {
    const Tarjeta tarjeta(nTarjeta, *pU, fSiguienteAnno);
    const string sTarjeta = toString(tarjeta);
    chk_incl_cstr(sTarjeta, "VISA");
    chk_incl_cstr(sTarjeta, nTarjeta);
    chk_incl_cstr(sTarjeta, "PERICO PEREZ PALOTES");
    chk_incl_cstr(sTarjeta, "Caduca:");

    // Equivalente en C++ a printf("%02d/%02d", mes, anno%100);
    ostringstream os;
    os << setfill('0') << setw(2) << tarjeta.caducidad().mes()
       << '/' << setw(2) << (tarjeta.caducidad().anno() % 100);
    const string sFecha = os.str();
    chk_incl_str(sTarjeta, sFecha);
  }
  FCT_TEST_END();

  // --- Pruebas de la asociación Usuario—Tarjeta

  FCT_TEST_BGN(Usuario---Tarjeta - usuario roba tarjeta) {
    Usuario caco {"caco", "John", "Koone", "5.ª avda., NYC",
	Clave("KorreEnCu3r05")};
    Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    caco.es_titular_de(tarjeta); // No. La tarjeta es robada.
    fct_chk(caco.tarjetas().empty());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Tarjeta - usuario no puede tener tarjeta anulada) {
    Usuario u2 {"otroId", "John", "Koone", "5.ª avda., NYC",
	Clave("CierraBares")};
    Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    pU->no_es_titular_de(tarjeta);
    u2.es_titular_de(tarjeta); // No hace nada
    fct_chk(u2. tarjetas().empty());
    fct_chk(pU->tarjetas().empty());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Tarjeta - destruccion de Tarjeta) {
    const Usuario::Tarjetas& tarjetas = pU->tarjetas();
    {
      const Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
      if(tarjetas.size() == 1)
	fct_chk(tarjetas.begin()->second->numero() == tarjeta.numero());
      else
	fct_chk(!"Debería haber 1 tarjeta");
    } // ~Tarjeta::tarjeta();
    fct_chk(tarjetas.empty());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Tarjeta - destruccion de Usuario) {
    const Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    delete pU;
    pU = nullptr;
    fct_chk(!tarjeta.titular());
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Usuario---Tarjeta - insercion en flujo) {
    const Tarjeta tarjeta(nTarjeta, *pU, fUnaSemana);
    const string s = toString(*pU);
    chk_incl_str(s, sId);
    chk_incl_str(s, clave.clave());
    chk_incl_str(s, sNombre);
    chk_incl_str(s, sApellidos);
    chk_incl_str(s, sDireccion);
    chk_incl_cstr(s, "Tarjetas:");
    chk_incl_cstr(s, nTarjeta);
  }
  FCT_TEST_END();

  // Pruebas del carrito de la compra (asociación Usuario—Articulo)

  FCT_TEST_BGN(Usuario---Articulo - meter en el carrito) {
    fct_chk_eq_int(pU->n_articulos(), 0);
    fct_chk(pU->compra().empty());
    pU->compra(articulo1, 3);
    fct_chk_eq_int(pU->n_articulos(), 1);
    fct_chk(pU->compra().begin()->first->referencia()==articulo1.referencia());
    fct_chk_eq_int(pU->compra().begin()->second, 3);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Usuario---Articulo - meter varias veces) {
    pU->compra(articulo1, 1);
    pU->compra(articulo1, 3);
    fct_chk_eq_int(pU->n_articulos(), 1);
    fct_chk_eq_int(pU->compra().find(&articulo1)->second, 3);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Articulo - meter varios articulos) {
    pU->compra(articulo1, 01);
    pU->compra(articulo2, 10);
    fct_chk_eq_int(pU->n_articulos(), 2);
    fct_chk_eq_int(pU->compra().find(&articulo1)->second, 01);
    fct_chk_eq_int(pU->compra().find(&articulo2)->second, 10);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Articulo - comprar y devolver) {
    pU->compra(articulo1, 5);
    pU->compra(articulo2, 7);
    pU->compra(articulo1, 0);
    fct_chk_eq_int(pU->n_articulos(), 1);
    fct_chk(pU->compra().begin()->first->referencia()==articulo2.referencia());
    fct_chk_eq_int(pU->compra().find(&articulo2)->second, 7);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Usuario---Articulo - mostrar_carro) {
    pU->compra(articulo1);
    pU->compra(articulo2, 3);

    ostringstream os;
    os.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
    mostrar_carro(os, *pU);
    string sCarro = os.str();
    chk_incl_str(sCarro, sId);
    chk_incl_cstr(sCarro, "Artículos: 2");

    os.str("");
    os << "[111] \"The Standard Template Library\", "
       << articulo1.f_publi().anno()
       << ". 42,10 €";
    chk_incl_str(sCarro, os.str());

    os.str("");
    os << "[110] \"Fundamentos de C++\", "
       << articulo2.f_publi().anno()
       << ". 35,95 €";
    chk_incl_str(sCarro, os.str());
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END()
