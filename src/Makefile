#MAKEFILE PARA PROJECTO AED KAKURO, COMPATIVEL COM VERSÃO v16.9 

#-----------------------argumentos
CFLAGS= -Wall -ansi

#-----------------------compilação
main: main.o input.o metGauss.o resolution.o solFinder.o error.o output.o
	gcc $(CFLAGS) input.o metGauss.o resolution.o solFinder.o error.o output.o main.o -o crosssums -lm
#-----------------------criação ficheiros objecto

#-------------para o main
main.o: main.c defs.h
	gcc $(CFLAGS) -c main.c 

#-------------resto dos headers

input.o: input.c input.h
	gcc $(CFLAGS) -c input.c

metGauss.o: metGauss.c metGauss.h
	gcc $(CFLAGS) -c metGauss.c

resolution.o: resolution.c resolution.h
	gcc $(CFLAGS) -c resolution.c

solFinder.o: solFinder.c solFinder.h
	gcc $(CFLAGS) -c solFinder.c

output.o: output.c output.h
	gcc $(CFLAGS) -c output.c

error.o: error.c error.h
	gcc $(CFLAGS) -c error.c

#clean:
#	rm -f *.o *.~ main *.gch

