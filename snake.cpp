
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <ctime>

using namespace std;

// Constants for game dimensions
const int WIDTH = 80;
const int HEIGHT = 20;

// Snake head coordinates
int x, y;
// Food coordinates
int fruitX, fruitY;
// Player's score
int score;
// Arrays to store the coordinates of the snake's tail
int tailX[100], tailY[100];
// Length of the snake's tail
int tailLength;
// Directions for snake movement
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
// Current direction of the snake
Direction dir;
// Game over flag
bool gameOver;

// Function to initialize the game
void initializeGame() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    tailLength = 0;
}

// Function to render the game board
void renderGame(string playerName) {
    system("cls"); // Clear the console

    // Top wall
    for (int i = 0; i < WIDTH + 2; i++) cout << "-";
    cout << endl;

    // Game area
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (j == 0 || j == WIDTH) {
                cout << "|"; // Side walls
            } else if (i == y && j == x) {
                cout << "O"; // Snake head
            } else if (i == fruitY && j == fruitX) {
                cout << "#"; // Food
            } else {
                bool printTail = false;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o"; // Snake tail
                        printTail = true;
                    }
                }
                if (!printTail) cout << " ";
            }
        }
        cout << endl;
    }

    // Bottom wall
    for (int i = 0; i < WIDTH + 2; i++) cout << "-";
    cout << endl;

    // Display score
    cout << playerName << "'s Score: " << score << endl;
}

// Function to update the game state
void updateGame() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    // Check for collision with the wall
    if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0) gameOver = true;

    // Check for collision with the tail
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }

    // Check for collision with the food
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
    }
}

// Function to set the difficulty level
int setDifficulty() {
    int difficulty, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n"
            "NOTE: If not chosen or pressed any other key, the difficulty will be set to Medium\n"
            "Choose difficulty level: ";
    cin >> choice;
    switch (choice) {
        case 1: difficulty = 150; break;
        case 2: difficulty = 100; break;
        case 3: difficulty = 50; break;
        default: difficulty = 100;
    }
    return difficulty;
}

// Function to handle user input
void handleInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = LEFT; break;
            case 'd': dir = RIGHT; break;
            case 'w': dir = UP; break;
            case 's': dir = DOWN; break;
            case 'x': gameOver = true; break;
        }
    }
}

// Main game loop
int main() {
    srand(time(0)); // Initialize random seed
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    int difficulty = setDifficulty();

    initializeGame();
    while (!gameOver) {
        renderGame(playerName);
        handleInput();
        updateGame();
        Sleep(difficulty); // Control game speed based on difficulty
    }

    return 0;
}
