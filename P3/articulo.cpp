#include "articulo.hpp"
#include <iomanip>


Articulo::Articulo(const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio, unsigned stock):
referencia_{referencia}, titulo_{titulo}, publicacion_{f_publi},precio_{precio},stock_{stock}
{}


ostream& operator <<(ostream& os , const Articulo& A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_publi().anno() << ". " << fixed << setprecision(2) <<A.precio() << " €"; 
    return os;
}
