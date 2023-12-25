#include <iostream>

const int MAX_SIZE = 10;
const int MIN_SIZE = 3;
const int MIN_MINES = 1;

int main()
{
    //Input size of matrix
    int n = 0;
    std::cout << "Please enter the desired size of field : ";
    std::cin >> n;
    //Validaition
    while (n < 3 || n>10)
    {
        std::cout << "Please enter a valid size in the range " << MIN_SIZE << " to " << MAX_SIZE<<" : ";
        std::cin >> n;
    }
    //Input of mines
    int mines = 0;
    std::cout << "Please enter the desired amount of mines : "; 
    std::cin >> mines;
    //Validation
    while (mines < 1|| mines > n)
    {
        std::cout << "Please enter a valid amount of mines between " << MIN_MINES << " to " << n << " : ";
        std::cin >> mines;
    }
}