#include "../../headers/var.h"

// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

// Function to modify a concert with a hallId
void modifyConcert(int hallId) {

  // Defining all the variables
  int sumRows = 0;
  // Concert *concert;
  int concertId;

  int concertCount;     // Le nombre de concerts dans la liste
  Concert *concertList; // La liste de concerts
  concertList = readConcertsFromFile(&concertCount);

  Hall *hallList; // La liste de hall
  int hallCount;  // Le nombre de Hall dans la liste
  hallList = readHallsFromFile(&hallCount);

  // Questions

  color(BOLD);
  printf("Here is the list of all the concerts in this hall :\n");
  color(RESET);
  displayConcerts(concertCount, concertList, hallId);

  int *concertDisplayed = malloc(sizeof(int) * concertCount); // the list store the position of
      
                                          // the concerts in a specific hall
  int counter = 0;
  for (int i = 0; i < concertCount; i++) {
    if (concertList[i].hallId == hallId) {
      concertDisplayed[counter] = i;
      counter++;
    }
  }

  do {
    color(BOLD);
    printf("Enter the ID of the concert you want to modify: \n");
    color(RESET);
  } while (!testValues(1, concertCount, &concertId));
  printf("\e[1;1H\e[2J");

  concertList[concertDisplayed[concertId - 1]].nbBookedSeats = 0; // concertList[concertDisplayed[concertId + 1]] is the concert we want to modify
  concertList[concertDisplayed[concertId - 1]].hallState = Empty; 

  printf("Enter the name of the artist :\n");
  scanf("%s", concertList[concertDisplayed[concertId - 1]].concertName);

  do {
    printf("Will there be a pit during this concert ?: \n");
    printf("0: No\n1: Yes\n");
  } while (!testValues(0, 1, &concertList[concertDisplayed[concertId - 1]].pit));

  for (int i = 0; i < NB_CATEGORY; i++) {
    do {
      color(BOLD);
      printf("\nEnter the price for category %c :\n", 'A' + i);
      color(RESET);
    } while (!testFloatValues(0, 10000, &concertList[concertDisplayed[concertId - 1]].price[i]));
  }

  do {
    for (int i = 0; i < 2; i++) {
      do {
        color(BOLD);
        printf("\nEnter the number of rows for category %c :\n", 'A' + i);
        color(RESET);
      } while (!testValues(1, hallList[hallId].nbRowsTotal,
                           &concertList[concertDisplayed[concertId - 1]].numRowsCategory[i]));
      sumRows += concertList[concertDisplayed[concertId - 1]].numRowsCategory[i];
    }
    if (sumRows > hallList[hallId].nbRowsTotal) {
      color(BOLD);
      color(RED);
      printf("!You have exceeded the maximum number of rows allowed (%d)!",
             hallList[hallId].nbRowsTotal);
      color(RESET);
      sumRows = 0; // Reset sumRows to re-enter the loop
    }
  } while (sumRows > hallList[hallId].nbRowsTotal);
  concertList[concertDisplayed[concertId - 1]].numRowsCategory[2] = hallList[hallId].nbRowsTotal - sumRows;

  // The start and the end of the concert
  do {
    printf("When does the concert start ? \n");
    concertList[concertDisplayed[concertId - 1]].startDate = getDateInput();

    printf("When does the concert end ? \n");
    concertList[concertDisplayed[concertId - 1]].endDate = getDateInput();

    if (!compareDates(&concertList[concertDisplayed[concertId - 1]].startDate, &concertList[concertDisplayed[concertId - 1]].endDate)) {
      printf("You can't put an end date before the start date\n");
    }
  } while (!compareDates(&concertList[concertDisplayed[concertId - 1]].startDate, &concertList[concertDisplayed[concertId - 1]].endDate));// a test


  // Save the updated concert list to a file.
  writeConcertsToFile(concertList, concertCount);

  printf("Modified complete");

  // Free memory
  free(hallList);
  free(concertList);
  free(concertDisplayed);
}

// #include <stdio.h>
// #include <stdlib.h>
// Concert *readConcertsFromFile(int *concertCount);
// Hall *readHallsFromFile(int *hallCount);
// void displayConcerts(int concertCount, Concert *concertList, int hallId);
// int testValues(int min, int max, int *value);

