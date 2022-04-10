#ifndef FECHA_HPP
#define FECHA_HPP

#include <cassert>
#include <iostream>

using namespace std;

class Fecha{
public:
    explicit Fecha(int d = 0, int m = 0, int y = 0); //Constructor de conversion
    Fecha(const char*); //Constructor de conversion

    class Invalida{
    public:
        Invalida(const char* reason) : why(reason){} 
        const char * por_que() const{return why;}; //Metodo para errores
    private:
        const char* why;
    };

    static const int AnnoMinimo = 1902;
    static const int AnnoMaximo = 2037; //Limites de años

    //Metodos observadores
    int dia() const;
    int mes() const;
    int anno() const;

    //Sobrecarga de operadores
    Fecha& operator ++(); //Prefijo
    Fecha operator ++(int); //Postfijo
    Fecha& operator --(); //Prefijo
    Fecha operator --(int); //Postfijo

    Fecha operator + (int) const;
    Fecha operator - (int) const;
    Fecha& operator += (int);
    Fecha& operator -= (int);

    const char* cadena() const;

private:
    int day;
    int month;
    int year;

};

bool esBisiesto(int);
bool validarFecha (int&,int&,int&);

bool operator < (const Fecha&,const Fecha&);
bool operator <= (const Fecha&,const Fecha&);
bool operator == (const Fecha&,const Fecha&);
bool operator > (const Fecha&,const Fecha&);
bool operator >= (const Fecha&,const Fecha&);
bool operator != (const Fecha&,const Fecha&);

istream& operator >>(istream&, Fecha&);
ostream& operator <<(ostream& , const Fecha&);

#endif