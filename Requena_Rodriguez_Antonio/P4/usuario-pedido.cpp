#include "usuario-pedido.hpp"


void Usuario_Pedido::asocia(Usuario& user,Pedido& P)
{
    AD[&user].insert(&P);
    AI[&P] = &user;
}

void Usuario_Pedido::asocia(Pedido& P, Usuario& user)
{
    asocia(user,P);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& user)
{
    return AD[&user];
}

Usuario* Usuario_Pedido::cliente(Pedido& P)
{
    return AI[&P];
}