#include "Combined.h"

void ShowBullet(float x,float y,float angle,Color color)
{
	glPushMatrix();
	glTranslatef(x,y,1000);
	glColor3f(color.GetR(),color.GetG(),color.GetB());
	GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
	GLfloat ambient[] = {0.7f,0.7f,0.7f,1.0f};
	GLfloat cyan[] = {0.8,0.8,0.8,1};
	GLfloat shininess[] = {100};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glutSolidSphere(10, 31, 10);	
	glPopMatrix();
}

void ShowMissile(float x, float y, float vx, float vy, Color color)
{
	GLUquadricObj *quadric=gluNewQuadric();
	
	int length=300;
	int radius=100;

	float vz = 0;
	float v = sqrt(vx*vx+vy*vy);
	float ax = 0;
	float rx = 57.29577*acos(vy/v);
	float ry = 57.29577*asin(vy/v);

	glPushMatrix();

	glTranslatef(x,y,1000);
	glRotatef(-0.5,0.0,1.0,1.0);

	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluCylinder(quadric,radius,radius,100,50,1);

	glPopMatrix();
	gluDeleteQuadric(quadric);
}

void ShowShip(float x, float y,float angle, Color color)
{
	glPushMatrix();
	int dimx=20;
	int dimy=40;
	int dimz=20;

	float sintheta = sin(angle);
	float costheta = cos(angle);

	float xcos = dimx*costheta
	float xsin = dimx*sintheta
	float ycos = dimy*costheta
	float ysin = dimy*sintheta

	glBegin(GL_QUADS);

	glRotatef()

	glColor3f(0.0,1.0,0.0);
	glVertex3f(x+xcos/2 - ysin/2, y+xsin/2 + ycos/2 ,dimz/2);
	glVertex3f(x+xcos/2 - ysin/2, y+xsin/2 + ycos/2 ,-dimz/2);
	glVertex3f(x+xcos/2 + ysin/2, y+xsin/2 - ycos/2 ,-dimz/2);
	glVertex3f(x+xcos/2 + ysin/2, y+xsin/2 - ycos/2 ,dimz/2);

	glColor3f(0.0,1.0,0.0);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,dimz/2);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,dimz/2);

	glColor3f(0.0,1.0,0.0);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,dimz/2);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,dimz/2);





	glEnd();
	glPopMatrix();
}


void display(void)
{
	std::cout<<"In display\n";
	int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
	int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
	float const window_aspect = (float)window_width / (float)window_height;
	glClearColor(0.5, 0.5, 1.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0-window_width, window_width,0- window_height,window_height,-2000,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ShowBullet(50,-60,5,Color(255,0,0));
	ShowBullet(-50,-60,5,Color(255,0,0));

	ShowMissile(-40.0,-40.0,10.0,10.0,Color(255,0,0));

	glPushMatrix();
	glTranslatef(100,100,1000);
	glColor3f(0.5,0.8,0.2);
	GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
	GLfloat ambient[] = {0.7f,0.7f,0.7f,1.0f};
	GLfloat cyan[] = {0.8,0.8,0.8,1};
	GLfloat shininess[] = {100};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glutSolidSphere(30, 31, 10);
	glPopMatrix();
	glutSwapBuffers();
	// glutPostRedisplay();
}

int main(int argc,char *argv[])
{
    // Wrapper function for graphics
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1600,900);
    glutCreateWindow("Team Babe Magnets");
    
    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    // glutMouseFunc(mouseclick);
    // glutKeyboardFunc(handleKeypress);
    // initRendering();

    glutMainLoop();

    return 0;
}