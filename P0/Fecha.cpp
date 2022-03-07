#include <iostream>
#include <ctime>
#include <string.h>
#include "Fecha.hpp"

std::time_t tiempo_calendario = std::time(nullptr);
std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    

Fecha::Fecha(int d , int m , int y )
{
    try
    {
        if(validarFecha(d,m,y))
        {
            day = d;
            month = m;
            year = y;
        }
    }
    catch(Fecha::Invalida e)
    {
        std::cerr << e.por_que() << '\n';
    }
}

inline Fecha::Fecha(const Fecha& F): day(F.day), month(F.month), year(F.year){}

Fecha::Fecha(const char* cadena)
{
    int dia,mes,anno;

    if(sscanf(cadena,"%d/%d/%d",&dia,&mes,&anno) !=3)
        throw Invalida("Cadena de texto invalida");
    else
    {
        if(validarFecha(dia,mes,anno))
        {
            day = dia;
            month = mes;
            year = anno;
        }
    }

}

bool validarFecha (int& d,int& m,int& y)
{
    unsigned int arrayDiasMes[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

    if (d == 0)
        d = tiempo_descompuesto->tm_mday;
    if (m == 0)
        m = tiempo_descompuesto->tm_mon + 1;
    if (y == 0)
        y = tiempo_descompuesto->tm_year + 1900;
    
    if(y < Fecha::AnnoMinimo || y > Fecha::AnnoMaximo)throw Fecha::Invalida("El año excede los limites");
    else if(d<=0||d>31) throw Fecha::Invalida("Dia Invalido");
        else if(m<=0||m>12) throw Fecha::Invalida("Mes invalido");
            else if(arrayDiasMes[m-1]<d) throw Fecha::Invalida("Dia invalido");
                else if(m==2 && d==29 && !esBisiesto(y))throw Fecha::Invalida("El año introducido no es bisiesto");
                    else return true;
    
}

bool esBisiesto(int y)
{
    if ((y%4==0)||(y%400==0)&&(y%100!=0)) return true;
    else return false;
}

inline int Fecha::dia() const {return day;}

inline int Fecha::mes() const {return month;}

inline int Fecha::anno() const {return year;}

Fecha& Fecha::operator = (const Fecha& F)
{
    if (this != &F)
    {
        day = F.day;
        month = F.month;
        year = F.year;
    }

    return *this;
}

bool Fecha::operator < (const Fecha& F) const
{
    if(year > F.year)
        return false;
    else if(year < F.year)
            return true;
        else
        {
            if(month > F.month)
                return false;
            else if(month < F.month)
                    return true;
                else
                {
                    if (day >= F.day)
                        return false;
                    else
                        return true;
                }
        }
}

bool Fecha::operator <= (const Fecha& F) const
{
    if(year > F.year)
        return false;
    else if(year < F.year)
            return true;
        else
        {
            if(month > F.month)
                return false;
            else if(month < F.month)
                    return true;
                else
                {
                    if (day > F.day)
                        return false;
                    else
                        return true;
                }
        }
}

bool Fecha::operator == (const Fecha& F) const {return(year==F.year && month == F.month && day == F.day);}

bool Fecha::operator > (const Fecha& F) const
{
    if(year < F.year)
        return false;
    else if(year > F.year)
            return true;
        else
        {
            if(month < F.month)
                return false;
            else if(month > F.month)
                    return true;
                else
                {
                    if (day <= F.day)
                        return false;
                    else
                        return true;
                }
        }
}
bool Fecha::operator >= (const Fecha& F) const
{
    if(year < F.year)
        return false;
    else if(year > F.year)
            return true;
        else
        {
            if(month < F.month)
                return false;
            else if(month > F.month)
                    return true;
                else
                {
                    if (day < F.day)
                        return false;
                    else
                        return true;
                }
        }
}

bool Fecha::operator != (const Fecha& F) const {return!(year==F.year && month == F.month && day == F.day);}

Fecha& Fecha::operator ++()
{
    day++;
    return *this;
}

Fecha Fecha::operator ++(int aux)
{   
    return Fecha(day++,month,year);
}

Fecha& Fecha::operator --()
{
    day--;
    return *this;
}

Fecha Fecha::operator --(int aux)
{   
    return Fecha(day--,month,year);
}


Fecha Fecha::operator + (int sum_dias) const
{
    Fecha Faux(*this);
    Faux.day = Faux.day + sum_dias;
    
    ordenarFecha(Faux);

    return Faux;
}

Fecha& Fecha::operator += (int sum_dias)
{
    day += sum_dias;
    ordenarFecha(*this);
    return *this;
}

Fecha Fecha::operator - (int rest_dias) const
{
    Fecha Faux(*this);
    Faux.day = Faux.day - rest_dias;
    ordenarFecha(Faux);

    return Faux;
}

Fecha& Fecha::operator -= (int rest_dias)
{
    day -= rest_dias;
    ordenarFecha(*this);
    return *this;
}

const char* Fecha::convertir_a_cadena() const 
{
    const char* dias[] = {"domingo","lunes","martes","miércoles","jueves","viernes","sabado"};
    const char* meses[] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"};

    static char fecha[50];
    tm date = {0};

    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;

    mktime(&date);
    std::sprintf(fecha,"%s %d de %s de %d", dias[date.tm_wday], date.tm_mday, meses[date.tm_mon], date.tm_year + 1900);
    std::cout << fecha;
    return fecha;
}

void ordenarFecha(Fecha& F)
{
    unsigned int arrayDiasMes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if(F.day <=0)
    {
        while(F.day <= 0)
        {

            if(F.month == 1)
            {
                F.day = arrayDiasMes[11] + F.day;
                F.month = 12;
                F.year--;
            }
        else if(F.month == 3 && esBisiesto(F.year))
            {
                F.day = 29 + F.day;
                F.month--;
            }
            else
            {
                F.day = arrayDiasMes[F.month - 2] + F.day;
                F.month--;
            }
        
        }
    }
    else
    {
        while(F.day > arrayDiasMes[F.month - 1])
        {   
            if(F.month==12)
            {
                if(F.year + 1 <= Fecha::AnnoMaximo)
                {
                    F.year++;
                    F.day = F.day-arrayDiasMes[F.month - 1];
                    F.month = 1;
                }
            else
                std::cout<< "NO se puede sobrepasar el año máximo";
        }
        else if(F.month == 2 && esBisiesto(F.year))
            {
                if(F.day > 29)
                {
                    F.day = F.day-29;
                    F.month++;
                }
            }
            else
            {
                F.day = F.day-arrayDiasMes[F.month - 1];
                F.month++;
            }  
        }
    }
}













