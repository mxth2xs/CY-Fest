#include "include/var.h"
#include <stdio.h>
#include <stdlib.h>

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

//----------------------
//     Manager Mode
//----------------------

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

Hall createConcertHall() {

  Hall h;
  h.totalSeats = 0;
  h.nbRowsTotal = 0;

  //----------------------
  //      Hall Name 
  //----------------------

  printf("Enter the name of the hall: \n");
  scanf("%s", h.hallName);

  //----------------------
  // Hall Rows & seat prices 
  //----------------------

  do {
    printf("Enter the total number of rows: \n");
    if (scanf("%d", &h.nbRowsTotal) != 1) {
      printf("Invalid input. Please enter a number.\n");
      h.nbRowsTotal = -1; // Force retry
    }
  } while (!testValues(1, 512, h.nbRowsTotal));

  //----------------------
  //   Memory Allocation
  //----------------------

  h.seatsPerRow = malloc(h.nbRowsTotal * sizeof(int));
  if (h.seatsPerRow == NULL) {
    printf("Memory allocation failed for seatsPerRow.\n");
    exit(1);
  }

  int **hallMap = malloc(h.nbRowsTotal * sizeof(int *));
  if (hallMap == NULL) {
    printf("Memory allocation failed for hallMap.\n");
    exit(1);
  }

  //----------------------
  // Get the number of rows in Category, end time etc...
  //----------------------

  h = modifyConcertHall(h);

  //----------------------
  // Number of seats in rows 
  //----------------------

  int currentRow = 0;
  for (int z = 0; z < 3; z++) {
    for (int i = 0; i < h.numRowsCategory[z]; i++) {
      do {
        printf("What is the number of seats in the row %d, in zone %c \n", i + 1, zones[z]);
        if (scanf("%d", &h.seatsPerRow[currentRow]) != 1) {
          printf("Invalid input. Please enter a number.\n");
          h.seatsPerRow[currentRow] = -1; // Force retry
        }
      } while (!testValues(1, 512, h.seatsPerRow[currentRow]));

      hallMap[currentRow] = malloc(h.seatsPerRow[currentRow] * sizeof(int));
      if (hallMap[currentRow] == NULL) {
        printf("Memory allocation failed for hallMap row %d.\n", currentRow);
        exit(1);
      }

      for (int j = 0; j < h.seatsPerRow[currentRow]; j++) {
        hallMap[currentRow][j] = 0; // 0 for empty
        h.totalSeats++;
      }
      currentRow++;
    }
  }

  //----------------------
  //      Save Hall
  //----------------------
  int *n = 0;
  Hall *hallList = readHallsFromFile(n);
  *(hallList + *n) = h;
  writeHallsToFile(hallList, *n + 1);

  return h;
}

void viewState(Hall hall) {
  int choice;
  do {
    printf("Do you want to see the ratio of the Hall, the hall state or both? (1 for Hall, 2 for room state, 3 for both) \n");
    if (scanf("%d", &choice) != 1) {
      printf("Invalid input. Please enter 1, 2, or 3.\n");
      choice = -1; // Force retry
    }
  } while (choice != 1 && choice != 2 && choice != 3);

  if (choice == 1) {
    printf("The ratio of the halls %s is: %2f.\n", hall.hallName, ((float)hall.nbBookedSeats * 100) / hall.totalSeats);
  } else if (choice == 2) {
    printf("The state of the hall %s is: %u.\n", hall.hallName, hall.hallState);
  } else {
    printf("The state of the hall %s is: %u.\n", hall.hallName, hall.hallState);
    printf("The ratio of the halls %s is: %2f.\n", hall.hallName, ((float)hall.nbBookedSeats * 100) / hall.totalSeats);
  }
}
