#include "../../headers/var.h"
#include "../../headers/manager.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"



/**
 * Free Memory
 *
 * @param concert Concert structure to free memory
 */
void freeConcert(Concert concert) {
  for (int i = 0; i < NB_CATEGORY; i++) {
    free(concert.hallMap[i]);
  }
  free(concert.hallMap);
}

/**
 * Save the list of concerts to a file.
 *
 * @param concertList pointer to an Array of Concert structures.
 * @param concertCount Number of concerts in the array.
 */
void writeConcertsToFile(Concert *concertList, int concertCount) {
  int hallCount;
  Hall *hallList = readHallsFromFile(&hallCount); //get the hall list
  Hall hall;
  Concert concert;

  //get location
  FILE *file = fopen("manager/concerts/save/concerts.cyfest", "wb");
  if (file == NULL) {
    perror("Error writing concerts file");
    exit(EXIT_FAILURE);
  }

  // Write the number of concerts
  fwrite(&concertCount, sizeof(int), 1, file);

  for (int c = 0; c < concertCount; c++) {
    // Get the Hall associated to the Concert
    concert = concertList[c];
    hall = hallList[concert.hallId];

    // Write the hall ID
    fwrite(&concert.hallId, sizeof(int), 1, file);

    // Write the concert name
    fwrite(concert.concertName, sizeof(char), CHAR_MAX_LENGTH, file);

    // Write pit information
    fwrite(&concert.pit, sizeof(int), 1, file);
    fwrite(&concert.nbPlacesPit, sizeof(int), 1, file);
    fwrite(&concert.nbBookedPlacesPit, sizeof(int), 1, file);

    // Write prices for different categories
    fwrite(concert.price, sizeof(float), NB_CATEGORY, file);

    // Write number of rows per category
    fwrite(concert.numRowsCategory, sizeof(int), NB_CATEGORY, file);

    // Write total number of booked seats
    fwrite(&concert.nbBookedSeats, sizeof(int), 1, file);

    // Write hall state
    fwrite(&concert.hallState, sizeof(HallState), 1, file);

    // Write hall map
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      fwrite(concert.hallMap[i], sizeof(int), hall.seatsPerRow[i], file);
    }

    // Write start date and end date
    fwrite(&concert.startDate, sizeof(Date), 1, file);
    fwrite(&concert.endDate, sizeof(Date), 1, file);
  }

  fclose(file);
}

/**
 * Read the list of concerts from a file.
 *
 * @param n Pointer to an int variable to store the number of concerts.
 * @return List of concerts read.
 */
Concert *readConcertsFromFile(int *n) {
  const char *file_path = "manager/concerts/save/concerts.cyfest";

  FILE *file = fopen(file_path, "rb");
  if (file == NULL) {
    color(BOLD);
    color(RED);
    printf("\n!Impossible to read concerts file!");
    color(RESET);
    exit(EXIT_FAILURE);
  }

  // Read the number of concerts
  fread(n, sizeof(int), 1, file);
  int concertCount = *n;

  // Allocate memory for the list of concerts
  Concert *concertList = (Concert *)malloc(concertCount * sizeof(Concert));
  if (concertList == NULL) {
    perror("Memory allocation failed");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  // Read hall information
  int hallCount;
  Hall *hallList = readHallsFromFile(&hallCount);
  Hall hall;

  int validConcertCount = 0;

  for (int c = 0; c < concertCount; c++) {
    Concert concert;

    // Read the hall ID
    fread(&concert.hallId, sizeof(int), 1, file);
    hall = hallList[concert.hallId];

    // Read the concert name
    fread(concert.concertName, sizeof(char), CHAR_MAX_LENGTH, file);

    // Read pit information
    fread(&concert.pit, sizeof(int), 1, file);
    fread(&concert.nbPlacesPit, sizeof(int), 1, file);
    fread(&concert.nbBookedPlacesPit, sizeof(int), 1, file);

    // Read prices for different categories
    fread(concert.price, sizeof(float), NB_CATEGORY, file);

    // Read number of rows per category
    fread(concert.numRowsCategory, sizeof(int), NB_CATEGORY, file);

    // Read total number of booked seats
    fread(&concert.nbBookedSeats, sizeof(int), 1, file);

    // Read hall state
    fread(&concert.hallState, sizeof(HallState), 1, file);

    // Allocate memory for hall map and read values
    concert.hallMap = (int **)malloc(hall.nbRowsTotal * sizeof(int *));
    if (concert.hallMap == NULL) {
      perror("Memory allocation for hallMap failed");
      free(concertList);
      fclose(file);
      exit(EXIT_FAILURE);
    }
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      concert.hallMap[i] = (int *)malloc(hall.seatsPerRow[i] * sizeof(int));
      if (concert.hallMap[i] == NULL) {
        perror("Memory allocation for hallMap rows failed");
        for (int j = 0; j < i; j++) {
          free(concert.hallMap[j]);
        }
        free(concert.hallMap);
        free(concertList);
        fclose(file);
        exit(EXIT_FAILURE);
      }
      fread(concert.hallMap[i], sizeof(int), hall.seatsPerRow[i], file);
    }

    // Read start date and end date
    fread(&concert.startDate, sizeof(Date), 1, file);
    fread(&concert.endDate, sizeof(Date), 1, file);

    // Validate and store the concert
    concertList[validConcertCount] = concert;
    validConcertCount++;
  }

  fclose(file);
  free(hallList);

  *n = validConcertCount;
  return (Concert *)realloc(concertList, validConcertCount * sizeof(Concert));
}
