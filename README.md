Initialization:

init(): Sets up the OpenGL environment and viewport.
glutInit(), glutCreateWindow(): Initializes the GLUT library and creates a window.
Drawing:

display(): Clears the screen and draws the plank, ball, and score. Shows "Game Over!" when needed.
Updating:

timer(): Updates ball position and checks for collisions. Resets ball position and increases score if the ball is caught by the plank.
Input Handling:

special(): Moves the plank left or right based on arrow keys. Starts or restarts the game with the F1 key.
Game Loop:

glutTimerFunc(): Calls the timer() function regularly to update the game state.
