#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1415926535897932384626

#define MAP_WIDTH 16
#define MAP_HEIGHT 16
#define TILE_SIZE 32

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 256

const double PLAYER_MOV_SPEED = 15.;
const double PLAYER_ANG_SPEED = .2;

int map[MAP_WIDTH][MAP_HEIGHT];

int walls[][4] = {
    {0, 0, MAP_WIDTH-1, 0},
    {MAP_WIDTH-1, 0, MAP_WIDTH-1, MAP_HEIGHT-1},
    {MAP_WIDTH-1, MAP_HEIGHT-1, 0, MAP_HEIGHT-1},
    {0, MAP_HEIGHT-1, 0, 0},
    {6, 6, 9, 9},
    {3, 12, 12, 12}
};
int walls_qty = sizeof(walls) / (sizeof(walls[0][0]) * 4);

double player_x, player_y, player_angle, player_mov_x, player_mov_y;

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
        int xi = fmin(walls[i][0], walls[i][2]) * TILE_SIZE;
        int yi = fmin(walls[i][1], walls[i][3]) * TILE_SIZE;
        int xf = (fmax(walls[i][2], walls[i][0]) + 1) * TILE_SIZE;
        int yf = (fmax(walls[i][3], walls[i][1]) + 1) * TILE_SIZE;

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

void updateAngleMovement(double player_angle) {
    player_mov_x = cos(player_angle);
    player_mov_y = sin(player_angle);
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 'a':
            player_angle -= PLAYER_ANG_SPEED;
            if(player_angle < 0) {player_angle += 2*PI;}
            updateAngleMovement(player_angle);
            break;
        case 'd':
            player_angle += PLAYER_ANG_SPEED;
            if(player_angle > 2*PI) {player_angle -= 2*PI;}
            updateAngleMovement(player_angle);
            break;
        case 'w':
            player_x += player_mov_x * PLAYER_MOV_SPEED;
            player_y += player_mov_y * PLAYER_MOV_SPEED;
            break;
        case 's': 
            player_x -= player_mov_x * PLAYER_MOV_SPEED;
            player_y -= player_mov_y * PLAYER_MOV_SPEED;
            break;
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
