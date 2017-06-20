fonctions.o : fonctions.c
	gcc -g -c -Wall -pedantic fonctions.c -o fonctions.o

fonctions_2.o : fonctions_2.c
	gcc -g -c -Wall -pedantic fonctions_2.c -o fonctions_2.o

compact_2.o : compact_2.c fonctions.h
	gcc -g -c -Wall -pedantic compact_2.c -o compact_2.o

all : compact_2.o fonctions.o fonctions_2.o
	gcc -g -Wall -pedantic compact_2.o fonctions.o fonctions_2.o -o compact_2
