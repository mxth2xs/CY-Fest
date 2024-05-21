#include "headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

//----------------------
//         MAIN
//----------------------
int main() {
  int selection = -1;

  Hall hall;
  int hallPosition = -1;

  int hallCount;
  Hall *hallList;

  while (1) {
    hallList = readHallsFromFile(&hallCount);
    do {
      printf("Welcome to Cy Fest, what is your role ?");
      printf("\n0: Manager\n1: Fetival-goer\n");
      scanf("%d", &selection);
      printf("\e[1;1H\e[2J");

    } while (!testValues(0, 1, selection));

    if (selection == 0) {
      printf("Here is the list of halls %d: \n", hallCount);
      displayHalls(hallCount, hallList);

      do {
        printf("Dou you want to:");
        printf("\n0: Create a new hall\n1: Modify an existing hall\n");
        scanf("%d", &selection);
      } while (!testValues(0, 1, selection));

      if (selection == 0) {
        createConcertHall();
      } else {
        do {
          printf("Enter the number of the hall you want to modify: \n");
          scanf("%d", &hallPosition);
        } while (!testValues(0, hallCount, hallPosition));
        printf("\e[1;1H\e[2J");

        hall = *(hallList + hallPosition);
        *(hallList + hallPosition) = modifyConcertHall(hall);
        writeHallsToFile(hallList, hallCount);
        printf("Hall successfully modified \n");
      }
    }
  }

  createConcertHall();

  return 0;
}
