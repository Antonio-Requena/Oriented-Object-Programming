#include "articulo.hpp"
#include <iomanip>


Articulo::Articulo(Autores& autores, const Cadena referencia, const Cadena titulo, const Fecha f_publi, double precio):
autores_{autores},referencia_{referencia}, titulo_{titulo}, publicacion_{f_publi},precio_{precio}
{}


ostream& operator <<(ostream& os , const Articulo& A)
{
    os << "[" << A.referencia() << "] \"" << A.titulo() << "\", " << A.f_publi().anno() << ". " << fixed << setprecision(2) <<A.precio() << " €" << std::endl;
       
    return os;
}
