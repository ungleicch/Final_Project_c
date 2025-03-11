int rowPrice[15] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
int rev = 0, sold = 0; 
char choice;

std::cout << "what would you like to see?\n 1: seating chart\n 2: view the ticket price per row\n";
std::cout << " 3: purchase ticket\n 4: view ticket sales report\n 5: exit\n";
std::cin >> choice; 


switch (choice)
{
case '1': 
{
    //seating chart
    break;
}
case '2': 
{
   std::cout << "row has a different price, but every seat in a row is the same price.\n";
   for(int i = 0; i < 15; i++)
   {
       std::cout << "row " << (i+1) << ": " << rowPrice[i] << "$\n";
   }
   break;
}
case '3':
{
    int seat, row;
    
    std::cout << "what row would you like? (1-15)\n";
    std::cin >> row;
    while (row > 15 || row < 1)
    {
        std::cout << "not a valid choice, please enter a number 1-15\n";
        std::cin >> row;
    }

    std::cout << "what seat in row " << row << " would you like? (1-30)\n";
    std::cin >> seat;
    while (seat > 30 || seat < 1)
        std::cout << "not a valid choice, please enter a number 1-30\n";
        std::cin >> seat;
    }
    
    
}
case '4':
{
    std::cout << sold << " tickets have been sold\n" << rev << "$ has been made off of sales";
    break;
}
case '5':
{
    std::cout << "goodbye";
    break;
}
default: 
    std::cout << "not a valid choice, please enter 1,2,3,4, or 5.\n";
    std::cin >> choice;
}
    
    return 0;
}
