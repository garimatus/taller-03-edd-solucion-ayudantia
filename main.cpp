#include <iostream>
#include <fstream>


#include "./Fecha.h"
#include "./Run.h"
#include "./Lista.h"
#include "./Inoculacion.h"


// HEADER
void informarFechaActual(Fecha fecha);
int cargarBaseDeDatos(std::istream& lectura, Lista<Paciente>& BddNoRelacional);
void resultadoCargaDeDatosPacientes(Lista<Paciente> LLS2, bool todos);
void crearDosis(Lista<Dosis>& listaDosis);
void iniciarVacunacion(Lista<Inoculacion>& listaInoculacion, Lista<Paciente>& listaPaciente, Lista<Dosis>& listaDosis, Fecha hoy);
void consultarPaciente(Lista<Paciente> listaPaciente, Lista<Inoculacion> listaInoculacion);

struct Stock {
    const char* tipo;
    int cantidad;
    int min;
    int max;
};

const Stock stock[3] = {{"Sinovac", 90, 18, 80}, {"Pfizer", 120, 15, 55}, {"AstraZeneca", 70, 18, 420}};

int main(int argc, char** argv) {
    
    Fecha hoy;
    std::ifstream lectura;
    
    lectura.open("pacientes.csv.txt", std::ios_base::in);

    if (lectura) {

        Lista<Inoculacion> LLS1;
        Lista<Paciente> LLS2;
        Lista<Dosis> LLS3;
        int cantidadPacientes = 0;

        std::cout << "\n\033[1;32mArchivo encontrado.\033[0m" << std::endl;

        /**
         * (a) Informar fecha actual:
         */
        informarFechaActual(hoy);

        /**
         * (b) Cargar base de de datos de pacientes:
         */
        cantidadPacientes += cargarBaseDeDatos(lectura, LLS2);

        
        if (cantidadPacientes) {
            
            std::cout << "\033[1;32m" << cantidadPacientes << " Pacientes válidos para la vacunación el proceso de vacunación hoy : \033[0m\n" << std::endl;
            
            /**
             * (c) Resultado de carga de datos pacientes:
             */
            resultadoCargaDeDatosPacientes(LLS2, true);


            /**
             * (d) Crear dosis:
             */
            crearDosis(LLS3);


            /**
             * (e) Iniciar vacunación:
             */
            iniciarVacunacion(LLS1, LLS2, LLS3, hoy);
            //resultadoCargaDeDatosPacientes(LLS2);

            /**
             * (f) Consultar paciente
             */
            consultarPaciente(LLS2, LLS1);


            /**
             * (g) Pacientes no vacunados
             */
            resultadoCargaDeDatosPacientes(LLS2, false);


        } else {
            std::cout << "\033[1;31m" << cantidadPacientes << " Pacientes válidos para la vacunación.\033[0m" << std::endl;
        }

    } else {
        
        std::cout << "\033[1;31mNo se pudo leer el archivo necesario para la ejecución.\033[0m" << std::endl;
        return 1;
    }

    return 0;
}

void informarFechaActual(Fecha fecha) {
    std::cout << std::endl;
    std::cout << "\033[1;34mLa fecha de hoy es : " << fecha.get_dia() << "/" << fecha.get_mes() << "/" << fecha.get_anyio() << "\033[0m" << std::endl;
    std::cout << std::endl;
}

int cargarBaseDeDatos(std::istream& lectura, Lista<Paciente>& BddNoRelacional) {
    
    int count = 0;
    std::string linea;

    for (linea; getline(lectura, linea, '\n');) {

        int columnaNumero = 0;
        bool validacion = true;
        std::stringstream lineastream(linea);
        Fecha fechaNacimiento;
        Run rut;
        std::string columna, genero, apellidos, nombres, fecha;

        for (columna; getline(lineastream, columna, ',');) {
            
            if (columnaNumero == 0) {
                
                if (rut.validarRun(columna)) {
                    rut.setRunAsString(columna);
                } else {
                    validacion = false;
                    break;
                }
            }

            if (columnaNumero == 1) {
                apellidos = columna;
            }

            if (columnaNumero == 2) {
                apellidos = apellidos + " " + columna;
            }

            if (columnaNumero == 3) {
                nombres = columna;
            }

            if (columnaNumero == 4) {
                if (columna == "f" || columna == "h") {
                    genero = columna;
                } else {
                    validacion = false;
                    break;
                }
            }

            if (columnaNumero == 5) {
                if (fechaNacimiento.validarFechaAsString(columna)) {
                    fechaNacimiento.setFechaAsString(columna);
                    
                } else {
                    validacion = false;
                    break;
                }
            }

            ++columnaNumero;
        }
        
        if (validacion) {
            Paciente paciente(fechaNacimiento, rut, nombres, apellidos, genero);
            BddNoRelacional.add_nodo(paciente);
            ++count;
        }
    }

    return count;
}

