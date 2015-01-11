#include "Board.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "Graphics.h"





#include <GL/glut.h>
#include <GL/gl.h>
#include <list>
#include "Ball.h"
#include "Graphics.h"
#include <iostream>


struct Graph {
	int x1;
	char **s1;
};

pthread_mutex_t UpdateLock;
Board FinalBoard;




void display(void)
{
	// cout<<"In display\n";
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
    
    for( int i=0;i<FinalBoard.GetNumberBalls();i++ ) 
    {
        glPushMatrix();
        // cout<<FinalBoard.GetVectorBalls()[i].GetX()<<"  "<<FinalBoard.GetVectorBalls()[i].GetY()<<endl;
        glTranslatef(FinalBoard.GetBallFromId(i).GetX()/(float)window_height, FinalBoard.GetBallFromId(i).GetY()/(float)window_height, 0);
        glutSolidSphere(FinalBoard.GetBallFromId(i).GetRadius()/1000.0, 31, 10);
        glPopMatrix();
    }
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


int graphics(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionY());
    glutCreateWindow("Team BabeMagents");
    
    glutDisplayFunc(display);
    // glutMouseFunc(mouseclick);

    glutMainLoop();

    return 0;
}



// int counter=0

void *UpdateBoardThread(void* id)
{
	while (true)
	{
		long ballid = (long) id;
		pthread_mutex_lock (&UpdateLock);
		// cout <<"Starting for ball " <<ballid<<"\n";
		Ball BallConsidered = FinalBoard.GetBallFromId(ballid);
		int BallConsidered_Coordx = BallConsidered.GetX();
		int BallConsidered_Coordy = BallConsidered.GetY();
		// cout <<BallConsidered_Coordx<<"\t"<<BallConsidered_Coordy<<"\n";
		int BallConsidered_VelocityX=BallConsidered.GetVelocityX();
		int BallConsidered_VelocityY=BallConsidered.GetVelocityY();
		// BallConsidered.SetX(((BallConsidered_Coordx+BallConsidered_VelocityX)%(2*FinalBoard.GetDimensionX())) -FinalBoard.GetDimensionX());
		BallConsidered.SetX((BallConsidered_Coordx+BallConsidered_VelocityX) % (FinalBoard.GetDimensionX()));
		// BallConsidered.SetY(((BallConsidered_Coordy+BallConsidered_VelocityY)%(2*FinalBoard.GetDimensionY())) -FinalBoard.GetDimensionY());
		FinalBoard.SetBallFromId(ballid,BallConsidered);
		pthread_mutex_unlock (&UpdateLock);	
		usleep(10000);
	}
}	

void *DisplayUpdate(void* id)
{
	Graph  *pa= (Graph *)id;
	// cout <<"Updating diaply\n";
	graphics(pa->x1,pa->s1);
	// usleep(10000);
}

int main(int argc, char **argv)
{
	const int NumberOfBalls = atoi(argv[1]);
	pthread_mutex_init(&UpdateLock,NULL);
	FinalBoard=Board(800,600,NumberOfBalls);
	pthread_t BallThreads [NumberOfBalls];
	pthread_t DisplayThread;


	cout<<FinalBoard.GetBoardInformation()<<"\n";


	Graph graphics1;
	graphics1.x1=argc;
	graphics1.s1=argv;

	std::cout <<"Ball threas" <<NumberOfBalls <<"\n";
	for (long i=0; i<NumberOfBalls ;i++)
	{
		cout <<"Creating thread i: " <<i <<"\n";
		pthread_create(&BallThreads[i],NULL,UpdateBoardThread,(void *)i);
	
	}
	cout <<"out of for loop\n";

	pthread_create(&DisplayThread,NULL,DisplayUpdate,&graphics1);
	

	for (int i=0; i<NumberOfBalls ;i++)
	{
		pthread_join(BallThreads[i],NULL);
	}


	pthread_join(DisplayThread,NULL);
	// create a display thread 
	// run the threads 
	pthread_exit(NULL);
	return 0;
}
