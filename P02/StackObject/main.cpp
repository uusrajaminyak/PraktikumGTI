#include <gl/glut.h> 
#include <gl/gl.h> 
#include <math.h> 

#define PI 3.1415926535898 

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix(); 
    glLineWidth(2.0f); 
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex3f(0.00f, 0.20f, 0.0f); 
    glVertex3f(0.00f, -0.20f, 0.0f); 
    glEnd(); 
    glPopMatrix(); 

    glPushMatrix(); 
    glPointSize(5.0f); 
    glTranslatef(0.35f, 0.35f, 0.0f); 
    glBegin(GL_POINTS); 
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex3f(0.25f, 0.25f, 0.0f); 
    glEnd(); 
    glPopMatrix(); 

    glPushMatrix(); 
    glTranslatef(0.50f, 0.50f, 0.00f); 
    glBegin(GL_TRIANGLE_STRIP); 
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-0.05f, -0.05f, 0.00f); 
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f( 0.15f, -0.05f, 0.00f); 
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-0.05f,  0.05f, 0.00f); 
    glColor3f(1.0f, 1.0f, 0.0f); glVertex3f( 0.15f,  0.05f, 0.00f); 
    glEnd(); 
    glPopMatrix(); 
    glPushMatrix();
	 
    glBegin(GL_LINE_LOOP); 
    GLint circle_points = 100; 
    int i; 
    float angle; 
    for (i = 0; i < circle_points; i++) { 
        angle = 2 * PI * i / circle_points; 
        glVertex2f(cos(angle), sin(angle)); 
    }
    glEnd();
    glPopMatrix(); 
    glFlush(); 
}

int main(int argc, char* argv[]) { 
    glutInit(&argc, argv); 
    glutInitWindowSize(640, 480); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutCreateWindow("Simple"); 
    glutDisplayFunc(RenderScene); 
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f); 
    glutMainLoop();
    return 0; 
}
