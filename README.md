
# CY'FEST Management System

Welcome to the CY'FEST Management System! This project is designed to help festival organizers manage different stages and concerts efficiently. It provides functionalities for both festival managers and Festival-goers, ensuring smooth operations and reservations.

## Table of Contents

- [Project Description](#project-description)
- [Features](#features)
  - [Manager Mode](#manager-mode)
  - [Festival-goer Mode](#Festival-goer-mode)
- [Installation](#installation)
- [Usage](#usage)
  - [Running the Application](#running-the-application)
  - [Manager Mode](#manager-mode-usage)
  - [Festival-goer Mode](#Festival-goer-mode-usage)
- [File Structure](#file-structure)
- [Authors](#authors)
- [License](#license)

## Project Description

The CY'FEST Management System is designed to manage festival stages, handle reservations, and provide a seamless experience for both managers and Festival-goers. The project leverages dynamic memory allocation, file management, and user-friendly interfaces to ensure robust performance and usability.

## Features

### Manager Mode

- **Create Concert Halls**: Set up new concert halls with customized seating arrangements.
- **Manage Concerts**: Schedule concerts, assign halls, and manage seating categories and prices.
- **View and Modify Halls**: Display the state of concert halls, modify configurations, and update seating arrangements.
- **Persistent Data**: Save and load hall and concert data to and from files.

### Festival-goer Mode

- **View Available Concerts**: Display upcoming concerts with available seating.
- **Make Reservations**: Reserve seats for concerts, view seating plans, and see pricing details.
- **User-friendly Interface**: Navigate through the reservation process easily.

## Installation

1. Clone the repository from GitHub:
   \`\`\`sh
   git clone https://github.com/yourusername/cyfest-management-system.git
   \`\`\`
2. Navigate to the project directory:
   \`\`\`sh
   cd cyfest-management-system
   \`\`\`
3. Compile the project using the provided Makefile:
   \`\`\`sh
   make
   \`\`\`

## Usage

### Running the Application

To run the application, use the following command:
\`\`\`sh
./cyfest
\`\`\`

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

### Festival-goer Mode Usage

1. **View Available Concerts**:
   - Browse through the list of upcoming concerts with open reservations.

2. **Make Reservations**:
   - Select a concert, choose seats from the seating plan, and confirm the reservation.
   - View the total cost and reserved seat details.

## File Structure

\`\`\`
cyfest-management-system/
├── manager/
│   ├── halls/
│   │   ├── createConcertHall.c
│   │   ├── displayHalls.c
│   │   ├── modifyHall.c
│   │   └── viewState.c
│   ├── concerts/
│   │   ├── createConcert.c
│   │   ├── displayConcerts.c
│   │   ├── findConcert.c
│   │   ├── modifyConcert.c
│   │   └── saveReadConcert.c
├── utils/
│   ├── dates.c
│   └── testValues.c
├── headers/
│   ├── manager.h
│   ├── festivalier.h
│   ├── utils.h
│   └── var.h
├── main.c
├── Makefile
└── README.md
\`\`\`

## Authors

- Nguyen Thuy Tran
- Decrand Lardière Romain
- Da Costa Silva Mathias

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
