#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include "./Fecha.h"
#include "./Run.h"


class Paciente {
    private :
        Fecha nacimiento;
        Run rut;
        std::string nombres;
        std::string apellidos;
        char genero;
        int age;
        bool inoculacion;
    
    public : 
        Paciente();
        Paciente(Fecha, Run, std::string, std::string, std::string);
        std::string get_nombres();
        std::string get_apellidos();
        int edad();
        Run get_run();
        Fecha get_nacimiento();
        char get_genero();
        void set_inoculacion(bool);
        bool get_inoculacion();
};



#endif
