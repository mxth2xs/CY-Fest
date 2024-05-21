#ifndef VAR_H
#define VAR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <stdbool.h>

//----------------------
//      CONSTANT
//----------------------
#define CHAR_MAX_LENGTH 100
#define NB_CATEGORY 3
#define MAX_HALLS 10

#define color(param) printf("\033[%sm", param)

//----------------------
//        STRUCT
//----------------------

typedef enum { Empty, Partial, Full } HallState;

typedef struct {
  char hallName[CHAR_MAX_LENGTH];
  int nbRowsTotal;
  int *seatsPerRow;                 // seatsPerRow[nbRowsTotal]
  int numRowsCategory[NB_CATEGORY]; // number of rows per category (A,B,C)
  float price[NB_CATEGORY];
  int nbBookedSeats;
  HallState hallState;
  int totalSeats;
  int **hallMap;
  int pit;     // True if have, False if not
  int endTime; // current state of the hall
} Hall;

//----------------------
//        FUNCT
//----------------------

void writeHallsToFile(Hall *halls, int n);
Hall *readHallsFromFile(int *n);
int testValues(int a, int b, int x);
void freeHall(Hall hall);
Hall modifyConcertHall(Hall h);
Hall createConcertHall();
void displayHalls(int hallCount, Hall *hallList);

// void printComingConcert(Hall *hall) {}
// void printStatusHall(Hall hall) {}
// void bookSeats(Hall hall) {}

// Hall createConcertHall() {}
// Hall modifyConcertHall(Hall h) {}
// void viewState (Hall hall){}

#endif /* VAR_H */