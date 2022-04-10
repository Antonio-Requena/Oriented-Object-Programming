#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "fecha.hpp"
#include "cadena.hpp"

class Articulo{
public:
    Articulo(const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, int stock = 0);
    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();
    int stock() const;
    int& stock();

private:
    const Cadena referencia_;
    const Cadena titulo_;
    const Fecha publicacion_;
    double precio_;
    int stock_;

};

ostream& operator <<(ostream& , const Articulo&);

#endif