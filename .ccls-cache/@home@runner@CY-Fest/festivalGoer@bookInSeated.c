#include "../headers/festival.h"
#include "../headers/var.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

int bookInSeated(Hall hall, Concert *concert) {
  /**
   * Allow users to book seats in the seated area of the hall
   *
   * @param hall The concert hall information
   * @param concert The concert information
   * @return int The total price of the booked seats
   */

  int nbBookingSeat;
  int seatRow;
  int seatColumn;
  int priceTotal = 0;
  int testInt; // To check whether a user input is an int

  printf("\nHow many seated places do you want to book ?\n");
  testInt = scanf("%d", &nbBookingSeat);

  // If not an int or trying to book more than the number of places available
  // (pit or seated)
  if (testInt == 0 ||
      (concert->pit == false &&
       nbBookingSeat > hall.totalSeats - concert->nbBookedSeats) ||
      (concert->pit == true && nbBookingSeat > hall.totalSeats -
                                                   concert->nbBookedSeats -
                                                   concert->nbPlacesPit / 2)) {
    do {
      color(BOLD);
      color(RED);
      if (testInt == 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        printf("\n!You must enter a number!\n");

      } else {
        printf("\n!You can't book more seats than the number of seats "
               "available!\n");
      }
      color(RESET);
      if (concert->pit) {
        printf("\nThere is %d places available.\n",
               hall.totalSeats - concert->nbBookedSeats -
                   concert->nbPlacesPit / 2);
      } else {
        printf("\nThere is %d places available.\n",
               hall.totalSeats - concert->nbBookedSeats);
      }
      printf("\nHow many seats do you want to book ?\n");
      testInt = scanf("%d", &nbBookingSeat);
    } while (testInt == 0 ||
             nbBookingSeat > hall.totalSeats - concert->nbBookedSeats ||
             (nbBookingSeat > hall.totalSeats - concert->nbBookedSeats -
                                  concert->nbPlacesPit / 2 &&
              concert->pit == true));
  }

  // Loop to book the seats
  for (int i = 0; i < nbBookingSeat; i++) {
    
    // Print the status of the hall 
    if (i > 0) {
      printStatusConcertHall(hall, *concert);
    }
    printf("\nChoose the row for the seat n°%d\n", i + 1);
    testInt = scanf("%d", &seatRow);
    if (testInt == 0) {
      do {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        color(BOLD);
        color(RED);
        printf("\n!You must enter a number!\n");
        color(RESET);
        printf("\nChoose the row for the seat n°%d\n", i + 1);
        testInt = scanf("%d", &seatRow);
      } while (testInt == 0);
    }
    printf("\nChoose the column for the seat n°%d\n", i + 1);
    testInt = scanf("%d", &seatColumn);
    if (testInt == 0) {
      do {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        color(BOLD);
        color(RED);
        printf("\n!You must enter a number!\n");
        color(RESET);
        printf("\nChoose the column for the seat n°%d\n", i + 1);
        testInt = scanf("%d", &seatColumn);
      } while (testInt == 0);
    }
    if (seatRow >= hall.nbRowsTotal ||
        seatColumn >= hall.seatsPerRow[seatRow] || seatRow < 0 ||
        seatColumn < 0 || isBooked(*concert, seatRow, seatColumn) == true ||
        (seatRow < concert->numRowsCategory[0] && concert->pit == true)) {
      do {
        color(BOLD);
        color(RED);
        if (seatRow >= hall.nbRowsTotal ||
            seatColumn >= hall.seatsPerRow[seatRow] || seatRow < 0 ||
            seatColumn < 0) {
          printf("\n!Please, enter a valid row and column!\n");
        } else if (isBooked(*concert, seatRow, seatColumn) == true) {
          printf("\n!This seat is already booked. Choose another seat!\n");
        } else if (seatRow < concert->numRowsCategory[0] &&
                   concert->pit == true) {
          printf("\n!This row is reserved for the pit!\n");
        }
        color(RESET);
        printf("\nChoose the row for the seat n°%d\n", i + 1);
        testInt = scanf("%d", &seatRow);
        if (testInt == 0) {
          do {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
              ;
            color(BOLD);
            color(RED);
            printf("\n!You must enter a number!\n");
            color(RESET);
            printf("\nChoose the row for the seat n°%d\n", i + 1);
            testInt = scanf("%d", &seatRow);
          } while (testInt == 0);
        }
        printf("\nChoose the column for the seat n°%d\n", i + 1);
        testInt = scanf("%d", &seatColumn);
        if (testInt == 0) {
          do {
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
              ;
            color(BOLD);
            color(RED);
            printf("\n!You must enter a number!\n");
            color(RESET);
            printf("\nChoose the column for the seat n°%d\n", i + 1);
            testInt = scanf("%d", &seatColumn);
          } while (testInt == 0);
        }
      } while (seatRow >= hall.nbRowsTotal ||
               seatColumn >= hall.seatsPerRow[seatRow] || seatRow < 0 ||
               seatColumn < 0 ||
               isBooked(*concert, seatRow, seatColumn) == true ||
               (seatRow < concert->numRowsCategory[0] && concert->pit == true));
    }

    concert->hallMap[seatRow][seatColumn] = 1;
    if (seatRow < concert->numRowsCategory[0]) {
      priceTotal += concert->price[0];
    } else if (seatRow < concert->numRowsCategory[1]) {
      priceTotal += concert->price[1];
    } else {
      priceTotal += concert->price[2];
    }
    color(BOLD);
    color(BLUE);
    printf("\nYour seat on row %d and column %d is booked\n", seatRow,
           seatColumn);
    color(RESET);
  }
  concert->nbBookedSeats += nbBookingSeat;
  if (nbBookingSeat < 1) {
    printf("We look forward to hearing from you in the future.");
  } else {
    color(GREEN);
    printf("\nYour %d seats are booked, thank you !\n", nbBookingSeat);
    color(RESET);
  }
  color(RESET);

  if ((concert->pit == false && concert->nbBookedSeats == hall.totalSeats) ||
      (concert->pit == true &&
       concert->nbBookedSeats + concert->nbBookedPlacesPit ==
           hall.totalSeats + concert->nbPlacesPit / 2)) {
    concert->hallState = Full;
  } else if (concert->nbBookedSeats > 0 || concert->nbBookedPlacesPit > 0) {
    concert->hallState = Partial;
  }

  return priceTotal;
}