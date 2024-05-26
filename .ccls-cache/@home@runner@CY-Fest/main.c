#include "headers/festival.h"
#include "headers/manager.h"
#include "headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

//----------------------
//         MAIN
//----------------------
int main() {
  int choice;    // choice menu
  int selection; // choice for the manager
  int maxPossibleValue = 0;

  int hallCount;
  Hall *hallList;

  int concertCount;
  Concert *concertList;

  int displayedConcertCount;

  color(BOLD);
  printf("\nWelcome to :\n");
  color(RESET);
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
  while (choice != 2) { // loop until the user choose to exit, so that the user
                        // can always come back to the menu
    hallList = readHallsFromFile(&hallCount);
    concertList = readConcertsFromFile(&concertCount);
    do {
      color(BOLD);
      color(BLUE);
      printf("THE MENU: \n\n");
      printf("What is your role ?");
      color(RESET);
      printf("\n  0: Manager\n  1: Festival-goer\n  2: Exit\n");
    } while (!testValues(0, 2, &choice));
    printf("\e[1;1H\e[2J"); // This sequence is used to clear the screen and
                            // reposition the cursor to the beginning.
    switch (choice) {
    case 0:
      if (hallCount > 0) {
        color(BOLD);
        printf("\nHere is the list of halls (%d) : \n\n\n", hallCount);
        color(RESET);
        displayHalls(hallCount, hallList);
      }
      do {
        color(BOLD);
        color(BLUE);
        printf("Do you want to:");
        color(RESET);
        printf("\n  0: Create a new hall\n");
        if (hallCount > 0) {
          printf("  1: Modify a concert hall\n");
          printf("  2: Create a concert\n");
          printf("  3: View the concert state\n");

          maxPossibleValue = 3;
        }
      } while (!testValues(0, maxPossibleValue, &selection));

      switch (selection) {

      case 0:
        createConcertHall(-1);
        break;

      case 1:
        printf("\e[1;1H\e[2J");
        modifyHalls();
        break;

      case 2:
        createConcert();
        break;

      case 3:
        viewState();
        break;
      }
      break;

    case 1: {
      int selection = -1;
      color(BOLD);
      color(BLUE);
      printf("Welcome in the festival goer mode\n");
      color(RESET);
      printf("Here's a list of upcoming concerts, sorted by halls :\n\n");
      displayedConcertCount = displayConcerts(concertCount, concertList, -1);
      if (displayedConcertCount == 0) {
        color(BOLD);
        color(RED);
        printf(
            "There aren't any upcoming concerts, please wait for the manager "
            "to add any.\n\n");
        color(RESET);
        break;
      }
      do {
        color(BOLD);
        color(BLUE);
        printf("\nEnter the number of the concert you want to book seats "
               "for:\n");
        color(RESET);
      } while (!testValues(1, displayedConcertCount, &selection));
      bookSeats(selection - 1);
      break;
    }
    case 2:
      free(hallList);
      free(concertList);
      break;
    }
  }

  return 0;
}