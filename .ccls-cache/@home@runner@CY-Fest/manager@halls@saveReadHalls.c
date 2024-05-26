#include "../../headers/var.h"
#include "../../headers/manager.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

// Function to free allocated memory for a single Hall
void freeHall(Hall hall) { free(hall.seatsPerRow); }


/**
 * Save the list of concert halls to a file.
 *
 * @param hallList pointer to an Array of ConcertHall structures.
 * @param hallCount Number of concert halls in the array.
 */
void writeHallsToFile(Hall *hallList, int hallCount) {
  FILE *file = fopen("manager/halls/save/halls.cyfest", "wb");
  if (file == NULL) {
    perror("Error writing halls file");
    exit(EXIT_FAILURE);
  }

  // Write the number of halls
  fwrite(&hallCount, sizeof(int), 1, file);

  for (int h = 0; h < hallCount; h++) {
    Hall hall = hallList[h];

    // Write the hall name
    fwrite(hall.hallName, sizeof(char), CHAR_MAX_LENGTH, file);

    // Write the number of rows
    fwrite(&hall.nbRowsTotal, sizeof(int), 1, file);

    // Write seats per row
    fwrite(hall.seatsPerRow, sizeof(int), hall.nbRowsTotal, file);

    // Write total seats
    fwrite(&hall.totalSeats, sizeof(int), 1, file);
  }

  fclose(file);
}

/**
 * Read the list of concert halls from a file.
 *
 * @param n Pointer to an int variable to store the number of concert halls.
 * @return Number of concert halls read.
 */

Hall *readHallsFromFile(int *n) { 
  
  // file location
  const char *file_path = "manager/halls/save/halls.cyfest";

  FILE *file = fopen(file_path, "rb");
  if (file == NULL) {
    color(BOLD);
    color(RED);
    printf("\n!Impossible to read halls file!");
    color(RESET);
    exit(EXIT_FAILURE);
  }

  // Read the number of halls
  fread(n, sizeof(int), 1, file);
  int hallCount = *n;

  // Allocate memory for the list of halls
  Hall *hallList = (Hall *)malloc(hallCount * sizeof(Hall));
  if (hallList == NULL) {
    perror("Memory allocation failed");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  for (int h = 0; h < hallCount; h++) {
    Hall hall;

    // Read the hall name
    fread(hall.hallName, sizeof(char), CHAR_MAX_LENGTH, file);

    // Read the number of rows
    fread(&hall.nbRowsTotal, sizeof(int), 1, file);

    // Allocate memory for seatsPerRow and read values
    hall.seatsPerRow = (int *)malloc(hall.nbRowsTotal * sizeof(int));
    if (hall.seatsPerRow == NULL) {
      perror("Memory allocation for seatsPerRow failed");
      free(hallList);
      fclose(file);
      exit(EXIT_FAILURE);
    }
    fread(hall.seatsPerRow, sizeof(int), hall.nbRowsTotal, file);

    // Read total seats
    fread(&hall.totalSeats, sizeof(int), 1, file);

    hallList[h] = hall;
  }

  fclose(file);
  return hallList;
}
