#include "../headers/var.h"
#include "../headers/manager.h"
// Disable fread warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"

/**
 * Validate a given date.
 *
 * @param date struct tm representing the date to validate.
 * @return 1 if the date is valid, 0 otherwise.
 */

// Fonction pour comparer deux dates en minutes

int DateToMin(Date date) {
  
    int totalMinutes = 0;
  
    //this function converts a date to minutes ( bissextile year and the difference total of days in month will be take into account)
    int daysMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0)){
        daysMonth[1] = 29; //bissextile year
    }


    // sum of min in full years
    for (int y = 1; y < date.year; y++) { //that is why we go from 1 to date.year -1 
        if (y%4 == 0){
            totalMinutes = totalMinutes + 366 * 24 * 60; // bissextile
        }
        else {totalMinutes = totalMinutes + 356 * 24 * 60;}
    }

    //sum of min in full months
    for (int m = 1; m < date.month; m++) { // same logic as years
        totalMinutes = totalMinutes + daysMonth[m-1] * 24 * 60 ;
    }

    // sum of min in full days 
    totalMinutes = totalMinutes +(date.day - 1) * 24 * 60; //same logic for days as years

    // sum of the rest hours and min
    totalMinutes = totalMinutes + date.hour * 60 + date.minute;
    return totalMinutes;
}


int compareDatesInMinutes(Date date1, Date date2) {
  int totalMinutesDate1 = DateToMin(date1);
  int totalMinutesDate2 = DateToMin(date2);

  // Retourner la différence totale en minutes
  return totalMinutesDate2 - totalMinutesDate1;
  
}

// Function to check the duration of a concert
int checkConcertDuration(Date startDate, Date endDate) {
  int differenceInMinutes = compareDatesInMinutes(startDate, endDate);
  if (differenceInMinutes < 30) {
    color(BOLD);
    color(RED);
    printf("\n!Concert too short, it has to last more than 30 minutes!\n\n");
    color(RESET);
    return 0;
  }
  if (differenceInMinutes > 240) {
    color(BOLD);
    color(RED);
    printf("\n!Concert too long, it must not exceed 4 hours!\n\n");
    color(RESET);
    return 0;
  }
  return 1;
}

Date getDateInput() {
  Date date;

  do {
    printf("  Enter the year: ");
  } while (!testValues(2024, 2030, &date.year));

  do {
    printf("  Enter the month (1-12): ");
  } while (!testValues(1, 12, &date.month));

  do {
    printf("  Enter the day (1-31): ");
  } while (!testValues(1, 31, &date.day));

  do {
    printf("  Enter the hour (0-23): ");
  } while (!testValues(0, 23, &date.hour));

  do {
    printf("  Enter the minute (0-59): ");
  } while (!testValues(0, 59, &date.minute));

  return date;
}


int compareDates(Date date1, Date date2) {
  // This function compares two dates
  // Return -1 if the difference between the two dates is equal or less than 4H
  // and equal or more than 1 min. Return 0 if the date2 is before the date1 or
  // that the two dates are similar
  if (date1.year != date2.year)
    return date1.year - date2.year;
  if (date1.month != date2.month)
    return date1.month - date2.month;
  if (date1.day != date2.day)
    return date1.day - date2.day;
  if (date1.hour != date2.hour)
    return date1.hour - date2.hour;
  return date1.minute - date2.minute;
}

int checkConcertOverlap(Concert concert) {
  int concertCount;
  Concert *concertList = readConcertsFromFile(&concertCount);
  int overlap = 1;

  for (int i = 0; i < concertCount; i++) {
    if (concert.hallId == concertList[i].hallId) {
      if (compareDates(concert.startDate, concertList[i].endDate) < 0 &&
          compareDates(concert.endDate, concertList[i].startDate) > 0) {
        color(BOLD);
        color(RED);
        printf(
            "\n!There already is %s's concert between %04d-%02d-%02d %02d:%02d "
            "and %04d-%02d-%02d %02d:%02d!\n\n",
            concertList[i].concertName, concertList[i].startDate.year,
            concertList[i].startDate.month, concertList[i].startDate.day,
            concertList[i].startDate.hour, concertList[i].startDate.minute,
            concertList[i].endDate.year, concertList[i].endDate.month,
            concertList[i].endDate.day, concertList[i].endDate.hour,
            concertList[i].endDate.minute);
        color(RESET);
        overlap = 0;
        break;
      }
    }
  }
  free(concertList); // Free the concert list
  return overlap;
}

// Function to check if a date is in the past
int isPastDate(Date *date) {
  time_t now = time(NULL);
  struct tm *now_tm = localtime(&now);

  Date currentDate;
  currentDate.year = now_tm->tm_year + 1900;
  currentDate.month = now_tm->tm_mon + 1;
  currentDate.day = now_tm->tm_mday;
  currentDate.hour = now_tm->tm_hour;
  currentDate.minute = now_tm->tm_min;

  return compareDates(*date, currentDate) < 0;
}
