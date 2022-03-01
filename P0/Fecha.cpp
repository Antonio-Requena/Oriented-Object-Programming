#include <iostream>
#include <ctime>
#include "Fecha.hpp"

const int AnnoMinimo = 1902;
const int AnnoMaximo = 2037; //Limites de años

std::time_t tiempo_calendario = std::time(nullptr);
std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    

Fecha::Fecha(int d , int m , int y )
{

    if(validarFecha(d,m,y))
    {
        day = d;
        month = m;
        year = y;
    }
    else
    {
        std::cout << "FAILED" ;
    }
}

inline Fecha::Fecha(const Fecha& F): day(F.day), month(F.month), year(F.year){}

bool validarFecha (int& d,int& m,int& y)
{
    unsigned int arrayDiasMes[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

    if (d == 0)
        d = tiempo_descompuesto->tm_mday;
    if (m == 0)
        m = tiempo_descompuesto->tm_mon + 1;
    if (y == 0)
        y = tiempo_descompuesto->tm_year + 1900;
    
    if(y < AnnoMinimo || y > AnnoMaximo) return false;
    if(d<=0||d>31) return false;
    if(m<=0||m>12) return false;
    if(m==2 && d>29) return false;
    if(arrayDiasMes[m-1]<d) return false;
    if(m==2 && d==29 && !esBisiesto(y)) return false;
    return true;
    
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

void ordenarFecha(Fecha& F)
{
    unsigned int arrayDiasMes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    while(F.day > arrayDiasMes[F.month - 1])
    {   
        if(F.month==12)
        {
            if(F.year + 1 <= AnnoMaximo)
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

    //CODIGO EN CUARENTENA : RESTAR DIAS

    if(F.day < 1)
    {
        int dias_atras = 1 - F.day;

        while(dias_atras > arrayDiasMes[F.month - 2])
        {
            if(F.month==1)
            {
                dias_atras -= arrayDiasMes[11];
                F.month = 12;
                F.year--;
            }
            else if(F.month - 1 == 2 && esBisiesto(F.year))
                {
                    dias_atras -= 29;
                    F.month--;
                }
                else
                {
                    dias_atras -= arrayDiasMes[F.month - 2];
                    F.month--;
                }
        }

        if(F.month - 1 == 2 && esBisiesto(F.year))
        {
            F.day = 29 - dias_atras + 1;
            F.month--;
        }
        else
        {
            F.day = arrayDiasMes[F.month-2] - dias_atras + 1;
            F.month--;
        }
        
    }
    //*********************************
}













