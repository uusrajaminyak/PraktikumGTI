#include <gl/glut.h>
#include <math.h>

#define PI 3.14

void drawLingkaran(float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    GLint circle_points = 100;
    for (int i = 0; i < circle_points; i++) {
        float angle = 2 * PI * i / circle_points;
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void drawPohon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    glColor3f(0.35f, 0.2f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f( 0.03f, 0.0f);
    glVertex2f( 0.02f, 0.2f);
    glVertex2f(-0.02f, 0.2f);
    glEnd();

    glTranslatef(0.0f, 0.22f, 0.0f); 
    drawLingkaran(0.15f, 0.1f, 0.5f, 0.1f); 
    
    glPopMatrix();
}

void drawRoda() {
    drawLingkaran(0.12f, 0.15f, 0.15f, 0.15f); 
    drawLingkaran(0.08f, 0.9f, 0.9f, 0.9f); 
    drawLingkaran(0.03f, 0.6f, 0.6f, 0.6f);
    glColor3f(0.3f, 0.3f, 0.3f);
    glLineWidth(3.0f);
    for(int i = 0; i < 8; i++) {
        glPushMatrix(); 
        glRotatef(i * 45.0f, 0.0f, 0.0f, 1.0f); 
        
        glBegin(GL_LINES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.08f, 0.0f);
        glEnd();
        
        glPopMatrix(); 
    }
}

void drawBackground() {
    glColor3f(0.4f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f,  0.0f);
    glVertex2f( 1.0f,  0.0f);
    glVertex2f( 1.0f,  1.0f);
    glVertex2f(-1.0f,  1.0f);
    glEnd();

    drawPohon(-0.6f, 0.17f);  
    drawPohon( 0.65f, 0.17f); 

    glColor3f(0.2f, 0.5f, 0.3f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.4f);
    glVertex2f( 1.0f, -0.4f);
    glVertex2f( 1.0f,  0.1f);
    glVertex2f( 0.6f,  0.2f);
    glVertex2f( 0.2f,  0.05f);
    glVertex2f(-0.4f,  0.25f);
    glVertex2f(-1.0f,  0.1f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.25f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f( 1.0f, -1.0f);
    glVertex2f( 1.0f, -0.4f);
    glVertex2f(-1.0f, -0.4f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.68f);
    glVertex2f( 1.0f, -0.68f);
    glVertex2f( 1.0f, -0.72f);
    glVertex2f(-1.0f, -0.72f);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    drawBackground();
    glPushMatrix(); 
    glTranslatef(0.0f, -0.3f, 0.0f); 

    glColor3f(0.6f, 0.1f, 0.15f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.60f, -0.15f); 
    glVertex2f( 0.55f, -0.15f); 
    glVertex2f( 0.65f, -0.05f); 
    glVertex2f( 0.40f,  0.05f); 
    glVertex2f(-0.60f,  0.05f); 
    glVertex2f(-0.65f, -0.05f); 
    glEnd();

    glColor3f(0.6f, 0.1f, 0.15f); 
    glBegin(GL_POLYGON);
    glVertex2f(-0.4f,  0.05f); 
    glVertex2f( 0.2f,  0.05f); 
    glVertex2f( 0.0f,  0.25f); 
    glVertex2f(-0.2f,  0.25f); 
    glEnd();

    glColor3f(0.6f, 0.8f, 0.9f); 
    
    glBegin(GL_POLYGON);
    glVertex2f(-0.35f, 0.07f);
    glVertex2f(-0.12f, 0.07f);
    glVertex2f(-0.12f, 0.22f);
    glVertex2f(-0.20f, 0.22f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.08f, 0.07f);
    glVertex2f( 0.15f, 0.07f);
    glVertex2f( 0.00f, 0.22f);
    glVertex2f(-0.08f, 0.22f);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.6f);
    glBegin(GL_POLYGON);
    glVertex2f(0.58f, -0.08f);
    glVertex2f(0.64f, -0.08f);
    glVertex2f(0.62f, -0.02f);
    glVertex2f(0.53f, -0.02f);
    glEnd();

    glColor3f(0.9f, 0.2f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-0.64f, -0.08f);
    glVertex2f(-0.60f, -0.08f);
    glVertex2f(-0.60f, -0.02f);
    glVertex2f(-0.62f, -0.02f);
    glEnd();

    glPushMatrix(); 
    glTranslatef(-0.4f, -0.15f, 0.0f); 
    drawRoda();
    glPopMatrix(); 

    glPushMatrix(); 
    glTranslatef( 0.35f, -0.15f, 0.0f); 
    drawRoda();
    glPopMatrix(); 

    glPopMatrix();
    glFlush(); 
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600); 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Mobil");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
