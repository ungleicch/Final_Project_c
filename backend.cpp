#include <fstream>
#include <iostream>
#include <ostream>



void get_rows(bool (&arr)[15][30], int arr2[2] = nullptr) {
    std::fstream file("SeatAvailability.txt");
    if(!file){
        std::ofstream outFile("SeatAvailability.txt");
        if(!outFile) {
            std::cerr << "There was an error, not able to provide the file!" << std::endl;
            return;
        }

        for(int i = 0; i < 15; i++){
            for(int j = 0; j < 30; j++){
                arr[i][j] = 0;
                outFile << "0";
            }
            outFile << "\n";
        }

        outFile.close();
        file.open("SeatAvailability.txt", std::ios::in | std::ios::out);
        if(!file){
            std::cerr << "Not able to open the file!!" << std::endl;
            return;
        }
    }

    for (int i = 0; i < 15; i++){
        for(int j = 0; j < 30; j++){
            int value;
            file >> value;
            arr[i][j] = (value != 0);
        }
    }

    if(arr2 != nullptr){
        int row = arr2[0] - 1;
        int col = arr2[1] - 1;

        if (row < 0 || row >= 15 || col < 0 || col >= 30) {
            std:: cerr << "Invalid row or colum indext!" << std::endl;
            file.close();
            return;
        }

        arr[row][col] = 1;
        file.close();

        std::ofstream outFile("SeatAvailability.txt");
        if(!outFile){
            std::cerr << "Error opening the file for changing the value!" << std::endl;
            return;
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
}

int main(){
    bool seats[15][30];
    int seatToMark[2] = {2, 5};
    get_rows(seats, seatToMark);


    return 0;
}
