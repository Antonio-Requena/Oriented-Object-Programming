#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include <map>
#include <unordered_map>
#include <unordered_set>

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
    private:
        Razon reason_;
    };

    Cadena clave() const;
    bool verifica(const char*) const;
private:
    Cadena passwd_;
};

//USUARIO

class Usuario
{
public:
    typedef std::unordered_map<Articulo*, size_t> Articulos;
    typedef std::unordered_set<Cadena> Usuarios;
    typedef std::map<Numero, Tarjeta*> Tarjetas;

    class Id_duplicado
    {
    public:
        Id_duplicado(Cadena id): idd_{id} {};
        Cadena idd() const {return idd_;};
    private:
        Cadena idd_;
    };

    Usuario(const Cadena&,const Cadena&,const Cadena&,const Cadena&,const Clave&);
    Usuario(const Usuario&) = delete;
    Usuario(Usuario&&) = delete;
    Usuario& operator = (const Usuario&) = delete;
    Usuario& operator = (Usuario&&) = delete;

    Cadena id() const;
    Cadena nombre() const;
    Cadena apellidos() const;
    Cadena direccion() const;
    const Tarjetas& tarjetas() const;
    const Articulos& compra() const;
    void compra(Articulo A,size_t cantidad = 1); //Asociación con articulo


    void es_titular_de (Tarjeta&);
    void no_es_titular_de (Tarjeta&);

    size_t n_articulos() const;
    
    friend ostream& operator <<(ostream& , const Usuario&);

    ~Usuario();

private:
    const Cadena id_;
    const Cadena nombre_;
    const Cadena apellidos_;
    const Cadena direccion_;
    Clave pass_;
    Tarjetas tarjetas_ ;
    Articulos carrito_;

    static Usuarios users_sistema;
};

ostream& mostrar_carro(ostream&, const Usuario::Articulos&);



#endif