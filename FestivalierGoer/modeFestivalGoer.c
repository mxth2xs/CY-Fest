#include "../headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
//----------------------
//  	FestivalGoer Mode
//----------------------

int maxTab(int *tab, unsigned int size) {
  /**
   * Find the maximum value in an array.
   *
   * @param tab The array to find the maximum value from
   * @param size The size of the array
   * @return int The maximum value in the array
   */

  if (size == 0)
    return 0;
  int max = tab[0];

  for (int i = 1; i < size; i++) {
    if (tab[i] > max) {
      max = tab[i];
    }
  }
  return max;
}

void printSeatedMapStatus(Hall hall, Concert concert, int startRow) {
  /**
   * Prints the status of a row in the concert hall including seat map and
   * categories.
   *
   * @param hall The information about the concert hall
   * @param concert The information about the concert
   * @param startRow The starting row number to print the status
   */

  int nbDigits = log10(hall.nbRowsTotal) + 1;
  for (int i = startRow; i < hall.nbRowsTotal; i++) {
    printf("R%*d ", nbDigits,
           i); // %*d formats 'i' with a width given by 'nbDigits'

    for (int j = 0; j < hall.seatsPerRow[i]; j++) {
      if (concert.hallMap[i][j] == 0) {
        if (i < concert.numRowsCategory[0]) {
          color(GREEN);
          printf("O ");
          color(RESET);
        } else if (i < concert.numRowsCategory[1]) {
          color(YELLOW);
          printf("O ");
          color(RESET);
        } else {
          color(BLUE);
          printf("O ");
          color(RESET);
        }
      } else {
        color(RED);
        printf("X ");
        color(RESET);
      }
    }
    printf("\n");
  }
}

void printStatusConcertHall(Hall hall, Concert concert) {
  /**
   * This function prints the status of the concert hall including the seat map
   * and price categories.
   *
   * @param hall The information about the concert hall
   * @param concert The information about the concert
   */
  color(BOLD);
  printf("\nMap of the %s hall\n", hall.hallName);
  color(RESET);
  printf("-------------------------------------\n");
  if (concert.pit) {
    printf("\nThere is a pit for this concert. Here's the current pit fill "
           "level:\n");
    int percentageFull =
        (concert.nbBookedPlacesPit * 100) / concert.nbPlacesPit;
    int numHashes = percentageFull / 5; // Each '#' represents 5%
    printf("[");
    for (int i = 0; i < 20; i++) {
      if (i < numHashes) {
        color(GREEN);
        printf("#");
        color(RESET);
      } else {
        printf(" ");
      }
    }
    printf("] %d%%\n", percentageFull);

    printSeatedMapStatus(hall, concert, concert.numRowsCategory[0]);

  } else {

    printSeatedMapStatus(hall, concert, 0);
  }

  printf("\n");
  color(BOLD);
  printf("Caption :\n");
  color(RESET);
  color(GREEN);
  if (concert.pit) {
    printf("  Pit");
  } else {
    printf("  O");
  }
  color(RESET);
  printf(" - A Category, %.2f€\n", concert.price[0]);
  color(YELLOW);
  printf("  O");
  color(RESET);
  printf(" - B Category, %.2f€\n", concert.price[1]);
  color(BLUE);
  printf("  O");
  color(RESET);
  printf(" - C Category, %.2f€\n", concert.price[2]);
  color(RED);
  printf("  X");
  color(RESET);
  printf(" - Already Reserved\n");
  printf("test");
}

bool isBooked(Concert concert, int row, int column) {
  /**
   * Check if a specific seat is already booked in the concert hall
   *
   * @param concert The concert information
   * @param row The row number of the seat
   * @param column The column number of the seat
   * @return bool True if the seat is booked, False otherwise
   */

  if (concert.hallMap[row][column] == 1) {
    return true;
  }
  return false;
}

int bookInPit(Hall hall, Concert concert) {
  /**
   * Book seats in the pit area of the concert hall
   *
   * @param hall The concert hall information
   * @param concert The concert information
   * @return int The total price of the booked pit places
   */

  int nbBookingPlaces;
  printf("How many places do you want to book in the pit ?\n");
  scanf("%d", &nbBookingPlaces);
  if (nbBookingPlaces > concert.nbPlacesPit - concert.nbBookedPlacesPit) {
    do {
      color(BOLD);
      color(RED);
      printf(
          "You can't book more places than the number of places available.\n");
      color(RESET);
      printf("There is %d places available.\n",
             concert.nbPlacesPit - concert.nbBookedPlacesPit);
      printf("How many places do you want to book in the pit ?\n");
      scanf("%d", &nbBookingPlaces);
    } while (nbBookingPlaces > concert.nbPlacesPit - concert.nbBookedPlacesPit);
  }
  concert.nbBookedPlacesPit += nbBookingPlaces;
  color(GREEN);
  printf("\nYour places in the pit are reserved, thank you !\n");
  color(RESET);

  return nbBookingPlaces;
}

