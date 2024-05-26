
# CY’Fest Management System

## Description

This project is aimed at developing a management system for the CY’Fest festival, enabling organizers to manage various festival stages and allowing participants to reserve and pay for concert tickets.

## Project Structure

- **headers/**
  - `var.h`
- **manager/**
  - **concerts/**
    - `createConcert.c`
    - `displayConcerts.c`
    - `saveReadConcert.c`
    - `save/concerts.cyfest`
  - **halls/**
    - `createConcertHall.c`
    - `displayHalls.c`
    - `modifyConcertHall.o`
    - `saveReadHalls.c`
    - `viewState.c`
    - `save/halls.cyfest`
  - `createConcertHall.o`
  - `displayHalls.o`
  - `modifyConcertHall.o`
  - `viewState.o`
- **utils/**
  - `dates.c`
  - `testValues.c`

## Completed Parts

### 1. Concert Management
- `createConcert.c` : Allows the creation of new concerts.
- `displayConcerts.c` : Displays existing concerts.
- `saveReadConcert.c` : Manages the saving and reading of concerts from a file.

### 2. Concert Hall Management
- `createConcertHall.c` : Allows the creation of new concert halls.
- `displayHalls.c` : Displays existing concert halls.
- `saveReadHalls.c` : Manages the saving and reading of concert halls from a file.
- `viewState.c` : Displays the state of different halls (ratio of reserved seats to total seats).

### 3. Utilities
- `dates.c` : Functions for handling dates.
- `testValues.c` : Contains functions for testing values.

## Remaining Tasks

### 1. Festival Attendee Mode
- Implement functionality to allow attendees to reserve seats.
- Display the seating plan with available seats and their categories.
- Calculate and display the price of reserved seats.

### 2. Advanced Hall Management
- Implement the ability for the manager to modify hall configurations after a concert ends.
- Add the management of the pit and the ability to double the seats in the pit.

### 3. Suggested Improvements
- Automate the creation of halls from a festival program file.
- Add functionality to find adjacent seats in a given category.

### 4. Error Handling and Stability
- Ensure the application does not crash unexpectedly.
- Handle all possible errors, especially those related to dynamic memory allocation.

### 5. Testing and Validation
- Set up a series of tests to validate existing and new functionalities.
- Document test cases and expected results.

## Compilation and Execution

Use the provided `Makefile` to compile and execute the project:

```sh
make
./cyfest
```

## Authors
Nguyen Thuy Tran, Decrand Lardière Romain, Da Costa Silva Mathias
