#include <fstream>
#include <iostream>
#include <ostream>


// request / update the file
int get_data(bool (&arr)[15][30], int arr2[2] = nullptr) { // taking a reference of the 2D array, and if we change a seat a 1D array of the place.
    std::fstream file("SeatAvailability.txt", std::ios::in | std::ios::out); // setting the file
    if(!file){ // if file is not loaded, not there yet
        std::ofstream outFile("SeatAvailability.txt", std::ios::trunc); // create file, with writing in rights
        if(!outFile) { // if file was not able to be created
            std::cerr << "There was an error, not able to provide the file!" << std::endl; // error
            return -1; // end the get_data
        }

        for(int i = 0; i < 15; i++){ // filling the new file with 0 for each seat.
            for(int j = 0; j < 30; j++){
                arr[i][j] = 0;
                outFile << "0 ";
            }
            outFile << "\n"; // new line
        }

        outFile.close(); // closing the file for writing, after also creating it.
        file.open("SeatAvailability.txt", std::ios::in | std::ios::out); // open the file with reading and writing rights.
        if(!file){
            std::cerr << "Not able to open the file!!" << std::endl; // Error if we are not able to open the file.
            return - 1; // end the fuction.
        }
    }

    for (int i = 0; i < 15; i++){ // the file exists, reading the values into the refrence array.
        for(int j = 0; j < 30; j++){
            int value;
            file >> value; // char by char reading in the values
            arr[i][j] = (value != 0);
        }
    }

    if(arr2 != nullptr){
        int row = arr2[0] - 1;
        int col = arr2[1] - 1;

        if (row < 0 || row >= 15 || col < 0 || col >= 30) {
            std:: cerr << "Invalid row or colum index!" << std::endl;
            file.close();
            return - 1;
        }

        arr[row][col] = 1;
        file.close();

        std::ofstream outFile("SeatAvailability.txt", std::ios::trunc);
        if(!outFile){
            std::cerr << "Error opening the file for changing the value!" << std::endl;
            return - 1;
        }

        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 30; j++){
                outFile << arr[i][j] << " ";
            }
            outFile << "\n";
        }

        outFile.close();
    } else {
        file.close();
    }
    return 1;
}

void displayChart(bool arr[][30])
{
    std::cout << "\t\tSeats\n";
    //Display the column numbers
    std::cout << "    \t";
    for(int tens = 0; tens < 3; tens++) //display tens digits
    {
        for(int ones = 0; ones < 10; ones++)
            std::cout << tens;
    }
    std::cout << std::endl;
    
    std::cout << "    \t";
    for(int tens = 0; tens < 3; tens++) //display ones digits
    {
        for(int ones = 0; ones < 10; ones++)
            std::cout << ones;
    }
    std::cout << std::endl;
    
    //display the chart
    for(int row = 0; row < 15; row++)
    {
        std::cout << "Row " << row+1 << "\t";
        for(int col = 0; col < 30; col++)
        {
            if(arr[row][col]) //true, 1, taken
                std::cout << "X";
            else
                std::cout << "O";
        }
        std::cout << std::endl;
    }
}

int main(){
    bool seats[15][30];
    int seatToMark[2] = {2, 5};
    get_data(seats, seatToMark);
    
    int userChoice;
    std::cout<< "Chose an option: \n";
    std::cout << "1. Display the seating chart.\n";
    std::cout << "2. View ticket price for each row.\n";
    std::cout << "3. Purchase a ticket.\n";
    std::cout << "4. View ticket sales report.\n";
    std::cout << "5. Exit program.\n";
    std::cin >> userChoice;
    
    switch(userChoice)
    {
        case 1:
        {
            displayChart(seats);
            break;
        }
        case 2:
        {
            //Ticket price for each row
            break;
        }
        case 3:
        {
            //Purchasing a ticket
            break;
        }
        case 4:
        {
            //View the ticket report
            break;
        }
        case 5:
        {
            //Exit the program
            return 0;
        }
        default:
        {
            std::cout << "Invalid choice! Please try again.";
            break;
        }
    }


    return 0;
}
