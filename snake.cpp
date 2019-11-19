//Programmer: Andy Simphaly

#include <cstdlib>
#include <ncurses.h>

//Variables of the game components
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
//Enum for Direction
enum edir {STOP=0, LEFT, RIGHT, UP, DOWN};
edir dir;
//Variables for the tail
int tail_x[100], tail_y[100];
int ntail;

//Setup function
void setup() {
    //Screen setting
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);

    //Set game variables
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruit_x = (rand() % width) + 1;
    fruit_y = (rand() % height) + 1;
    score = 0;
}

//Draw the board
void draw() {
    //Clear board
    clear();

    //Print Borders, fruit, head, and tail
    for(int i = 0; i < height + 2; i++) {
        for(int j = 0; j < width + 2; j++) {
            if (i == 0 || i == 21) {
                mvprintw(i,j,"+");
            } else if (j == 0 || j == 21) {
                mvprintw(i,j,"+");
            } else if (i == y && j == x) {
                mvprintw(i,j,"O");
            } else if (i == fruit_y && j == fruit_x) {
                mvprintw(i,j,"@");
            } else {
                for(int k = 0; k < ntail; k++) {
                    if (tail_x[k] == j && tail_y[k] == i) {
                        mvprintw(i,j,"o");
                    }
                }
            }
        }
    }

    //Print score
    mvprintw(23,0,"Score %d",score);

    //Refresh board
    refresh();

    return;
}

//User input function
void input() {

    //Keypad and speed of the game
    keypad(stdscr, TRUE);
    halfdelay(1);

    //Input key
    int key = getch();

    //Switch case to change to the intended direction
    switch(key) {
        case 97:
            //Check that the snake does not go into itself
            if (dir != RIGHT) {
                dir = LEFT;
            }
            break;
        case 100:
            //Check that the snake does not go into itself
            if (dir != LEFT) {
                dir = RIGHT;
            }
            break;
        case 115:
            //Check that the snake does not go into itself
            if (dir != UP) {
                dir = DOWN;
            }
            break;
        case 119:
            //Check that the snake does not go into itself
            if (dir != DOWN) {
                dir = UP;
            }
            break;
        case KEY_LEFT:
            //Check that the snake does not go into itself
            if (dir != RIGHT) {
                dir = LEFT;
            }
            break;
        case KEY_RIGHT:
            //Check that the snake does not go into itself
            if (dir != LEFT) {
                dir = RIGHT;
            }
            break;
        case KEY_DOWN:
            //Check that the snake does not go into itself
            if (dir != UP) {
                dir = DOWN;
            }
            break;
        case KEY_UP:
            //Check that the snake does not go into itself
            if (dir != DOWN) {
                dir = UP;
            }
            break;
        //Quit key (Q)
        case 113:
            gameOver = true;
            break;
    }
}


void logic() {
    //Variables to set the tail values
    int prevx = tail_x[0];
    int prevy = tail_y[0];
    int prevx2, prevy2;
    tail_x[0] = x;
    tail_y[0] = y;

    //For loop to increment the tail values
    for(int i = 1; i < ntail; i++) {
        prevx2 = tail_x[i];
        prevy2 = tail_y[i];
        tail_x[i] = prevx;
        tail_y[i] = prevy;
        prevx = prevx2;
        prevy = prevy2;
    }

    //Changing the direction of the snake
    switch(dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }

    //Game over if border is hit
    if (x > width || x < 1 || y < 1 || y > height) {
        gameOver = true;
    }
    
    //Game over if the snake runs into itself
    for(int i = 0; i < ntail; i++) {
        if (tail_x[i] == x && tail_y[i] == y) {
            gameOver = true;
        }
    }

    //Increase score, make new fruit, add a tail
    if (x == fruit_x && y == fruit_y) {
        score++;
        fruit_x = (rand() % width) + 1;
        fruit_y = (rand() % height) + 1;
        //While loop to ensure that a fruit does not spawn on the snake
        for(int i = 0; i < ntail; i++) {
            while (tail_x[i] == fruit_x && tail_y[i] == fruit_y) {
                fruit_x = (rand() % width) + 1;
                fruit_y = (rand() % height) + 1;
            }
        }
        ntail++;
    }
}

int main() {
    setup();
    
    //Loop to keep the game going
    while(!gameOver) {
        draw();
        input();
        logic();
    }
    
    getch();
    endwin();

    return 0;
}