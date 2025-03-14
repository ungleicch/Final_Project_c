// authors: Maxwell Furtwangler, Jack Heupel, Tom Malter
// Final Project
// V.5
// 13. March 25
// Github: https://github.com/ungleicch/Final_Project_c
#include <iostream>
#include <fstream>

// const Row and Cols
static const int ROWS = 15;
static const int COLS = 30;

// fuction structure
int loadSeats(bool seats[ROWS][COLS]); //loading the seats from the file into the array
int saveSeats(const bool seats[ROWS][COLS]); // saves the seats from the to the file
void displayChart(bool seats[ROWS][COLS]); // displays the chart of seats with the taken and availabile ones
void viewTicketPrices(const double rowPrice[ROWS]); // showes the price for every row
void purchaseTicket(bool seats[ROWS][COLS], const double rowPrice[ROWS]); // andeling the user input and processing for buying a seat
void viewSalesReport(const bool seats[ROWS][COLS], const double rowPrice[ROWS]); // showes an overview of the total seats availabil sold and amount money made.

int main(){
    // seats array
    bool seats[ROWS][COLS] = {false}; // all are not taken

    // array of prices for the rows
    double rowPrice[ROWS] = {10, 10, 10, 15, 15, 15, 20, 20, 20, 25, 25, 25, 30, 30, 30};

    if (loadSeats(seats) == -1) { // if the loading returns -1, we know something went wrong error
        std::cout << "Failing to load or create the SeatAvailability.txt, Program is exited !!!" << std::endl; // exiting and error
        return 1; // ending the program
    }

    bool exit = false; // validation variable
    while (!exit){ // run this until the user chose the Exit option
        std::cout << "\n---- MENU ----\n" << std::endl // print out the title Menu
        << "1. Display Seating Chart" << std::endl // print out first option: The seat chart
        << "2. View Ticket Price for Each Row" << std::endl // print out the second option: The view ticket price for all the rows
        << "3. Purchase tickets" << std::endl // print out the third option andeling the ticket buying
        << "4. View Ticket Sales Report" << std::endl // print out the 4. option to view the ticket sales report
        << "5. Exit the Program" << std::endl // print out the 5. option to exit the program
        << "Enter your choice of extions in terms of the number (1-5): "; // prompting the user to choose an option
        int choice; // int to save the option
        std::cin >> choice; // read in the option into choice

        switch (choice){
            case 1:
                displayChart(seats); // call of displaying the chart
                break;
            case 2:
                viewTicketPrices(rowPrice); // call of viewing the ticket prices
                break;
            case 3:
                purchaseTicket(seats, rowPrice); // call of andling buying tickets
                break;
            case 4:
                viewSalesReport(seats, rowPrice); // call of the function to see the overall report
                break;
            case 5:
                exit = true; // changing the exit variable to true to end the program no new loop is executed
                break;
            default:
                std::cout << "Invalid choice!! Please try again, with a valid number." << std::endl; // number not in the list (1-5) prompts the user to enter a valid number
                break;
        }
    }
    // if the program is here, we have the exit variable to true and this is only executed if the user wants to exit the program
    if (saveSeats(seats) == -1){ // if the return == -1 / something went wrong
        std::cerr << "Error saving the updated seat data." << std::endl; // error if we were not able to save the data
    } else {
        std::cout << "Seat data was updated successfully!!!" << std::endl; // we were able to save the data to the file
    }
    std::cout << "Exiting the program..." << std::endl; // final output
    return 0;
}

// function to load the seats into the array from the text file
int loadSeats(bool seats[ROWS][COLS]){
    std::ifstream inFile("SeatAvailability.txt"); // input stream is the "SeatAvailability.txt" file
    if(!inFile){
        // file does not exist, creat file
        std::ofstream outFile("SeatAvailability.txt");
        if (!outFile) { // if we were not able to creat the new file, we send an error
            std::cerr << "Error: could not find the SeatAvailability file and also not create it..." << std::endl;
            return -1; // return -1 for our main to catch and handel the error
        }
        // file was newly created, this part is executed
        for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
                seats[i][j] = false; // array with only false because new file created
                outFile << 0 << " "; // new file with only 0's
            }
            outFile << "\n"; // next row
        }
        outFile.close(); // close the file
        std::cout << "A new SeatAvailability file was created, with all seats available." << std::endl; // print out that we created the new file succesfuly
        return 1; // returns 1 to catch for the main function
    }

    // if the file exists, read the seat data into the array
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            int value;
            if (!(inFile >> value)) { // if we are not able to read in the values into the int variable
                std::cerr << "Error reading in the seat data from the file..." << std::endl; // output the error
                inFile.close(); // close the file
                return -1; // return -1 to catch for the main function
            }
            seats[i][j] = (value != 0); // true or false into the postion
        }
    }
    inFile.close(); // close the file
    return 1;
}

