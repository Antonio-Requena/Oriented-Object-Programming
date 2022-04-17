#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"

class Articulo{
public:
    Articulo(const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, int stock = 0);
    Articulo(const Articulo&) = delete;
    Articulo(Articulo&&) = delete;
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