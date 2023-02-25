#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

void clear()
{
#if defined _WIN32
    system("cls");
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}

class Board
{
private:
    string board[4][4] = {{" 1", " 2", " 3", " 4"}, {" 5", " 6", " 7", " 8"}, {" 9", "10", "11", "12"}, {"13", "14", "15", "  "}};
    int x = 3, y = 3;
public:
    void display(){
        cout << "\n+----+----+----+----+" << endl;
        for (size_t i = 0; i < 4; i++){
            for (size_t j = 0; j < 4; j++)
                cout << "| " << board[i][j] << " ";
            cout << "|" << endl;
            cout << "+----+----+----+----+" << endl;  
        }
    }

    int swap_up(){
        if (x == 0)
            return 0;
        board[x][y] = board[x - 1][y];
        board[x - 1][y] = "  ";
        x--;
        return 1;
    }
    int swap_down(){
        if (x == 3)
            return 0;
        board[x][y] = board[x + 1][y];
        board[x + 1][y] = "  ";
        x++;     
        return 1;   
    }
    int swap_left(){
        if (y == 0)
            return 0;
        board[x][y] = board[x][y - 1];
        board[x][y - 1] = "  ";
        y--;
        return 1;
    }
    int swap_right(){
        if (y == 3)
            return 0;
        board[x][y] = board[x][y + 1];
        board[x][y + 1] = "  ";
        y++;     
        return 1;   
    }

    int move(char input){
        switch (input){
        case 'w':
            return swap_down();
            break;
        case 's':
            return swap_up();
            break;
        case 'd':
            return swap_left();
            break;
        case 'a':
            return swap_right();
            break;
        }
        return 0;
    }
    int random_move(){
        int randomNumber = rand() % 4;
        switch (randomNumber){
        case 0:
            return swap_down();
            break;
        case 1:
            return swap_up();
            break;
        case 2:
            return swap_left();
            break;
        case 3:
            return swap_right();
            break;
        }
        return 0;
    }

    int validate(){
        string correct[4][4] = {{" 1", " 2", " 3", " 4"}, {" 5", " 6", " 7", " 8"}, {" 9", "10", "11", "12"}, {"13", "14", "15", "  "}};
        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                if (correct[i][j] != board[i][j])
                    return 0;
        return 1;
    }

    void shuffle(int n){
        for (size_t i = 0; i < n; i++)
            random_move();
    }
};


int main(){
    srand(time(0));
    int total_moves = 0;
    Board b;
    b.shuffle(10);

    while (!b.validate())
    {
        clear();
        cout << endl << "total moves : " << total_moves << endl;
        b.display();
        cout << "Enter direction ('r' for random movement): ";
        char input = getchar();
        cin.clear();
        if (input == 'r'){
            // while (!b.validate()){
                clear();
                cout << endl << "total moves : " << total_moves << endl;
                b.display();
                total_moves += b.random_move();
            // }
        }
        else
            total_moves += b.move(input);
    }

    clear();
    b.display();
    cout << "\n\nYou win!" << endl;
    cout << "Total moves: " <<  total_moves << endl;
    return 0;
}