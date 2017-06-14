all : compact_2.o fonctions.o
	gcc -Wall -pedantic compact_2.o fonctions.o -o compact_2

fonctions.o : fonctions.c
	gcc -c -Wall -pedantic fonctions.c -o fonctions.o

compact_2.o : compact_2.c fonctions.h
	gcc -c -Wall -pedantic compact_2.c -o compact_2.o
