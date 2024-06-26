
# CY'FEST

Welcome to the CY'FEST Management System! This project is designed to help festival organizers manage different stages and concerts efficiently. It provides functionalities for both festival Managers and Festival-Goers, ensuring smooth operations and reservations.
 
## Table of Contents

- [Project Description](#project-description)
- [Features](#features)
  - [Manager Mode](#manager-mode)
  - [Festival-Goer Mode](#Festival-goer-mode)
- [Installation](#installation)
- [Usage](#usage)
  - [Running the Application](#running-the-application)
  - [Manager Mode](#manager-mode-usage)
  - [Festival-Goer Mode](#Festival-goer-mode-usage)
- [File Structure](#file-structure)
- [Authors](#authors)

## Project Description

The CY'FEST Management System is designed to manage festival stages, handle reservations, and provide a seamless experience for both managers and Festival-Goers. The project leverages dynamic memory allocation, file management, and user-friendly interfaces to ensure robust performance and usability.

## Features

### Manager Mode

- **Create Concert Halls**: Set up new concert halls with customized seating arrangements.
- **Manage Concerts**: Schedule concerts, assign halls, and manage seating categories and prices.
- **View and Modify Halls**: Display the state of concert halls, modify configurations, and update seating arrangements.
- **Persistent Data**: Save and load hall and concert data to and from files.

### Festival-Goer Mode

- **View Available Concerts**: Display upcoming concerts with available seating.
- **Make Reservations**: Reserve seats for concerts, view seating plans, and see pricing details.
- **User-friendly Interface**: Navigate through the reservation process easily.

## Installation

1. Clone the repository from GitHub:
   ```sh
   git clone https://github.com/mxth2xs/CY-Fest.git
   ```
2. Navigate to the project directory:
   ```sh
   cd Cy-Fest
   ```
3. Compile the project using the provided Makefile:
   ```sh
   make
   ```

## Usage

### Running the Application

To run the application, use the following command:
```sh
./cyfest
```

### Manager Mode Usage

1. **Create a Concert Hall**:
   - Follow the prompts to define the hall name, number of rows, and seats per row.
   - Assign seating categories and set prices.

2. **Manage Concerts**:
   - Schedule new concerts, assign them to halls, and set end times.
   - Modify existing concerts and update hall configurations as needed.

3. **View and Modify Halls**:
   - Check the status of concert halls, including seat availability.
   - Make changes to hall layouts and update seating arrangements.

### Festival- Goer Mode Usage

1. **View Available Concerts**:
   - Browse through the list of upcoming concerts with open reservations.

2. **Make Reservations**:
   - Select a concert, choose seats from the seating plan, and confirm the reservation.
   - View the total cost and reserved seat details.

## File Structure

```
Cy-Fest/
├── headers
│   ├── festival.h
│   ├── manager.h
│   └── var.h
├── utils
│   ├── dates.c
│   └── testValues.c
├── festivalGoer
│   ├── bookInPit.c
│   ├── bookInSeated.c
│   ├── bookSeats.c
│   ├── isBooked.c
│   ├── printSeatedMapStatus.c
│   └── printStatusConcertHall.c
├── manager
│   ├── concerts
│   │   ├── createConcert.c
│   │   ├── displayConcerts.c
│   │   ├── findConcert.c
│   │   ├── saveReadConcert.c
│   │   └── viewState.c
│   └── halls
│       ├── createConcertHall.c
│       ├── displayHalls.c
│       ├── modifyHall.c
│       └── saveReadHalls.c
├── main.c
├── Makefile
└── README.md



```

## Authors

- Nguyen Thuy Tran
- Decrand Lardière Romain
- Da Costa Silva Mathias
