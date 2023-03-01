#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "fecha.hpp"
#include "cadena.hpp"
#include <iostream>

using namespace std;

class Articulo{
public:
    Articulo(const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, unsigned stock = 0);

    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();
    unsigned stock() const;
    unsigned& stock();

private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha publicacion_;
    double precio_;
    unsigned stock_;

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

inline unsigned Articulo::stock() const
{
    return stock_;
}

inline unsigned& Articulo::stock()
{
    return stock_;
}

#endif