// void writeConcertsToFile(Concert *concertList, int concertCount);

// void resetColor();

// void modifyConcert(int hallId) {
//   printf("Here is %d\n", hallId);

//   // Initialize variables
//   int sumRows = 0;
//   int concertId;

//   int concertCount;     // Number of concerts in the list
//   Concert *concertList; // List of concerts
//   concertList = readConcertsFromFile(&concertCount);
//   if (concertList == NULL) {
//     fprintf(stderr, "Error: Could not read concerts from file\n");
//     return;
//   }

//   Hall *hallList; // List of halls
//   int hallCount;  // Number of halls in the list
//   hallList = readHallsFromFile(&hallCount);
//   if (hallList == NULL) {
//     fprintf(stderr, "Error: Could not read halls from file\n");
//     free(concertList);
//     return;
//   }

//   // Display all concerts in the specified hall
//   color(BOLD);
//   printf("Here is the list of all the concerts in this hall:\n");
//   color(RESET);
//   displayConcerts(concertCount, concertList, hallId);

//   // Create a list to store the indices of concerts in the specified hall
//   int *concertDisplayed = malloc(sizeof(int) * concertCount);
//   if (concertDisplayed == NULL) {
//     fprintf(stderr, "Error: Could not allocate memory for concertDisplayed\n");
//     free(hallList);
//     free(concertList);
//     return;
//   }

//   int counter = 0;
//   for (int i = 0; i < concertCount; i++) {
//     if (concertList[i].hallId == hallId) {
//       concertDisplayed[counter] = i;
//       counter++;
//     }
//   }

//   // Select a concert to modify
//   do {
//     color(BOLD);
//     printf("Enter the ID of the concert you want to modify: \n");
//     color(RESET);
//   } while (!testValues(0, counter - 1,
//                        &concertId)); // Corrected range for valid indices
//   printf("\e[1;1H\e[2J");

//   // Get the concert to be modified
//   Concert *concert = &concertList[concertDisplayed[concertId]];
//   concert->nbBookedSeats = 0;
//   concert->hallState = Empty;

//   // Modify concert details
//   printf("Enter the name of the artist:\n");
//   scanf("%s", concert->concertName);

//   do {
//     printf("Will there be a pit during this concert?: \n");
//     printf("0: No\n1: Yes\n");
//   } while (!testValues(0, 1, &concert->pit));

//   for (int i = 0; i < NB_CATEGORY; i++) {
//     do {
//       color(BOLD);
//       printf("\nEnter the price for category %c:\n", 'A' + i);
//       color(RESET);
//     } while (!testFloatValues(0, 10000, &concert->price[i]));
//   }

//   // Modify row counts for each category
//   do {
//     sumRows = 0;
//     for (int i = 0; i < 2; i++) {
//       do {
//         color(BOLD);
//         printf("\nEnter the number of rows for category %c:\n", 'A' + i);
//         color(RESET);
//       } while (!testValues(1, hallList[hallId].nbRowsTotal,
//                            &concert->numRowsCategory[i]));
//       sumRows += concert->numRowsCategory[i];
//     }
//     if (sumRows > hallList[hallId].nbRowsTotal) {
//       color(BOLD);
//       color(RED);
//       printf("!You have exceeded the maximum number of rows allowed (%d)!\n",
//              hallList[hallId].nbRowsTotal);
//       color(RESET);
//     }
//   } while (sumRows > hallList[hallId].nbRowsTotal);
//   concert->numRowsCategory[2] = hallList[hallId].nbRowsTotal - sumRows;

//   // Set concert start and end dates
//   do {
//     printf("When does the concert start?\n");
//     concert->startDate = getDateInput();

//     printf("When does the concert end?\n");
//     concert->endDate = getDateInput();

//     if (!compareDates(&concert->startDate, &concert->endDate)) {
//       printf("You can't put an end date before the start date\n");
//     }
//   } while (!compareDates(&concert->startDate, &concert->endDate));

//   printf("Modification complete\n");

//   // Save the updated concert list to a file
//   writeConcertsToFile(concertList, concertCount);

//   // Free memory
//   free(hallList);
//   free(concertList);
//   free(concertDisplayed);
// }
