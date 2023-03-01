#include "tarjeta.hpp"
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include <iostream>
#include <iomanip>


int Pedido::n = 0;

Pedido::Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,const Tarjeta & t, const Fecha& F):
n_pedido(n + 1), tarj(&t), fecha_pedido(F) , importe(0)
{
    if(t.caducidad() < F)
    {
        throw Tarjeta::Caducada(t.caducidad());
    }

    if(u.n_articulos() == 0)
    {
        throw Vacio(u);
    }

    if(t.titular() != &u)
    {
        throw Impostor(u);
    }

    if(t.activa() != true )
    {
    	throw Tarjeta::Desactivada();
    }

	auto carrito = u.compra();

    for(auto i: carrito)
    {
        if((i.first)->stock() < (i.second))
        {
            const_cast<Usuario::Articulos&>(u.compra()).clear();
            throw SinStock(*(i.first));
        }
    }

    for(auto it : carrito)
    {
        int cant = (it.second);
        Articulo* art = (it.first);
        double p = art->precio();
        art->stock() -= cant;

        pa.pedir(*this, *art, p, cant);
        importe += p * cant;
        u.compra(*art, 0);
    }

    up.asocia(u, *this);

    ++n;

}

std::ostream& operator <<(std::ostream& os, const Pedido& p)
{   
    os  << "\nNúm. pedido:     " << p.numero() << std::endl 
        << "Fecha:	 	 " << p.fecha() << std::endl;
    if(p.tarjeta()->tipo() == 0)
        os << "Pagado con:	 Tipo indeterminado n.º: "<< p.tarjeta()->numero() << std::endl ;
    else
        os << "Pagado con:	 " << p.tarjeta()->tipo() << " n.º: "<< p.tarjeta()->numero() << std::endl; 
    os << "Importe:	 " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;

    return os;
}

