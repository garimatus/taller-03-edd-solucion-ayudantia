#include "./Fecha.h"
#include "./Paciente.h"
#include "./Dosis.h"

class Inoculacion {
    public :
        Inoculacion(Dosis, Paciente, Fecha);
        Inoculacion();
        Dosis get_dosis();
        Paciente get_paciente();
        Fecha get_fecha();
    private :
        Dosis dosis;
        Paciente paciente;
        Fecha fecha;
};


