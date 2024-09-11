#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Game variables
float plankWidth = 0.2f, plankHeight = 0.02f;
float ballSize = 0.02f;
float plankX = 0.0f;
float ballX = 0.0f, ballY = 1.0f;
float ballSpeed = 0.01f;
int score = 0;
bool gameStarted = false;
bool gameOver = false;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw the plank
    glColor3f(0.5f, 0.35f, 0.05f); // Wood color
    glBegin(GL_QUADS);
    glVertex2f(plankX - plankWidth / 2, -1 + plankHeight);
    glVertex2f(plankX + plankWidth / 2, -1 + plankHeight);
    glVertex2f(plankX + plankWidth / 2, -1);
    glVertex2f(plankX - plankWidth / 2, -1);
    glEnd();
    
    // Draw the ball
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(ballX, ballY);
    for (int i = 0; i <= 20; ++i) {
        float angle = 2.0f * 3.1415926f * float(i) / float(20);
        float dx = ballSize * cosf(angle);
        float dy = ballSize * sinf(angle);
        glVertex2f(ballX + dx, ballY + dy);
    }
    glEnd();
    
    // Draw the score
    glColor3f(1.0f, 1.0f, 1.0f); // White color
    glRasterPos2f(-0.95f, 0.9f);
    string scoreText = "Score: " + to_string(score);
    for (char c : scoreText) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    if (gameOver) {
        glColor3f(1.0f, 0.0f, 0.0f);
        glRasterPos2f(-0.1f, 0.0f);
        string gameOverText = "Game Over!";
        for (char c : gameOverText) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }

    glutSwapBuffers();
}

void timer(int value) {
    if (gameStarted && !gameOver) {
        ballY -= ballSpeed;
        if (ballY < -1) {
            ballY = 1.0f;
            ballX = (rand() % 200 - 100) / 100.0f; // Randomize ball X position
        }
        
        // Check for collision
        if (ballY <= -1 + plankHeight && ballX >= plankX - plankWidth / 2 && ballX <= plankX + plankWidth / 2) {
            score++;
            ballY = 1.0f;
            ballX = (rand() % 200 - 100) / 100.0f; // Randomize ball X position
            if (score >= 10) {
                gameOver = true;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 FPS
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Escape key to exit
}

void special(int key, int x, int y) {
    if (gameStarted && !gameOver) {
        float moveSpeed = 0.05f;
        if (key == GLUT_KEY_LEFT) plankX -= moveSpeed;
        if (key == GLUT_KEY_RIGHT) plankX += moveSpeed;
        plankX = max(-1.0f + plankWidth / 2, min(plankX, 1.0f - plankWidth / 2));
    }
    if (key == GLUT_KEY_F1) {
        if (gameOver) {
            score = 0;
            gameOver = false;
        }
        gameStarted = true;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    srand(static_cast<unsigned>(time(nullptr))); // Seed random number generator

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Catch Me Game");
    
    init();
    
    glutDisplayFunc(display);
    glutTimerFunc(25, timer, 0); // Set timer for game loop
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    
    glutMainLoop();
    return 0;
}
