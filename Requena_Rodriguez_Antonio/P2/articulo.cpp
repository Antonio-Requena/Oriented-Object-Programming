#include "articulo.hpp"
#include <iomanip>

Articulo::Articulo(const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, int stock):
referencia_{referencia}, titulo_{titulo}, publicacion_{f_publi},precio_{precio},stock_{stock}
{}

Cadena Articulo::referencia() const
{
    return referencia_;
}

Cadena Articulo::titulo() const
{
    return titulo_;
}

Fecha Articulo::f_publi() const
{
    return publicacion_;
}

double Articulo::precio() const
{
    return precio_;
}

double& Articulo::precio() 
{
    return precio_;
}

int Articulo::stock() const
{
    return stock_;
}

int& Articulo::stock()
{
    return stock_;
}

ostream& operator <<(ostream& os , const Articulo& A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_publi().anno() << ". " << fixed << setprecision(2) <<A.precio() << " €"; 
    return os;
}
