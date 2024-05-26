#include "../headers/festival.h"
#include "../headers/var.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

void printStatusConcertHall(Hall hall, Concert concert) {
  /**
   * This function prints the status of the concert hall including the pit, the
   * seat map and price categories.
   *
   * @param hall The information about the concert hall
   * @param concert The information about the concert
   */
  
  color(BOLD);
  printf("\nMap of the %s hall\n", hall.hallName);
  color(RESET);
  printf("-------------------------------------\n");
  if (concert.pit) {
    printf("\nThere is a pit for this concert. Here's the current pit fill "
           "level:\n\n");
    int percentageBooked =
        (concert.nbBookedPlacesPit * 100) / concert.nbPlacesPit;
    int numHashes = percentageBooked / 5; // Each '#' represents 5%
    printf("[");
    for (int i = 0; i < 20; i++) {
      if (i < numHashes) {
        color(GREEN);
        printf("#");
        color(RESET);
      } else {
        printf(" ");
      }
    }
    printf("] %d%%\n", percentageBooked);
    printSeatedMapStatus(hall, concert, concert.numRowsCategory[0]);

  } else {

    printSeatedMapStatus(hall, concert, 0);
  }

  printf("\n");
  color(BOLD);
  printf("Caption :\n");
  color(RESET);
  color(GREEN);
  if (concert.pit) {
    printf("  Pit");
  } else {
    printf("  O");
  }
  color(RESET);
  printf(" - A Category, %.2f€\n", concert.price[0]);
  color(YELLOW);
  printf("  O");
  color(RESET);
  printf(" - B Category, %.2f€\n", concert.price[1]);
  color(BLUE);
  printf("  O");
  color(RESET);
  printf(" - C Category, %.2f€\n", concert.price[2]);
  color(RED);
  printf("  X");
  color(RESET);
  printf(" - Already Reserved\n");
}