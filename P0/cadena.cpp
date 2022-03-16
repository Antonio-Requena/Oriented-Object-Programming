#include <iostream>
#include "cadena.hpp"

Cadena::Cadena(size_t t, char c_relleno)
{
    tam_ = t;
    s_ = new char[tam_ + 1];
    for (size_t i=0; i < tam_; i++) //Se rellena la cadena del caracter rellenador
    {
        s_[i] = c_relleno;
    }
    s_[tam_] = '\0'; //Se agrega el caracter terminador
}

Cadena::Cadena(const char* cad)
{
    tam_ = std::strlen(cad);
    s_ = new char[tam_ + 1];
    for (size_t i=0; i < tam_; i++)
    {
        s_[i] = cad[i];
    }
    s_[tam_] = '\0'; //Se agrega el caracter terminador
}

Cadena::Cadena(const Cadena& C)
{
    tam_ = C.length();
    s_ = new char[tam_ + 1];
    for (size_t i=0; i < tam_; i++)
    {
        s_[i] = C[i];
    }
    s_[tam_] = '\0'; //Se agrega el caracter terminador
}

Cadena::operator const char* () const{return s_;}
inline size_t Cadena::length() const{return tam_;}

inline char Cadena::operator [](size_t i) const{return s_[i];}

inline char& Cadena::operator [](size_t i){return s_[i];}

char Cadena::at(size_t i) const
{
    if (i < 0 || i > length()-1 || tam_ == 0) throw std::out_of_range("Indice no valido");
    else
    {
        return s_[i];
    }

}

char& Cadena::at(size_t i)
{
    if (i < 0 || i > length()-1 || tam_ == 0) throw std::out_of_range("Indice no valido");
    else
    {
        return s_[i];
    }
}

Cadena Cadena::substr(size_t i, size_t t) const
{
    if(i + t > length() || i > length() || i + t < i) throw std::out_of_range("Tamaño fuera de los limites");
    
    Cadena aux;
    for (unsigned indice = 0; indice < t ; indice++)
    {
        aux[indice] = s_[indice+i];
    }
    aux.tam_ = t;
    return aux;
}

Cadena& Cadena::operator= (const Cadena& C)
{
    if (this != &C)
    {
        tam_ = C.tam_;
        s_ = new char[tam_ + 1];
        std::strcpy(s_,C.s_);
    }
    return *this;
}

Cadena& Cadena::operator=(const char* cad)
{
    if(std::strcmp(s_,cad))
    {
        tam_ = std::strlen(cad);
        s_ = new char[tam_ + 1];
        std::strcpy(s_,cad);

    }

    return *this;
}

Cadena Cadena::operator+ (const Cadena& C) const
{
    Cadena aux(*this);
    aux+=C;

    return aux;
}

Cadena& Cadena::operator+=(const Cadena& C)
{
    std::strcat(s_,C);
    tam_ += C.tam_;
    return *this;
}

bool operator ==(const Cadena& A, const Cadena& B){return !(std::strcmp(A,B));}
bool operator !=(const Cadena& A, const Cadena& B){return std::strcmp(A,B);}

bool operator >(const Cadena& A, const Cadena& B){return std::strcmp(A,B) > 0;}

bool operator >=(const Cadena& A, const Cadena& B){return (A == B || A > B);}

bool operator <(const Cadena& A, const Cadena& B){return B > A;}

bool operator <=(const Cadena& A, const Cadena& B){return (A == B || B > A);}

Cadena::~Cadena(){delete[] s_;}
