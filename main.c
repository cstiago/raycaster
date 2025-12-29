#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

const unsigned int SCREEN_WIDTH = 512;
const unsigned int SCREEN_HEIGHT = 256;

const unsigned int MAP_WIDTH = 16;
const unsigned int MAP_HEIGHT = 16;
const unsigned int TILE_SIZE = 32;

const double PLAYER_SPEED = 15.;

int hz_walls[][3] = {{1, 1, 3}, {2, 3, 9}, {8, 5, 14}};
int hz_walls_qty = sizeof(hz_walls) / (sizeof(hz_walls[0][0]) * 3);

int vt_walls[][3] = {{1, 1, 3}};
int vt_walls_qty = sizeof(vt_walls) / (sizeof(vt_walls[0][0]) * 3);

double player_x, player_y;

void drawMap2D() {
    glColor3f(1,1,1);

    for(int i = 0; i < hz_walls_qty; i++) {
        int xi = hz_walls[i][1] * TILE_SIZE;
        int yi = hz_walls[i][0] * TILE_SIZE;
        int xf = (hz_walls[i][2] + 1) * TILE_SIZE;
        int yf = yi + TILE_SIZE;

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
    drawMap2D();
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

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
}
