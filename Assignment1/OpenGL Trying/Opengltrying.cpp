#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <algorithm>
#include <iostream>
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
double zoom=1;
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
	glScalef(zoom,zoom,zoom);
	
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
    glColor3f(  0.2,    0.8,  0.2 );	
    glutSolidSphere(100, 100, 100);
        glPopMatrix();
    glPushMatrix();
    glColor3f(  0.55,    0.3,  0.41 );
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
int prevx=0;
int prevy=0;
int mx=0;
int my=0;
int buttonpressed=false;
int state=0;
void mouseclick(int button,int state,int x,int y )
{	if(button==GLUT_LEFT_BUTTON)
	{
    	if(state== GLUT_UP )
    	{
    	    int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
    	    int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
    	    float const window_aspect = (float)window_width / (float)window_height;
    	    cout<<x<<'\t'<<y<<endl;
    		buttonpressed=false;
    	    
    	}
	}
	if(button==3)
	{
		if(state==0)
		{
			zoom+=0.03;
		}
	}

	if(button==4)
	{
		if(state==0)
		{
			zoom-=0.03;
		}
	}
	if(state=GLUT_UP)
	{
		mx=x;
    	    my=y;
    	    prevx=x;
    	    prevy=y;
    	    state=0;
	}

    glutPostRedisplay();

}


void mousemotion(int x, int y)
 {	
 	if(abs(mx-x)>10&& !buttonpressed)
	{
	state=1;
	buttonpressed=true;
	}
 	
 	if(abs(my-y)>10 && !buttonpressed)
 			{
 				state=2;
 				buttonpressed=true;
 	}
 	if(state==1)
 	{
 		if(x>prevx)
 			rotate_y+=0.75;
 		else
 			rotate_y+=-0.75;
 	}
 	if(state==2)
 		if(y>prevy)
 			rotate_x+=0.75;
 		else
 			rotate_x+=-0.75;
 	prevx=x;
 	prevy=y;
 	// cout<<x<<"\t"<<prevx<<"\t"<<mx<<"\t"<<endl;
 	// cout<<y<<"\t"<<prevy<<"\t"<<my<<endl<<endl;
 	glutPostRedisplay();
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
 
  glutMouseFunc(mouseclick);
  glutMotionFunc(mousemotion);
  glutMainLoop();
 
  return 0;

}
