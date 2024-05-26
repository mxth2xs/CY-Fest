#include "../../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

/**
 * View the state of a concert hall.
 *
 * @param hall ConcertHall structure to view the state of.
 */
void viewState() {

  int hallCount;
  int choice;
  int hallId;

  Hall *hallList;
  hallList = readHallsFromFile(&hallCount); // List of halls
  Hall choosedHall;

  do {
    color(BOLD);
    printf("Enter the ID of the hall you want to modify: \n");
    color(RESET);
  } while (!testValues(1, hallCount, &hallId));
  printf("\e[1;1H\e[2J");

  Concert concert = findConcert(hallId);
  choosedHall = hallList[hallId - 1];

  do {
    color(BOLD);
    printf("Do you want to see the ratio of the concert, the concert state or "
           "both? "
           "(1 for the ratio, 2 for the state , 3 for both) \n");
    color(RESET);
  } while (!testValues(1, 3, &choice));

  // Options
  if (choice == 1) {
    printf("The ratio of the concert %s is: %2f.\n", concert.concertName,
           ((float)concert.nbBookedSeats * 100) /
               choosedHall.totalSeats); // force the nbBookedSeats to be a float
  } else if (choice == 2) {
    printf("The state of the concert %s is: %u.\n", concert.concertName,
           concert.hallState);
  } else {
    printf("The state of the cooncert %s is: %u.\n", concert.concertName,
           concert.hallState);
    printf("The ratio of the concert %s is: %2f.\n", concert.concertName,
           ((float)concert.nbBookedSeats * 100) / choosedHall.totalSeats);
  }
}