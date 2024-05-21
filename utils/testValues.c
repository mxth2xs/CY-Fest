#include "../headers/var.h"

// Min: a, Max: b, user input: x
int testValues(int min, int max, int value) {
  // clear scanf input
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
  // Check for input value
  if (value >= min && value <= max) {
    return 1;
  } else {
    color(RED);
    printf("Please, enter a number between %d and %d \n", min, max);
    color(RESET);
    return 0;
  }
}