void resultadoCargaDeDatosPacientes(Lista<Paciente> LLS2, bool todos) {

    nodo<Paciente>* L = LLS2.get_cabeza();
    
    std::cout << "  RUN   |   APELLIDOS   |   NOMBRES   |   EDAD   |   SEXO   |   D.O.B.   |   VACUNADO   " << '\n' << std::endl;
    
    while(L != NULL) {
        
        if (L -> instancia.get_inoculacion() || todos) {
            std::cout
            << L -> instancia.get_run().getRun() << " | "
            << L -> instancia.get_apellidos() << " | "
            << L -> instancia.get_nombres() << " | "
            << L -> instancia.edad() << " | "
            << L -> instancia.get_genero() << " | "
            << L -> instancia.get_nacimiento().get_dia() << "/"
            << L -> instancia.get_nacimiento().get_mes() << "/"
            << L -> instancia.get_nacimiento().get_anyio() << " | ";
            if (L -> instancia.get_inoculacion()) { std::cout << "Sí\n"; }
            else { std::cout << "No\n"; }
            std::cout << std::endl;
        }

        
        L = L -> sgte;
    }
}


void crearDosis(Lista<Dosis>& listaDosis) {

    long int numero_de_serie = 10000;

    for (int i = 0; i < stock[0].cantidad; ++i) {

        numero_de_serie += 3;
        
        Dosis instanciaSinovac(stock[0].tipo, stock[0].min, stock[0].max, numero_de_serie);
        
        listaDosis.add_nodo(instanciaSinovac);
    }

    for (int i = 0; i < stock[1].cantidad; ++i) {
        
        numero_de_serie += 7;
        
        Dosis instanciaPfizer(stock[1].tipo, stock[1].min, stock[1].max, numero_de_serie);
        
        listaDosis.add_nodo(instanciaPfizer);

    }

    for (int i = 0; i < stock[2].cantidad; ++i) {
        
        numero_de_serie += 5;
        
        Dosis instanciaAstraZeneca(stock[2].tipo, stock[2].min, stock[2].max, numero_de_serie);
        
        listaDosis.add_nodo(instanciaAstraZeneca);

    }
}

