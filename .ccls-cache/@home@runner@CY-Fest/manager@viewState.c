#include "../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

void viewState(Hall hall) {
  int choice;
  do {
    printf("Do you want to see the ratio of the Hall, the hall state or both? "
           "(1 for Hall, 2 for room state, 3 for both) \n");
    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Please enter 1, 2, or 3.\n");
      choice = -1; // Force retry
    }
  } while (choice != 1 && choice != 2 && choice != 3);

  if (choice == 1) {
    printf("The ratio of the halls %s is: %2f.\n", hall.hallName,
           ((float)hall.nbBookedSeats * 100) / hall.totalSeats);
  } else if (choice == 2) {
    printf("The state of the hall %s is: %u.\n", hall.hallName, hall.hallState);
  } else {
    printf("The state of the hall %s is: %u.\n", hall.hallName, hall.hallState);
    printf("The ratio of the halls %s is: %2f.\n", hall.hallName,
           ((float)hall.nbBookedSeats * 100) / hall.totalSeats);
  }
}