#include "../../headers/manager.h"
#include "../../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

Concert findConcert(int hallId) {

  int concertCount;
  Concert *concertList; // concerts list
  int concertId;
  Concert c;

  concertList = readConcertsFromFile(&concertCount);
  int displayedConcertCount;

  color(BOLD);
  printf("\nHere is the list of all the concerts in this hall :\n");
  color(RESET);

  displayedConcertCount = displayConcerts(concertCount, concertList, hallId);
  if (displayedConcertCount == 0) {
    color(BOLD);
    color(RED);
    printf("!There are no concert in this hall!\n\n");
    color(RESET);
    c.nbPlacesPit = -1;
    return c;
  }

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

  //the concert we need
  c = concertList[concertDisplayed[concertId]];

  //free memory
  free(concertList);
  free(concertDisplayed);

  return c;
}