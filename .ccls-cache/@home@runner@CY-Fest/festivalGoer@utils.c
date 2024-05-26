#include "../headers/var.h"
#include "../headers/festival.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

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