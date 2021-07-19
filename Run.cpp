
#include "./Run.h"

Run::Run() {
    this -> rut = "\0";
}

Run::~Run() {

}

Run::Run(std::string rut) {

    this -> rut = rut;
}

void Run::setRunAsString(std::string rut) {
    this -> rut = rut;
}

void Run::setRunAsNumber(long int rut, int dv) {
    this -> rut = std::to_string(rut);

    this -> rut = this -> rut + std::to_string(dv);
}

std::string Run::getRun() {
    return this -> rut;
}

int Run::getDvAsInt() {
    
    /* ¡ Convertir el últ. caracter a integer !
    return std::stoi(this -> rut[this -> rut.length()-1]); */
}

char Run::getDvAsChar() {
    char dv = this -> rut[this -> rut.length()-1];
}

bool Run::validarRun(std::string rut) {
    bool validacion = false;
    
    std::stringstream rutstream(rut);
    std::string item;
    std::vector<std::string> items;
    
    while (getline(rutstream, item, '-')) { items.push_back(item); }
   
    if (items.size() == 2) {
 
        long int numero = std::stoi(items.at(0));
        int mod11, dv, dv_calculado, contador = 2, suma = 0;

        if (items.at(1) == "k" || items.at(1) == "K") {
            dv = 10;
        }

        else {
            char c = (items.at(1)[0]);
            
            if (isdigit(c) == 0 || items.at(1).length() != 1)
                return false;
            
            dv = std::stoi(items.at(1));

            if (dv == 0) dv = 11;
        }

        while (numero > 0) {

            int aux = numero % 10;
            
            if (contador < 8) {
                suma = suma + (aux * contador);
            }

            else {
                contador = 2;
                suma = suma + (aux * contador);
            }
            
            numero /= 10;

            contador++;
        }
        
        mod11 = suma % 11;
        dv_calculado = 11 - mod11;
        
        if (dv == dv_calculado) {
            validacion = true;
        }
    }
    
    return validacion;
}

long int Run::getRunAsNumber() {
    
    std::string item;

    while (getline(std::stringstream(this -> rut), item, '-')) { 
        break;
    }

    return std::stoi(item);
}