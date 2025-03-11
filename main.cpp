#include <iostream>
#include <fstream>

// const Row and Cols
static const int ROWS = 15;
static const int COLS = 30;

// fuction structure
int loadSeats(bool seats[ROWS][COLS]);
int saveSeats(const bool seats[ROWS][COLS]);
void displayChart(bool seats[ROWS][COLS]);
void viewTicketPrices(const double rowPrice[ROWS]);
void purchaseTicket(bool seats[ROWS][COLS], const double rowPrice[ROWS]);
void viewSalesReport(const bool seats[ROWS][COLS], const double rowPrice[ROWS]);

int main(){
    // seats array
    bool seats[ROWS][COLS] = {false}; // all are not taken

    // array of prices for the rows
    double rowPrice[ROWS] = {10, 10, 10, 15, 15, 15, 20, 20, 20, 25, 25, 25, 30, 30, 30};

    if (loadSeats(seats) == -1) { // if the loading returns -1, we know something went wrong error
        std::cout << "Failing to load or create the SeatAvailability.txt, Program is exited !!!" << std::endl;
        return 1;
    }

    // run this until the user chose the Exit
    bool exit = false;
    while (!exit){
        std::cout << "\n---- MENU ----\n" << std::endl
        << "1. Display Seating Chart" << std::endl
        << "2. View Ticket Price for Each Row" << std::endl
        << "3. Purchase tickets" << std::endl
        << "4. View Ticket Sales Report" << std::endl
        << "5. Exit the Program" << std::endl
        << "Enter your choice of extions in terms of the number (1-5): ";
        int choice;
        std::cin >> choice;

        switch (choice){
            case 1:
                displayChart(seats);
                break;
            case 2:
                viewTicketPrices(rowPrice);
                break;
            case 3:
                purchaseTicket(seats, rowPrice);
                break;
            case 4:
                viewSalesReport(seats, rowPrice);
                break;
            case 5:
                exit = true;
                break;
            default:
                std::cout << "Invalid choice!! Please try again, with a valid number." << std::endl;
                break;
        }
    }
    if (saveSeats(seats) == -1){ // if the return == -1 / something went wrong
        std::cerr << "Error saving the updated seat data." << std::endl;
    } else {
        std::cout << "Seat data was updated successfully!!!" << std::endl;
    }
    std::cout << "Exiting the program..." << std::endl;
    return 0;
}

int loadSeats(bool seats[ROWS][COLS]){
    std::ifstream inFile("SeatAvailability.txt");
    if(!inFile){
        // file does not exist, creat file
        std::ofstream outFile("SeatAvailability.txt");
        if (!outFile) {
            std::cerr << "Error: could not find the SeatAvailability file and also not create it..." << std::endl;
            return -1;
        }
        for (int i = 0; i < ROWS; i++){
            for (int j = 0; j < COLS; j++){
                seats[i][j] = false; // array with only false because new file created
                outFile << 0 << " "; // new file with only 0's
            }
            outFile << "\n";
        }
        outFile.close();
        std::cout << "A new SeatAvailability file was created, with all seats available." << std::endl;
        return 1;
    }

    // if the file exists, read teh seat data into the array
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            int value;
            if (!(inFile >> value)) {
                std::cerr << "Error reading in the seat data from the file..." << std::endl;
                inFile.close();
                return -1;
            }
            seats[i][j] = (value != 0); // true or false into the postion
        }
    }
    inFile.close();
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
    std::cout << "    \t";
    for(int tens = 0; tens < 3; tens++) { //display tens digits
        for(int ones = 0; ones < 10; ones++) {
            std::cout << tens;
        }
    }

    std::cout << "\n    \t";
    for(int tens = 0; tens < 3; tens++) { //display ones digits
        for(int ones = 0; ones < 10; ones++) {
            std::cout << ones;
        }
    }

    std::cout << std::endl;
    for(int row = 0; row < ROWS; row++) { //display the chart
        std::cout << "Row " << row + 1;
        if (row + 1 < 10) {
            std::cout << "  : ";
        } else {
            std::cout << " : ";
        }
        for (int col = 0; col < COLS; col++){
            std::cout << (seats[row][col] ? "X" : "O"); // if ture = X if false O
        }
        std::cout << std::endl;
    }
}

