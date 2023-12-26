#include <iostream>


const int MAX_SIZE = 10;
const int MIN_SIZE = 3;
const int MIN_MINES = 1;
const int MATRIX_FOUNDATION = 45; // ASCII code for #
const int MATRIX_MINE = '*';

// I'm not really sure if using built in randomisers is allowed 
// Having pondered on this question for a while I came to a realisation
// I appear to be lacking the capabilities to implement it in another way.
// As such I will take advantage of all such functionality.

//simple function that verifies that a certain element is in the voundaries of the array.
bool is_in_matrix(int row, int col, int rows, int cols)
{
    return (row >= 0) && (row < rows) && (col >= 0) && (col < cols);
}
#pragma region Matrix_lifespan

//puts the numbers that indicate the count of mines around each element in the matrix.
void enumerate_matrix(char** matrix, const int rows, const int cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            int count = 0;
            if (matrix[i][j] == MATRIX_MINE)
            {
                continue;
            }
            if (is_in_matrix(i - 1, j, rows, cols))
            {
                if (matrix[i - 1][j] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i - 1, j - 1, rows, cols))
            {
                if (matrix[i - 1][j - 1] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i, j - 1, rows, cols))
            {
                if (matrix[i][j - 1] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i + 1, j - 1, rows, cols))
            {
                if (matrix[i + 1][j - 1] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i + 1, j, rows, cols))
            {
                if (matrix[i + 1][j] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i + 1, j + 1, rows, cols))
            {
                if (matrix[i + 1][j + 1] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i, j + 1, rows, cols))
            {
                if (matrix[i][j + 1] == MATRIX_MINE)
                {
                    count++;
                }
            }
            if (is_in_matrix(i - 1, j + 1, rows, cols))
            {
                if (matrix[i - 1][j + 1] == MATRIX_MINE)
                {
                    count++;
                }
            }
            matrix[i][j] = count + 48;
        }
    }
}

//generates the mines and places them in the matrix.
void place_mines(char** matrix, const int rows, const int cols, const int mine_count)
{
    //declaring a matrix to keep track of where the mines are.
    bool map[MAX_SIZE][MAX_SIZE] = { {0} };

    // We dont change the declared variable i in the for because we validate the existance of a bomb on the same tile
    for (unsigned i = 0; i < mine_count;)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        //Better safe then sorry
        if (x >= 0 && y >= 0 && x < cols && y < rows)
        {
            if (map[x][y] == false)
            {
                matrix[x][y] = ::MATRIX_MINE;
                map[x][y] = true;
                i++;
            }
        }
    }

}

//prints out a matrix.
void print_matrix(char** matrix, const int rows, const int cols)
{
    std::cout << "  | ";
    for (size_t i = 0; i < cols; i++)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    for (size_t i = 0; i < cols + 1; i++)
    {
        std::cout << (char)196 << " ";

    }
    std::cout << "\n";
    for (int i = 0; i < rows; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

char** create_matrix(const int rows, const int cols) {
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
            matrix[i][j] = ::MATRIX_FOUNDATION;
        }
    }

}

void delete_matrix(char** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}
#pragma endregion



//Writes out a Welcoming message on the console.
void welcome_text() {
    const char* minesweeperText[] = {
        "          __          __  _                            _              \n"
        "          \\ \\        / / | |                          | |             \n"
        "           \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___        \n"
        "            \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\       \n"
        "             \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) |      \n"
        "           __ \\/_ \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/       \n"
        "          |  \\/  |(_)                                                  \n"
        "          | \\  / |_ _ __   ___  _____      _____  ___ _ __   ___ _ __ \n"
        "          | |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
        "          | |  | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n"
        "          |_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n"
        "                                                     | |              \n"
        "                                                     |_|              \n"
    };

    for (const char* line : minesweeperText) {
        std::cout << line << std::endl;
    }
}

int try_terminate()

//Core game mechanics.
void game()
{
#pragma region Configuration

    //Input size of matrix
    int n = 0;
    std::cout << "Please enter the desired size of field : ";
    std::cin >> n;
    //Validaition
    while (n < 3 || n>10)
    {
        std::cout << "Please enter a valid size in the range " << MIN_SIZE << " to " << MAX_SIZE << " : ";
        std::cin >> n;
    }
    //Input of mines
    int mines = 0;
    std::cout << "Please enter the desired amount of mines : ";
    std::cin >> mines;
    //Validation
    while (mines < 1 || mines > n)
    {
        std::cout << "Please enter a valid amount of mines between " << MIN_MINES << " to " << n << " : " << std::endl;
        std::cin >> mines;
    }
    char** real_matrix = create_matrix(n, n);
    char** player_matrix = create_matrix(n, n);

    //what the player sees.
    initialise_matrix(player_matrix, n, n);
    place_mines(real_matrix, n, n, mines);
    enumerate_matrix(real_matrix, n, n);
    print_matrix(real_matrix, n, n);
#pragma endregion

    bool game_on = true;
    while (game_on)
    {
        print_matrix(player_matrix, n, n);
        std::cout << "Enter your move as follows - > x y : ";
        int x = 0;
        int y = 0;
        std::cin >> x;
        std::cin >> y;
        while (x > n || y > n || x < 0 || y < 0)
        {
            std::cout << "Please enter valid coordinates!";
            std::cin >> x;
            std::cin >> y;
        }
    }


#pragma region CleanUp
    delete_matrix(real_matrix, n); delete_matrix(player_matrix, n); //Actively hoping this works.
#pragma endregion
}
int main()
{
    welcome_text();

    srand(time(NULL));

    game();
}