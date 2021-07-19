#ifndef RUN_H
#define RUN_H


#include <string>
#include <vector>
#include <sstream>



class Run {
    public : 
        Run();
        virtual ~Run();
        Run(std::string);
        void setRun(std::string);
        std::string getRun();
        int getDv();
        bool validarRun(std::string);
        long int getRunAsNumber();
        void setRunAsString(std::string);
        void setRunAsNumber(long int, int);
        int getDvAsInt();
        char getDvAsChar();
    private : 
        std::string rut;
};



#endif