void viewTicketPrices(const double rowPrice[ROWS]){
    std::cout << "\nRow Prices:\n";
    for (int i = 0; i < ROWS; i++){ // prining all the prices
        std::cout << "Row " << i + 1 << ": $" << rowPrice[i] << std::endl;
    }


}

void purchaseTicket(bool seats[ROWS][COLS], const double rowPrice[ROWS]){
    int rowNum, colNum, seatNum;
    std::cout << "\nHow many seats would you like to purchase? ";
    std::cin >> seatNum;
    while (seatNum < 1) {
        std::cout << "Invalid number of seats. You must purchase at least 1 seat." << std::endl;
        std::cout << "Enter a valid number or (-1) to return to the Menu";
        std::cin >> seatNum;
        if (seatNum == -1){ // return to the menu
            return;
        }
    }
    int selectedRow[seatNum];
    int selectedCol[seatNum];
    double totalCost = 0;

    bool tempSeats[ROWS][COLS];
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            tempSeats[i][j] = seats[i][j];
        }
    }

    for (int i = 0; i < seatNum; i++) {
        std::cout << "Enter the data for the " << i + 1 << " seat.";
        std::cout << "\nEnter row number (1-" << ROWS << "): ";
        std::cin >> rowNum;
        while (rowNum < 1 || rowNum > ROWS){
            std::cout << "Invalid row number!!" << std::endl;
            std::cout << "Enter a valid number:";
            std::cin >> rowNum;
        }
        std::cout << "Enter a column number (1-" << COLS << "): ";
        std::cin >> colNum;
        while(colNum < 1 || colNum > COLS){
            std::cout << "Invalid column number!!" << std::endl;
            std::cout << "Enter a valid number:";
            std::cin >> colNum;
    }
    int realRow = rowNum - 1; // real value for the row
    int realCol = colNum - 1; // real value for the col (-1)

    if (seats[realRow][realCol] || tempSeats[realRow][realCol]) { // if 1 = true is taken also for or temp one
        char next;
        std::cout << "Sorry, that seat is already sold or selected in this transaction." << std::endl;
        std::cout << "Do you want to chose a different seat ? (y/n):";
        std::cin >> next;
        next = std::tolower(next);
        if (next == 'y'){
            i--;
            continue;
        } else {
            std::cout << "Back to the Menu." << std::endl;
            return;
        }
    }
    tempSeats[realRow][realCol] = true;
    selectedRow[i] = realRow;
    selectedCol[i] = realCol;
    totalCost += rowPrice[realRow];
    }
    std::cout << "\n---- Ticket Bill ----\n";
    for (int i = 0; i < seatNum; i++){
        std::cout << "Seat " << i + 1 << ": Row " << selectedRow[i] + 1
        << ", Column " << selectedCol[i] + 1 << ", Price: " << rowPrice[selectedRow[i]] << std::endl;
    }
    std::cout << "Total Price for " << seatNum << " seat(s): $" << totalCost << std::endl;
    std::cout << "Confirm purchase? (y/n): ";
    char confirm;
    std::cin >> confirm;
    confirm = std::tolower(confirm);
    if (confirm == 'y') {
        for (int i = 0; i < seatNum; i++) {
            seats[selectedRow[i]][selectedCol[i]] = true;
        }
        std::cout << "Purchase successful! Seats have been reserved." << std::endl;
    } else {
        std::cout << "Purchase canceled. No seats were reserved." << std::endl;
    }

}

void viewSalesReport(const bool seats[ROWS][COLS], const double rowPrice[ROWS]){
    int totalSold = 0;
    double totalRevenue = 0;

    for (int i = 0; i < ROWS; i++){
        int rowSold = 0;
        for (int j = 0; j < COLS; j++){
            if (seats[i][j]) {
                rowSold++;
            }
        }
        totalSold += rowSold;
        totalRevenue += rowSold * rowPrice[i];
    }
    int totalSeats = ROWS * COLS;
    int totalAvailable = totalSeats - totalSold;

    std::cout << "\n======= TICKET SALES REPORT =======" << std::endl
    << "Total Seats:      " << totalSeats << std::endl
    << "Seats Sold:       " << totalSold << std::endl
    << "Seats Available:  " << totalAvailable << std::endl
    << "Total Revenue:   $" << totalRevenue << std::endl;
}
