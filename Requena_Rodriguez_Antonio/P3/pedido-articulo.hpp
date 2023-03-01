#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "../P2/articulo.hpp"
#include "pedido.hpp"
#include <utility>
#include <map>

class LineaPedido{
public:
    explicit LineaPedido(double p, int c = 1);
    double precio_venta() const {return precio_;}
    int cantidad() const {return cantidad_;}
private:
    double precio_;
    int cantidad_;
};

std::ostream& operator <<(std::ostream&, const LineaPedido& );

//PEDIDO_ARTICULOS

class OrdenaArticulos
{
public:
    bool operator()(const Articulo* a1, const Articulo* a2) const { return a1->referencia() < a2->referencia() ; }
};


class OrdenaPedidos
{
public:
    bool operator()(const Pedido* p1, const Pedido* p2) const {return p1->numero() < p2->numero();}
};

class Pedido_Articulo
{
public:
    typedef std::map<Articulo*,LineaPedido,OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*,LineaPedido,OrdenaPedidos> Pedidos;

    void pedir(Pedido& p, Articulo& a, double precio, int cantidad = 1);

    void pedir(Articulo& a, Pedido& p, double precio, int cantidad = 1);

    const ItemsPedido& detalle(Pedido& p);
    Pedidos ventas(Articulo& a);

    std::ostream& mostrarDetallePedidos(std::ostream& os);
    std::ostream& mostrarVentasArticulos(std::ostream& os);
private:
    std::map<Pedido*,ItemsPedido,OrdenaPedidos> PA;
    std::map<Articulo*,Pedidos,OrdenaArticulos> AP;
};

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip) ;
std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& p) ;

#endif