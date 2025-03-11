# Seat Reservation System

This document provides an overview of the Seat Reservation System, a C++ program designed to manage seat availability and ticket sales for a venue. The program features a text-based interface that displays seating charts, presents ticket pricing, processes ticket purchases, and generates sales reports.

---

## Overview

The system is built for a venue with 15 rows and 30 columns of seats. It uses a file named `SeatAvailability.txt` to store the current state of seat availability. If the file does not exist when the program starts, it is automatically created and initialized with all seats available.

---

## Key Functionalities

- **Display Seating Chart:**  
  Presents a formatted seating layout where available seats are denoted by `O` and sold seats by `X`.

- **View Ticket Prices:**  
  Lists the ticket prices for each row, enabling users to review cost details before making a selection.

- **Purchase Tickets:**  
  Allows users to select one or more seats. The program validates the availability of the chosen seats, calculates the total cost based on row-specific pricing, and updates the seating data accordingly.

- **View Sales Report:**  
  Generates a report detailing the total number of seats, the number of seats sold, available seats, and the overall revenue generated from ticket sales.

---

## Program Structure

- **File Operations:**  
  - `loadSeats(bool seats[ROWS][COLS])`: Reads seat data from `SeatAvailability.txt`. If the file is missing, it creates and initializes it.
  - `saveSeats(const bool seats[ROWS][COLS])`: Writes the current seating state to `SeatAvailability.txt`.

- **User Interface Functions:**  
  - `displayChart(bool seats[ROWS][COLS])`: Displays the seating chart.
  - `viewTicketPrices(const double rowPrice[ROWS])`: Outputs the pricing details for each row.
  - `purchaseTicket(bool seats[ROWS][COLS], const double rowPrice[ROWS])`: Handles the process of purchasing tickets, including validation and cost calculation.
  - `viewSalesReport(const bool seats[ROWS][COLS], const double rowPrice[ROWS])`: Provides a summary of ticket sales and seating availability.

- **Main Function:**  
  Implements a menu-driven loop that prompts the user to select an action until the program is terminated.

---

## Compilation and Execution

1. **Requirements:**  
   A C++ compiler (e.g., `g++`) is required.

2. **Compilation Steps:**  
   - Open your terminal or command prompt.
   - Navigate to the directory containing the source file (e.g., `SeatReservation.cpp`).
   - Compile the program using:
     ```bash
     g++ -o SeatReservation SeatReservation.cpp
     ```

3. **Running the Program:**  
   Execute the compiled binary:
   ```bash
   ./SeatReservation
