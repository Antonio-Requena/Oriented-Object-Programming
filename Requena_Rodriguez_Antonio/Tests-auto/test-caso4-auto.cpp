/* $Id: test-caso4-auto.cpp 338 2016-04-27 12:04:21Z gerardo $
 * ©2014 Antonio G.ª Dguez.
 * ©2015-16 el resto de profesores de POO
 */
#ifdef P4

#include "test-auto.hpp"
using namespace std;

namespace {
  // Para pruebas de Autor
  const Cadena sNombreAutor1 = "Nobuo",
    sApellidosAutor1 = "Uematsu",
    sDireccionAutor1 = "Tokyo, Japón";

  // Para pruebas de Libro
  Autor autor1(sNombreAutor1, sApellidosAutor1, sDireccionAutor1);
  Articulo::Autores autores = crea_autores(autor1);

  const Cadena sReferenciaLibro = "110", sTituloLibro = "Fundamentos de C++";
  const Fecha  fechaLibro(1,1,1998);
  const double precioLibro = 35.95;
  const unsigned paginasLibro = 650, stockLibro = 100;

  // Para pruebas de Cederron
  const Cadena
    sReferenciaCederron("404"),
    sTituloCederron("Ubuntu Hysterical Hyena");
  const Fecha fechaCederron(8, 4, 2005);
  const double precioCederron    = 0.01;
  const unsigned tamanyoCederron = 400;
  const unsigned stockCederron   = 1000;

  // Para pruebas de LibroDigital
  const Cadena sReferencia_eBook("4337"),
    sTitulo_eBook("Minority Report");
  const Fecha fecha_eBook(9,9,2009);
  const double precio_eBook = 9000;

  // Hay que usar punteros, o puede haber un fallo de segmentación si
  // el orden de inicialización de los atributos estáticos no es el
  // apropiado
  Usuario *pUsuarioPedido;
  Tarjeta *pTarjetaPedido;
  Pedido_Articulo pedArt;
  Usuario_Pedido  usuPed;

  Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                 fechaCederron, precioCederron, tamanyoCederron,
                 stockCederron);
  LibroDigital eBookNoExpirado(autores, sReferencia_eBook,
                                   sTitulo_eBook, fecha_eBook,
                                   precio_eBook, Fecha() + 7);
  LibroDigital eBookExpirado(autores, sReferencia_eBook,
                                 sTitulo_eBook, fecha_eBook,
                                 precio_eBook, Fecha() - 7);

  // Parte común
  bool bPrimera = true;

  using TIPO = Tarjeta::Tipo;
}

