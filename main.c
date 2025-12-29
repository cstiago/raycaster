#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

const unsigned int SCREEN_WIDTH = 512;
const unsigned int SCREEN_HEIGHT = 256;

const unsigned int MAP_WIDTH = 16;
const unsigned int MAP_HEIGHT = 16;
const unsigned int TILE_SIZE = 32;

const double PLAYER_SPEED = 15.;

int map[MAP_WIDTH][MAP_HEIGHT];

int walls[][4] = {
    {0, 0, MAP_WIDTH-1, 0},
    {MAP_WIDTH-1, 0, MAP_WIDTH-1, MAP_HEIGHT-1},
    {MAP_WIDTH-1, MAP_HEIGHT-1, 0, MAP_HEIGHT-1},
    {0, MAP_HEIGHT-1, 0, 0},
    {1, 1, 3, 1},
    {1, 2, 9, 2},
    {8, 5, 14, 5},
    {7, 7, 9, 9}
};
int walls_qty = sizeof(walls) / (sizeof(walls[0][0]) * 4);

double player_x, player_y;

double min(double a, double b) {return a < b ? a : b;}
double max(double a, double b) {return a > b ? a : b;}

void setWalls() {
    for(int i = 0; i < walls_qty; i++) {
        for(int x = walls[i][0]; x < walls[i][1]; x++) {
            for(int y = walls[i][2]; y < walls[i][3]; y++) {
                map[x][y] = 1;
            }
        }
    }
}

void drawWalls() {
    glColor3f(1,1,1);

    for(int i = 0; i < walls_qty; i++) {
        int xi = min(walls[i][0], walls[i][2]) * TILE_SIZE;
        int yi = min(walls[i][1], walls[i][3]) * TILE_SIZE;
        int xf = (max(walls[i][2], walls[i][0]) + 1) * TILE_SIZE;
        int yf = (max(walls[i][3], walls[i][1]) + 1) * TILE_SIZE;

        glBegin(GL_QUADS);
        glVertex2i(xi, yi);
        glVertex2i(xf, yi);
        glVertex2i(xf, yf);
        glVertex2i(xi, yf);
        glEnd();
    }
}

void drawPlayer() {
    glColor3f(0,1,2);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2i(player_x, player_y);
    glEnd();
}

void setPlayerPosition(double x, double y) {
    player_x = x; player_y = y;
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a': player_x -= PLAYER_SPEED; break;
        case 'd': player_x += PLAYER_SPEED; break;
        case 'w': player_y -= PLAYER_SPEED; break;
        case 's': player_y += PLAYER_SPEED; break;
    }
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawWalls();
    drawPlayer();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.3, 0.3, 0.3, 0);
    gluOrtho2D(0, 1024, 512, 0);
    setPlayerPosition(150, 150);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Raycaster");

    setWalls();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
}
