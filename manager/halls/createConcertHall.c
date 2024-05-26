#include "../../headers/manager.h"
#include "../../headers/var.h"



// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

/**
 * Create a new hall.
 *
 * @param replaceHall ID of the Hall you want to replace, -1 if you don't want to replace an existing one.
 */
Hall createConcertHall(int replaceHall) {

  Hall h;
  h.totalSeats = 0;
  h.nbRowsTotal = 0;

  //----------------------
  //      Hall Name
  //----------------------

  printf("\e[1;1H\e[2J");
  printf("Enter the name of the hall: \n");
  scanf("%99[^\n]", h.hallName);

  //----------------------
  //      Hall Rows
  //----------------------

  do {
    printf("\nEnter the total number of rows: \n");
  } while (!testValues(1, 512, &h.nbRowsTotal));

  //----------------------
  //   Memory Allocation
  //----------------------

  h.seatsPerRow = malloc(h.nbRowsTotal * sizeof(int));
  if (h.seatsPerRow == NULL) {
    color(BOLD);
    color(RED);
    printf("\n!Memory allocation failed for seatsPerRow!\n");
    color(RESET);
    exit(1);
  }

  //----------------------
  // Get the number of seats in Row
  //----------------------

  int currentRow = 0;
  for (int i = 0; i < h.nbRowsTotal; i++) {
    do {
      printf("\nWhat is the number of seats in row %d?\n", i + 1);
    } while (!testValues(1, 512, &h.seatsPerRow[currentRow]));

    h.totalSeats += h.seatsPerRow[currentRow];
    currentRow++;
  }

  //----------------------
  //      Save Hall
  //----------------------
  if (replaceHall == -1) {
    int n = 0;
    Hall *hallList =
        readHallsFromFile(&n); // Pass n by reference to get the value updated
    hallList = realloc(
        hallList,
        (n + 1) * sizeof(Hall)); // Ensure enough memory for the new hall
    if (hallList == NULL) {
      color(BOLD);
      color(RED);
      printf("\n!Memory reallocation failed for hallList!\n");
      color(RESET);
      exit(1);
    }
    hallList[n] = h; // Save new hall at the end
    writeHallsToFile(hallList, n + 1);
    printf("\nThe hall %s has been created successfully.\n\n", h.hallName);

    free(hallList);      // Free the allocated memory
    free(h.seatsPerRow); // Free the seatsPerRow allocation
  } else {
    int n = 0;
    Hall *hallList =
        readHallsFromFile(&n); // Pass n by reference to get the value updated

    hallList[replaceHall] = h; // Save new hall at the end
    writeHallsToFile(hallList, n);
    printf("\nThe hall %s has been saved.\n\n", h.hallName);

    free(hallList);      // Free the allocated memory
    free(h.seatsPerRow); // Free the seatsPerRow allocation
  }

  return h;
}
