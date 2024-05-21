#include "../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

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
      printf("\n");
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

  h.hallMap = malloc(h.nbRowsTotal * sizeof(int *));
  if (h.hallMap == NULL) {
    printf("Memory allocation failed for hallMap.\n");
    exit(1);
  }

  // Initializing numRowsCategory
  for (int i = 0; i < 3; i++) {
    h.numRowsCategory[i] = 0;
  }

  //----------------------
  // Get the number of seats in Row, end time etc...
  //----------------------

  h = modifyConcertHall(h);

  int currentRow = 0;
  for (int z = 0; z < 3; z++) {
    for (int i = 0; i < h.numRowsCategory[z]; i++) {
      do {
        printf("What is the number of seats in the row %d, in zone %c \n",
               i + 1, 'a' + z);
        if (scanf("%d", &h.seatsPerRow[currentRow]) != 1) {
          printf("\n");
          h.seatsPerRow[currentRow] = -1; // Force retry
        }
      } while (!testValues(1, 512, h.seatsPerRow[currentRow]));

      h.hallMap[currentRow] = malloc(h.seatsPerRow[currentRow] * sizeof(int));
      if (h.hallMap[currentRow] == NULL) {
        printf("Memory allocation failed for hallMap row %d.\n", currentRow);
        exit(1);
      }

      for (int j = 0; j < h.seatsPerRow[currentRow]; j++) {
        h.hallMap[currentRow][j] = 0; // 0 for empty
        h.totalSeats++;
      }
      currentRow++;
    }
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

  free(hallList); // Free the allocated memory
  for (int i = 0; i < h.nbRowsTotal; i++) {
    free(h.hallMap[i]); // Free each row allocation
  }
  free(h.hallMap); // Free the main hallMap allocation

  return h;
}
