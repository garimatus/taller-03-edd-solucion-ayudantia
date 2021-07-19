#ifndef FECHA_H
#define FECHA_H

#include <string>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctype.h>



class Fecha {
    private : 
        int anyio;
        int mes;
        int dia;

    public : 
        Fecha();
        virtual ~Fecha();
        void setFechaAsNumbers(int, int, int);
        void setFechaAsString(std::string);
        bool validarFechaAsNumbers(int, int, int);
        bool validarFechaAsString(std::string);
        int rdn(int, int, int);
        int get_anyio();
        int get_mes();
        int get_dia();
};


#endif