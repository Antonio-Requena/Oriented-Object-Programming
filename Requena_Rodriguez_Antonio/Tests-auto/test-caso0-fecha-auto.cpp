/* $Id: test-caso0-fecha-auto.cpp 344 2016-04-29 20:20:13Z gerardo $
 * 
 * Pruebas unitarias automáticas para la clase Fecha (P0-P1)
 *
 * ©2014 Antonio G.ª Dguez.
 * ©2015-20 el resto de profesores de POO
 */

#include "test-auto.hpp"

using namespace std;

/*
 *       Funciones y macros auxiliares
 */

#define fecha_is_eq(f, d, m, a) (f.anno() == a && f.mes() == m && f.dia() == d)

#define chk_eq_fecha(f, d, m, a)\
  fct_xchk(\
    fecha_is_eq(f,d,m,a),\
    "failed chk_eq_fecha:\n<%02d/%02d/%04d>!=<%02d/%02d/%04d>",\
    f.dia(), f.mes(), f.anno(), d, m, a)
#define Fecha_chk_eq chk_eq_fecha

namespace {
  int annoSistema, mesSistema, diaSistema;
  bool bPrimera = true;
}

FCTMF_FIXTURE_SUITE_BGN(test_fecha) {
  if (bPrimera) {
    bPrimera = false;
    cerr << 
#ifdef P0
      "\n---------- PRÁCTICA 0: FECHA ----------\n" 
#else
      "\n---------- PRÁCTICA 1: FECHA ----------\n" 
#endif
	 << endl;
  }
  
  FCT_SETUP_BGN() {
    // 1.º establecemos la zona horaria a UTC para evitar cosas raras
    setenv("TZ", "", 1);
    tzset();
    // y después obtenemos la hora UTC del sistema
    const time_t ahora =   time(nullptr);
    const tm*    fecha = gmtime(& ahora);
    annoSistema = fecha->tm_year + 1900;
    mesSistema  = fecha->tm_mon  +    1;
    diaSistema  = fecha->tm_mday +    0;
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    // Nothing to do here.
  }
  FCT_TEARDOWN_END();

   FCT_TEST_BGN(Fecha - Ctor.: dia-mes-anyo; no ceros) {
      const Fecha f(18, 7, 1936);
      Fecha_chk_eq(f, 18, 7, 1936);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-mes; no ceros) {
      const Fecha f(17, 7);
      Fecha_chk_eq(f, 17, 7, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia; no cero) {
      const Fecha f(1);
      Fecha_chk_eq(f, 1, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia; no conversion implicita) {
      bool conversion_implicita = is_convertible<int, Fecha>::value;
      fct_chk(!conversion_implicita);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-cero) {
      const Fecha f(2, 0);
      Fecha_chk_eq(f, 2, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-mes-cero) {
      const Fecha f(3, 7, 0);
      Fecha_chk_eq(f, 3, 7, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-cero-cero) {
      const Fecha f(2, 0, 0);
      Fecha_chk_eq(f, 2, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia-cero-anno) {
      const Fecha f(3, 0, 2010);
      Fecha_chk_eq(f, 3, mesSistema, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-cero-anno) {
      const Fecha f(0, 0, 2012);
      Fecha_chk_eq(f, diaSistema, mesSistema, 2012);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-mes-anno) {
      const Fecha f(0, 3, 2000);
      Fecha_chk_eq(f, diaSistema, 3, 2000);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-mes-cero) {
      const Fecha f(0, 3, 000);
      Fecha_chk_eq(f, diaSistema, 3, annoSistema);
    }
    FCT_TEST_END();
    
    FCT_TEST_BGN(Fecha - Ctor.: predeterminado) {
      const Fecha hoy;
      Fecha_chk_eq(hoy, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cero-cero-cero) {
      const Fecha f(0, 0, 0);
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: copia) {
      const Fecha f(2, 3, 2000);
      const Fecha g(f);
      Fecha_chk_eq(f, g.dia(), g.mes(), g.anno());
      Fecha_chk_eq(g, 2, 3, 2000);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: copia trivial) {
#if __GLIBCXX__ >= 20160301
      fct_chk(is_trivially_copy_constructible<Fecha>::value);
#endif
      fct_chk(is_nothrow_copy_constructible<Fecha>::value);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena dd/mm/aaaa) {
      const Fecha f("11/09/2001");
      Fecha_chk_eq(f, 11, 9, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena d/m/aaaa) {
      const Fecha f = "1/5/2010";
      Fecha_chk_eq(f, 1, 5, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena d/m/0) {
      const Fecha f = "1/5/0";
      Fecha_chk_eq(f, 1, 5, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena d/0/aaaa) {
      const Fecha f = "1/0/2010";
      Fecha_chk_eq(f, 1, mesSistema, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/mm/aaaa) {
      const Fecha f = "0/10/2010";
      Fecha_chk_eq(f, diaSistema, 10, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena dd/0/0) {
      const Fecha f = "01/0/0";
      Fecha_chk_eq(f, 1, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/0/aaaa) {
      const Fecha f = "0/0/2012";
      Fecha_chk_eq(f, diaSistema, mesSistema, 2012);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/mes/0) {
      const Fecha f = "0/10/0";	// Poner un mes de 31 días
      Fecha_chk_eq(f, diaSistema, 10, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena 0/0/0) {
      const Fecha f = "0/0/0";
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena formato incorrecto) {
      fct_chk_ex(Fecha::Invalida, Fecha("22/03"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: cadena sobran caracteres no numericos) {
      const Fecha f("11/09/2001)&...");
      Fecha_chk_eq(f, 11, 9, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha (31, 4));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia valido para bisiesto) {
      try {
	const Fecha f(29, 2, 2004);
	Fecha_chk_eq(f, 29, 2, 2004);
      } catch(Fecha::Invalida) {
	fct_chk(!"No se esperaba una excepción Fecha::Invalida");
      }
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: dia no valido ni para bisiesto) {
      fct_chk_ex(Fecha::Invalida, Fecha(29, 2, 2003));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: mes no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha (31, 33));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor.: anno no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha (2, 5, 1808));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor. cadena: dia invalido y Fecha::Invalida::por_que)
      try {
        Fecha f("29/2/2015");
        fct_chk(!"Se esperaba una excepción Fecha::Invalida");
      } catch (const Fecha::Invalida& e) {
        fct_chk(e.por_que());
      }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor. cadena: mes no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha("1/-1/2028"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Ctor. cadena: anno no valido) {
      fct_chk_ex(Fecha::Invalida, Fecha("1/1/-1"));
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Constantes AnnoMinimo y AnnoMaximo) {
      fct_chk_eq_int(Fecha::AnnoMinimo, 1902);
      fct_chk_eq_int(Fecha::AnnoMaximo, 2037);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Preincremento) {
      Fecha f(31, 3, 2010);
      const Fecha g(++f);
      Fecha_chk_eq(f, 1, 4, 2010);
      Fecha_chk_eq(g, 1, 4, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Preincremento - asociatividad) {
      Fecha f(31, 3, 2010);
      const Fecha g(++++f);
      Fecha_chk_eq(f, 2, 4, 2010);
      Fecha_chk_eq(g, 2, 4, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Preincremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(31, 12, Fecha::AnnoMaximo); ++f);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postincremento) {
      Fecha f(31, 3, 2010);
      const Fecha g(f++);
      Fecha_chk_eq(f, 1, 4, 2010);
      Fecha_chk_eq(g, 31, 3, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postincremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(31, 12, Fecha::AnnoMaximo); f++);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Predecremento) {
      Fecha f(1, 1, 2010);
      const Fecha g(--f);
      Fecha_chk_eq(f, 31, 12, 2009);
      Fecha_chk_eq(g, 31, 12, 2009);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Predecremento - asociatividad) {
      Fecha f(1, 1, 2010);
      const Fecha g(----f);
      Fecha_chk_eq(f, 30, 12, 2009);
      Fecha_chk_eq(g, 30, 12, 2009);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Predecremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(1, 1, Fecha::AnnoMinimo); --f);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postdecremento) {
      Fecha f(1, 1, 2010);
      const Fecha g(f--);
      Fecha_chk_eq(f, 31, 12, 2009);
      Fecha_chk_eq(g, 1, 1, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Postdecremento - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(1, 1, Fecha::AnnoMinimo); f--);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma de dias - fecha + dias) {
      const Fecha f(30, 4, 2003);
      const Fecha g(f + 10);
      Fecha_chk_eq(g, 10, 5, 2003);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma de dias - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, const Fecha f(31, 12, Fecha::AnnoMaximo);
		 f + 7);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta de dias - fecha - dias) {
      const Fecha f(1, 4, 2008);
      const Fecha g(f - 10);
      Fecha_chk_eq(g, 22, 3, 2008);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta de dias - fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(1, 1, Fecha::AnnoMinimo); f - 3);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma con asignacion) {
      Fecha f(5, 5, 2005);
      f += 3;
      Fecha_chk_eq(f, 8, 5, 2005);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma con asignacion - asociatividad) {
      Fecha f(5, 5, 2005);
      (f += 3) += 2;
      Fecha_chk_eq(f, 10, 5, 2005);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Suma con asignacion: fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(31, 12, Fecha::AnnoMaximo); f += 2);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta con asignacion) {
      Fecha f(2, 1, 2010);
      f -= 2;
      Fecha_chk_eq(f, 31, 12, 2009);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta con asignacion - asociatividad) {
      Fecha f(2, 7, 2010);
      (f -= 2) -= 5;
      Fecha_chk_eq(f, 25, 6, 2010);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Resta con asignacion: fecha fuera de rango) {
      fct_chk_ex(Fecha::Invalida, Fecha f(1, 1, Fecha::AnnoMinimo); f -= 2);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Asignacion entre fechas) {
      const Fecha f(1, 1, 2001);
      Fecha g(3, 4, 2005);
      g = f;
      Fecha_chk_eq(g, 1, 1, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Asignacion trivial entre fechas) {
#if __GLIBCXX__ >= 20160301
      fct_chk(is_trivially_copy_assignable<Fecha>::value);
#endif
      fct_chk(is_nothrow_copy_assignable<Fecha>::value);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Asignacion entre fechas - asociatividad) {
      const Fecha f(1, 1, 2001);
      Fecha g(3, 4, 2005);
      Fecha h(g);
      h = g = f;
      Fecha_chk_eq(h, 1, 1, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Observadores dia-mes-anno){
      const Fecha f(29, 2, 2000);
      fct_chk_eq_int(f.dia(), 29);
      fct_chk_eq_int(2, f.mes());
      fct_chk_eq_int(f.anno(), 2000);
    }
    FCT_TEST_END();

#ifdef P0
    FCT_TEST_BGN(Fecha - Conversion implicita a cadena) {
#else
    FCT_TEST_BGN(Fecha - Funcion cadena) {
#endif
      const Fecha f(2, 4, 2006);
#ifdef P0
      const char* s = f;
#else
      const char* s = f.cadena();
#endif
      bool es_conv_a_cadena = is_convertible<Fecha, const char*>::value;
      fct_chk_incl_str(s, "domingo");
      fct_chk_incl_str(s, "2 "     );
      fct_chk_incl_str(s, "abril"  );
      fct_chk_incl_str(s, "2006"   );
      const Fecha g("25/09/1968"   );
#ifdef P0
      s = g;
      fct_chk(es_conv_a_cadena);
#else
      s = g.cadena();
      fct_chk(!es_conv_a_cadena);
#endif
      fct_chk_eq_str(s, "miércoles 25 de septiembre de 1968");
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: igualdad) {
      const Fecha f(1, 2, 2000);
      const Fecha g(f);
      const Fecha h(2, 3, 2001);
      fct_chk(f == g);
      fct_chk(!(f == h));
#ifndef P0
      fct_chk(f == "1/2/2000");
      fct_chk("2/3/2001" == h);
#endif
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: desigualdad) {
      const Fecha f(1, 2, 2000);
      const Fecha g(f);
      const Fecha h(2, 3, 2001);
      fct_chk(!(f != g));
      fct_chk(f != h);
#ifndef P0
      fct_chk(f != "00002/003/02001");
      fct_chk("1/1/2001" != g);
#endif
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: mayor) {
      const Fecha f(10, 2, 2000);
      const Fecha g( 9, 2, 2001);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(!(f > f));
      fct_chk(g > f);
      fct_chk(f > h);
      fct_chk(i > f);
      fct_chk(f > j);
      fct_chk(k > f);
#ifndef P0
      fct_chk(f > "11/2/1999");
      fct_chk("1/1/2005" > k);
#endif
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: mayor o igual) {
      const Fecha f(10, 2, 2000);
      const Fecha g( 9, 2, 2001);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(f >= f);
      fct_chk(g >= f);
      fct_chk(f >= h);
      fct_chk(i >= f);
      fct_chk(f >= j);
      fct_chk(k >= f);
#ifndef P0
      fct_chk(f >= "9/2/1999");
      fct_chk("10/4/2001" >= i);
#endif
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: menor) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(!(f < f));
      fct_chk(f < g);
      fct_chk(h < f);
      fct_chk(f < i);
      fct_chk(j < f);
      fct_chk(f < k);
#ifndef P0
      fct_chk(f < "11/3/2001");
      fct_chk("9/5/2000" < i);
#endif
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Comparacion: menor o igual) {
      const Fecha f(10, 2, 2000);
      const Fecha g(15, 2, 2000);
      const Fecha h(20, 1, 2000);
      const Fecha i(10, 5, 2000);
      const Fecha j(30, 5, 1999);
      const Fecha k(1, 1, 2004);
      fct_chk(f <= f);
      fct_chk(f <= g);
      fct_chk(h <= f);
      fct_chk(f <= i);
      fct_chk(j <= f);
      fct_chk(f <= k);
#ifndef P0
      fct_chk(f <= "10/02/2000");
      fct_chk("20/001/2000" <= h);
#endif
    }
    FCT_TEST_END();

#ifndef P0
    // P1 - E/S

    FCT_TEST_BGN(Fecha - Extraccion: fecha valida) {
      istringstream is("01/01/2001");
      Fecha f;
      is >> f;
      Fecha_chk_eq(f, 1, 1, 2001);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Extraccion: fecha no valida) {
      istringstream is("90/20/4000");
      Fecha f;
      try {
	is >> f;
        fct_chk(!"Se esperaba una excepción Fecha::Invalida");
      }
      catch(Fecha::Invalida) {
	fct_chk(is.fail());
	is.clear();
      }
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Extraccion: entrada no valida) {
      istringstream is("gomi");
      Fecha f;
      try {
	is >> f;
        fct_chk(!"Se esperaba una excepción Fecha::Invalida");
      }
      catch(Fecha::Invalida) {
	fct_chk(is.fail());
	is.clear();
      }
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Extraccion: desbordamiento) {
      istringstream is("007/007/1997");
      Fecha f;
      try {
	is >> f;
        fct_chk(!"Se esperaba una excepción Fecha::Invalida");
      }
      catch(Fecha::Invalida) {
	fct_chk(is.fail());
	is.clear();
      }
      Fecha_chk_eq(f, diaSistema, mesSistema, annoSistema);
    }
    FCT_TEST_END();

    FCT_TEST_BGN(Fecha - Insercion) {
      const Fecha f("23/09/2015");
      ostringstream os;
      os << f;
      fct_chk_eq_str("miércoles 23 de septiembre de 2015", os.str().c_str());
    }
    FCT_TEST_END();
#endif
}
FCTMF_FIXTURE_SUITE_END()
