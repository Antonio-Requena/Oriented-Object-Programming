#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include <utility>
#include <iomanip>
#include "fecha.hpp"
#include "../P2/usuario.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
public:
    Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,const Tarjeta& t, const Fecha& F = Fecha());

    class Vacio{
    public:
        Vacio(Usuario& u): user{&u}{};
        Usuario& usuario() const {return *user;}
    private:
        Usuario* user;
    };

    class Impostor{
    public:
        Impostor(Usuario& u): user{&u}{};
        Usuario& usuario() const {return *user;}
    private:
        Usuario* user;
    };

    class SinStock{
    public:
        SinStock(const Articulo& A): art{&A}{};
        const Articulo& articulo() const {return *art;};
    private:
        const Articulo* art;
    };

    int numero() const { return n_pedido; }
    double total() const { return importe;}
    Fecha fecha() const  {return fecha_pedido;}
    static int n_total_pedidos() {return n;}
    const Tarjeta* tarjeta() const {return tarj ;}
private:
    int n_pedido;
    const Tarjeta* tarj;
    Fecha fecha_pedido;
    double importe;
    static int n;

};

std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif