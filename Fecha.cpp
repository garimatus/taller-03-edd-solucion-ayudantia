#include "./Fecha.h"



const std::string meses_nombres[12] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};
const int cantidad_dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Fecha::Fecha() {
    
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    
    this -> anyio = now -> tm_year + 1900;
    this ->  mes = now -> tm_mon + 1;
    this ->  dia = now -> tm_mday;
}

Fecha::~Fecha() {
    /* Declarar destructor */
}

void Fecha::setFechaAsNumbers(int anyio, int mes, int dia) {

    if (validarFechaAsNumbers(anyio, mes, dia)) {

        this -> anyio = anyio;

        this -> mes = mes;

        this -> dia = dia;
    }

    else {
        std::cout << "\033[1;31mNo se pudo actualizar la fecha, fecha ingresada inválida.\033[0m" << std::endl;
    }
}

void Fecha::setFechaAsString(std::string fecha) {

    std::stringstream fechastream(fecha);
    std::string item;
    std::vector<std::string> items;
    
    while (getline(fechastream, item, '-')) { items.push_back(item); }

    this -> anyio = stoi(items.at(2));

    std::transform(items.at(1).begin(), items.at(1).end(), items.at(1).begin(),
    [](unsigned char c){ return std::tolower(c); });
    
    for(int i = 0; i < 12; ++i) {
        if (items.at(1) == meses_nombres[i]) {
            this -> mes = i + 1;
            break;
        }
    }

    this -> dia = stoi(items.at(0));
}

bool Fecha::validarFechaAsString(std::string fecha) {

    std::stringstream fechastream(fecha);
    std::string item;
    std::vector<std::string> items;
    
    while (getline(fechastream, item, '-')) { items.push_back(item); }
    
    if (items.size() == 3) {
        
        bool existeMes = false, existeDia = false;
        int i = 0;

        int dia = stoi(items.at(0));
        std::string mes = items.at(1);
        int anyio = stoi(items.at(2));

        std::transform(mes.begin(), mes.end(), mes.begin(),
        [](unsigned char c){ return std::tolower(c); });
        
        for(i; i < 12; ++i) {
            if (mes == meses_nombres[i]) {
                existeMes = true;
                break;
            }
        }

        if (existeMes) {
            
            if(anyio%400 == 0 || (anyio%4 == 0 && anyio%100 != 0) && i == 1) {
                
                if (stoi(items.at(2)) <= 29 && stoi(items.at(2)) > 0) {
                    existeDia = true;
                }

            } else {
                    
                if (dia > 0 && dia <= cantidad_dias[i]) {
                    existeDia = true;
                }
                    
            }
            
            return (existeMes && existeDia);

        } else {
            return false;
        }

    } else {

        return false;
    }
}

bool Fecha::validarFechaAsNumbers(int anyio, int mes, int dia) {

    bool existeDia = false, existeMes = false;

    if (anyio > 0) {
        
        if (mes > 0 && mes <= 12) {

            existeMes = true;

            if(anyio%400 == 0 || (anyio%4 == 0 && anyio%100 != 0)) {
                
                if (dia > 0 && dia <= 29) {
                    existeDia = true;
                }
            } else {
                
                if (dia > 0 && dia <= cantidad_dias[mes-1]) {
                    existeDia = true;
                }
            }    
        }
    }
    
    return (existeDia && existeMes);
}


int Fecha::get_anyio() {
    return this -> anyio;
}


int Fecha::get_mes() {
    return this -> mes;
}

int Fecha::get_dia() {
    return this -> dia;
}

int Fecha::rdn(int y, int m, int d) { /* Rata Die day one is 0001-01-01 */
    if (m < 3)
        y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}