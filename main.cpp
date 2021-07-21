#include <iostream>
#include <fstream>


#include "./Fecha.h"
#include "./Run.h"
#include "./Lista.h"
#include "./Inoculacion.h"


// Header (Estas funciones están debajo de main).
void informarFechaActual(Fecha);
int cargarBaseDeDatos(std::istream&, Lista<Paciente>&);
void resultadoCargaDeDatosPacientes(Lista<Paciente>, bool);
void crearDosis(Lista<Dosis>&);
void iniciarVacunacion(Lista<Inoculacion>&, Lista<Paciente>&, Lista<Dosis>&, Fecha);
void consultarPaciente(Lista<Paciente>, Lista<Inoculacion>);



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
            return 1;
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
                
                if (!rut.setRunAsString(columna)) {
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
    
    std::cout << "\033[1;34m RUN | APELLIDOS | NOMBRES | EDAD | SEXO | D.O.B. | INOCULADO/A \033[0m" << std::endl;
    
    while(L != NULL) {
        
        if (L -> instancia.get_inoculacion() || todos) {
            std::cout << "\033[1;34m_____________________________________________________________________________\033[0m" << std::endl;
            std::cout
            << "\033[1;32m" << L -> instancia.get_run().getRun() << "\033[0m \033[1;34m | \033[0m"
            << "\033[1;32m" << L -> instancia.get_apellidos() << "\033[0m \033[1;34m | \033[0m"
            << "\033[1;32m" << L -> instancia.get_nombres() << "\033[0m \033[1;34m | \033[0m"
            << "\033[1;32m" << L -> instancia.edad() << "\033[0m \033[1;34m | \033[0m"
            << "\033[1;32m" << L -> instancia.get_genero() << "\033[0m \033[1;34m | \033[0m"
            << "\033[1;32m" << L -> instancia.get_nacimiento().get_dia() << "/"
            << "\033[1;32m" << L -> instancia.get_nacimiento().get_mes() << "/"
            << "\033[1;32m" << L -> instancia.get_nacimiento().get_anyio() << "\033[0m \033[1;34m | \033[0m";
            if (L -> instancia.get_inoculacion()) { std::cout << "\033[1;32m Sí \033[0m" << std::endl; }
            else { std::cout << "\033[1;31m No \033[0m" << std::endl; }
        }

        L = L -> sgte;
    }
    
    std::cout << std::endl;
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

    int countSinovac = 0, countPfizer = 0, countAstraZeneca = 0;
    int count0 = 0, count19 = 0, count25 = 0, count35 = 0, count45 = 0, count65 = 0;
    
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

            if (instanciaPaciente.edad() <= 18)
                ++count0;
            
            if (instanciaPaciente.edad() >= 19 && instanciaPaciente.edad() <= 24)
                ++count19;
            
            if (instanciaPaciente.edad() >= 25 && instanciaPaciente.edad() <= 34)
                ++count25;
                
            if (instanciaPaciente.edad() >= 35 && instanciaPaciente.edad() <= 44)
                ++count35;
                
            if (instanciaPaciente.edad() >= 45 && instanciaPaciente.edad() <= 64)
                ++count45;
                
            if (instanciaPaciente.edad() >= 65)
                ++count65;
        }

        nodoDosis = nodoDosis -> sgte;
    }

    std::cout << "\033[1;34m========= ESTADÍSTICOS DEL PROCESO DE VACUNACÓN =========" << std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas con Sinovac :\033[0m \033[1;32m" << countSinovac << "\033[0m" << std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas con Pfizer :\033[0m \033[1;32m" << countPfizer << "\033[0m" << std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas con AstraZeneca :\033[0m \033[1;32m" << countAstraZeneca << "\033[0m" << std::endl;
    std::cout << "\033[1;34m---------------------------------------------------------" << std::endl;
    std::cout << "\033[1;34mCantidad de vacunas Sinovac disponibles :\033[0m \033[1;32m" << stock[0].cantidad - countSinovac << "\033[0m" << std::endl;
    std::cout << "\033[1;34mCantidad de vacunas Pfizer disponibles :\033[0m \033[1;32m" << stock[1].cantidad - countPfizer << "\033[0m" << std::endl;
    std::cout << "\033[1;34mCantidad de vacunas AstraZeneca disponibles :\033[0m \033[1;32m" << stock[2].cantidad - countAstraZeneca << "\033[0m" << std::endl;
    std::cout << "\033[1;34m---------------------------------------------------------" << std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas de entre 0 a 18 años :\033[0m \033[1;32m" << count0 << "\033[0m" <<std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas de entre 19 a 24 años :\033[0m \033[1;32m" << count19 << "\033[0m" <<std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas de entre 25 a 34 años :\033[0m \033[1;32m" << count25 << "\033[0m" <<std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas de entre 35 a 44 años :\033[0m \033[1;32m" << count35 << "\033[0m" <<std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas de entre 45 a 64 años :\033[0m \033[1;32m" << count45 << "\033[0m" <<std::endl;
    std::cout << "\033[1;34mCantidad de personas vacunadas de entre 65 o más :\033[0m " << "\033[1;32m" << count65 << "\033[0m" <<std::endl;
    std::cout << "\033[1;34m=========================================================\033[0m" << std::endl;
    std::cout << std::endl;
}


void consultarPaciente(Lista<Paciente> listaPaciente, Lista<Inoculacion> listaInoculacion) {

    std::string rut;
    Run instancia;
    nodo<Paciente>* nodoPaciente = listaPaciente.get_cabeza();;
    std::cout << "Ingrese RUN del paciente a consultar : ";
    std::cin >> rut;
    bool existePaciente = false, existeInoculacion = false;

    if (instancia.setRunAsString(rut)) {

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
                        std::cout << "\033[1;34m===== DATOS DE EL/LA PACIENTE INOCULADO/A =====\033[0m" << std::endl;
                        std::cout << "\033[1;34mRUN :\033[0m \033[1;32m" << instanciaPaciente.get_run().getRun() << "\033[0m" << std::endl;
                        std::cout << "\033[1;34mAPELLIDOS :\033[0m \033[1;32m" << instanciaPaciente.get_apellidos() << "\033[0m" << std::endl;
                        std::cout << "\033[1;34mNOMBRES :\033[0m \033[1;32m" << instanciaPaciente.get_nombres() << "\033[0m" << std::endl;
                        std::cout << "\033[1;34mEDAD :\033[0m \033[1;32m" << instanciaPaciente.edad() << "\033[0m" << std::endl;
                        std::cout << "\033[1;34mSEXO :\033[0m \033[1;32m" << instanciaPaciente.get_genero() << "\033[0m" << std::endl;
                        std::cout << "\033[1;34mFECHA DE NACIMIENTO : \033[1;32m" << instanciaPaciente.get_nacimiento().get_dia() << "/"
                        << instanciaPaciente.get_nacimiento().get_mes() << "/"
                        << instanciaPaciente.get_nacimiento().get_anyio() << " (" <<instanciaPaciente.edad() << " años)" "\033[0m" << std::endl;
                        std::cout << "\033[1;34mDOSIS :\033[0m \033[1;32m" << instanciaDosis.get_tipo() << "\033[0m" << std::endl;
                        std::cout << "\033[1;34mID DE DOSIS :\033[0m \033[1;32m " << instanciaDosis.get_id() << "\033[0m" << "\033[0m" << std::endl;
                        std::cout << "\033[1;34m===============================================\033[0m" << std::endl;
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

        if (!existePaciente) {
            
            std::cout << std::endl;
            std::cout << "\033[1;31mEl/la paciente ingresado/a no existe dentro de los registros.\033[0m" << std::endl;
            std::cout << std::endl;
            
        } else {
            
            if (!existeInoculacion) {
                std::cout << std::endl;
                std::cout << "\033[1;31mEl/la paciente ingresado/a no ha sido vacunado/a.\033[0m" << std::endl;
                std::cout << std::endl;
            }    
        }
        
    } else {
        std::cout << std::endl;
        std::cout << "\033[1;31mEl Run ingresado no es válido.\033[0m" << std::endl;
        std::cout << std::endl;
    }
    
    char c;
    std::cout << "Ingrese cualquier caracter y presione Enter para continuar ..." << std::endl;
    std::cin >> c;
    std::cout << std::endl;
}
