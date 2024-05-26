#include "../../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

// Create a new hall
Hall modifyConcertHall(int hallId) {

  Hall h;
  h.totalSeats = 0;
  h.nbRowsTotal = 0;

  //----------------------
  //      Hall Name
  //----------------------

  printf("\e[1;1H\e[2J");
  printf("Enter the name of the hall you want to create: \n");
  scanf("%s", h.hallName);

  //----------------------
  //      Hall Rows
  //----------------------

  do {
    printf("Enter the total number of rows: \n");
    if (scanf("%d", &h.nbRowsTotal) != 1) {
      printf("\n");
      h.nbRowsTotal = -1; // Force retry
    }
  } while (!testValues(1, 512, &h.nbRowsTotal));

  //----------------------
  //   Memory Allocation
  //----------------------

  h.seatsPerRow = malloc(h.nbRowsTotal * sizeof(int));
  if (h.seatsPerRow == NULL) {
    printf("Memory allocation failed for seatsPerRow.\n");
    exit(1);
  }

  //----------------------
  // Get the number of seats in Row
  //----------------------

  int currentRow = 0;
  for (int i = 0; i < h.nbRowsTotal; i++) {
    do {
      printf("What is the number of seats in row %d?\n", i + 1);
      if (scanf("%d", &h.seatsPerRow[currentRow]) != 1) {

        h.seatsPerRow[currentRow] = -1; // Force retry
      }
    } while (!testValues(1, 512, &h.seatsPerRow[currentRow]));

    h.totalSeats += h.seatsPerRow[currentRow];
    currentRow++;
  }

  //----------------------
  //      Save Hall
  //----------------------
  int n = 0;
  Hall *hallList =
      readHallsFromFile(&n); // Pass n by reference to get the value updated
  hallList =
      realloc(hallList,
              (n + 1) * sizeof(Hall)); // Ensure enough memory for the new hall
  if (hallList == NULL) {
    printf("Memory reallocation failed for hallList.\n");
    exit(1);
  }
  hallList[n] = h; // Save new hall at the end
  writeHallsToFile(hallList, n + 1);
  printf("The hall %s has been created successfully.\n", h.hallName);

  free(hallList);      // Free the allocated memory
  free(h.seatsPerRow); // Free the seatsPerRow allocation

  return h;
}
