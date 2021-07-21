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
        long int getRunAsNumber();
        bool setRunAsString(std::string);
        bool setRunAsNumber(long int, int);
        int getDvAsInt();
        char getDvAsChar();
    private : 
        std::string rut;
        bool validarRun(std::string);
};



#endif
