/* $Id: test-caso3-auto.cpp 344 2016-04-29 20:20:13Z gerardo $
 * ©2014 Antonio G.ª Dguez.
 * ©2015-19 el resto de profesores de POO
 *
 */

#include "test-auto.hpp"

using namespace std;

namespace {
  const Cadena referencia("1234XYZ");
  const Cadena titulo("Prueba");
  const Fecha  fecha(10, 10, 2000);
  const Cadena sId("pperez");
  const Cadena sNombre("Perico");
  const Cadena sApellidos("Perez Palotes");
  const Cadena sDireccion("13 Rue del Percebe");
  const Clave  clave("pedrofueacomprarpan");
  const Numero nTarjeta("01234 56789 012 8");
  const Numero nTarjeta2("01234567890128");
  const Numero nTarjeta3("11234567890126");
  const Fecha  fHoy;
  const Fecha  fUnaSemana = fHoy + 7;
  const Fecha  fSiguienteAnno(1, 1, fHoy.anno() + 1);
#ifdef P4
  Autor autor("Harry", "Potter", "Hogwarts");
  Articulo::Autores autores { &autor };
  Libro articulo1(autores, "111", "The Standard Template Library",
		  fHoy, 42.10, 200, 50);
  Cederron articulo2(autores, "110", "Fundamentos de C++",
		     fHoy, 35.95, 100, 50);
#else
  Articulo articulo1("111", "The Standard Template Library", fHoy, 42.10, 50),
    articulo2("110", "Fundamentos de C++", fHoy, 35.95, 50);
#endif
  Usuario* pU { nullptr };
    
  Usuario_Pedido  *pAsocUsuarioPedido;
  Pedido_Articulo *pAsocPedidoArticulo;
  Usuario         *pU2;
  Tarjeta         *pTarjetaU;
  const Tarjeta   *pTarjetaU2;
  const Fecha     fAyer = fHoy - 1;
  
  const Pedido  *pPed1, *pPed2;
  const unsigned cantidad_A1_P1 = 1;
  const unsigned cantidad_A1_P2 = 3;
  const unsigned cantidad_A2_P2 = 5;
  
  bool bPrimera = true;

  using TIPO = Tarjeta::Tipo;
}

