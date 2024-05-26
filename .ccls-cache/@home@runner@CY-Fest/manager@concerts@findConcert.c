#include "../../headers/manager.h"
#include "../../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

/**
 * Find the right concert on a hall with a hallId
 *
 * @param hallId Id of the hall we want to find the concert
 * Return a concert
 */
Concert findConcert(int hallId) {

  int concertCount; //number of the concert in the hall
  Concert *concertList; // concerts list
  int concertId; //which will be the index of the concert in the hall
  Concert c; 

  concertList = readConcertsFromFile(&concertCount); // get all the concerts created
  int displayedConcertCount; //number of concert that will be displayed

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
  printf("\e[1;1H\e[2J"); //get the concertt
  concertId--;

  //the concert we need
  c = concertList[concertDisplayed[concertId]]; //here it is, with the index

  //free memory
  free(concertList);
  free(concertDisplayed);

  return c;
}