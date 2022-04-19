#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include <set>

class Numero{
public:
    
    enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
    Numero(const Cadena&);

    class Incorrecto
    {
    public:
        Incorrecto(Razon razon): r_{razon}{};
        Razon razon() const{return r_;};
    private:
        Razon r_;
    };

    operator const char*() const;
    friend bool operator < (const Numero&, const Numero&);
private:
    Cadena num_;
    bool luhn(const Cadena&);
};

//CLASE TARJETA//
class Usuario;

class Tarjeta{
public:
    typedef std::set<Numero> Tarjetas;
    enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
    class Caducada{
    public:
        Caducada(const Fecha& F): caducada_{F}{};
        Fecha cuando() const {return caducada_;}
    private:
        Fecha caducada_;
    };
    class Num_duplicado{
    public:
        Num_duplicado(const Numero& N): n_duplicado{N}{};
        Numero que() const {return n_duplicado;}
    private:
        Numero n_duplicado;
    };
    class Desactivada{};

    Tarjeta(const Numero&,Usuario&,const Fecha&);
    Tarjeta(const Tarjeta&) = delete;
    Tarjeta(Tarjeta&&) = delete;
    Tarjeta& operator = (const Tarjeta&) = delete;
    Tarjeta& operator = (Tarjeta&&) = delete;

    Numero numero() const;
    const Usuario* titular() const;
    Fecha caducidad() const;
    bool activa() const;
    Tipo tipo() const;

    void anular_titular();

    bool activa(bool b = true);

    ~Tarjeta();
private:
    const Numero n_tarjeta;
    const Usuario *titular_;
    const Fecha caducidad_;
    bool activa_;

    static Tarjetas tarjetas_sistema;

};

ostream& operator <<(ostream& , const Tarjeta &);


inline bool operator < (const Tarjeta&A, const Tarjeta&B){return A.numero() < B.numero();}

#endif