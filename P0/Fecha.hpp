#ifndef FECHA_HPP
#define FECHA_HPP

class Fecha{
public:
    Fecha(int d = 0, int m = 0, int y = 0); //Constructor de conversion
    Fecha(const Fecha&); //Constructor de copia
    Fecha(const char*); //Constructor de conversion
    void por_que(); //Metodo para errores
    void dia() const;
    void mes() const;
    void anno() const;

private:
    int day;
    int month;
    int year;
};

#endif