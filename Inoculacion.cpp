#include "./Inoculacion.h"

Inoculacion::Inoculacion() {

}

Inoculacion::Inoculacion(Dosis dosis, Paciente paciente, Fecha fecha) {
    this -> dosis = dosis;
    this -> paciente = paciente;
    this -> fecha = fecha;
}

Dosis Inoculacion::get_dosis() {
    return this -> dosis;
}

Paciente Inoculacion::get_paciente() {
    return this -> paciente;
}

Fecha Inoculacion::get_fecha() {
    return this -> fecha;
}