#include "usuario.hpp"
#include "tarjeta.hpp"
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>


bool luhn(const Cadena&);

Numero::Numero(const Cadena& C): num_{limpia(C)}
{
  
  if( std::count_if(num_.begin(), num_.end(), static_cast<int(*)(int)>(std::isdigit)) != num_.length() )
    throw Incorrecto(Razon::DIGITOS);
  
  if(!luhn(num_))
    throw Incorrecto(Razon::NO_VALIDO);
  

}

Cadena Numero::eliminar_espacios(const Cadena &cad)
{
  Cadena aux (cad);

  std::remove_if(aux.begin(),aux.end()+1,[](char c){return isspace(c);});

  return Cadena(aux.c_str()) ;

}

Cadena Numero::limpia(const Cadena &cad)
{


  Cadena aux = eliminar_espacios(cad) ;

  if(aux.length() > 19 || aux.length() == 0 || aux.length() < 13 )
  {
    throw Incorrecto(Razon::LONGITUD) ;
  }

  return aux ;
}

Numero::operator const char*() const
{
    return num_.c_str();
}

bool operator < (const Numero& A, const Numero& B)
{
  return A.num_ < B.num_;
}


//IMPLEMENTACION CLASE TARJETA//

Tarjeta::Tarjetas Tarjeta::tarjetas_sistema;

ostream& operator <<(ostream& os, Tarjeta::Tipo tipo)
{
  switch (tipo)
  {
  case 0:
    os << "Otro";
    break;
  case 1:
    os << "VISA";
    break;
  case 2:
    os << "Mastercard";
    break;
  case 3:
    os << "Maestro";
    break;
  case 4:
    os << "JCB";
    break;
  case 5:
    os << "AmericanExpress";
    break;
  default:
    break;
  }
  return os;
}


Tarjeta::Tarjeta(const Numero& n, Usuario& t,const Fecha& f): n_tarjeta{n},titular_{&t},caducidad_{f}
{
  Fecha actual;
  if (caducidad_ < actual)
    throw Tarjeta::Caducada(caducidad_);
  if(!tarjetas_sistema.insert(n).second)
    throw Tarjeta::Num_duplicado(n);
  
  activa_= true;
  t.es_titular_de(*this);
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

ostream& operator <<(ostream& os , const Tarjeta& T)
{
  Cadena Nombre = T.titular()->nombre();
  Cadena Apellidos = T.titular()->apellidos();
  
  for (int i = 0; i < Nombre.length(); i++) 
  {
    Nombre[i] = toupper(Nombre[i]);
  }
  for (int j = 0; j < Apellidos.length(); j++) 
  {
    Apellidos[j] = toupper(Apellidos[j]);
  }
  
  os << T.tipo() << endl << T.numero() << endl << Nombre << " " << Apellidos << endl 
    << "Caduca: " << std::setfill('0') << std::setw(2) << T.caducidad().mes() << "/" << std::setw(2) << (T.caducidad().anno() % 100 );

  return os;
}

Tarjeta::~Tarjeta()
{
  if(titular_)
  {
    const_cast<Usuario*>(titular_)->no_es_titular_de(*this);
    titular_ = nullptr;
  }
  tarjetas_sistema.erase(n_tarjeta);
  
  
}