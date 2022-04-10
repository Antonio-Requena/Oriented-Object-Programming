#ifndef CADENA_HPP
#define CADENA_HPP

#include <cassert>

class Cadena
{
public:
    explicit Cadena(size_t t = 0, char c_relleno = ' '); //Constructor conversion + por defecto
    Cadena(const char* cad);
    Cadena(const Cadena& C); //Constructor de copia

    operator const char* () const; //Conversor implicito a cadena

    size_t length() const;
    Cadena substr(size_t i, size_t t) const;
    
    Cadena operator + (const Cadena& C) const;

    char operator [] (size_t i) const;
    char& operator [] (size_t i); //Mismo metodo pero modificable

    char at(size_t i) const;
    char& at(size_t i);

    Cadena& operator += (const Cadena& C);
    Cadena& operator = (const Cadena&);
    Cadena& operator = (const char*);

    ~Cadena(); //Destructor
private:
    char* s_;
    size_t tam_; 
};

bool operator ==(const Cadena& A, const Cadena& B);
bool operator !=(const Cadena& A, const Cadena& B);
bool operator >(const Cadena& A, const Cadena& B);
bool operator >=(const Cadena& A, const Cadena& B);
bool operator <(const Cadena& A, const Cadena& B);
bool operator <=(const Cadena& A, const Cadena& B);



#endif