void iniciarVacunacion(Lista<Inoculacion>& listaInoculacion, Lista<Paciente>& listaPaciente, Lista<Dosis>& listaDosis, Fecha hoy) {

    nodo<Dosis>* nodoDosis = listaDosis.get_cabeza();

    int countSinovac = 0;
    int countPfizer = 0;
    int countAstraZeneca = 0;
    
    
    while (nodoDosis != NULL) {

        bool disponibilidadDosis = nodoDosis -> instancia.get_disponibilidad();
        Dosis instanciaDosis = nodoDosis -> instancia;
        nodo<Paciente>* nodoPaciente = listaPaciente.get_cabeza();
        Paciente instanciaPaciente;
        
        while (nodoPaciente != NULL) {

            if (!nodoPaciente -> instancia.get_inoculacion()) {

                int edadPaciente = nodoPaciente -> instancia.edad();
                char sexo = nodoPaciente -> instancia.get_genero();
                
                if (edadPaciente >= 15) {

                    if (edadPaciente <= 55 && instanciaDosis.get_tipo() == "Sinovac") {
                        
                        disponibilidadDosis = false;
                        nodoPaciente -> instancia.set_inoculacion(true);
                        instanciaPaciente = nodoPaciente -> instancia;
                        ++countSinovac;
                        break;
                    }

                    if (edadPaciente <= 80 && instanciaDosis.get_tipo() == "Pfizer") {
                        
                        disponibilidadDosis = false;
                        nodoPaciente -> instancia.set_inoculacion(true);
                        instanciaPaciente = nodoPaciente -> instancia;
                        ++countPfizer;
                        break;
                    }

                    if (instanciaDosis.get_tipo() == "AstraZeneca") {
                       
                        if (sexo == 'f') {

                            if (edadPaciente > 41) {
                                
                                disponibilidadDosis = false;
                                nodoPaciente -> instancia.set_inoculacion(true);
                                instanciaPaciente = nodoPaciente -> instancia;
                                ++countAstraZeneca;
                                break;
                            }

                        } else {

                            if (edadPaciente >= 18) {
                                
                                disponibilidadDosis = false;
                                nodoPaciente -> instancia.set_inoculacion(true);
                                instanciaPaciente = nodoPaciente -> instancia;
                                ++countAstraZeneca;
                                break;
                            }
                        }
                    }
                }
            }
            
            nodoPaciente = nodoPaciente -> sgte;
        }

        if (!disponibilidadDosis) {
            
            instanciaPaciente.set_inoculacion(true);
            instanciaDosis.set_disponibilidad(disponibilidadDosis);
            Inoculacion instancia(instanciaDosis, instanciaPaciente, hoy);
            listaInoculacion.add_nodo(instancia);
        }

        nodoDosis = nodoDosis -> sgte;
    }

    std::cout << "Resultados del proceso de vacunación : " << std::endl;
    std::cout << "Cantidad de personas vacunadas con Sinovac : " << countSinovac << std::endl;
    std::cout << "Cantidad de personas vacunadas con Pfizer : " << countPfizer << std::endl;
    std::cout << "Cantidad de personas vacunadas con AstraZeneca : " << countAstraZeneca << std::endl;
    std::cout << std::endl;
    std::cout << "Cantidad de vacunas Sinovac disponibles : " << stock[0].cantidad - countSinovac << std::endl;
    std::cout << "Cantidad de vacunas Pfizer disponibles : " << stock[1].cantidad - countPfizer << std::endl;
    std::cout << "Cantidad de vacunas AstraZeneca disponibles : " << stock[2].cantidad - countAstraZeneca << std::endl;
    std::cout << std::endl;
}


void consultarPaciente(Lista<Paciente> listaPaciente, Lista<Inoculacion> listaInoculacion) {

    std::string rut;
    Run instancia;
    nodo<Paciente>* nodoPaciente = listaPaciente.get_cabeza();;
    std::cout << "Ingrese RUN del paciente a consultar : ";
    std::cin >> rut;
    bool existePaciente = false, existeInoculacion = false;

    if (instancia.validarRun(rut)) {

        instancia.setRunAsString(rut);
        
        while (nodoPaciente != NULL) {
            
            if (instancia.getRun() == nodoPaciente -> instancia.get_run().getRun()) {

                existePaciente = true;

                nodo<Inoculacion>* nodoInoculacion = listaInoculacion.get_cabeza();

                while (nodoInoculacion != NULL) {

                    if (nodoInoculacion -> instancia.get_paciente().get_run().getRun() == instancia.getRun()) {

                        existeInoculacion = true;
                        Paciente instanciaPaciente = nodoInoculacion -> instancia.get_paciente();
                        Dosis instanciaDosis = nodoInoculacion -> instancia.get_dosis();
                        
                        std::cout << std::endl;
                        std::cout << "=== DATOS DEL PACIENTE INOCULADO ===" << std::endl;
                        std::cout << "RUN : " << instanciaPaciente.get_run().getRun() << std::endl;
                        std::cout << "APELLIDOS : " << instanciaPaciente.get_apellidos() << std::endl;
                        std::cout << "NOMBRES : " << instanciaPaciente.get_nombres() << std::endl;
                        std::cout << "EDAD : " << instanciaPaciente.edad() << std::endl;
                        std::cout << "SEXO : " << instanciaPaciente.get_genero() << std::endl;
                        std::cout << "FECHA DE NACIMIENTO : " << instanciaPaciente.get_nacimiento().get_dia() << "/"
                        << instanciaPaciente.get_nacimiento().get_mes() << "/"
                        << instanciaPaciente.get_nacimiento().get_anyio() << " (" <<instanciaPaciente.edad() << " años)" << std::endl;
                        std::cout << "DOSIS : " << instanciaDosis.get_tipo() << std::endl;
                        std::cout << "ID DE DOSIS : " << instanciaDosis.get_id() << std::endl;
                        std::cout << std::endl;

                        break;
                    }

                    nodoInoculacion = nodoInoculacion -> sgte;
                }
            }

            if (existePaciente) {
                break;
            }
            
            nodoPaciente = nodoPaciente -> sgte;
        }

    } else {

        std::cout << "El Run ingresado no es válido." << std::endl;
    }
}

