#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include "../P2/usuario.hpp"
#include <set>

class Pedido;

class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;
    typedef std::map<Usuario*,Pedidos> Usuario_Pedidos;
    typedef std::map<Pedido*,Usuario*> Pedido_Usuario;

    void asocia(Usuario&,Pedido&);
    void asocia(Pedido&,Usuario&);

    Pedidos pedidos(Usuario&);
    Usuario* cliente(Pedido&);
private:
    Usuario_Pedidos AD;
    Pedido_Usuario AI;
};

#endif