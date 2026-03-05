#include <gl/glut.h>
void Window(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640,480);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("biru");
	glutDisplayFunc(Window);
	glClearColor (0.0f, 0.0f, 1.0f, 1.0f);
	glutMainLoop();
	return 0;
}
