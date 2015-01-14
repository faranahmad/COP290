#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <algorithm>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
using namespace std;

void display();
void specialKeys();
double rotate_y=0; 
double rotate_x=0;
void display()
{
	int const w  = glutGet(GLUT_WINDOW_WIDTH);
	int const h = glutGet(GLUT_WINDOW_HEIGHT);
	float const wa = (float)w / (float)h;
	    
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	 // glLoadIdentity();
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-w,w,-h,h,-1000,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef( rotate_x, 200, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 200, 0.0 );
	
	float f=(4.0/6.0)*min(w,h);
	glBegin(GL_POLYGON);
	
	glColor3f( 1.0, 0, 0.0 );    
	glVertex3f( f , -f, -f); 
	// glColor3f( 0.5, 1.0, 0.0 );
	glVertex3f(  f,  f, -f );
	// glColor3f( 0.0, 0.5, 1.0 );    
	glVertex3f( -f,  f, -f );       
	// glColor3f( 1.0, 0.0, 0.5 );     
	glVertex3f( -f, -f, -f);      
	
	glEnd();
	
	// glBegin(GL_POLYGON);
	// glColor3f(   1.0,  1.0, 1.0 );
	// glVertex3f(  f, -f, f );
	// glVertex3f(  f,  f, f);
	// glVertex3f( -f,  f, f);
	// glVertex3f( -f, -f, f );
	// glEnd();
	
	// Purple side - RIGHT
	glBegin(GL_POLYGON);
	glColor3f(  0.0,    1.0,  0 );
	glVertex3f( f, -f, -f );
	glVertex3f( f,  f, -f );
	glVertex3f( f,  f,  f );
	glVertex3f( f, -f,  f );
	glEnd();
	
	glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(  1,    1.0,  0 );	
    glutSolidSphere(100, 100, 100);
        glPopMatrix();
    glPushMatrix();
    glColor3f(  0.0,    1.0,  1 );
    glTranslatef(200, 200, 200);	
    glutSolidSphere(100, 100, 100);
        glPopMatrix();
	// Green side - LEFT
	// glBegin(GL_POLYGON);
	// glColor3f(   0.0,  1.0,  0.0 );
	// glVertex3f( -f, -f,  f );
	// glVertex3f( -f,  f,  f );
	// glVertex3f( -f,  f, -f );
	// glVertex3f( -f, -f, -f );
	// glEnd();
	
	// Blue side - TOP
	// glBegin(GL_POLYGON);
	// glColor3f(   0.0,  0.0,  1.0 );
	// glVertex3f(  f,  f,  f );
	// glVertex3f(  f,  f, -f );
	// glVertex3f( -f,  f, -f );
	// glVertex3f( -f,  f,  f );
	// glEnd();
	
	// Red side - BOTTOM
	glBegin(GL_POLYGON);
	glColor3f(   0,  0,  1 );
	glVertex3f(  f, -f, -f );
	glVertex3f(  f, -f,  f );
	glVertex3f( -f, -f,  f );
	glVertex3f( -f, -f, -f );
	glEnd();
	
	glFlush();
	glutSwapBuffers();
 
}
 
void specialKeys( int key, int x, int y ) 
{
 
  if (key == GLUT_KEY_RIGHT)
    rotate_y += 2;
 
  else if (key == GLUT_KEY_LEFT)
    rotate_y -= 2;
 
  else if (key == GLUT_KEY_UP)
    rotate_x += 2;
 
  else if (key == GLUT_KEY_DOWN)
    rotate_x -= 2;
 
  glutPostRedisplay();
 
}
 


void reshape(int x, int y)
{
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    int w=glutGet(GLUT_WINDOW_WIDTH);
    int h=glutGet(GLUT_WINDOW_HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluOrtho2D(-600,600,-1200,1200);
    // if(window_aspect > 1.) {
    glOrtho(0-w,w,0-h,h,-2000,2000);
    // }
    

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char* argv[])
{
 
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000,500);	 
  glutCreateWindow("Kartikeya Gupta");
 
  glEnable(GL_DEPTH_TEST);
 
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
  glutReshapeFunc(reshape);
 
  glutMainLoop();
 
  return 0;

}
