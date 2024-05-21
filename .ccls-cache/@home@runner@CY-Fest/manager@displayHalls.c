#include "../headers/var.h"
void displayHalls(int hallCount, Hall *hallList) {
  for (int h = 0; h < hallCount; h++) {
    printf("Hall number %d: \n", h + 1);
    Hall hall = hallList[h];
    printf("Hall Name: %s\n", hall.hallName);
    printf("Number of Rows: %d\n", hall.nbRowsTotal);
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      printf("Seats in Row %d: %d\n", i + 1, hall.seatsPerRow[i]);
    }
    printf("Number of Booked Seats: %d\n", hall.nbBookedSeats);
    printf("Hall State: %d\n", hall.hallState);
    printf("Total Seats: %d\n", hall.totalSeats);
    printf("Pit: %d\n", hall.pit);
    printf("End Time: %d\n", hall.endTime);
    printf("\n");
    freeHall(hall);
  }
}