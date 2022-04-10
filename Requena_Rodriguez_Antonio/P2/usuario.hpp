#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "../P1/cadena.hpp"

class Clave
{
public:
    enum Razon {CORTA,ERROR_CRYPT};

    Clave(const char*);

    class Incorrecta
    {
    public:
        Incorrecta(const Razon r): reason_{r} {};
        Razon razon() const {return reason_; };
        bool verifica(const char*) const;
    private:
        Razon reason_;
    };

    Cadena clave() const;
private:
    Cadena passwd_;
};

//USUARIO

class Usuario
{
public:
    Usuario(Cadena,Cadena,Cadena,Cadena,Clave);
private:
    Cadena id_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave pass_;
};


#endif