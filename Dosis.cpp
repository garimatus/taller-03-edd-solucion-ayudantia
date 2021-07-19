#include "./Dosis.h"


Dosis::Dosis() {
    
}

Dosis::Dosis(const char* tipo, int min, int max, long int id) {

    this -> tipo = std::string(tipo);
    this -> edad_min = min;
    this -> edad_max = max;
    this -> id = id;
    this -> disponibilidad = true;
}

Dosis::~Dosis() {

}

void Dosis::set_tipo(const char* tipo) {
    this -> tipo = std::string(tipo);
}

void Dosis::set_edad_min(int edad) {
    this -> edad_min = edad;
}

void Dosis::set_edad_max(int edad) {
    this -> edad_max = edad;
}

void Dosis::set_id(long int id) {
    this -> id = id;
}

void Dosis::set_disponibilidad(bool disponibilidad) {
    this -> disponibilidad = disponibilidad;
}

std::string Dosis::get_tipo() {
    return this -> tipo;
}

int Dosis::get_edad_min() {
    return this -> edad_min;
}

int Dosis::get_edad_max() {
    return this -> edad_max;
}

long int Dosis::get_id() {
    return this -> id;
}

bool Dosis::get_disponibilidad() {
    return this -> disponibilidad;
}