#include "headers/var.h"

// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
//----------------------
//  	FestivalGoer Mode
//----------------------

int maxTab(int *tab, unsigned int size) {
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

void printComingConcert(Hall *hall) {}

void printStatusHall(Hall hall) {
  printf("Map of the %s hall\n", hall.hallName);
  printf("-------------------\n");
  if (hall.pit) {
    // AJOUTER LE POURCENTAGE DE REMPLISSAGE DU PIT
    printf("There is a pit for this concert. Here's the current pit fill "
           "level.\n");

    for (int i = hall.numRowsCategory[0]; i < hall.nbRowsTotal; i++) {
      for (int j = 0; j < hall.seatsPerRow[i]; j++) {
        if (hall.hallMap[i][j] == 0) {
          if (j < hall.numRowsCategory[1]) {
            color("33"); // yellow
            printf("O ");
            color("0");
          } else {
            color("34"); // blue
            printf("O ");
            color("0");
          }
        } else {
          color("31"); // red
          printf("X ");
          color("0");
        }
      }
      printf("\nR%d", i + 1);
    }
  } else {
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      for (int j = 0; j < hall.seatsPerRow[i]; j++) {
        if (hall.hallMap[i][j] == 0) {
          if (i < hall.numRowsCategory[0]) {
            color("32"); // green
            printf("O ");
            color("0");
          } else if (j < hall.numRowsCategory[1]) {
            color("33"); // yellow
            printf("O ");
            color("0");
          } else {
            color("34"); // blue
            printf("O ");
            color("0");
          }
        } else {
          color("31"); // red
          printf("X ");
          color("0");
        }
      }
      printf("\nR%d", i + 1);
    }
  }

  printf("\n\n");
  printf("Caption :\n");
  color("32");
  printf("O - A Category\n");
  color("33");
  printf("O - B Category\n");
  color("34");
  printf("O - C Category\n");
  printf("X - Already Reserved\n");
}

bool isBooked(Hall hall, int row, int column) {
  if (hall.hallMap[row][column] == 1) {
    return true;
  }
  return false;
}

void bookSeats(Hall hall) {
  int nbBookingSeat;
  int nbColumnMax;
  int seatRow;
  int seatColumn;

  nbColumnMax = maxTab(hall.seatsPerRow, hall.nbRowsTotal);

  printStatusHall(hall);
  printf("How many seats do you want to book?");
  scanf("%d", &nbBookingSeat);

  // AJOUTER LA POSSIBILITE D'ACHETER DANS UN PIT OU NON

  if (nbBookingSeat > hall.nbBookedSeats) {
    printf("You can't book more seats than the number of seats available");
  } else {
    for (int i = 0; i < nbBookingSeat; i++) {
      printf("Choose the row for the seat n°%d", i + 1);
      scanf("%d", &seatRow);
      printf("Choose the column for the seat n°%d", i + 1);
      scanf("%d", &seatColumn);
      while (isBooked(hall, seatRow, seatColumn) == true ||
             seatRow > hall.nbRowsTotal || seatColumn > nbColumnMax ||
             seatRow < 0 || seatColumn < 0) {
        if (isBooked(hall, seatRow, seatColumn) == true) {
          do {
            printf("This seat is already booked. Choose another seat.");
            printf("Choose the row for the seat n°%d", i + 1);
            scanf("%d", &seatRow);
            printf("Choose the column for the seat n°%d", i + 1);
            scanf("%d", &seatColumn);
          } while (isBooked(hall, seatRow, seatColumn) == true);
        }
      }

      printf("Your seat on row %d and column %d is booked", seatRow,
             seatColumn);
    }
  }
}