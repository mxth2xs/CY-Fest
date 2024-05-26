#include "../../headers/var.h"


//Procedure to delete all past concerts
void deletePastConcerts() {
  int concertCount;
  Concert *concertList = readConcertsFromFile(&concertCount);

  int validConcertCount = 0;
  Concert *validConcertList = (Concert *)malloc(concertCount * sizeof(Concert));

  for (int i = 0; i < concertCount; i++) {
    if (!isPastDate(&concertList[i].startDate)) {
      validConcertList[validConcertCount++] = concertList[i];
    } else {
      freeConcert(concertList[i]);
    }
  }

  free(concertList);

  writeConcertsToFile(validConcertList, validConcertCount);
  free(validConcertList);
}