int saveSeats(const bool seats[ROWS][COLS]){
    std::ofstream outFile("SeatAvailability.txt", std::ios::trunc); // trunc clears file rewrites it
    if (!outFile){ // file not able to read in, give error
        std::cerr << "Error opening the SeatAvailability file..." << std::endl;
        return -1;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            outFile << (seats[i][j] ? 1 : 0) << " ";// is the value in seats[i][j] meaning is it true if yes write 1 else write 0 = false
        }
        outFile << std::endl;
    }
    outFile.close();
    return 1;
}

void displayChart(bool seats[ROWS][COLS]){
    std::cout << "\n\t\tSeats\n";
    //Display the column numbers
    std::cout << "       \t ";
    for(int tens = 0; tens < 1; tens++) { //display tens digits (1-9)
        for(int ones = 1; ones < 10; ones++) {
            std::cout << tens;
        }
    }

    for(int tens = 1; tens < 3; tens++) { //display tens digits (0-9)
        for(int ones = 0; ones < 10; ones++) {
            std::cout << tens;
        }
    }
    std::cout << 3; //display the 3 for 30

    std::cout << "\n     \t ";
    for(int tens = 0; tens < 1; tens++) { //display ones digits (1-9)
        for(int ones = 1; ones < 10; ones++) {
            std::cout << ones;
        }
    }

    for(int tens = 1; tens < 3; tens++) { //display ones digits (0-9)
        for(int ones = 0; ones < 10; ones++) {
            std::cout << ones;
        }
    }
    std::cout << 0; //display the 0 for 30

    std::cout << std::endl;
    for(int row = 0; row < ROWS; row++) { //display the chart
        std::cout << "Row " << row + 1;
        if (row + 1 < 10) {
            std::cout << "  : ";
        } else {
            std::cout << " : ";
        }
        for (int col = 0; col < COLS; col++){
            std::cout << (seats[row][col] ? "X" : "O"); // if true = X if false O
        }
        std::cout << std::endl;
    }
}

// printing out the prices for each row
void viewTicketPrices(const double rowPrice[ROWS]){
    std::cout << "\nRow Prices:\n";
    for (int i = 0; i < ROWS; i++){ // prining all the prices
        std::cout << "Row " << i + 1 << ": $" << rowPrice[i] << std::endl;
    }
}

