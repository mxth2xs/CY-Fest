#include "../../headers/var.h"
#include "../../headers/manager.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

Concert findConcert(int hallId) {

  int concertCount;
  Concert *concertList; // concerts list
  int concertId;

  concertList = readConcertsFromFile(&concertCount);

  color(BOLD);
  printf("Here is the list of all the concerts in this hall :\n");
  color(RESET);

  displayConcerts(concertCount, concertList, hallId);

  int *concertDisplayed =
      malloc(sizeof(int) * concertCount); // the list store the position of the
                                          // concerts in a specific hall

  int counter = 0;
  for (int i = 0; i < concertCount; i++) {
    if (concertList[i].hallId == hallId) {
      concertDisplayed[counter] = i;
      counter++;
    }
  }

  do {
    color(BOLD);
    printf("Enter the ID of the concert you want to check: \n");
    color(RESET);
  } while (!testValues(1, concertCount, &concertId));
  printf("\e[1;1H\e[2J");
  concertId--;

  return concertList[concertDisplayed[concertId]];
}