#ifndef DOSIS_H
#define DOSIS_H

#include <string>


struct Stock {
    const char* tipo;
    int cantidad;
    int min;
    int max;
};

const Stock stock[3] = {{"Sinovac", 90, 18, 80}, {"Pfizer", 120, 15, 55}, {"AstraZeneca", 70, 18, 420}};

class Dosis {
    private :
        std::string tipo;
        int edad_min;
        int edad_max;
        long int id;
        bool disponibilidad;
    public :
        Dosis();
        Dosis(const char*, int, int, long int);
        virtual ~Dosis();
        void set_tipo(const char*);
        void set_edad_min(int);
        void set_edad_max(int);
        void set_id(long int);
        void set_disponibilidad(bool);
        std::string get_tipo();
        int get_edad_min();
        int get_edad_max();
        long int get_id();
        bool get_disponibilidad();
};

#endif