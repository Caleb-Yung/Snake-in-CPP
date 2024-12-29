#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

// Window dimensions
const int WIDTH = 800;
const int HEIGHT = 600;

// Snake and food properties
const int GRID_SIZE = 20;
const int GRID_WIDTH = WIDTH / GRID_SIZE;
const int GRID_HEIGHT = HEIGHT / GRID_SIZE;

enum Direction { UP, DOWN, LEFT, RIGHT };
Direction dir = RIGHT;

struct Point {
    int x, y;
};

std::deque<Point> snake = {{5, 5}, {4, 5}, {3, 5}};
Point food = {10, 10};
bool gameOver = false;

int score = -1;                // Player's current score
int highScore = 0;            // High score from the file

// Function to draw a rectangle (used for snake and food)
void drawRect(int x, int y) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

// Function to spawn food at a random location
void spawnFood() {
    score += 1;
    food.x = rand() % GRID_WIDTH;
    food.y = rand() % GRID_HEIGHT;
}

// Function to handle keyboard input
void keyboard(int key, int, int) {
    if (key == GLUT_KEY_UP && dir != DOWN) dir = UP;
    if (key == GLUT_KEY_DOWN && dir != UP) dir = DOWN;
    if (key == GLUT_KEY_LEFT && dir != RIGHT) dir = LEFT;
    if (key == GLUT_KEY_RIGHT && dir != LEFT) dir = RIGHT;
}

// Function to save the high score to a JSON file
void saveHighScore() {
    try {
        nlohmann::json j;
        j["highscore"] = highScore;

        std::ofstream file("highscore.json");
        
        if (file.is_open()) {
            file << j.dump(4); // Pretty-print JSON
            std::cerr << "the file has sucessfullyh been written to";
        } else {
            throw std::ios_base::failure("Unable to open highscore.json for writing.");
        }
        file.close();
    } catch (const std::exception& e) {
        std::cerr << "Error saving highscore: " << e.what() << "\n";
    }
}

// Function to load the high score from a JSON file
void loadHighScore() {
    std::ifstream file("highscore.json");
    if (file.is_open()) {
        try {
            nlohmann::json j;
            file >> j;

            if (j.contains("highscore") && j["highscore"].is_number_integer()) {
                highScore = j["highscore"].get<int>();
            } else {
                std::cerr << "Invalid highscore format. Resetting to 0.\n";
                highScore = 0;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error loading highscore file: " << e.what() << "\n";
            highScore = 0; // Reset to default
        }
    } else {
        // Handle file not found or unable to open the file
        std::cerr << "Highscore file not found. Creating a new one with highscore = 0.\n";
        highScore = 0;
        saveHighScore();  // Save the default highscore (0) to a new file
    }
    file.close();
}



// Function to update the score and check for high score
 

// Function to update the game state
// Function to update the game state
void update(int) {
    if (gameOver) {
        // Save high score immediately after the game ends (before dialog box)  // Update the score
        if (score > highScore) { saveHighScore();}  // Save high score to file

        // Display the game over message after saving
        int response = MessageBox(NULL, "You hit the wall or your tail", "Game Over", MB_OK | MB_ICONINFORMATION);
        if (response == IDOK) {
            std::exit(1);  // Exit the game after the dialog
        }

        return;  // Return to avoid further updates after the game ends
    }

    // Move the snake
    Point head = snake.front();
    switch (dir) {
        case UP: head.y++; break;
        case DOWN: head.y--; break;
        case LEFT: head.x--; break;
        case RIGHT: head.x++; break;
    }

    // Check for collisions with walls
    if (head.x < 0 || head.x >= GRID_WIDTH || head.y < 0 || head.y >= GRID_HEIGHT) {
        gameOver = true;
        return;
    }

    // Check for collisions with itself
    for (const auto& segment : snake) {
        if (head.x == segment.x && head.y == segment.y) {
            gameOver = true;
            return;
        }
    }

    // Add the new head to the snake
    snake.push_front(head);

    // Check if the snake eats the food
    if (head.x == food.x && head.y == food.y) {
        spawnFood();
    } else {
        // Remove the tail if no food is eaten
        snake.pop_back();
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0); // Call update every 100ms
}


// Function to render the game
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);
    for (const auto& segment : snake) {
        drawRect(segment.x, segment.y);
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    drawRect(food.x, food.y);

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(2, GRID_HEIGHT - 1);
    std::string scoreText = "Score: " + std::to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    glRasterPos2f(2, GRID_HEIGHT - 2);
    std::string highScoreText = "High Score: " + std::to_string(highScore);
    for (char c : highScoreText) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, c);
    }

    if (gameOver) {
        if (score > highScore) { saveHighScore();}
        int response = MessageBox(NULL, "You hit the wall or your tail", "Game Over", MB_OK | MB_ICONINFORMATION);
        if (response == IDOK) {
            std::exit(1);
        }
    }

    glutSwapBuffers();
}

// Function to initialize OpenGL
void init() {
    loadHighScore(); // Load the high score from the file
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, GRID_WIDTH, 0, GRID_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    spawnFood();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Snake Game");

    init();

    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    glutTimerFunc(100, update, 0);

    glutMainLoop();
    return 0;
}