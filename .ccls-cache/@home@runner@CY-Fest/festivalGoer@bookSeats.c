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
  Concert concert = concertList[concertId];

  int hallCount;
  Hall *hallList = readHallsFromFile(&hallCount);
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

    concertList[concertId] = concert;
    writeConcertsToFile(concertList, concertCount); // Save in file
    color(BOLD);
    color(BLUE);
    printf("\nYou will have to pay %d€ on the day of the concert.\n\n\n",
           finalPrice);
    color(RESET);
  }
}