FCTMF_FIXTURE_SUITE_BGN(test_p4) {

  if (bPrimera) {
    bPrimera = false;
    cerr << "\n---------- PRÁCTICA 4 ----------\n" << endl;
  }

  FCT_SETUP_BGN() {
    pUsuarioPedido = new Usuario("fjord", "Franz", "Jordan",
                                 "Rue del Percebe, 13", Clave("supersecreta"));
    pTarjetaPedido = new Tarjeta(Numero("11234567890126"), 
				 *pUsuarioPedido, Fecha() + 7);
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pUsuarioPedido;
    delete pTarjetaPedido;
  }
  FCT_TEARDOWN_END();

  FCT_TEST_BGN(Autor - observadores) {
    const Autor autor(sNombreAutor1, sApellidosAutor1, sDireccionAutor1);
    chk_eq_str(autor.nombre   (), sNombreAutor1   );
    chk_eq_str(autor.apellidos(), sApellidosAutor1);
    chk_eq_str(autor.direccion(), sDireccionAutor1);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Articulo - es abstracta) {
    fct_chk(is_abstract<Articulo>::value);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Articulo - tiene destructor virtual) {
    fct_chk(has_virtual_destructor<Articulo>::value);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(ArticuloAlmacenable - es abstracta) {
    fct_chk(is_abstract<ArticuloAlmacenable>::value);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(ArticuloAlmacenable - tiene destructor virtual) {
    fct_chk(has_virtual_destructor<ArticuloAlmacenable>::value);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Libro - observadores) {
    const Libro libro(autores, sReferenciaLibro, sTituloLibro, fechaLibro,
                      precioLibro, paginasLibro, stockLibro);
    fct_chk_eq_int(autores.size(), 1);
    fct_chk_eq_int(libro.autores().count(&autor1), 1);

    chk_eq_str(libro.referencia(), sReferenciaLibro);
    chk_eq_str(libro.titulo(), sTituloLibro);
    fct_chk(libro.f_publi() == fechaLibro);
    fct_chk_eq_dbl(libro.precio(), precioLibro);
    fct_chk_eq_int(libro.n_pag(), paginasLibro);
    fct_chk_eq_int(libro.stock(), stockLibro);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Libro - insercion en flujo) {
    Autor autor2("María", "Martínez", "Algeciras");
    Articulo::Autores autores2 { &autor1, &autor2 };
    const Libro libro(autores2, sReferenciaLibro, sTituloLibro, fechaLibro,
                      precioLibro, paginasLibro, stockLibro);
    ostringstream os;
    os.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
    os << libro;
    string sLibro = os.str();
    fct_chk_eq_str(sLibro.c_str(),
                   "[110] \"Fundamentos de C++\", de Uematsu, Martínez. "
		   "1998. 35,95 €\n\t650 págs., 100 unidades.");
    os.str("");
    libro.impresion_especifica(os);
    sLibro = os.str();
    fct_chk_eq_str(sLibro.c_str(), "650 págs., 100 unidades.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Libro - modificacion) {
    Libro libro(autores, sReferenciaLibro, sTituloLibro, fechaLibro,
                precioLibro, paginasLibro, stockLibro);
    const double nuevoPrecio  = 10.5;
    const unsigned nuevoStock = libro.stock() + 1;
    libro.precio() = nuevoPrecio;
    libro.stock()  = nuevoStock ;
    fct_chk_eq_dbl(libro.precio(), nuevoPrecio);
    fct_chk_eq_int(libro.stock(), nuevoStock);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(CD - observadores) {
    const Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                         fechaCederron, precioCederron, tamanyoCederron,
                         stockCederron);
    fct_chk_eq_int(autores.size(), 1);
    fct_chk_eq_int(cdrom.autores().count(&autor1), 1);

    chk_eq_str(cdrom.referencia(), sReferenciaCederron);
    chk_eq_str(cdrom.titulo(), sTituloCederron);
    fct_chk(cdrom.f_publi() == fechaCederron);
    fct_chk_eq_dbl(cdrom.precio(), precioCederron);
    fct_chk_eq_int(cdrom.tam(), tamanyoCederron);
    fct_chk_eq_int(cdrom.stock(), stockCederron);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(CD - insercion en flujo) {
    const Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                         fechaCederron, precioCederron, tamanyoCederron,
                         stockCederron);
    ostringstream os;
    os.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
    os << cdrom;
    string sCdrom = os.str();
    fct_chk_eq_str(sCdrom.c_str(),
                   "[404] \"Ubuntu Hysterical Hyena\", "
		   "de Uematsu. 2005. 0,01 €\n"
                   "\t400 MB, 1000 unidades.");
    os.str("");
    cdrom.impresion_especifica(os);
    sCdrom = os.str();
    fct_chk_eq_str(sCdrom.c_str(), "400 MB, 1000 unidades.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(CD - modificacion) {
    Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                   fechaCederron, precioCederron, tamanyoCederron,
                   stockCederron);
    const double nuevoPrecio  = 10.5;
    const unsigned nuevoStock = cdrom.stock() + 1;
    cdrom.precio() = nuevoPrecio;
    cdrom.stock()  = nuevoStock ;
    fct_chk_eq_dbl(cdrom.precio(), nuevoPrecio);
    fct_chk_eq_int(cdrom.stock(), nuevoStock);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LibroDigital - observadores) {
    const Fecha fManyana = Fecha() + 1;
    const LibroDigital eBook(autores, sReferencia_eBook, sTitulo_eBook,
                                 fecha_eBook, precio_eBook, fManyana);
    fct_chk_eq_int(autores.size(), 1);
    fct_chk_eq_int(eBook.autores().count(&autor1), 1);

    chk_eq_str(eBook.referencia(), sReferencia_eBook);
    chk_eq_str(eBook.titulo(), sTitulo_eBook);
    fct_chk(eBook.f_publi() == fecha_eBook);
    fct_chk(eBook.f_expir() == fManyana);
    fct_chk_eq_dbl(eBook.precio(), precio_eBook);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LibroDigital - insercion en flujo) {
    const Fecha fExpiracion = Fecha() + 1;
    const LibroDigital eBook(autores, sReferencia_eBook, sTitulo_eBook,
                                 fecha_eBook, precio_eBook, fExpiracion);
    ostringstream os;
    os.imbue(std::locale(std::locale("es_ES.UTF-8"), new sin_separador()));
    os << eBook;
    string sEBook = os.str();
    os.str("");
    os << "[4337] \"Minority Report\", de Uematsu. 2009. 9000,00 €\n"
      "\tA la venta hasta el " << fExpiracion << ".";
    string sEsperado = os.str();

    fct_chk_eq_str(sEBook.c_str(), sEsperado.c_str());

    os.str("");
    eBook.impresion_especifica(os);
    sEBook = os.str();
    os.str("");
    os << "A la venta hasta el " << fExpiracion << ".";
    sEsperado = os.str();
    fct_chk_eq_str(sEBook.c_str(), sEsperado.c_str()); 
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LibroDigital - modificacion) {
    LibroDigital eBook(autores, sReferencia_eBook, sTitulo_eBook,
                           fecha_eBook, precio_eBook, Fecha() + 1);
    const double nuevoPrecio = 10.5;
    eBook.precio() = nuevoPrecio;
    fct_chk_eq_dbl(eBook.precio(), nuevoPrecio);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LibroDigital - compra de eBook no expirado) {
    pUsuarioPedido->compra(cdrom, 1);
    pUsuarioPedido->compra(eBookNoExpirado, 1);
    Pedido p(usuPed, pedArt, *pUsuarioPedido, *pTarjetaPedido);

    // Cálculo en coma flotante con precisión limitada: no se puede
    // usar == directamente. Hay que permitir un cierto margen de
    // diferencia, debido al error de aproximación.
    const double totalEsperado = cdrom.precio() + eBookNoExpirado.precio();
    fct_chk_eq_dbl(p.total(), totalEsperado);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LibroDigital - eBook expirado y carrito no queda vacio) {
    pUsuarioPedido->compra(cdrom, 1);
    pUsuarioPedido->compra(eBookExpirado, 1);
    Pedido p(usuPed, pedArt, *pUsuarioPedido, *pTarjetaPedido);

    fct_chk_eq_dbl(p.total(), cdrom.precio());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LibroDigital - eBook expirado y carrito queda vacio) {
    pUsuarioPedido->compra(eBookExpirado, 1);
    fct_chk_ex(Pedido::Vacio, 
	       Pedido(usuPed, pedArt, *pUsuarioPedido, *pTarjetaPedido));
  }
  FCT_TEST_END();

}
FCTMF_FIXTURE_SUITE_END()

#endif	// ifdef P4
