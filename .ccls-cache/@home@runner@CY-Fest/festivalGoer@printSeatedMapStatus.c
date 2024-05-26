#include "../headers/var.h"
#include "../headers/festival.h"


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

void printSeatedMapStatus(Hall hall, Concert concert, int startRow) {
  /**
   * Prints the status of a row in the concert hall including seat map and
   * categories.
   *
   * @param hall The information about the concert hall
   * @param concert The information about the concert
   * @param startRow The starting row number to print the status
   */

  int nbDigits = log10(hall.nbRowsTotal) + 1;
  for (int i = startRow; i < hall.nbRowsTotal; i++) {
    printf("R%*d ", nbDigits,
           i); // %*d formats 'i' with a width given by 'nbDigits'
    // printf("\ni:%d %d \n", i, concert.numRowsCategory[1]);
    for (int j = 0; j < hall.seatsPerRow[i]; j++) {
      if (concert.hallMap[i][j] == 0) {

        if (i < concert.numRowsCategory[0]) {
          color(GREEN);
          printf("O ");
          color(RESET);
        } else if (i <
                   concert.numRowsCategory[0] + concert.numRowsCategory[1]) {
          color(YELLOW);
          printf("O ");
          color(RESET);
        } else {
          color(BLUE);
          printf("O ");
          color(RESET);
        }
      } else {
        color(RED);
        printf("X ");
        color(RESET);
      }
    }
    printf("\n");
  }
}
