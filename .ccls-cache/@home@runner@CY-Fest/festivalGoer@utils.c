#include "../headers/var.h"
#include "../headers/festival.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

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