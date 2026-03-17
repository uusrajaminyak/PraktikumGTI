#include <gl/glut.h>
#include <math.h>

#define PI 3.14

void displayLingkaran(void) {
    glClear(GL_COLOR_BUFFER_BIT); 
    glLoadIdentity();
    glColor3f(0.2f, 0.6f, 0.8f); 
    glBegin(GL_POLYGON); 
    GLint circle_points = 100; 
    float radius = 0.4f;      
    
    for (int i = 0; i < circle_points; i++) {
        float angle = 2 * PI * i / circle_points;
        glVertex2f(radius * cos(angle), radius * sin(angle)); 
    }
    
    glEnd();
    glFlush(); 
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Lingkaran");
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glutDisplayFunc(displayLingkaran);
    glutMainLoop();
    return 0;
}
