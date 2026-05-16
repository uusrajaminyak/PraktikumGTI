#include <gl/glut.h>
#include <math.h>

float sudutBumi = 0.0f;
float sudutRevolusiBulan = 0.0f;
float sudutRotasiBulan = 0.0f;

void drawPlanet(float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for(int i = 0; i < 360; i += 5) {
        float theta = i * 3.14159f / 180.0f;
        glVertex2f(radius * cos(theta), radius * sin(theta));
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(radius, 0.0f);
    glEnd();
}

void displayBumiBulan(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); 
    glPushMatrix(); 
    glRotatef(sudutBumi, 0.0f, 0.0f, 1.0f); 
    drawPlanet(0.2f, 0.2f, 0.5f, 1.0f); 
    glPopMatrix();
    glPushMatrix(); 
    glRotatef(sudutRevolusiBulan, 0.0f, 0.0f, 1.0f); 
    glTranslatef(0.6f, 0.0f, 0.0f); 
    glRotatef(sudutRotasiBulan, 0.0f, 0.0f, 1.0f); 
    drawPlanet(0.08f, 0.6f, 0.6f, 0.6f); 
    glPopMatrix(); 
    glutSwapBuffers(); 
}

void update(int value) {
    sudutBumi += 2.0f;              
    sudutRevolusiBulan += 1.0f;     
    sudutRotasiBulan += 3.0f;       
    if (sudutBumi > 360) sudutBumi -= 360;
    if (sudutRevolusiBulan > 360) sudutRevolusiBulan -= 360;
    if (sudutRotasiBulan > 360) sudutRotasiBulan -= 360;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); 
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
    glutCreateWindow("Sistem Bumi dan Bulan");
    glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
    glutDisplayFunc(displayBumiBulan);
    glutTimerFunc(16, update, 0); 
    glutMainLoop();
    return 0;
}
