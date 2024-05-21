#include "../include/var.h"

char zones[3] = {'A', 'B', 'C'};
Hall modifyConcertHall(Hall h) {

  //----------------------
  // Change Category
  //----------------------

  do {
    for (int i = 0; i < 2; i++) {
      do {
        printf("How many rows are in the zone %c \n", zones[i]);
        if (scanf("%u", &h.numRowsCategory[i]) != 1) {
          printf("Invalid input. Please enter a number.\n");
          h.numRowsCategory[i] = -1; // Force retry
        }
      } while (!testValues(0, 512, h.numRowsCategory[i]));
      do {
        printf("What is the price for a seat in zone %c \n", zones[i]);
        if (scanf("%f", &h.price[i]) != 1) {
          printf("Invalid input. Please enter a valid price.\n");
          h.price[i] = -1; // Force retry
        }
      } while (!testValues(0, 512, h.price[i]));
    }

    //----------------------
    // Category C
    //----------------------

    h.numRowsCategory[2] = h.nbRowsTotal - (h.numRowsCategory[0] + h.numRowsCategory[1]);
    if (h.numRowsCategory[2] < 0) {
      printf("You entered more rows than the total number of rows. Please, try again.\n");
    }
  } while (h.numRowsCategory[2] < 0);

  //----------------------
  // Change pit
  //----------------------

  do {
    printf("Is there a Pit in the zone A (0 for no, 1 for yes)? \n");
    if (scanf("%d", &h.pit) != 1) {
      printf("Invalid input. Please enter 0 or 1.\n");
      h.pit = -1; // Force retry
    }
  } while (!testValues(0, 1, h.pit));

  //----------------------
  //      Concert End 
  //----------------------

  do {
    printf("When does the concert end? (between 00 and 23) \n");
    if (scanf("%d", &h.endTime) != 1) {
      printf("Invalid input. Please enter a number between 00 and 23.\n");
      h.endTime = -1; // Force retry
    }
  } while (!testValues(0, 23, h.endTime));

  h.hallState = Empty;
  h.nbBookedSeats = 0;

  return h;
}
