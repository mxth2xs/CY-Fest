CC = gcc
CFLAGS = -Iinclude

# Liste des fichiers objets
OBJ = main.o manager/displayHalls.c manager/createConcertHall.o manager/modifyConcertHall.o manager/viewState.o modeFestivalGoer.o utility.o utils/saveReadHalls.o

# Cible par défaut
all: main

# Règle pour générer l'exécutable
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

# Règles de compilation des fichiers sources
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Règle de nettoyage
clean:
	rm -f *.o main
