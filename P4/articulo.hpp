#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>
#include <set>

using namespace std;

class Articulo{
public:
    typedef set<Autor*> Autores;
    Articulo(Autores& autores,const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio);

    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();

    virtual void impresion_especifica(ostream&) const = 0;
    virtual ~Articulo(){};
private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha publicacion_;
    double precio_;
    const Autores autores_;

};

class ArticuloAlmacenable : public Articulo
{
public:
    ArticuloAlmacenable(Autores& autores,const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, unsigned stock = 0);
    unsigned stock() const;
    unsigned& stock();
    
private:
    unsigned stock_;

};

class Libro : public ArticuloAlmacenable
{
public:
    Libro(Autores& autores,const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, unsigned pag, unsigned stock = 0);
    unsigned n_pag() const {return paginas_;}
    void impresion_especifica(ostream&) const;
private:
    const unsigned paginas_;
};

class Cederron : public ArticuloAlmacenable
{
public:
    Cederron(Autores& autores,const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, unsigned t,unsigned stock = 0);
    unsigned tam() const {return tam_;}
    void impresion_especifica(ostream&) const;
private:
    const unsigned tam_;
};

class LibroDigital : public Articulo
{
public:
    LibroDigital(Autores& autores,const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, const Fecha expiracion);
    const Fecha& f_exp() const {return f_exp_;}
    void impresion_especifica(ostream&) const;
private:
    const Fecha f_exp_;
};

class Autor
{
public:
    Cadena nombre() const {return nombre_;}
    Cadena apellidos() const {return apellidos_;}
    Cadena direccion() const {return direccion_;}
private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
};

ostream& operator <<(ostream& , const Articulo&);


inline Cadena Articulo::referencia() const
{
    return referencia_;
}

inline Cadena Articulo::titulo() const
{
    return titulo_;
}

inline Fecha Articulo::f_publi() const
{
    return publicacion_;
}

inline double Articulo::precio() const
{
    return precio_;
}

inline double& Articulo::precio() 
{
    return precio_;
}

inline unsigned ArticuloAlmacenable::stock() const
{
    return stock_;
}

inline unsigned& ArticuloAlmacenable::stock()
{
    return stock_;
}


#endif