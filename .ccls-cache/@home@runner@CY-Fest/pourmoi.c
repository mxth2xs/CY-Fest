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

    printf("\nWelcome to :\n");
    color(BLUE);
    printf("_________________________________________________________________"
           "______\n"
           "|                                                                "
           "     |\n"
           "|   /$$$$$$  /$$     /$$      /$$$$$$$$ /$$$$$$$$  /$$$$$$  "
           "/$$$$$$$$ |\n"
           "|  /$$__  $$|  $$   /$$/     | $$_____/| $$_____/ /$$__  $$|__  "
           "$$__/ |\n"
           "| | $$  \\__/ \\  $$ /$$/      | $$      | $$      | $$  \\__/   "
           "| $$    |\n"
           "| | $$        \\  $$$$//$$$$$$| $$$$$   | $$$$$   |  $$$$$$    | "
           "$$    |\n"
           "| | $$         \\  $$/|______/| $$__/   | $$__/    \\____  $$   "
           "| $$    |\n"
           "| | $$    $$    | $$         | $$      | $$       /$$  \\ $$   | "
           "$$    |\n"
           "| |  $$$$$$/    | $$         | $$      | $$$$$$$$|  $$$$$$/   | "
           "$$    |\n"
           "|  \\______/     |__/         |__/      |________/ \\______/    "
           "|__/    |\n"
           "|________________________________________________________________"
           "_____|\n"
           "\n\n\n");
    color(RESET);
    do {
      printf("What is your role ?");
      printf("\n0: Manager\n1: Festival-goer\n");
      scanf("%d", &selection);
      printf("\e[1;1H\e[2J");

    } while (!testValues(0, 1, selection));

    if (selection == 0) {
      if (hallCount > 0) {
        printf("Here is the list of halls (%d) : \n\n", hallCount);
        displayHalls(hallCount, hallList);
      }
      do {
        printf("Do you want to:");
        printf("\n0: Create a new hall\n");
        if (hallCount > 0) {
          printf("1: Modify an existing hall\n");
          printf("2: Delete an existing hall\n");
        }

        scanf("%d", &selection);
      } while (!testValues(0, 1, selection));

      if (selection == 0) {
        createConcertHall();
      } else {
        do {
          printf("Enter the number of the hall you want to modify: \n");
          scanf("%d", &hallPosition);
        } while (!testValues(1, hallCount, hallPosition));
        
        printf("\e[1;1H\e[2J");
        
        printf("Here is the List of concerts for hall %s: \n\n", hallList[hallPosition].hallName);
        displayConcerts(hallPosition);
        
        printf("Hall successfully modified \n");
      }
    }
    
  }

  return 0;
}
