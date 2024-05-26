#ifndef VAR_H
#define VAR_H

// Inclusion of necessary standard libraries
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//----------------------
//      CONSTANT
//----------------------

// Defining constants for maximum lengths and limits
#define CHAR_MAX_LENGTH 100
#define NB_CATEGORY 3
#define MAX_HALLS 10
#define MAX_ROWS 10000000
#define MAX_SEATS_PER_ROW 100

// Macros for setting terminal text color
#define color(param) printf("\033[%sm", param)

// Define color codes
#define RESET "0"     // Reset colo
#define RED "31"      // Red text
#define GREEN "32"    // Green text
#define YELLOW "33"   // Yellow text
#define BLUE "34"     // Blue text
#define MAGENTA "35"  // Magenta text
#define CYAN "36"     // Cyan text
#define WHITE "37"    // White text
#define BOLD "1"      // Bold text
#define UNDERLINE "4" // Underline text

//----------------------
//        STRUCT
//----------------------

// Enumeration to represent the state of a hall
typedef enum { Empty, Partial, Full } HallState;

// Structure to represent a date and time
typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
} Date; // Date of the concert

// Structure to represent a concert hall
typedef struct {
  char hallName[CHAR_MAX_LENGTH]; // Name of the hall
  int nbRowsTotal;                // Total number of rows in the hall
  int *seatsPerRow; // Array representing the number of seats per row
  int totalSeats;   // Total number of seats in the hall
} Hall;

// Structure to represent a concert
typedef struct {
  int hallId; // ID of the hall where the concert takes place
  char concertName[CHAR_MAX_LENGTH]; // Name of the concert
  int pit;                           // Indicates if the concert has a pit area
  int nbPlacesPit;          // Number of places in the pit area (if pit is true)
  int nbBookedPlacesPit;    // Number of booked places in the pit area
  float price[NB_CATEGORY]; // Prices for different categories
  int numRowsCategory[NB_CATEGORY]; // Number of rows per category (A, B, C)
  int nbBookedSeats;                // Total number of booked seats
  HallState hallState;              // State of the hall (Empty, Partial, Full)
  int **hallMap;                    // Map of the hall seating arrangement
  Date startDate;                   // Start date and time of the concert
  Date endDate;                     // End date and time of the concert
} Concert;

//----------------------
//        UTILS
//----------------------

// Dates functions
int DateToMin(Date date);
int compareDatesInMinutes(Date date1, Date date2);
int checkConcertDuration(Date startDate, Date endDate);
Date getDateInput();
int compareDates(Date date1, Date date2);
int checkConcertOverlap(Concert concert);
int isPastDate(Date *date);
int compareDatesInMinutes(Date date1, Date date2);

// Values functions
int testValues(int min, int max, int *value);
int testFloatValues(int min, int max, float *value);

#endif /* VAR_H */