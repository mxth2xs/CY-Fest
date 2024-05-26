#ifndef MANAGER_H
#define MANAGER_H

#include "var.h"

//functions for manager mode

// halls
void writeHallsToFile(Hall *halls, int n);
Hall *readHallsFromFile(int *n);
void freeHall(Hall hall);
Hall createConcertHall(int replaceConcert);
void displayHalls(int hallCount, Hall *hallList);
int modifyHalls();

// concerts
Concert *readConcertsFromFile(int *concertCount);
void writeConcertsToFile(Concert *concertList, int concertCount);
int displayConcerts(int concertCount, Concert *concertList, int hallId);
Concert findConcert(int hallId);
void createConcert();
void freeConcert(Concert concert);
int checkConcertOverlap(Concert concert);

int compareDatesInMinutes(Date date1, Date date2);
int checkConcertDuration(Date startDate, Date endDate);
int viewState();

#endif /* MANAGER_H */