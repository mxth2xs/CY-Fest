#include "../../headers/manager.h"
#include "../../headers/var.h"
// Disable scanf warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"


/**
 * Create a new concert
 */
void createConcert() {
  
  // Defining all the variables
  Concert concert;
  int sumRows = 0; // Total rows of the first 2 categories

  int hallCount; //number of halls
  Hall *hallList; // Pointer to a list of Hall structures
  hallList =
      readHallsFromFile(&hallCount); // Read the list of halls from a file, hallCount will be update and take the number of all the hall
  Hall hall;

  int concertCount = 0; //same logic as hallCount
  Concert *concertList = readConcertsFromFile(
      &concertCount); // Pass n by reference to get the value updated

  int choice; // for hall

  // Initialize concert fields
  concert.nbBookedSeats = 0;
  concert.nbBookedPlacesPit = 0;
  concert.hallState = Empty;
  concert.nbPlacesPit = 0;


  do {
    color(BOLD);
    color(BLUE);
    printf("\nDo you want to create a new hall or use an existant hall for the concert?\n");
    color(RESET);
    printf("  0: Use an existant hall\n  1: New Hall\n");
  } while (!testValues(0, 1, &choice)); // Test

  if (choice == 0){
    do {
      color(BOLD);
      color(BLUE);
      printf("\nEnter the number of concert's hall :\n");
      color(RESET);
    } while (!testValues(1, hallCount, &concert.hallId)); // Test
    concert.hallId -= 1; //so that the hallId is the same as the index of the hall in the hallList
  }
  else{
    createConcertHall(-1); //create a new hall
    hallList = readHallsFromFile(&hallCount); //get the new list with the hall we just create, the hallCount is update again
    concert.hallId = hallCount-1; // so that we get the index of the hall in the list
  }
  

  // Get the hall in which the concert will take place
  hall = hallList[concert.hallId]; 

  color(BOLD);
  color(BLUE);
  printf("\nEnter the name of the artist who will perform :\n");
  color(RESET);
  scanf("%99[^\n]", concert.concertName); //just to get the name

  do {
    color(BOLD);
    color(BLUE);
    printf("\nWill there be a pit during this concert ?: \n");
    color(RESET);
    printf("  0: No\n  1: Yes\n");
  } while (!testValues(0, 1, &concert.pit)); // Tests

  for (int i = 0; i < NB_CATEGORY; i++) {
    do {
      color(BOLD);
      color(BLUE);
      printf("\nEnter the price for category %c :\n", 'A' + i);
      color(RESET);
    } while (
        !testFloatValues(0, 10000, &concert.price[i])); // Test with a float
  }

  do {
    color(BOLD);
    printf("\nThere is a total of %d rows in the hall\n", hall.nbRowsTotal);
    color(RESET);
    sumRows = 0; // Reset sumRows to re-enter the loop
    for (int i = 0; i < 2; i++) { //to enter the number of rows for the first 2 categories
      do {
        color(BOLD);
        color(BLUE);
        printf("\nEnter the number of rows for category %c  :\n", 'A' + i);
        color(RESET);
      } while (!testValues(0, hall.nbRowsTotal,
                           &concert.numRowsCategory[i])); // Test
      sumRows += concert.numRowsCategory[i]; //sum of rows
    }
    if (sumRows > hall.nbRowsTotal) {
      color(BOLD);
      color(RED);
      printf("\n!You have exceeded the maximum number of rows allowed (%d)!\n",
             hall.nbRowsTotal);
      color(RESET);
    }
  } while (sumRows > hall.nbRowsTotal);

  concert.numRowsCategory[2] =
      hall.nbRowsTotal - sumRows; // Number of rows in the third category

  if (concert.pit) {
    for (int i = 0; i < concert.numRowsCategory[0]; i++) {
      concert.nbPlacesPit += hall.seatsPerRow[i] * 2;
    }
  } // If there is a pit, the number of seats in the first category is doubled
  color(BOLD);
  color(BLUE);
  printf("Before you enter the dates, here are the others concerts in the "
         "same hall : \n\n");
  color(RESET);
  displayConcerts(concertCount, concertList, concert.hallId);
  do {

    //Date
    do {
      color(BOLD);
      color(BLUE);
      printf("When does the concert start ? \n");
      color(RESET);
      concert.startDate = getDateInput();

      color(BOLD);
      color(BLUE);
      printf("When does the concert end ? \n");
      color(RESET);
      concert.endDate = getDateInput();

      if (compareDates(concert.startDate, concert.endDate) >= 0) {
        color(BOLD);
        color(RED);
        printf("!You can't put an end date before the start date!\n");
        color(RESET);
      }
    } while (compareDates(concert.startDate,
                          concert.endDate) >= 0); // Test only for date
  } while (!checkConcertOverlap(concert) ||
           !checkConcertDuration(concert.startDate, concert.endDate));

  concert.hallMap = malloc(hall.nbRowsTotal * sizeof(int *)); //create the map of the concert
  if (concert.hallMap == NULL) {
    color(BOLD);
    color(RED);
    perror("\n!Memory allocation for hallMap failed!");
    color(RESET);
    free(hallList);
    free(concertList);
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < hall.nbRowsTotal; i++) {
    concert.hallMap[i] = malloc(MAX_SEATS_PER_ROW * sizeof(int)); 
    if (concert.hallMap[i] == NULL) {
      color(BOLD);
      color(RED);
      perror("\n!Memory allocation for hallMap row failed!");
      color(RESET);
      // Free previously allocated memory before exiting
      for (int j = 0; j < i; j++) {
        free(concert.hallMap[j]);
      }
      free(concert.hallMap);
      free(hallList);
      free(concertList);
      exit(EXIT_FAILURE);
    }
    // Initialize the hall map with 0s
    for (int j = 0; j < hall.seatsPerRow[i]; j++) {
      concert.hallMap[i][j] = 0;
    }
  }

  //----------------------
  //      Save Concert
  //----------------------

  Concert *tempConcertList =
      realloc(concertList,
              (concertCount + 1) *
                  sizeof(Concert)); // Ensure enough memory for the new concert
  
  if (tempConcertList == NULL) {
    color(BOLD);
    color(RED);
    printf("\n!Memory reallocation failed for concertList!\n");
    color(RESET);
    
    // Free allocated memory
    for (int i = 0; i < hall.nbRowsTotal; i++) {
      free(concert.hallMap[i]);
    }
    free(concert.hallMap);
    free(hallList);
    free(concertList); 
    exit(1);
  }
  concertList = tempConcertList;
  concertList[concertCount] = concert; // Save new concert at the end
  writeConcertsToFile(concertList, concertCount + 1); //update the file with the new concert

  color(BOLD);
  color(BLUE);
  printf("\nThe Concert %s has been created successfully.\n\n",
         concert.concertName);
  color(RESET);
  printf("----------------------------\n\n");

  // Free allocated memory
  for (int i = 0; i < hall.nbRowsTotal; i++) {
    free(concert.hallMap[i]);
  }
  free(concert.hallMap);
  free(concertList); // Free the concert list
  free(hallList);    // Free the hall list
}
