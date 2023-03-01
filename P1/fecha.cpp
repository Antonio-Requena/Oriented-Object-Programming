#include <iostream>
#include <ctime>
#include "fecha.hpp"

std::time_t tiempo_calendario = std::time(nullptr);
std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
    

Fecha::Fecha(int d , int m , int y ) : day{d},month{m}, year{y}
{
    
    std::time_t tc = std::time(nullptr);
    std::tm* td = std::localtime(&tc);

    if(y == 0)
    {
        year = td->tm_year + 1900;
    }

    if(m == 0)
    {
        month = td->tm_mon + 1;
    }

    if(d == 0)
    {
        day = td->tm_mday;
    }
    validarFecha(day,month,year);

}


Fecha::Fecha(const char* cadena)
{
    int dia,mes,anno;

    if(sscanf(cadena,"%d/%d/%d",&dia,&mes,&anno) !=3)
        throw Invalida("Cadena de texto invalida");
    else
    {

        day = dia;
        month = mes;
        year = anno;

        std::time_t tc = std::time(nullptr);
        std::tm* td = std::localtime(&tc);

        if(year == 0)
        {
            year = td->tm_year + 1900;
        }

        if(month == 0)
        {
            month = td->tm_mon + 1;
        }

        if(day == 0)
        {
            day = td->tm_mday;
        }

        validarFecha(day,month,year);

    }

}

void validarFecha (int& d,int& m,int& y)
{
    unsigned int arrayDiasMes[12] = {31,29,31,30,31,30,31,31,30,31,30,31};

    if(y < Fecha::AnnoMinimo || y > Fecha::AnnoMaximo)throw Fecha::Invalida("El año excede los limites");
    else if(d<=0||d>31) throw Fecha::Invalida("Dia Invalido");
        else if(m<=0||m>12) throw Fecha::Invalida("Mes invalido");
            else if(arrayDiasMes[m-1]<d) throw Fecha::Invalida("Dia invalido");
                else if(m==2 && d==29 && !esBisiesto(y))throw Fecha::Invalida("El año introducido no es bisiesto");
    
}

bool esBisiesto(int y)
{
    if ((y%4==0)||((y%400==0)&&(y%100!=0))) return true;
    else return false;
}

inline int Fecha::dia() const {return day;}

inline int Fecha::mes() const {return month;}

inline int Fecha::anno() const {return year;}

bool operator < (const Fecha& A, const Fecha& B)
{
    if(A.anno() > B.anno())
        return false;
    else if(A.anno() < B.anno())
            return true;
        else
        {
            if(A.mes() > B.mes())
                return false;
            else if(A.mes() < B.mes())
                    return true;
                else
                {
                    if (A.dia() >= B.dia())
                        return false;
                    else
                        return true;
                }
        }
}

bool operator <= (const Fecha& A,const Fecha& B)
{
    return (A < B || A == B);
}

bool operator == (const Fecha& A,const Fecha& B) {return(A.dia() == B.dia() && A.mes()==B.mes() && A.anno() == B.anno());}

bool operator > (const Fecha& A,const Fecha& B)
{
    return B < A;
}
bool operator >= (const Fecha& A,const Fecha& B)
{
    return (B < A || A == B);
}

bool operator != (const Fecha& A,const Fecha& B) {return!(A==B);}

Fecha& Fecha::operator ++()
{
    return *this+=1;
}

Fecha Fecha::operator ++(int aux)
{   
    Fecha auxiliar(*this);
    *this+=1;
    return auxiliar;
}

Fecha& Fecha::operator --()
{
    return *this+=-1;
}

Fecha Fecha::operator --(int aux)
{   
    Fecha auxiliar(*this);
    *this+=-1;
    return auxiliar;
}


Fecha Fecha::operator + (int sum_dias) const
{
    Fecha Faux(*this);
    return Faux+=sum_dias;
}

Fecha& Fecha::operator += (int sum_dias)
{
    day += sum_dias;
    tm date = {0};

    date.tm_mday = day;
    date.tm_mon = month - 1;
    date.tm_year = year - 1900;

    mktime(&date);

    if(date.tm_year + 1900 < Fecha::AnnoMinimo || date.tm_year + 1900 > Fecha::AnnoMaximo) throw Fecha::Invalida("Limites de años sobrepasados");
    else
    {
        day = date.tm_mday;
        month = date.tm_mon + 1;
        year = date.tm_year + 1900;
        
        return *this;
    }

}

Fecha Fecha::operator - (int rest_dias) const
{
    Fecha Faux(*this);
    return Faux+= -rest_dias;
}

Fecha& Fecha::operator -= (int rest_dias)
{
    return *this+=-rest_dias;
}

const char* Fecha::cadena () const 
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
    return fecha;
}



ostream& operator <<(ostream& os, const Fecha& F)
{
    os << F.cadena();
    return os;
}

istream& operator >>(istream& is, Fecha& F)
{
    char cad_aux[11];
    is.getline(cad_aux,11);

    try{
        F = Fecha(cad_aux);
    }
    catch(const Fecha::Invalida& e)
    {
        is.setstate(std::ios_base::failbit);
        throw e;
        
    }
    
    return is;
    
}










