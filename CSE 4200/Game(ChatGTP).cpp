#include <GL/glut.h>
#include <iostream>
#include <cmath>

const int ROWS = 3;
const int COLS = 3;
const int CELL_SIZE = 100;
const int BOARD_WIDTH = CELL_SIZE * COLS;
const int BOARD_HEIGHT = CELL_SIZE * ROWS;

int board[ROWS][COLS] = { 0 };
bool game_over = false;
int winner = 0;

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, BOARD_WIDTH, 0, BOARD_HEIGHT);
}

void drawBoard() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int i = 1; i < ROWS; ++i) {
        glVertex2i(0, i * CELL_SIZE);
        glVertex2i(BOARD_WIDTH, i * CELL_SIZE);
    }
    for (int i = 1; i < COLS; ++i) {
        glVertex2i(i * CELL_SIZE, 0);
        glVertex2i(i * CELL_SIZE, BOARD_HEIGHT);
    }
    glEnd();
}

void drawX(int row, int col) {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2i(col * CELL_SIZE + 10, row * CELL_SIZE + 10);
    glVertex2i((col + 1) * CELL_SIZE - 10, (row + 1) * CELL_SIZE - 10);
    glVertex2i(col * CELL_SIZE + 10, (row + 1) * CELL_SIZE - 10);
    glVertex2i((col + 1) * CELL_SIZE - 10, row * CELL_SIZE + 10);
    glEnd();
}

void drawO(int row, int col) {
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14 / 180.0;
        glVertex2f(col * CELL_SIZE + CELL_SIZE / 2.0 + CELL_SIZE / 4.0 * cos(angle),
            row * CELL_SIZE + CELL_SIZE / 2.0 + CELL_SIZE / 4.0 * sin(angle));
    }
    glEnd();
}

void drawSymbol(int row, int col, int symbol) {
    if (symbol == 1) {
        drawX(row, col);
    }
    else if (symbol == 2) {
        drawO(row, col);
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBoard();

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            drawSymbol(i, j, board[i][j]);
        }
    }

    glutSwapBuffers();
}

bool checkWin() {
    // Check rows
    for (int i = 0; i < ROWS; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
            winner = board[i][0];
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < COLS; ++i) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0) {
            winner = board[0][i];
            return true;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
        winner = board[0][0];
        return true;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
        winner = board[0][2];
        return true;
    }

    // Check if the board is full (tie)
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (board[i][j] == 0) {
                return false;
            }
        }
    }

    winner = 0;
    return true;
}



void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !game_over) {
        int row = y / CELL_SIZE;
        int col = x / CELL_SIZE;
        if (board[row][col] == 0) {
            int player = (winner == 0 || winner == 2) ? 1 : 2;
            board[row][col] = player;
            if (player == 2) {
                drawO(row, col); // draw an "O" in the specified cell
            }
            game_over = checkWin();
            glutPostRedisplay();
        }
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(BOARD_WIDTH, BOARD_HEIGHT);
    glutCreateWindow("Tic Tac Toe");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}