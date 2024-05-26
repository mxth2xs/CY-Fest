#include "../../headers/manager.h"
#include "../../headers/var.h"
/**
 * Display the list of concert halls.
 *
 * @param hallList pointer to an Array of ConcertHall structures.
 * @param hallCount Number of concert halls in the array.
 */
int displayConcerts(int concertCount, Concert *concertList, int hallId) {
  int hallCount;
  Hall *hallList;

  hallList = readHallsFromFile(&hallCount);
  int counter = 0; // To display the right number

  int displayedConcertCount = 0;

  for (int c = 0; c < concertCount; c++) {
    Concert concert = concertList[c];
    if ((concert.hallId == hallId) ||
        (hallId == -1 && !isPastDate(&concert.endDate))) { // -1 is set to display all Concerts
      displayedConcertCount++;

      color(BOLD);
      color(BLUE);
      printf("\nConcert %d: %s (Hall %s)\n\n", c + 1, concert.concertName,
             hallList[concert.hallId].hallName);
      color(RESET);
      // printf("  Hall ID: %d\n", concert.hallId);
      printf("  Pit Area: %s\n", concert.pit ? "Yes" : "No");
      if (concert.pit) {
        printf("  Number of Places in Pit: %d\n", concert.nbPlacesPit);
        printf("  Number of Booked Places in Pit: %d\n",
               concert.nbBookedPlacesPit);
        printf("  Number of Booked Seats: %d\n", concert.nbBookedSeats);
      }
      color(UNDERLINE);
      printf("                       ");
      printf("\n   Prices by Category: \n");
      color(RESET);
      for (int i = 0; i < NB_CATEGORY; i++) {
        printf("    Category %c: %.2f\n", 'A' + i, concert.price[i]);
      }
      color(UNDERLINE);
      printf("                       ");
      printf("\n   Rows by Category:   \n");
      color(RESET);
      for (int i = 0; i < NB_CATEGORY; i++) {
        printf("    Category %c: %d rows\n", 'A' + i,
               concert.numRowsCategory[i]);
      }
      printf("\n  Total number of people expected: %d\n",
             concert.nbBookedSeats + concert.nbBookedPlacesPit);
      printf("  Hall State: %s\n", concert.hallState == Empty     ? "Empty"
                                   : concert.hallState == Partial ? "Partial"
                                                                  : "Full");
      color(RESET);
      printf("  Start Date: %04d-%02d-%02d %02d:%02d\n", concert.startDate.year,
             concert.startDate.month, concert.startDate.day,
             concert.startDate.hour, concert.startDate.minute);
      printf("  End Date: %04d-%02d-%02d %02d:%02d\n\n", concert.endDate.year,
             concert.endDate.month, concert.endDate.day, concert.endDate.hour,
             concert.endDate.minute);
      color(BOLD);
      printf("----------------------------\n");
      counter++;
      freeConcert(concert); // Assuming freeConcert properly handles all dynamic
                            // allocations
    }
  }
  free(hallList); // Free the hall
  return displayedConcertCount;
}
