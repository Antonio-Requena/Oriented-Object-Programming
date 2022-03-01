#ifndef FECHA_HPP
#define FECHA_HPP

#include <cassert>

class Fecha{
public:
    Fecha(int d = 0, int m = 0, int y = 0); //Constructor de conversion
    Fecha(const Fecha&); //Constructor de copia
    Fecha(const char*); //Constructor de conversion

    class Invalida{
    public: 
        void por_que(); //Metodo para errores
    };

    //Metodos observadores
    int dia() const;
    int mes() const;
    int anno() const;

    //Sobrecarga de operadores
    Fecha& operator ++(); //Prefijo
    Fecha operator ++(int aux); //Postfijo
    Fecha& operator --(); //Prefijo
    Fecha operator --(int); //Postfijo

    Fecha operator + (int) const;
    Fecha operator - (int) const;
    Fecha& operator += (int);
    Fecha& operator -= (int);

    bool operator < (const Fecha&) const;
    bool operator <= (const Fecha&) const;
    bool operator == (const Fecha&) const;
    bool operator > (const Fecha&) const;
    bool operator >= (const Fecha&) const;
    bool operator != (const Fecha&) const;

    Fecha& operator = (const Fecha&); //Operador de asignación

private:
    int day;
    int month;
    int year;

    //Métodos privados
    friend void ordenarFecha(Fecha&);
};

bool esBisiesto(int);
bool validarFecha (int&,int&,int&);

#endif