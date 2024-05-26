#include <stdio.h>
#include "../../headers/var.h"
#include "../../headers/manager.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

/**
 * View the state of a concert hall.
 *
 * @param hall ConcertHall structure to view the state of.
 */
void viewState() {

  //define variables
  int hallCount;
  int choice;
  int hallId;

  Hall *hallList;
  Hall choosedHall;
  const char *state[] = {"Empty", "Partial", "Full"};
  hallList = readHallsFromFile(&hallCount); // List of halls
  
  
  do {
    color(BOLD);
    printf("\nEnter the ID of the hall you want to modify: \n");
    color(RESET);
  } while (!testValues(1, hallCount, &hallId));
  hallId--;
  printf("\e[1;1H\e[2J");

  Concert concert = findConcert(hallId); //use this function to find the right concert
  choosedHall = hallList[hallId - 1]; //hallId - 1 because the users only see the ID start at 1 not 0

  do {
    color(BOLD);
    printf("Do you want to see the ratio of the concert, the concert state or "
           "both? "
           "(1 for the ratio, 2 for the state , 3 for both) \n");
    color(RESET);
  } while (!testValues(1, 3, &choice));


  // Options
  if (choice == 1) {
    printf("\nThe ratio of the concert %s is: %2f.\n\n", concert.concertName,
           ((float)concert.nbBookedSeats * 100) /
               choosedHall.totalSeats); // force the nbBookedSeats to be a float
  } else if (choice == 2) {
    printf("\nThe state of the concert %s is: %s.\n\n", concert.concertName,
           state[concert.hallState]);
  } else {
    printf("\nThe state of the concert %s is: %s.\n", concert.concertName,
      state[concert.hallState]);
    printf("\nThe ratio of the concert %s is: %2f.\n\n", concert.concertName,
           ((float)concert.nbBookedSeats * 100) / choosedHall.totalSeats);
  }
}