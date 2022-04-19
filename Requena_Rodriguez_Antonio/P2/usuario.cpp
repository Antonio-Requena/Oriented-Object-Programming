#include <random>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include "usuario.hpp"
#include "tarjeta.hpp"

Clave::Clave(const char* C)
{
    const char* salt = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA9876543210/.";
    char* cifrado = new char [2];

    if (strlen(C) < 5)
        throw Incorrecta(Razon::CORTA);
    
    cifrado[0] = salt[rand() % 64];
    cifrado[1] = salt[rand() % 64];

    if(crypt(C,cifrado) == NULL)
        throw Incorrecta(Razon::ERROR_CRYPT);
    
    
   passwd_ = crypt(C,cifrado);
}

Cadena Clave::clave() const
{
    return passwd_;
}

bool Clave::verifica(const char* C) const
{
    return !strcmp(crypt(C, passwd_.c_str()), passwd_.c_str());
}

//USUARIO//

Usuario::Usuario(const Cadena& identificador,const Cadena& nom,const Cadena& apell,const Cadena& dir,const Clave& password):
id_{identificador},nombre_{nom},apellidos_{apell},direccion_{dir},pass_{password}
{
    if(!users_sistema.insert(id_).second)
        throw(Usuario::Id_duplicado(id_));
}

Cadena Usuario::id() const{return id_;}
Cadena Usuario::nombre() const{return id_;}
Cadena Usuario::apellidos() const{return id_;}
Cadena Usuario::direccion() const{return id_;}
const Usuario::Tarjetas& Usuario::tarjetas() const{return tarjetas_;}
const Usuario::Articulos& Usuario::compra() const{return carrito_;}

void Usuario::es_titular_de(Tarjeta& T)
{
    if(this == T.titular())
        tarjetas_.insert(std::make_pair(T.numero(),&T));
}

void Usuario::no_es_titular_de(Tarjeta& T)
{
    T.anular_titular();
    tarjetas_.erase(T.numero());
}

Usuario::~Usuario()
{
    for(auto i = tarjetas_.begin(); i != tarjetas_.end();i++)
    {
        i->second->anular_titular();
    }
    users_sistema.erase(id_);
}

void Usuario::compra(Articulo A,size_t cantidad)
{
    if(cantidad>0)
        carrito_[&A]= cantidad;
    else
        carrito_.erase(&A);
}

size_t Usuario::n_articulos() const
{
    return carrito_.size();
}

ostream& operator <<(ostream& os , const Usuario& user)
{
    os << user.id_ << " [" << user.pass_.clave() << "] " << user.nombre_ << " " << user.apellidos_ << std::endl
        << user.direccion_ << std::endl << "Tarjetas:" << std::endl;

    for (auto i = user.tarjetas().begin();i!= user.tarjetas().end();i++)
    {
        os << i->second << std::endl;
    }
    return os;
}

ostream& mostrar_carro(ostream& os, const Usuario & user)
{
    os << "Carrito de compra de " << user.id() << " [Articulos: " << user.n_articulos() << "]" << std::endl
        << " Cant. Articulo" << std::endl << std::setfill('=') << std::setw(59) << std::endl;

    for (auto i = user.compra().begin();i!= user.compra().end();i++)
    {
        os << std::setfill(' ') << std::setw(3) << i->second << std::setfill(' ') << std::setw(3) << *(i->first) << std::endl;
    }

    return os;
}