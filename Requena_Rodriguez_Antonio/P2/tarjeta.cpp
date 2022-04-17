#include "tarjeta.hpp"
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>


Numero::Numero(const Cadena& C): num_{C}
{
  remove_if(num_.begin(), num_.end(), ::isspace);
  
  if( std::count_if(num_.begin(), num_.end(), static_cast<int(*)(int)>(std::isdigit)) != num_.length() )
    throw Incorrecto(Razon::DIGITOS);
  
  if(num_.length() < 13 || num_.length()>19)
    throw Incorrecto(Razon::LONGITUD);
  if(!luhn(num_))
    throw Incorrecto(Razon::NO_VALIDO);
  

}

Numero::operator const char*() const
{
    return num_.c_str();
}

bool operator < (const Numero& A, const Numero& B)
{
  return A < B;
}

bool Numero::luhn(const Cadena& numero)
{
  size_t n = numero.length();
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}

//IMPLEMENTACION CLASE TARJETA//

Tarjeta::Tarjeta(const Numero& n, Usuario& t,const Fecha& f): n_tarjeta{n},titular_{&t},caducidad_{f},activa_{true}
{
  Fecha actual;
  if (caducidad_ < actual)
    throw Tarjeta::Caducada(caducidad_);

  t.es_titular_de(*this);
  if(!tarjetas_sistema.insert(n_tarjeta).second)
    throw Tarjeta::Num_duplicado(n_tarjeta);
  
}

Numero Tarjeta::numero() const{return n_tarjeta;}
const Usuario* Tarjeta::titular() const{return titular_;}
Fecha Tarjeta::caducidad() const{return caducidad_;}
bool Tarjeta::activa() const{return activa_;}

Tarjeta::Tipo Tarjeta::tipo() const
{

  if(n_tarjeta[0]=='3' && (n_tarjeta[1] == '4' || n_tarjeta[1] == '7'))
    return AmericanExpress;
  else if(n_tarjeta[0]=='3')
    return JCB;
  else if(n_tarjeta[0]=='4')
    return VISA;
  else if(n_tarjeta[0]=='5')
    return Mastercard;
  else if(n_tarjeta[0]=='6')
    return Maestro;
  else
    return Otro;
}

bool Tarjeta::activa(bool b)
{
  activa_ = b;
  return activa_;
}

void Tarjeta::anular_titular()
{
  titular_ = nullptr;
  (*this).activa(false);
}
