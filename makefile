CC = gcc
CFLAGS = -g -Wall -Iheaders

OBJ = main.o \
festivalGoer/bookInPit.o \
festivalGoer/bookInSeated.o \
festivalGoer/bookSeats.o \
festivalGoer/printSeatedMapStatus.o \
festivalGoer/printStatusConcertHall.o \
festivalGoer/isBooked.o \
manager/concerts/createConcert.o \
manager/concerts/saveReadConcert.o \
manager/concerts/displayConcerts.o \
manager/concerts/viewState.o \
manager/concerts/findConcert.o \
manager/halls/createConcertHall.o \
manager/halls/displayHalls.o \
manager/halls/saveReadHalls.o \
utils/dates.o \
utils/testValues.o \
manager/halls/modifyHall.o \

# Target
all: main

# Rule for generating the executable
main: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS) -lm

# Compilation Rules for Source Files
%.o: %.c
	$(CC) -g -c -o $@ $< $(CFLAGS)

# Cleaning rule"
clean:
	rm -f $(OBJ) main
