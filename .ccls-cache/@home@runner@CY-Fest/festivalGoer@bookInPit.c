#include "../headers/festival.h"
#include "../headers/var.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

int bookInPit(Hall hall, Concert *concert) {
  /**
   * Book seats in the pit area of the concert hall
   *
   * @param hall The concert hall information
   * @param concert The concert information
   * @return int The total price of the booked pit places
   */

  int nbBookingPlaces;
  int testInt; 

  printf("How many places do you want to book in the pit ?\n");
  testInt = scanf("%d", &nbBookingPlaces);

  if (testInt == 0 ||
      nbBookingPlaces > concert->nbPlacesPit - concert->nbBookedPlacesPit) {
    do {
      color(BOLD);
      color(RED);
      if (testInt == 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
          ;
        printf("\n!You must enter a number!\n");
      } else {
        printf("You can't book more places than the number of places "
               "available.\n");
      }
      color(RESET);
      printf("There is %d places available.\n",
             concert->nbPlacesPit - concert->nbBookedPlacesPit);
      printf("How many places do you want to book in the pit ?\n");
      testInt = scanf("%d", &nbBookingPlaces);
    } while (testInt == 0 || nbBookingPlaces > concert->nbPlacesPit -
                                                   concert->nbBookedPlacesPit);
  }
  concert->nbBookedPlacesPit += nbBookingPlaces;
  color(GREEN);
  printf("\nYour places in the pit are reserved, thank you !\n");
  color(RESET);
  return nbBookingPlaces * concert->price[0];
}