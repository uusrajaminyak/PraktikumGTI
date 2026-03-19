#include <GL/glut.h>
#include <stdlib.h>

static int shoulder = 0, elbow = 0, palm = 0;
static int thumb = 0, indexFinger = 0, middle = 0, ring = 0, little = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix(); 
    glTranslatef(-2.0, 0.0, 0.0); 
    glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0); 
    glPopMatrix();
    
    glTranslatef(1.0, 0.0, 0.0); 
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(2.0, 0.4, 1.0);
    glutWireCube(1.0); 
    glPopMatrix();

    glTranslatef(1.0, 0.0, 0.0); 
    glRotatef((GLfloat)palm, 0.0, 0.0, 1.0);
    glTranslatef(0.4, 0.0, 0.0);
    
    glPushMatrix();
    glScalef(0.8, 0.6, 1.0); 
    glutWireCube(1.0); 
    glPopMatrix();

    glTranslatef(0.4, 0.0, 0.0); 

    glPushMatrix();
    glTranslatef(-0.2, 0.35, 0.0);  
    glRotatef((GLfloat)thumb, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);    
    glScalef(0.4, 0.12, 1.0);       
    glutWireCube(1.0); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.2, 0.0); 
    glRotatef((GLfloat)indexFinger, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glScalef(0.5, 0.1, 1.0);
    glutWireCube(1.0); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.05, 0.0); 
    glRotatef((GLfloat)middle, 0.0, 0.0, 1.0);
    glTranslatef(0.3, 0.0, 0.0);
    glScalef(0.6, 0.1, 1.0);      
    glutWireCube(1.0); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -0.1, 0.0); 
    glRotatef((GLfloat)ring, 0.0, 0.0, 1.0);
    glTranslatef(0.25, 0.0, 0.0);
    glScalef(0.5, 0.1, 1.0);
    glutWireCube(1.0); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -0.25, 0.0); 
    glRotatef((GLfloat)little, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glScalef(0.4, 0.1, 1.0);       
    glutWireCube(1.0); 
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -6.0); 
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's': shoulder = (shoulder + 5) % 360; glutPostRedisplay(); break;
        case 'S': shoulder = (shoulder - 5) % 360; glutPostRedisplay(); break;
        case 'e': elbow = (elbow + 5) % 360; glutPostRedisplay(); break;
        case 'E': elbow = (elbow - 5) % 360; glutPostRedisplay(); break;
        case 'p': palm = (palm + 5) % 360; glutPostRedisplay(); break;
        case 'P': palm = (palm - 5) % 360; glutPostRedisplay(); break;
        
        case 't': thumb = (thumb + 5) % 360; glutPostRedisplay(); break;        
        case 'T': thumb = (thumb - 5) % 360; glutPostRedisplay(); break;
        case 'i': indexFinger = (indexFinger + 5) % 360; glutPostRedisplay(); break;  
        case 'I': indexFinger = (indexFinger - 5) % 360; glutPostRedisplay(); break;
        case 'm': middle = (middle + 5) % 360; glutPostRedisplay(); break;      
        case 'M': middle = (middle - 5) % 360; glutPostRedisplay(); break;
        case 'r': ring = (ring + 5) % 360; glutPostRedisplay(); break;          
        case 'R': ring = (ring - 5) % 360; glutPostRedisplay(); break;
        case 'l': little = (little + 5) % 360; glutPostRedisplay(); break;     
        
        case 27: exit(0); break; 
        default: break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(900, 600); 
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tangan");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
