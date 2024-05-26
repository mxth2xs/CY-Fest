#ifndef FESTIVAL_H
#define FESTIVAL_H

#include "var.h"

int bookInPit(Hall hall, Concert *concert);
int bookInSeated(Hall hall, Concert *concert);
void bookSeats(int concertId);
void printSeatedMapStatus(Hall hall, Concert concert, int startRow);
void printStatusConcertHall(Hall hall, Concert concert);
int maxTab(int *tab, unsigned int size);
bool isBooked(Concert concert, int row, int column);

#endif /* FESTIVAL_H */