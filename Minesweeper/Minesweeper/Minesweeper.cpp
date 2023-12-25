#include <iostream>

const int MAX_SIZE = 10;
const int MIN_SIZE = 3;
const int MIN_MINES = 1;

void print_matrix(char** matrix,const int rows,const int cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

char** create_matrix(const int rows,const int cols) {
    char** matrix = new char* [rows];

    for (int i = 0; i < rows; ++i) 
    {
        matrix[i] = new char[cols]; 
    }

    return matrix;
}

void initialise_matrix(char** matrix, const int rows, const int cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
           matrix[i][j] = 35;
        }
    }
}

void delete_matrix(char** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}


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

    char** matrix = create_matrix(n, n);
    initialise_matrix(matrix, n, n);
    print_matrix(matrix, n, n);
    delete_matrix(matrix, n);  // Sending prayers this works.

}