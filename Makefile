


taller03: main.o fecha.o run.o paciente.o dosis.o inoculacion.o
	g++ main.o fecha.o run.o paciente.o dosis.o inoculacion.o -o taller03
	rm -fr *.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

fecha.o: Fecha.cpp Fecha.h
	g++ -c Fecha.cpp -o fecha.o

run.o: Run.cpp Run.h
	g++ -c Run.cpp -o run.o

paciente.o: Paciente.cpp Paciente.h
	g++ -c Paciente.cpp -o paciente.o

dosis.o: Dosis.cpp Dosis.h
	g++ -c Dosis.cpp -o dosis.o

inoculacion.o: Inoculacion.cpp Inoculacion.h
	g++ -c Inoculacion.cpp -o inoculacion.o

clean:
	rm -fr *.o