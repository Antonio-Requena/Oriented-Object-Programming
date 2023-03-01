#include <iomanip>
#include <ostream>
#include "pedido-articulo.hpp"
#include "../P2/tarjeta.hpp"
//Clase LineaPedido

LineaPedido::LineaPedido(double p, int c): precio_{p},cantidad_{c}{}

std::ostream& operator <<(std::ostream& os, const LineaPedido& l)
{
    os << std::fixed << std::setprecision(2) << l.precio_venta() << ' ' << "€" << '\t' << l.cantidad() ;

    return os ;
}

//Clase Pedido-Articulo

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, int cantidad)
{
    PA[&p].insert(std::make_pair(&a,LineaPedido(precio,cantidad)));
    AP[&a].insert(std::make_pair(&p,LineaPedido(precio,cantidad)));
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, int cantidad)
{
    pedir(p,a,precio,cantidad);
}

const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p)
{
    return PA[&p];
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a)
{
    return AP[&a];
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido& ip)
{

    double p= 0;

    os << "\n" 
        << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl 
        << "PVP \t Cant.\t Articulo\n" 
        << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto i = ip.begin(); i != ip.end() ; i++)
    {

        os << (i->second).precio_venta() << "€\t" 
            << (i->second).cantidad() << "\t" 
            << "[ "<< (i->first)->referencia() << "]\t"
            << "\"" << (i->first)->titulo() << "\"" << std::endl;

        p += (i->second).cantidad() * (i->second).precio_venta() ;
    }

    os<< std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    os << std::fixed << std::setprecision(2) << p << " €" << std::endl ;

    return os;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p)
{

    double precio = 0;
    int c = 0  ;

    os << "\n" << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl 
        << "PVP \t Cant.\t Fecha venta\n" 
        << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

    for(auto i = p.begin(); i != p.end() ; i++)
    {

        os << " " << (i->second).precio_venta() << " €\t" 
            << (i->second).cantidad() << "\t" 
            << (i->first)->fecha() << std::endl ;

        precio += (i->second).cantidad() * (i->second).precio_venta() ;
        c += (i->second).cantidad() ;
    }


    os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
    os << std::fixed << std::setprecision(2) << precio << " €\t" << c << std::endl ;

    return os ;

}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
    for(auto i = AP.begin(); i != AP.end(); i++)
    {
        os << "Ventas de [" << (i->first)->referencia() << "] \"" << i->first->titulo() << "\"" ;
        os << i->second << std::endl ;
    }

    return os ;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{
    double p = 0;

    for(auto i = PA.begin(); i != PA.end() ; i++)
    {

        os << "Pedido núm." << (i->first)->numero() << std::endl
            << "Cliente: " << (i->first)->tarjeta()->titular()->nombre() << "\t"
            << "Fecha: " << (i->first)->fecha() << (i->second) ;

        p += (i->first)->total() ;
    }

    os << std::fixed << "TOTAL VENTAS: " << std::setprecision(2) << p << " €" << std::endl ;

    return os ;
}
