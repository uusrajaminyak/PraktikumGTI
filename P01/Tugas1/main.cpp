#include <gl/glut.h>

void displayPrimitif(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f); 
    glVertex3f(-0.8f, 0.8f, 0.0f);
    glVertex3f(-0.6f, 0.8f, 0.0f);
    glVertex3f(-0.6f, 0.5f, 0.0f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 1.0f, 0.0f); 
    glVertex3f(-0.4f, 0.8f, 0.0f);
    glVertex3f(-0.2f, 0.8f, 0.0f);
    glVertex3f(-0.3f, 0.5f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0f, 0.0f, 1.0f); 
    glVertex3f(0.3f, 0.65f, 0.0f); 
    glVertex3f(0.1f, 0.8f, 0.0f);
    glVertex3f(0.5f, 0.8f, 0.0f);
    glVertex3f(0.6f, 0.5f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1.0f, 1.0f, 0.0f); 
    glVertex3f(-0.8f, -0.2f, 0.0f);
    glVertex3f(-0.6f, -0.2f, 0.0f);
    glVertex3f(-0.8f, -0.5f, 0.0f);
    glVertex3f(-0.6f, -0.5f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 1.0f); 
    glVertex3f(-0.4f, -0.2f, 0.0f);
    glVertex3f(-0.2f, -0.2f, 0.0f);
    glVertex3f(-0.2f, -0.5f, 0.0f);
    glVertex3f(-0.4f, -0.5f, 0.0f);
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glColor3f(1.0f, 0.0f, 1.0f); 
    glVertex3f(0.1f, -0.2f, 0.0f);
    glVertex3f(0.1f, -0.5f, 0.0f);
    glVertex3f(0.3f, -0.2f, 0.0f);
    glVertex3f(0.3f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.2f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glEnd();

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Fungsi Primitif");
    glutDisplayFunc(displayPrimitif);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); 
    glutMainLoop();
    return 0;
}