// is called to buy a ticket
void purchaseTicket(bool seats[ROWS][COLS], const double rowPrice[ROWS]){
    int rowNum, colNum, seatNum; // rowNum = the row number, colNUm = is the column number, the seatNum = number of how many seats the user wants
    std::cout << "\nHow many seats would you like to purchase? ";
    std::cin >> seatNum; // number of seats requested
    while (seatNum < 1) { // validata at least one seat
        std::cout << "Invalid number of seats. You must purchase at least 1 seat." << std::endl;
        std::cout << "Enter a valid number or (-1) to return to the Menu";
        std::cin >> seatNum;
        if (seatNum == -1){ // return to the menu // if the usre wants to return to the Menu enter -1
            return;
        }
    }
    int selectedRow[seatNum]; // array with len of the amount of seats (for the rows)
    int selectedCol[seatNum]; // array with the len of the amount of seats (for the columns)
    double totalCost = 0; // storing the total cost for the transaction

    bool tempSeats[ROWS][COLS]; // create a temp array to check in the run time in the ongoing transaction that the user int not taking the same seat again
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            tempSeats[i][j] = seats[i][j]; // populate the temp array
        }
    }

    for (int i = 0; i < seatNum; i++) { // for the amout of seats we will run this loop x times
        std::cout << "Enter the data for the " << i + 1 << " seat."; // Tell the user the x's seat is processed right now
        std::cout << "\nEnter row number (1-" << ROWS << "): "; // number for the row the user wants
        std::cin >> rowNum;
        while (rowNum < 1 || rowNum > ROWS){ // validate the row (1-15)
            std::cout << "Invalid row number!!" << std::endl;
            std::cout << "Enter a valid number:";
            std::cin >> rowNum;
        }
        std::cout << "Enter a column number (1-" << COLS << "): "; // prompting to enter the column number the user wants
        std::cin >> colNum;
        while(colNum < 1 || colNum > COLS){ // validata the column (1-30)
            std::cout << "Invalid column number!!" << std::endl;
            std::cout << "Enter a valid number:";
            std::cin >> colNum;
    }
    int realRow = rowNum - 1; // real value for the row
    int realCol = colNum - 1; // real value for the col (-1)

    if (seats[realRow][realCol] || tempSeats[realRow][realCol]) { // if 1 = true is taken also for or temp one
        char next; // next = next action yes or no
        std::cout << "Sorry, that seat is already sold or selected in this transaction." << std::endl; // tell the user the seat is taken
        std::cout << "Do you want to chose a different seat ? (y/n):"; // ask if he wants a diffent seat
        std::cin >> next;
        next = std::tolower(next);
        if (next == 'y'){ // if the aswer is y for yes we decrease i by 1 to have the loop run again, keep the amount of seats the user entered
            i--;
            continue; // redo the loop
        } else {
            std::cout << "Back to the Menu." << std::endl; // go back to the menue if n or any other chracter or number
            return;
        }
    }
    tempSeats[realRow][realCol] = true; // if we are here, we know the seat is not taken so we set the seat to true = 1
    selectedRow[i] = realRow; // we add the real row the user choose for the seat to the row array
    selectedCol[i] = realCol; // we add teh real column the user choose to the seat to the column array
    totalCost += rowPrice[realRow]; // add the price of a seat in the spesifc row to the total cost of the current transaction
    }
    std::cout << "\n---- Ticket Bill ----\n"; // print out the bill for the user after the loop is done
    for (int i = 0; i < seatNum; i++){ // for the amount of seats we do this loop
        std::cout << "Seat " << i + 1 << ": Row " << selectedRow[i] + 1 // we print out the seat number respectively to the amount of seats the uer choose + the Row and Column
        << ", Column " << selectedCol[i] + 1 << ", Price: " << rowPrice[selectedRow[i]] << std::endl; // and the price or the seat
    }
    std::cout << "Total Price for " << seatNum << " seat(s): $" << totalCost << std::endl; // we print out the total price of the transaction
    std::cout << "Confirm purchase? (y/n): "; // ask the user if he wants to buy the selected seats
    char confirm; // store the answer
    std::cin >> confirm;
    confirm = std::tolower(confirm);
    if (confirm == 'y') { // if the user agree with 'y' or 'Y'
        for (int i = 0; i < seatNum; i++) { // we have a loop adding the seats to the seat array make them true / taken
            seats[selectedRow[i]][selectedCol[i]] = true;
        }
        std::cout << "Purchase successful! Seats have been reserved." << std::endl; // enter a succes of the transaction
    } else {
        std::cout << "Purchase canceled. No seats were reserved." << std::endl; // if the user typed something else we end the fuction without saving
    }

}

// function to print out the Report (not the runtime report, it is the over all report)
void viewSalesReport(const bool seats[ROWS][COLS], const double rowPrice[ROWS]){
    int totalSold = 0; // counts the total sold seats
    double totalRevenue = 0; // stores the total money made

    // loop over all rows
    for (int i = 0; i < ROWS; i++){
        int rowSold = 0; // sets the seat's in the row to 0 at the start
        for (int j = 0; j < COLS; j++){ // for every column
            if (seats[i][j]) { // if 'is' just caling gives a true or false / if true
                rowSold++; // we add one to is sold in the row
            }
        }
        totalSold += rowSold; // to the total sold seats we add the seats that were sold in the spesific row
        totalRevenue += rowSold * rowPrice[i]; // adding the amount of seats multiplied by the price to the total revenue
    }
    int totalSeats = ROWS * COLS; // total seats are the rows we have times the columns we have
    int totalAvailable = totalSeats - totalSold; // the total avaialbe seats are the seats after substacting the sold seats from the total seats

    std::cout << "\n======= TICKET SALES REPORT =======" << std::endl // print out of the report
    << "Total Seats:      " << totalSeats << std::endl // The amount of seats we have over all
    << "Seats Sold:       " << totalSold << std::endl // the number of seats we sold
    << "Seats Available:  " << totalAvailable << std::endl // Total number of seats that are free
    << "Total Revenue:   $" << totalRevenue << std::endl; // total amount of money made
}
