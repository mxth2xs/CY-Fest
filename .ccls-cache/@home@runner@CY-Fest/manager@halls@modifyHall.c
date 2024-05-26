#include "../../headers/manager.h"
#include "../../headers/var.h"

/**
 * Modify a concert hall.
 *
 */

int modifyHalls() {
  int concertCount; // Get concert count
  Concert *concertList = readConcertsFromFile(&concertCount); // get concert list

  int hallCount; // get hall count
  Hall *hallList = readHallsFromFile(&hallCount); // get hall list

  int *editableHalls = malloc(sizeof(int) * hallCount); // create a tab to store the halls that can be edited
  int editableHallsCounter = 0;

  int notPastCounter = 0;
  color(BOLD);
  printf("\nYou can modify the following halls:\n");
  color(RESET);

  int selection;
/// store the halls that can be edited
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
    printf("\nEnter the number of the hall you want to modify: \n");
  } while (!testValues(1, editableHallsCounter, &selection));
  selection--;
//replace the hall you want to edit with a new one
  createConcertHall(editableHalls[selection]);
  return 1;
}