#include "../headers/festival.h"
#include "../headers/manager.h"
#include "../headers/var.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

void bookSeats(int concertId) {
  /**
   * Book seats for the concert based on user selection
   * Calculates the final price of booking and provides necessary instructions
   *
   * @param hall The concert hall information
   * @param concert The concert information
   */

  int concertCount;
  Concert *concertList = readConcertsFromFile(&concertCount);

  int hallCount;
  Hall *hallList = readHallsFromFile(&hallCount);

  int *displayedConcertList =
      malloc(sizeof(int) * concertCount); // create a tab to store the
                                          // displayed Concert List

  int notPastCounter = 0;

  /// store the ids of the concerts that were displayed to the user
  for (int i = 0; i < concertCount; i++) {
    if (!isPastDate(&concertList[i].endDate)) {
      displayedConcertList[notPastCounter] = i;
      notPastCounter++;
    }
  }

  Concert concert = concertList[displayedConcertList[concertId]];
  Hall hall = hallList[concert.hallId];

  int finalPrice = 0;

  printStatusConcertHall(hall, concert);
  if (isPastDate(&concert.startDate)) {
    color(BOLD);
    color(RED);
    printf("\n!The concert has already started!\n");
    color(RESET);
  } else if (concert.hallState == Full) {
    color(BOLD);
    color(RED);
    printf("\n!The concert is already full!\n\n");
    color(RESET);
  } else {
    // There is still space in the hall, you can book seats

    if (concert.pit) {
      int selection = -1;

      // Check if the pit is full
      if (concert.nbBookedPlacesPit == concert.nbPlacesPit) {
        color(BOLD);
        color(RED);
        printf("\nSorry, the pit is full!\n");
        color(RESET);

        // Launch program to buy seated place
        finalPrice += bookInSeated(hall, &concert);

      } else {
        do {
          color(BOLD);
          color(BLUE);
          printf("\nDo you want to book a place in the pit ?");
          color(RESET);
          printf("\n  1: Yes\n  0: No\n");
        } while (!testValues(0, 1, &selection));
        if (selection == 1) {
          finalPrice += bookInPit(hall, &concert);
        }

        // Check that the room is not composed of a pit only
        if (concert.nbPlacesPit / 2 != hall.totalSeats) {

          // Check if seating is available
          if (concert.nbBookedSeats !=
              hall.totalSeats - concert.nbPlacesPit / 2) {
            finalPrice += bookInSeated(hall, &concert);
          } else {
            color(BOLD);
            color(RED);
            printf("\nSorry, all seating has been reserved.\n");
            color(RESET);
          }
        }
      }

    } else {
      finalPrice += bookInSeated(hall, &concert);
    }

    concertList[displayedConcertList[concertId]] = concert;
    writeConcertsToFile(concertList, concertCount); // Save in file
    color(BOLD);
    color(BLUE);
    printf("\nYou will have to pay %d€ on the day of the concert.\n\n\n",
           finalPrice);
    color(RESET);
  }
  free(hallList);
  free(displayedConcertList);
}