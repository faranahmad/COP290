#include <GL/glut.h>
#include <GL/gl.h>
#include <list>
#include <iostream>
#include <stdlib.h>
// #include <SFML/Audio.hpp>
using namespace std;


int x=0;
int y=0;

void display(void)
{
    int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
    int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
    float const window_aspect = (float)window_width / (float)window_height;
    // cout<<window_width<<"   "<<window_height<<endl;
    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, window_width, window_height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // gluOrtho2D(-600,600,-1200,1200);
    if(window_aspect > 1.) {
        glOrtho(-1200, 1200, -600, 600, -1200, 1200);
    }
    else {
        glOrtho(-1, 1, -1/window_aspect, 1/window_aspect, -1, 1);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat const light_pos[4]     = {1200, -600, 0    , 1.0  };
    GLfloat const light_color[4]   = { 0,  0,  1, 1.};
    GLfloat const light_ambient[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos),
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

        GLfloat const light_pos2[4]     = {-1200, -600,  0  , 1.0  };
    GLfloat const light_color2[4]   = { 1,  0,  0, 1.};
    GLfloat const light_ambient2[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2),
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color2);

    GLfloat const light_pos3[4]     = {0, 600,  0  , 1.0  };
    GLfloat const light_color3[4]   = { 0,  1,  0, 1.};
    GLfloat const light_ambient3[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos3),
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color3);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_color3);

    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);


    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
        glTranslatef(x, y, 0);
        glColor3f(0, 0, 1); 
        GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
        GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        GLfloat shininess[] = {50};
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        x+=1;
        y+=1; 
        system("canberra-gtk-play -f sound.wav");
//         sf::SoundBuffer buffer;
// if (!buffer.loadFromFile("sound.wav")){
//     return -1;
// }
// // sf::Sound sound;
// // sound.setBuffer(buffer);
// // sound.play();
        // PlaySound("sound.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
glutSolidSphere(100.4, 100, 100);
        glPopMatrix();

    glPushMatrix();
        glTranslatef(0-x, 0-y, 0);
        // x+=1;
        // y+=1;
        glColor3f(1,0,0);
        glutSolidSphere(100, 31, 10);
        glPopMatrix();
    // for(  ) 
    // {

    //     glPushMatrix();
    //     glTranslatef(sc->x, sc->y, 0);
    //     glutSolidSphere(0.1, 31, 10);
    //     glPopMatrix();
    // }

    glutSwapBuffers();
    glutPostRedisplay();
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


int main(int argc,char *argv[] )
{
    x=atoi(argv[1]);
    y=atoi(argv[2]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Yo");
    
    glutDisplayFunc(display);
    // glutMouseFunc(mouseclick);

    glutMainLoop();

    return 0;
}