FCTMF_FIXTURE_SUITE_BGN(test_p3_clases) {

  if (bPrimera) {
    bPrimera = false;
    cerr << "\n---------- PRÁCTICA 3 ----------\n" << endl;
  }

  // --- Pruebas de la clase LineaPedido

  FCT_TEST_BGN(LineaPedido - valor por defecto en 2do. parametro constructor) {
    const double pVenta  {  10.5  };
    const LineaPedido lp { pVenta /* , 1u */};
    fct_chk_eq_dbl(lp.precio_venta(), pVenta);
    fct_chk_eq_int(lp.cantidad    (),      1);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(LineaPedido - constructor de 2 parametros) {
    const double      pVenta   { 7.3 };
    const unsigned    cantidad { 5   };
    const LineaPedido lp       { pVenta, cantidad };
    fct_chk_eq_dbl(lp.precio_venta(), pVenta  );
    fct_chk_eq_int(lp.cantidad()    , cantidad);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(LineaPedido - insercion en flujo) {
    const LineaPedido lp { 9.2, 42 };
    chk_incl_cstr(toString(lp), "9,20 €");
    chk_incl_cstr(toString(lp), "42");
  }
  FCT_TEST_END();

  // El éxito de las pruebas depende de su orden. ¡No reordenar!
  FCT_SETUP_BGN() {
    pAsocUsuarioPedido  = new Usuario_Pedido ;
    pAsocPedidoArticulo = new Pedido_Articulo;
    pU  = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
    pU2 = new Usuario("u2", "Mario", "Segali", "Mundo 1-1", "jumpman");
    pTarjetaU  = new Tarjeta(nTarjeta , *pU , fUnaSemana);
    pTarjetaU2 = new Tarjeta(nTarjeta3, *pU2, fUnaSemana);
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pTarjetaU2;
    delete pTarjetaU;
    delete pU2;
    delete pU;
    delete pAsocPedidoArticulo;
    delete pAsocUsuarioPedido;
  }
  FCT_TEARDOWN_END();

  // --- Pruebas de Pedido

  FCT_TEST_BGN(Pedido - carrito vacio) {
    try {
      Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy };
      fct_chk(!"Se esperaba una excepción Pedido::Vacio");
    }
    catch(const Pedido::Vacio& ex) {
      fct_chk(&ex.usuario() == pU);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido - impostor) {
    pU2->compra(articulo1, 3);
    try {
      Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU2, *pTarjetaU, fHoy };
      fct_chk(!"Se esperaba una excepción Pedido::Impostor");
    }
    catch(const Pedido::Impostor& ex) {
      fct_chk(&ex.usuario() == pU2);
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - sin stock) {
    pU->compra(articulo1, 9001);
    try {
      Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy };
      fct_chk(!"Se esperaba una excepción Pedido::SinStock");
    }
    catch (const Pedido::SinStock& ex) {
      fct_chk(&ex.articulo() == &articulo1);
      fct_chk(pU->compra().empty());
    }
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - tarjeta caducada) {
    pU->compra(articulo1, 4649);
    try {
      Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy + 30 };
      fct_chk(!"Se esperaba una excepción Tarjeta::Caducada");
    }
    catch (const Tarjeta::Caducada& ex) {
      fct_chk(ex.cuando() == fUnaSemana);
    }
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido - tarjeta desactivada) {
    pU->compra(articulo1, 4649);
    pTarjetaU->activa(false);
    fct_chk_ex(Tarjeta::Desactivada,
	       Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo,
		      *pU, *pTarjetaU, fHoy));
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - actualizacion relacionados y asociaciones) {
    const unsigned int cantidad { 1u };
    pU->compra(articulo1, cantidad);
    pU->compra(articulo2, cantidad);
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy } 
    };
    
    // Actualización de carrito y stock
    fct_chk(pU->compra().empty());
    fct_chk_eq_int(articulo1.stock(), 49);
    fct_chk_eq_int(articulo2.stock(), 49);
    
    // Asociación Usuario-Pedido
    fct_chk(pAsocUsuarioPedido->cliente(*const_cast<Pedido*>(pPed.get()))
	    == pU);
    if (pAsocUsuarioPedido->pedidos(*pU).size() == 1) {
      fct_chk(*pAsocUsuarioPedido->pedidos(*pU).begin() == pPed.get());
    }
    else
      fct_chk(!"Debería asociarse al usuario con el pedido");
    
    // Asociación Artículo-Pedido
    const Pedido_Articulo::ItemsPedido itPed {
      pAsocPedidoArticulo->detalle(* const_cast<Pedido*>(pPed.get())) 
	};
    if (itPed.size() == 2) {
      // Los artículos deben ir ordenados por código de referencia
      auto it = itPed.cbegin();
      fct_chk_eq_int(it->second.cantidad(), cantidad);
      fct_chk_eq_dbl(it->second.precio_venta(), articulo2.precio());
      ++it;
      fct_chk_eq_int(it->second.cantidad(), cantidad);
      fct_chk_eq_dbl(it->second.precio_venta(), articulo1.precio());
    }
    else
      fct_chk(!"El pedido debería tener dos artículos");
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - observadores) {
    pU->compra(articulo1, 1);
    pU->compra(articulo2, 1);
    const double totalEsperado { articulo1.precio() + articulo2.precio() };
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU }
    };
    fct_chk_eq_int(pPed->numero(), 2);
    fct_chk(pPed->tarjeta() == pTarjetaU);
    fct_chk(pPed->fecha() == fHoy);
    fct_chk_eq_dbl(pPed->total(), totalEsperado);
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido - insercion en flujo) {
    pU->compra(articulo1, 1);
    pU->compra(articulo2, 1);
    const double totalEsperado { articulo1.precio() + articulo2.precio() };
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU }
    };
    const string sPed { toString(*pPed) };
    chk_incl_cstr(sPed, "Núm. pedido:");
    chk_incl_cstr(sPed, "Fecha:"      );
    chk_incl_cstr(sPed, "Pagado con:" );
    chk_incl_cstr(sPed, "Tipo indeterminado" );
    chk_incl_cstr(sPed, "Importe:"    );
    chk_incl_str (sPed, toString(pPed->numero()));
    chk_incl_cstr(sPed, pPed->fecha().cadena()  );
    chk_incl_cstr(sPed, pTarjetaU->numero()     );
    chk_incl_str (sPed, toEuros(totalEsperado)  );
  }
  FCT_TEST_END();
  
  // Pruebas de la clase de asociación Pedido_Articulo

  FCT_TEST_BGN(Articulo---Pedido - detalle de un pedido) {
    pU->compra(articulo1, 1);
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy }
    };
    const Pedido_Articulo::ItemsPedido detalle {
      pAsocPedidoArticulo->detalle(*const_cast<Pedido*>(pPed.get()))
	};
    if (detalle.size() == 1) {
      const auto& it = detalle.cbegin();
      const LineaPedido& lp { detalle.cbegin()->second };
      fct_chk(it->first == &articulo1);
      fct_chk_eq_dbl(lp.precio_venta(), articulo1.precio());
      fct_chk_eq_int(lp.cantidad(), 1);
    }
    else
      fct_chk(!"El pedido debería tener un solo elemento");
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Articulo---Pedido - insercion en flujo de ItemsPedido) {
    const unsigned int cantidad { 1u };
    pU->compra(articulo1, cantidad);
    const unique_ptr<const Pedido> pPed {
      new Pedido { *pAsocUsuarioPedido, *pAsocPedidoArticulo,
	  *pU, *pTarjetaU, fHoy }
    };
    const Pedido_Articulo::ItemsPedido detalle {
      pAsocPedidoArticulo->detalle(*const_cast<Pedido*>(pPed.get()))
	};
    const string sDetalle { toString(detalle) };
    chk_incl_str(sDetalle, toString(pPed->total()));
    chk_incl_str(sDetalle, toString(cantidad));
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END()

FCTMF_FIXTURE_SUITE_BGN(test_p3_informes) {

  /// Batería de pruebas para los informes. Simula dos ventas de dos usuarios.  
  FCT_SETUP_BGN() {
    pAsocUsuarioPedido  = new Usuario_Pedido ;
    pAsocPedidoArticulo = new Pedido_Articulo;
    pU  = new Usuario(sId, sNombre, sApellidos, sDireccion, clave);
    pU2 = new Usuario("u2", "Mario", "Segali", "Mundo 1-1", "jumpman");
    pTarjetaU  = new Tarjeta(nTarjeta, *pU, fUnaSemana);
    pTarjetaU2 = new Tarjeta(nTarjeta3,*pU2,fUnaSemana);

    // Primera venta
    pU->compra(articulo1, cantidad_A1_P1);
    pPed1 = new Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo, 
		       *pU, *pTarjetaU, fHoy);

    // Segunda venta, de otro usuario
    pU2->compra(articulo1, cantidad_A1_P2);
    pU2->compra(articulo2, cantidad_A2_P2);
    pPed2 = new Pedido(*pAsocUsuarioPedido, *pAsocPedidoArticulo,
                       *pU2, *pTarjetaU2, fHoy);
  };
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pPed2;
    delete pPed1;
    delete pTarjetaU2;
    delete pTarjetaU;
    delete pU2;
    delete pU;
    delete pAsocPedidoArticulo;
    delete pAsocUsuarioPedido;
  }
  FCT_TEARDOWN_END();

  FCT_TEST_BGN(Articulo---Pedido - ventas de un articulo vendido) {
    const auto& pedArticulo1 = pAsocPedidoArticulo->ventas(articulo1);
    if (pedArticulo1.size() == 2) {
      auto it = pedArticulo1.find(const_cast<Pedido*>(pPed1));
      fct_chk_eq_dbl(it->second.precio_venta(), articulo1.precio());
      fct_chk_eq_int(it->second.cantidad(), cantidad_A1_P1);
      ++it;
      fct_chk_eq_dbl(it->second.precio_venta(), articulo1.precio());
      fct_chk_eq_int(it->second.cantidad(), cantidad_A1_P2);
    }
    else
      fct_chk(!"El artículo 1 debería tener 2 ventas");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Articulo---Pedido - ventas de un articulo no comprado) {
#ifdef P4
    Autor Hitler("Adolf", "Hitler", "Berlin");
    Articulo::Autores a { &Hitler };
    Libro MeinKampf(a, "666", "Mein Kampf", fHoy, 55.55, 555);
#else
    Articulo MeinKampf { "666", "Mein Kampf", fHoy, 55.55, 555 };
#endif
    const auto& pedArticulo3 = pAsocPedidoArticulo->ventas(MeinKampf);
    fct_chk(pedArticulo3.empty());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Articulo---Pedido - insercion en flujo de Pedidos) {
    const auto& pedArticulo1 = pAsocPedidoArticulo->ventas(articulo1);
    const string sPedidos { toString(pedArticulo1) };
    
    chk_incl_str(sPedidos,  toString(articulo1.precio()));
    chk_incl_str(sPedidos,  toString(cantidad_A1_P1));
    chk_incl_cstr(sPedidos, pPed1->fecha().cadena());
    chk_incl_str(sPedidos,  toString(cantidad_A1_P2));
    chk_incl_cstr(sPedidos, pPed2->fecha().cadena());
    
    const double totalEsperado =
      (cantidad_A1_P1 + cantidad_A1_P2) * articulo1.precio();
    chk_incl_str(sPedidos, toEuros(totalEsperado));
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Articulo---Pedido - mostrar detalle pedidos) {
    ostringstream os;
    pAsocPedidoArticulo->mostrarDetallePedidos(os);
    const string sDetalle { os.str() };
    
    const double totalEsperado =
      (cantidad_A1_P1 + cantidad_A1_P2) * articulo1.precio()
      + cantidad_A2_P2 * articulo2.precio();
    chk_incl_str(sDetalle, toEuros(totalEsperado));
    chk_incl_str(sDetalle, articulo1.titulo());
    chk_incl_str(sDetalle, articulo2.titulo());
    chk_incl_str(sDetalle, toString(cantidad_A1_P1));
    chk_incl_str(sDetalle, toString(cantidad_A1_P2));
    chk_incl_str(sDetalle, toString(cantidad_A2_P2));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Articulo---Pedido - mostrar ventas agrupadas) {
    ostringstream os;
    pAsocPedidoArticulo->mostrarVentasArticulos(os);
    const string sDetalle { os.str() };
    /*
      Construimos expresiones regulares que buscan las cantidades
      como palabras separadas del resto por espacios. Es decir, si
      la cantidad es 1, ' 1' a final de línea, '1 ' a principio de
      línea, o ' 1 ' valen, pero no '123', por ejemplo.
    */
    const string sRegexPrefijo { "€[[:space:]]+"   }; // "(€[[:space:]]|^)";  
    const string sRegexSufijo  { "([[:space:]]|$)" };
#ifndef CPP11REGEX
    const string 
      sRegexA1P1(sRegexPrefijo + toString(cantidad_A1_P1) + sRegexSufijo),
      sRegexA1P2(sRegexPrefijo + toString(cantidad_A1_P2) + sRegexSufijo),
      sRegexA2P2(sRegexPrefijo + toString(cantidad_A2_P2) + sRegexSufijo);
    const regoff_t 
      posCantidad_A1_P1 = find_regex(sRegexA1P1.c_str(), sDetalle.c_str()),
      posCantidad_A1_P2 = find_regex(sRegexA1P2.c_str(), sDetalle.c_str()),
      posCantidad_A2_P2 = find_regex(sRegexA2P2.c_str(), sDetalle.c_str());
    // Las tres compras deben estar en la salida
    fct_chk(posCantidad_A1_P1 != -1);
    fct_chk(posCantidad_A1_P2 != -1);
    fct_chk(posCantidad_A2_P2 != -1);
    // Las compras deben estar agrupadas por artículo, y debidamente ordenadas.
    fct_chk(posCantidad_A2_P2 < posCantidad_A1_P1);
    fct_chk(posCantidad_A1_P1 < posCantidad_A1_P2);
#else
    regex  		// La nueva biblioteca regex de C++11
      sRegexA1P1(sRegexPrefijo + toString(cantidad_A1_P1) + sRegexSufijo),
      sRegexA1P2(sRegexPrefijo + toString(cantidad_A1_P2) + sRegexSufijo),
      sRegexA2P2(sRegexPrefijo + toString(cantidad_A2_P2) + sRegexSufijo);
    smatch cantidad_A1_P1, cantidad_A1_P2, cantidad_A2_P2;
    // Las tres compras deben estar en la salida
    fct_chk(regex_search(sDetalle, cantidad_A1_P1, sRegexA1P1));
    fct_chk(regex_search(sDetalle, cantidad_A1_P2, sRegexA1P2));
    fct_chk(regex_search(sDetalle, cantidad_A2_P2, sRegexA2P2));
    // Las compras deben estar agrupadas por artículo, y debidamente ordenadas.
    fct_chk(cantidad_A2_P2.position(0) < cantidad_A1_P1.position(0));
    fct_chk(cantidad_A1_P1.position(0) < cantidad_A1_P2.position(0));
#endif
  }
  FCT_TEST_END();
  
  FCT_TEST_BGN(Pedido---Usuario - pedidos de un usuario) {
    const auto& pedidosU2 = pAsocUsuarioPedido->pedidos(*pU2);
    if (pedidosU2.size() == 1)
      fct_chk(*pedidosU2.begin() == pPed2);
    else
      fct_chk(!"Debería haber 1 pedido registrado del usuario 2");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Pedido---Usuario - usuario de los pedidos) {
    fct_chk(pAsocUsuarioPedido->cliente(*const_cast<Pedido*>(pPed1)) == pU );
    fct_chk(pAsocUsuarioPedido->cliente(*const_cast<Pedido*>(pPed2)) == pU2);
  }
  FCT_TEST_END();
}
FCTMF_FIXTURE_SUITE_END()
