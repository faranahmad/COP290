#include <GL/glut.h>
#include <GL/gl.h>
#include <list>
#include "Ball.h"
#include "Graphics.h"
#include <iostream>

std::vector<Ball> vballs;

void display(void)
{
      int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
      int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
    float const window_aspect = (float)window_width / (float)window_height;

    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(window_aspect > 1.) {
        glOrtho(-window_aspect, window_aspect, -1, 1, -1, 1);
    }
    else {
        glOrtho(-1, 1, -1/window_aspect, 1/window_aspect, -1, 1);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat const light_pos[4]     = {-1.00,  1.00,  1.00, 0.};
    GLfloat const light_color[4]   = { 0.85,  0.90,  0.70, 1.};
    GLfloat const light_ambient[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos),
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

    // glPushMatrix();
    //     glTranslatef(x/(float)window_width, y/(float)window_height, 0);
    //     glutSolidSphere(0.2, 31, 10);
    //     glPopMatrix();
    
    for( int i=0;i<vballs.size();i++ ) 
    {
        glPushMatrix();
        // cout<<vballs[i].GetX()<<"  "<<vballs[i].GetY()<<endl;
        glTranslatef(vballs[i].GetX()/(float)window_height, vballs[i].GetY()/(float)window_height, 0);
        glutSolidSphere(vballs[i].GetRadius()/1000.0, 31, 10);
        glPopMatrix();
    }

    glutSwapBuffers();
}

// void mouseclick(
//     int button,
//     int state,
//     int mouse_x,
//     int mouse_y )
// {
//       int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
//       int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
//     float const window_aspect = (float)window_width / (float)window_height;

//     v2f_t const sc = {
//         (window_aspect > 1.0 ? window_aspect : 1.) *
//         (  ((float)mouse_x / (float)window_width )*2. - 1.),

//         (window_aspect < 1.0 ? 1./window_aspect : 1.) *
//         ( -((float)mouse_y / (float)window_height)*2. + 1.)
//     };
//     sphere_centers.push_back(sc);

//     glutPostRedisplay();
// }


int graphics(int argc,char *argv[], Board board)
{
    vballs=board.GetVectorBalls();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(board.GetDimensionX(),board.GetDimensionY());
    glutCreateWindow("Team BabeMagents");
    
    glutDisplayFunc(display);
    // glutMouseFunc(mouseclick);

    glutMainLoop();

    return 0;
}

