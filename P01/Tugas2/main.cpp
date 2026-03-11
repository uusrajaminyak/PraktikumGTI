#include <gl/glut.h>

void drawKubus() {
    glColor3f(0.53f, 0.01f, 0.01f); 
    glBegin(GL_QUADS);
    glVertex2f(-0.05f, -0.05f);
    glVertex2f( 0.05f, -0.05f); 
    glVertex2f( 0.05f,  0.05f);
    glVertex2f(-0.05f,  0.05f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); 
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.05f, -0.05f); 
    glVertex2f( 0.05f, -0.05f); 
    glVertex2f( 0.05f,  0.05f);
    glVertex2f(-0.05f,  0.05f); 
    glEnd();
}

const int ROWS = 13;
const int COLS = 13;
int map[ROWS][COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0}, 
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
    {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, 
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0}, 
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0}, 
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
};

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity(); 
    float startX = -0.6f;
    float startY =  0.6f;
    float step   =  0.1f; 
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (map[r][c] == 1) {
                glPushMatrix();
                glTranslatef(startX + (c * step), startY - (r * step), 0.0f);
                drawKubus(); 
                glPopMatrix();
            }
        }
    }
    glFlush(); 
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutCreateWindow("Menumpuk Kubus");
    glClearColor(0.97f, 0.78f, 0.86f, 1.0f); 
    glutDisplayFunc(display); 
    glutMainLoop(); 
    return 0; 
}
