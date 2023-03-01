#include <iostream>
#include <string.h>
#include "cadena.hpp"

using namespace std;

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
    tam_ = strlen(cad);
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

Cadena::Cadena(Cadena&& C): s_(C.s_), tam_(C.tam_)
{
    C.s_ = nullptr;
    C.tam_ = 0;
}

inline const char* Cadena::c_str() const {return s_;} 

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
        delete[] s_;
        tam_ = C.tam_;
        s_ = new char[tam_ + 1];
        strcpy(s_,C.s_);
    }
    return *this;
}

Cadena& Cadena::operator= (Cadena&& C)
{
    if (this != &C)
    {
        delete[] s_;
        tam_ = C.tam_;
        s_ = C.s_;
        
        C.s_ = nullptr;
        C.tam_ = 0;
    }
    return *this;
}

Cadena& Cadena::operator=(const char* cad)
{
    if(strcmp(s_,cad))
    {
        tam_ = strlen(cad);
        s_ = new char[tam_ + 1];
        strcpy(s_,cad);

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
    strcat(s_,C.c_str());
    tam_ += C.tam_;
    return *this;
}

bool operator ==(const Cadena& A, const Cadena& B){return !(strcmp(A.c_str(),B.c_str()));}
bool operator !=(const Cadena& A, const Cadena& B){return strcmp(A.c_str(),B.c_str());}

bool operator >(const Cadena& A, const Cadena& B){return strcmp(A.c_str(),B.c_str()) > 0;}

bool operator >=(const Cadena& A, const Cadena& B){return (A == B || A > B);}

bool operator <(const Cadena& A, const Cadena& B){return B > A;}

bool operator <=(const Cadena& A, const Cadena& B){return (A == B || B > A);}

ostream& operator <<(ostream& os, const Cadena& C)
{
    os << C.c_str();
    return os;
}

istream& operator >>(istream& is, Cadena& C)
{
    char* cad = new char[32];
    unsigned i = 0;

    while(isspace(is.get())!= 0 && i < 32)
    {
        i++;
    }
    is.unget();
    i=0;

    while(!isspace(is.peek()) && i < 32 && is.good())
    {
        cad[i] = is.get();
        i++;
    }

    cad[i] = '\0';
    C = Cadena(cad);
    delete[] cad;
    return is;  
    
}


Cadena::~Cadena(){delete[] s_;}
