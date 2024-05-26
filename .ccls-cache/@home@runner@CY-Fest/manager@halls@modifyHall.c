#include "../../headers/manager.h"
#include "../../headers/var.h"

int modifyHalls() {
  int concertCount;
  Concert *concertList = readConcertsFromFile(&concertCount);

  printf("ccc: %d \n", concertCount);

  int hallCount;
  Hall *hallList = readHallsFromFile(&hallCount);

  int *editableHalls = malloc(sizeof(int) * hallCount);
  int editableHallsCounter = 0;

  int notPastCounter = 0;
  color(BOLD);
  printf("\nYou can modify the following halls:\n");
  color(RESET);

  int selection;

  for (int i = 0; i < hallCount; i++) {
    for (int j = 0; j < concertCount; j++) {
      if (!isPastDate(&concertList[j].endDate) && concertList[j].hallId == i) {
        notPastCounter++;
      }
    }
    if (notPastCounter == 0) {
      printf("\n%d. %s \n", editableHallsCounter+1, hallList[i].hallName);
      editableHalls[editableHallsCounter] = i;
      editableHallsCounter++;
    }
    notPastCounter = 0;
  }

  do {
    printf("Enter the number of the hall you want to modify: \n");
  } while (!testValues(1, editableHallsCounter, &selection));
  selection--;

  createConcertHall(editableHalls[selection]);
  return 1;
}