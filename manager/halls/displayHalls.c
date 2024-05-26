#include "../../headers/manager.h"
#include "../../headers/var.h"
/**
 * Display the list of concert halls.
 *
 * @param hallList pointer to an Array of ConcertHall structures.
 * @param hallCount Number of concert halls in the array.
 */
void displayHalls(int hallCount, Hall *hallList) {
  for (int h = 0; h < hallCount; h++) { 
    Hall hall = hallList[h];
    color(BOLD);
    printf("%d. Hall Name: %s\n\n", h + 1, hall.hallName);
    color(RESET);
    printf("  Number of Rows: %d\n", hall.nbRowsTotal);
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      printf("      Seats in Row %d: %d\n", i + 1, hall.seatsPerRow[i]);
    }
    printf("  Total Seats: %d\n", hall.totalSeats);
    printf("\n");
    freeHall(hall);
  }
}
