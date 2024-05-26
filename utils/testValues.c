#include "../headers/var.h"

// Min: a, Max: b, user input: x
int testValues(int min, int max, int *value) {
  int result;
  result = scanf("%d", value);
  // clear scanf input
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  // Check for input value
  if (*value >= min && *value <= max && result) {
    return 1;
  }
  color(RED);
  color(BOLD);
  printf("\n\n!Please, enter a number between %d and %d!\n\n", min, max);
  color(RESET);
  return 0;
}

// Min: a, Max: b, user input: x
int testFloatValues(int min, int max, float *value) {
  int result;
  result = scanf("%f", value);
  // clear scanf input
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  // Check for input value
  if (*value >= min && *value <= max && result) {
    return 1;
  }
  color(RED);
  color(BOLD);
  printf("\n\n!Please, enter a number between %d and %d!\n\n", min, max);
  color(RESET);
  return 0;
}