int bookInSeated(Hall hall, Concert concert) {
  /**
   * Allow users to book seats in the seated area of the hall
   *
   * @param hall The concert hall information
   * @param concert The concert information
   * @return int The total price of the booked seats
   */

  int nbBookingSeat;
  int nbColumnMax;
  int seatRow;
  int seatColumn;
  int priceTotal = 0;

  nbColumnMax = maxTab(hall.seatsPerRow, hall.nbRowsTotal);
  printf("\nHow many seats do you want to book ?\n");
  scanf("%d", &nbBookingSeat);
  // VERIFY THAT THIS IF IS FUNCTIONAL (do not count the standing places)"
  if (nbBookingSeat > hall.totalSeats - concert.nbBookedSeats ||
      (nbBookingSeat >
           hall.totalSeats - concert.nbBookedSeats - concert.nbPlacesPit / 2 &&
       concert.pit == true)) {
    do {
      color(BOLD);
      color(RED);
      printf(
          "\n!You can't book more seats than the number of seats available!\n");
      color(RESET);
      if (concert.pit) {
        printf("\nThere is %d places available.\n",
               hall.totalSeats - concert.nbBookedSeats -
                   concert.nbPlacesPit / 2);
      } else {
        printf("\nThere is %d places available.\n",
               hall.totalSeats - concert.nbBookedSeats);
      }
      printf("\nHow many seats do you want to book ?\n");
      scanf("%d", &nbBookingSeat);
    } while (nbBookingSeat > hall.totalSeats - concert.nbBookedSeats ||
             (nbBookingSeat > hall.totalSeats - concert.nbBookedSeats -
                                  concert.nbPlacesPit / 2 &&
              concert.pit == true));
  } else {
    for (int i = 0; i < nbBookingSeat; i++) {
      printf("\nChoose the row for the seat n°%d\n", i + 1);
      scanf("%d", &seatRow);
      printf("\nChoose the column for the seat n°%d\n", i + 1);
      scanf("%d", &seatColumn);
      do {
        if (isBooked(concert, seatRow, seatColumn) == true) {
          do {
            color(BOLD);
            color(RED);
            printf("\n!This seat is already booked. Choose another seat!\n");
            color(RESET);
            printf("\nChoose the row for the seat n°%d\n", i + 1);
            scanf("%d", &seatRow);
            printf("\nChoose the column for the seat n°%d\n", i + 1);
            scanf("%d", &seatColumn);
          } while (isBooked(concert, seatRow, seatColumn) == true);
        } else if (seatRow < concert.numRowsCategory[0] &&
                   concert.pit == true) {
          do {
            color(BOLD);
            color(RED);
            printf("\n!This row is reserved for the pit!\n");
            color(RESET);
            printf("\nChoose the row for the seat n°%d\n", i + 1);
            scanf("%d", &seatRow);
            printf("\nChoose the column for the seat n°%d\n", i + 1);
            scanf("%d", &seatColumn);
          } while (seatRow < concert.numRowsCategory[0] && concert.pit == true);
        } else if (seatRow > hall.nbRowsTotal || seatColumn > nbColumnMax ||
                   seatRow < 0 || seatColumn < 0) {
          do {
            color(RED);
            printf("\n!Please, enter a valid row and column!\n");
            color(RESET);
            printf("\nChoose the row for the seat n°%d\n", i + 1);
            scanf("%d", &seatRow);
            printf("\nChoose the column for the seat n°%d\n", i + 1);
            scanf("%d", &seatColumn);
          } while (seatRow > hall.nbRowsTotal || seatColumn > nbColumnMax ||
                   seatRow < 0 || seatColumn < 0);
        }
      } while (isBooked(concert, seatRow, seatColumn) == true ||
               seatRow > hall.nbRowsTotal || seatColumn > nbColumnMax ||
               seatRow < 0 || seatColumn < 0 ||
               (seatRow < concert.numRowsCategory[0] && concert.pit == true));

      concert.hallMap[seatRow][seatColumn] = 1;
      if (seatRow < concert.numRowsCategory[0]) {
        priceTotal += concert.price[0];
      } else if (seatRow < concert.numRowsCategory[1]) {
        priceTotal += concert.price[1];
      } else {
        priceTotal += concert.price[2];
      }
      color(BOLD);
      color(BLUE);
      printf("\nYour seat on row %d and column %d is booked\n", seatRow,
             seatColumn);
    }
    concert.nbBookedSeats += nbBookingSeat;
    printf("\nYour %d seats are booked, thank you !\n", nbBookingSeat);
    color(RESET);
  }

  return priceTotal;
}

void bookSeats(int concertId) {
  int concertCount; // Nbr de concerts dans la liste
  Concert *concertList =
      readConcertsFromFile(&concertCount); // Liste des concerts
  Concert concert = concertList[concertId];

  int hallCount;
  Hall *hallList = readHallsFromFile(&hallCount);
  Hall hall = hallList[concert.hallId];

  /**
   * Book seats for the concert based on user selection
   * Calculates the final price of booking and provides necessary instructions
   *
   * @param hall The concert hall information
   * @param concert The concert information
   */

  int finalPrice = 0;

  printStatusConcertHall(hall, concert);
  if (isPastDate(&concert.startDate)) {
    color(BOLD);
    color(RED);
    printf("\n1The concert has already started!\n");
    color(RESET);
  } else {

    if (concert.pit) {
      int selection = -1;
      do {
        color(BOLD);
        color(BLUE);
        printf("\nDo you want to book a place in the pit ?");
        color(RESET);
        printf("\n  1: Yes\n  0: No\n");
      } while (!testValues(0, 1, &selection));
      if (selection == 1) {
        int tempBooked = bookInPit(hall, concert);
        concert.nbBookedPlacesPit = tempBooked;
        finalPrice += tempBooked * concert.price[0];
      }
      finalPrice += bookInSeated(hall, concert);

    } else {
      finalPrice += bookInSeated(hall, concert);
    }

    concertList[concertId] = concert;
    writeConcertsToFile(concertList, concertCount);
    color(BOLD);
    color(BLUE);
    printf("\nYou will have to pay %d€ on the day of the concert.\n\n",
           finalPrice);
    color(RESET);
  }
}