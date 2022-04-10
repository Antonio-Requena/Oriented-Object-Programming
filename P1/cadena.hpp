#ifndef CADENA_HPP
#define CADENA_HPP

#include <cassert>
#include <iostream>
#include <iterator>

using namespace std;

class Cadena
{
public:
    explicit Cadena(size_t t = 0, char c_relleno = ' '); //Constructor conversion + por defecto
    Cadena(const char* cad);
    Cadena(const Cadena& C); //Constructor de copia
    Cadena(Cadena&& C);

    const char* c_str() const; //Conversor implicito a cadena

    size_t length() const;
    Cadena substr(size_t i, size_t t) const;
    
    Cadena operator + (const Cadena& C) const;

    char operator [] (size_t i) const;
    char& operator [] (size_t i); //Mismo metodo pero modificable

    char at(size_t i) const;
    char& at(size_t i);

    Cadena& operator += (const Cadena& C);
    Cadena& operator = (const Cadena&);
    Cadena& operator = (Cadena&&);
    Cadena& operator = (const char*);

    ~Cadena(); //Destructor

    //Iterators
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin(){return s_;}
    const_iterator begin() const{return cbegin();}
    const_iterator cbegin() const{return s_;}
    reverse_iterator rbegin(){return reverse_iterator(end());}
    const_reverse_iterator rbegin() const{return crbegin();}
    const_reverse_iterator crbegin() const{return const_reverse_iterator(end());}

    iterator end(){return &s_[tam_];}
    const_iterator end() const{return cend();}
    const_iterator cend() const{return &s_[tam_];}
    reverse_iterator rend(){return reverse_iterator(begin());}
    const_reverse_iterator rend() const{return crend();}
    const_reverse_iterator crend() const{return const_reverse_iterator(begin());}


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


istream& operator >>(istream&, Cadena&);
ostream& operator <<(ostream& , const Cadena&);




#endif