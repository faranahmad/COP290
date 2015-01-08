#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
 
void display();
void specialKeys();
double rotate_y=0; 
double rotate_x=0;
void display(){
 
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glRotatef( rotate_x, 0.75, 0.0, 0.0 );
  glRotatef( rotate_y, 0.0, 0.75, 0.0 );
 
  glBegin(GL_POLYGON);
 
  glColor3f( 1.0, 1.0, 0.0 );     glVertex3f(  0.5, -0.5, -0.5 );      glColor3f( 0.5, 1.0, 0.0 );     glVertex3f(  0.5,  0.5, -0.5 );        glColor3f( 0.0, 0.5, 1.0 );     glVertex3f( -0.5,  0.5, -0.5 );       glColor3f( 1.0, 0.0, 0.5 );     glVertex3f( -0.5, -0.5, -0.5 );      
 
  glEnd();
 
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0, 1.0 );
  glVertex3f(  0.5, -0.5, 0.5 );
  glVertex3f(  0.5,  0.5, 0.5 );
  glVertex3f( -0.5,  0.5, 0.5 );
  glVertex3f( -0.5, -0.5, 0.5 );
  glEnd();
 
  // Purple side - RIGHT
  glBegin(GL_POLYGON);
  glColor3f(  0.0,    1.0,  1.0 );
  glVertex3f( 0.5, -0.5, -0.5 );
  glVertex3f( 0.5,  0.5, -0.5 );
  glVertex3f( 0.5,  0.5,  0.5 );
  glVertex3f( 0.5, -0.5,  0.5 );
  glEnd();
 
  // Green side - LEFT
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  1.0,  0.0 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  // Blue side - TOP
  glBegin(GL_POLYGON);
  glColor3f(   0.0,  0.0,  1.0 );
  glVertex3f(  0.5,  0.5,  0.5 );
  glVertex3f(  0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5, -0.5 );
  glVertex3f( -0.5,  0.5,  0.5 );
  glEnd();
 
  // Red side - BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  1.0,  0.0 );
  glVertex3f(  0.5, -0.5, -0.5 );
  glVertex3f(  0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5,  0.5 );
  glVertex3f( -0.5, -0.5, -0.5 );
  glEnd();
 
  glFlush();
  glutSwapBuffers();
 
}
 
void specialKeys( int key, int x, int y ) {
 
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
 
int main(int argc, char* argv[]){
 
  glutInit(&argc,argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 
  glutCreateWindow("Kartikeya Gupta");
 
  glEnable(GL_DEPTH_TEST);
 
  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);
 
  glutMainLoop();
 
  return 0;

}