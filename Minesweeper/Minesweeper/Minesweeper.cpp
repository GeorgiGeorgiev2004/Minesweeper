#include <iostream>


const int MAX_SIZE = 10;
const int MIN_SIZE = 3;
const int MIN_MINES = 1;
const int MATRIX_FOUNDATION = 45; // ASCII code for #
const int MATRIX_MINE = '*';
const int MATRIX_REVEALED_SIGN = 46;

// I'm not really sure if using built in randomisers is allowed 
// Having pondered on this question for a while I came to a realisation
// I appear to be lacking the capabilities to implement it in another way.
// As such I will take advantage of all such functionality.

bool bombs_makred(char** real,char** player,int rows,int cols) 
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (real[i][j]==MATRIX_MINE&&player[i][j]!='M')
            {
                return false;
            }
        }
    }
}

//simple function that verifies that a certain element is in the voundaries of the array.
bool is_in_matrix(int row, int col, int rows, int cols)
{
    return (row >= 0) && (row < rows) && (col >= 0) && (col < cols);
}
//Marks a tile or unmarks is depending on the bool variable marked
void mark(char** matrix, int row, int col, bool marked)
{
    if (marked)
    {
        matrix[row][col] = MATRIX_FOUNDATION;
    }
    if (!marked)
    {
        matrix[row][col] = 'M';
    }
}
// After switching all seen 0's to the MATRIX_REVEALED_SIGN we reveal all tiles surrounding them.
void reveal_matrix(char** real_matrix, char** player_matrix,int rows,int cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            //A lot of if's for a rather easy task.
            if (real_matrix[i][j] == MATRIX_REVEALED_SIGN)
            {
                if (is_in_matrix(i - 1, j, rows, cols))
                {
                    player_matrix[i - 1][j] = real_matrix[i - 1][j];
                }
                if (is_in_matrix(i + 1, j, rows, cols))
                {
                    player_matrix[i + 1][j] = real_matrix[i + 1][j];
                }
                if (is_in_matrix(i, j+1, rows, cols))
                {
                    player_matrix[i ][j+1] = real_matrix[i][j+1];
                }
                if (is_in_matrix(i, j-1, rows, cols))
                {
                    player_matrix[i][j-1] = real_matrix[i][j-1];
                }
                if (is_in_matrix(i - 1, j-1, rows, cols))
                {
                    player_matrix[i - 1][j-1] = real_matrix[i - 1][j-1];
                }
                if (is_in_matrix(i - 1, j+1, rows, cols))
                {
                    player_matrix[i - 1][j+1] = real_matrix[i - 1][j+1];
                }
                if (is_in_matrix(i + 1, j-1, rows, cols))
                {
                    player_matrix[i + 1][j-1] = real_matrix[i + 1][j - 1];
                }
                if (is_in_matrix(i + 1, j+1, rows, cols))
                {
                    player_matrix[i + 1][j+1] = real_matrix[i + 1][j + 1];
                }
            }
        }
    }
}
//Flood Fill algorithm reveals all the 0's the real matrix.
void replace_empty_spaces(char** real_matrix,char** player_matrix,int rows,int cols,int row,int col) 
{
    if (!is_in_matrix(row,col,rows,cols)|| real_matrix[row][col] != '0')
    {
        return;
    }
    real_matrix[row][col] = MATRIX_REVEALED_SIGN;
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row-1, col);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row+1, col);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row, col+1);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row, col-1);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row-1, col-1);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row+1, col+1);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row-1, col+1);
    replace_empty_spaces(real_matrix, player_matrix, rows, cols, row+1, col-1);
}
//basic rewrite of the place_bomb function 
void replace_bomb(char** matrix, int row, int col, int rows, int cols)
{
    bool map[MAX_SIZE][MAX_SIZE] = { {0} };

    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            if (matrix[i][j] == MATRIX_MINE)
            {
                map[i][j] == 1;
            }
        }
    }
    for (unsigned i = 0; i < 1;)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        //Better safe then sorry
        if (x >= 0 && y >= 0 && x < cols && y < rows && x != row && y != col)
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
    std::cout << "\n";
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
    int marks = 0;

    int counter = 0;
  
    std::cout << "You can mark, unravel or unmark a tile by the following commands : \n"
        << "Unravel : open x y \n"
        << "Mark : mark x y \n"
        << "Unmark : unmark x y \n";

    print_matrix(player_matrix, n, n);
    while (game_on) {
        if (bombs_makred(real_matrix,player_matrix,n,n))
        {
            std::cout << "You won! Congratulations!";
            game_on = false; break;
        }
        char command[6] = { 0 };
        int x = 0;
        int y = 0;
        int ctr = 0;
        for (size_t i = 0; i < 12; i++)
        {
            std::cin >> command[i];
            ctr++;
            if (command[0] == 'o' && command[1] == 'p' && command[2] == 'e' && command[3] == 'n') break;
            if (command[0] == 'm' && command[1] == 'a' && command[2] == 'r' && command[3] == 'k') break;
            if (command[0] == 'u' && command[1] == 'n' && command[2] == 'm' && command[3] == 'a' && command[4] == 'r' && command[5] == 'k') break;
            if (command[0] == 'e' && command[1] == 'n' && command[2] == 'd')break;
            if (ctr == 6)break;
        }
        while (true)
        {
            if (command[0] == 'o' && command[1] == 'p' && command[2] == 'e' && command[3] == 'n') break;
            if (command[0] == 'm' && command[1] == 'a' && command[2] == 'r' && command[3] == 'k') break;
            if (command[0] == 'u' && command[1] == 'n' && command[2] == 'm' && command[3] == 'a' && command[4] == 'r' && command[5] == 'k') break;
            if (command[0] == 'e' && command[1] == 'n' && command[2] == 'd')break;
            std::cout << "Please enter a valid command! : ";
            std::cin >> command;
        }
        if (command[0] == 'e' && command[1] == 'n' && command[2] == 'd') { game_on = false; break; }
        std::cin >> x;
        std::cin >> y;
        while (x > n - 1 || y > n - 1 || x < 0 || y < 0)
        {
            std::cout << "Please enter valid coordinates! : ";
            std::cin >> x;
            std::cin >> y;
        }
        if (command[0] == 'o' && command[1] == 'p' && command[2] == 'e' && command[3] == 'n')
        {
            if (real_matrix[x][y] == MATRIX_MINE && counter == 0)
            {
                replace_bomb(real_matrix, x, y, n, n);
                real_matrix[x][y] = MATRIX_FOUNDATION;
                enumerate_matrix(real_matrix, n, n);
                player_matrix[x][y] = real_matrix[x][y];
                counter++;
                print_matrix(real_matrix, n, n);
                print_matrix(player_matrix, n, n);
                replace_empty_spaces(real_matrix, player_matrix, n, n, x, y);
                reveal_matrix(real_matrix, player_matrix, n, n);
                continue;
            }
            counter++;
            if (player_matrix[x][y]!=MATRIX_FOUNDATION)
            {
                std::cout << "Tile already opened \n"<<"Please enter a valid command : "; continue;
            }
            if (player_matrix[x][y]=='M')
            {
                std::cout << "This tile is marked and can't be opened \n"; continue;
            }
            if (real_matrix[x][y]==MATRIX_MINE)
            {
                for (size_t i = 0; i < n; i++)
                {
                    for (size_t j = 0; j < n; j++)
                    {
                        if (real_matrix[i][j]==MATRIX_MINE )
                        {
                            player_matrix[i][j] = real_matrix[i][j];
                        }
                    }
                }
                std::cout << "You lost!";
                return;
            }
            else
            {
                if (real_matrix[x][y]=='0')
                {
                replace_empty_spaces(real_matrix, player_matrix, n, n, x, y);
                reveal_matrix(real_matrix, player_matrix, n, n);
                }
                else
                {
                    player_matrix[x][y] = real_matrix[x][y];
                }
            }
        }
        if (command[0] == 'm' && command[1] == 'a' && command[2] == 'r' && command[3] == 'k')
        {
            if (player_matrix[x][y]=='M')
            {
                std::cout << "position is already marked \n";
                continue;
            }
            mark(player_matrix, x, y, false);
            marks++;
        }
        if (command[0] == 'u' && command[1] == 'n' && command[2] == 'm' && command[3] == 'a' && command[4] == 'r' && command[5] == 'k')
        {
            if (player_matrix[x][y] != 'M')
            {
                std::cout << "position is not marked \n";
                continue;
            }
            mark(player_matrix, x, y, true);
            marks--;
        }
        std::cout << "Marks left : " << mines-marks<<"\n";
        print_matrix(real_matrix, n, n);
        print_matrix(player_matrix, n, n);
        
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