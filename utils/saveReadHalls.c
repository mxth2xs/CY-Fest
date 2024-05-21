#include "../headers/var.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

// Function to free allocated memory for a single Hall
void freeHall(Hall hall) {
  free(hall.seatsPerRow);
  for (int i = 0; i < hall.nbRowsTotal; i++) {
    free(hall.hallMap[i]);
  }
  free(hall.hallMap);
}

// Function to save the list of Hall structures to a binary file
void writeHallsToFile(Hall *hallList, int hallCount) {
  FILE *file = fopen("utils/halls/halls.txt", "wb");
  if (file == NULL) {
    perror("Error opening file");
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

    // Write number of rows per category
    fwrite(hall.numRowsCategory, sizeof(int), NB_CATEGORY, file);

    // Write prices per category
    fwrite(hall.price, sizeof(float), NB_CATEGORY, file);

    // Write number of booked seats
    fwrite(&hall.nbBookedSeats, sizeof(int), 1, file);

    // Write hall state
    fwrite(&hall.hallState, sizeof(HallState), 1, file);

    // Write total seats
    fwrite(&hall.totalSeats, sizeof(int), 1, file);

    // Write hall map
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      fwrite(hall.hallMap[i], sizeof(int), hall.seatsPerRow[i], file);
    }

    // Write pit and endTime
    fwrite(&hall.pit, sizeof(int), 1, file);
    fwrite(&hall.endTime, sizeof(int), 1, file);
  }

  fclose(file);
}

// Function to read the list of Hall structures from a binary file
Hall *readHallsFromFile(int *n) {
  FILE *file = fopen("utils/halls/halls.txt", "rb");
  if (file == NULL) {
    perror("Error opening file");
    exit(EXIT_FAILURE);
  }

  // Read the number of halls
  fread(n, sizeof(int), 1, file);
  int hallCount = (*n)+1;

  // Allocate memory for the list of halls
  Hall *hallList = (Hall *)malloc(hallCount * sizeof(Hall));

  for (int h = 0; h < hallCount; h++) {
    Hall hall;

    // Read the hall name
    fread(hall.hallName, sizeof(char), CHAR_MAX_LENGTH, file);

    // Read the number of rows
    fread(&hall.nbRowsTotal, sizeof(int), 1, file);

    // Allocate memory for seatsPerRow and read values
    hall.seatsPerRow = (int *)malloc(hall.nbRowsTotal * sizeof(int));
    fread(hall.seatsPerRow, sizeof(int), hall.nbRowsTotal, file);

    // Read number of rows per category
    fread(hall.numRowsCategory, sizeof(int), NB_CATEGORY, file);

    // Read prices per category
    fread(hall.price, sizeof(float), NB_CATEGORY, file);

    // Read number of booked seats
    fread(&hall.nbBookedSeats, sizeof(int), 1, file);

    // Read hall state
    fread(&hall.hallState, sizeof(HallState), 1, file);

    // Read total seats
    fread(&hall.totalSeats, sizeof(int), 1, file);

    // Allocate and read the hall map
    hall.hallMap = (int **)malloc(hall.nbRowsTotal * sizeof(int *));
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      hall.hallMap[i] = (int *)malloc(hall.seatsPerRow[i] * sizeof(int));
      fread(hall.hallMap[i], sizeof(int), hall.seatsPerRow[i], file);
    }

    // Read pit and endTime
    fread(&hall.pit, sizeof(int), 1, file);
    fread(&hall.endTime, sizeof(int), 1, file);

    hallList[h] = hall;
  }

  fclose(file);
  return hallList;
}