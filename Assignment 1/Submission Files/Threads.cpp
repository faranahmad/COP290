#include "Board.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "Graphics.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <algorithm>
#include <cmath>


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

    // if(window_aspect > 1.) {
    // glOrtho(0-FinalBoard.GetDimensionX(), FinalBoard.GetDimensionX(), 0-FinalBoard.GetDimensionY(),+FinalBoard.GetDimensionY(), -1, 1);
    glOrtho(0-FinalBoard.GetDimensionX(), FinalBoard.GetDimensionX(), 0-FinalBoard.GetDimensionY(),+FinalBoard.GetDimensionY(),
     0-min(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionY()), min(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionY()));
    
    // }
    // else {
        // glOrtho(-1, 1, -1/window_aspect, 1/window_aspect, -1, 1);
    // }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // GLfloat const light_pos[4]     = { 0,  0,  500, 1.0};
    // GLfloat const light_color[4]   = { 0.85,  0.90,  0.70, 1.};
    // GLfloat const light_ambient[4] = { 0.10,  0.10,  0.30, 1.};
    // glLightfv(GL_LIGHT0, GL_POSITION, light_pos),
    // glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);

    for( int i=0;i<FinalBoard.GetNumberBalls();i++ ) 
    {
        glPushMatrix();
        // cout<<FinalBoard.GetVectorBalls()[i].GetX()<<"  "<<FinalBoard.GetVectorBalls()[i].GetY()<<endl;
        glTranslatef(FinalBoard.GetBallFromId(i).GetX(), FinalBoard.GetBallFromId(i).GetY(), 0);
        glColor3f(FinalBoard.GetBallFromId(i).GetColor()[0],FinalBoard.GetBallFromId(i).GetColor()[1],FinalBoard.GetBallFromId(i).GetColor()[2]);
        glutSolidSphere(FinalBoard.GetBallFromId(i).GetRadius(), 31, 10);
        glPopMatrix();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}


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
		double BallConsidered_Radius = BallConsidered.GetRadius();
		// cout <<BallConsidered_Coordx<<"\t"<<BallConsidered_Coordy<<"\n";
		int BallConsidered_VelocityX=BallConsidered.GetVelocityX();
		int BallConsidered_VelocityY=BallConsidered.GetVelocityY();
		// BallConsidered.SetX(((BallConsidered_Coordx+BallConsidered_VelocityX)%(2*FinalBoard.GetDimensionX())) -FinalBoard.GetDimensionX());
		if (BallConsidered_Coordx+BallConsidered_VelocityX +BallConsidered_Radius> FinalBoard.GetDimensionX())
		{
			BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());
		}
		else if (BallConsidered_Coordx+BallConsidered_VelocityX + FinalBoard.GetDimensionX() -BallConsidered_Radius<0)
		{
			BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());	
		}
		else
		{
			BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);
		}
		
		if (BallConsidered_Coordy+BallConsidered_VelocityY +BallConsidered_Radius> FinalBoard.GetDimensionY())
		{
			BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());
		}
		else if (BallConsidered_Coordy+BallConsidered_VelocityY + FinalBoard.GetDimensionY() -BallConsidered_Radius <0)
		{
			BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());	
		}
		else
		{
			BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
		}
		vector<Ball> Vector_Of_Balls = FinalBoard.GetVectorBalls()
		for(int i=0;i<FinalBoard.GetNumberBalls();i++)
		{
			if (Vector_Of_Balls[i]=!BallConsidered)
			{
				if(BallConsidered.GetRadius()+Vector_Of_Balls[i].GetRadius()>=(sqrt(double((BallConsidered.GetX()-Vector_Of_Balls[i].GetX())*(BallConsidered.GetX()-Vector_Of_Balls[i].GetX())+(BallConsidered.GetY()-Vector_Of_Balls[i].GetY())*(BallConsidered.GetY()-Vector_Of_Balls[i].GetY())))))
				{
					int mass1 = BallConsidered.GetRadius()*BallConsidered.GetRadius()*BallConsidered.GetRadius();
					int mass2 = Vector_Of_Balls[i].GetRadius()*Vector_Of_Balls[i].GetRadius()*Vector_Of_Balls[i].GetRadius(); 
					int vx1 = BallConsidered.GetVelocityX();
					int vx2 = Vector_Of_Balls[i].GetVelocityX();
					int vy1 =  BallConsidered.GetVelocityY();
					int vy2 =  Vector_Of_Balls[i].GetVelocityY();
					int  dx = BallConsidered.GetX()-Vector_Of_Balls[i].GetX();
					int dy = BallConsidered.GetY()-Vector_Of_Balls[i].GetY();
					double distance = sqrt(double(dx*dx+dy*dy));
					double ax = dx/distance;
					double ay = dy/distance;
					double va1 = (vx1*ax+vy1*ay),vb1 =(-vx1*ay+vy1*ax);
					double va2=(vx2*ax+vy2*ay), vb2=(-vx2*ay+vy2*ax);
					double vaP1=va1 + 2*(va2-va1)/(1+double(mass1)/mass2);
					double vaP2=va2 + 2*(va1-va2)/(1+double(mass2)/mass1);
					vx1=int(vaP1*ax-vb1*ay);  vy1=int(vaP1*ay+vb1*ax);// new vx,vy for ball 1 after collision
					vx2=int(vaP2*ax-vb2*ay);  vy2=int(vaP2*ay+vb2*ax);// new vx,vy for ball 2 after collision
					BallConsidered.setVelocity(vx1,vy1);
					Vector_Of_Balls[i].setVelocity(vx2,vy2);
				}			
			}
		}

		// BallConsidered.SetY((BallConsidered_Coordy+BallConsidered_VelocityY)%FinalBoard.GetDimensionY());

		// BallConsidered.SetX((BallConsidered_Coordx+BallConsidered_VelocityX +4*FinalBoard.GetDimensionX()) % 2*(FinalBoard.GetDimensionX()) -FinalBoard.GetDimensionX());
		// BallConsidered.SetY((BallConsidered_Coordy+BallConsidered_VelocityY +4*FinalBoard.GetDimensionY()) % 2*(FinalBoard.GetDimensionY()) -FinalBoard.GetDimensionY());
		// cout <<FinalBoard.GetBoardInformation()<<"\n";
		FinalBoard.SetVectorBalls(SetVectorBalls(Vector_Of_Balls);
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
	srand(time(NULL));
	const int NumberOfBalls = atoi(argv[1]);
	pthread_mutex_init(&UpdateLock,NULL);
	FinalBoard=Board(800,600,NumberOfBalls);
	// cout <<FinalBoard.Get
	pthread_t BallThreads [NumberOfBalls];
	pthread_t DisplayThread;
	cout <<"Starting\n";

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
