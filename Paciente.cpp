
#include "./Paciente.h"



Paciente::Paciente() {

}

Paciente::Paciente(Fecha nacimiento, Run rut, std::string nombres, std::string apellidos, std::string genero) {
    
    
    this -> nacimiento = nacimiento;
    this -> rut = rut;
    this -> nombres = nombres;
    this -> apellidos = apellidos;
    this -> genero = genero[0];
    
    Fecha hoy;

    this -> age = (hoy.rdn(hoy.get_anyio(), hoy.get_mes(), hoy.get_dia()) - hoy.rdn(nacimiento.get_anyio(), nacimiento.get_mes(), nacimiento.get_dia())) / 365;

    this -> inoculacion = false;
}

std::string Paciente::get_nombres() {
    return this -> nombres;
}

std::string Paciente::get_apellidos() {
    return this -> apellidos;
}

int Paciente::edad() {
    return this -> age;
}

Run Paciente::get_run() {
    return this -> rut;
}

Fecha Paciente::get_nacimiento() {
    return this -> nacimiento;
}

char Paciente::get_genero() {
    return this -> genero;
}

void Paciente::set_inoculacion(bool inoculacion) {
    this -> inoculacion = inoculacion;
}

bool Paciente::get_inoculacion() {
    return this -> inoculacion;
}