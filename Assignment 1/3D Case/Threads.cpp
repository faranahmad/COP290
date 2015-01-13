#include "Board.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include "Graphics.h"
#include "Image.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <fstream>

struct Graph {
	int x1;
	char **s1;
};

pthread_mutex_t UpdateLock;
Board FinalBoard;
bool PauseBoard;

GLuint _textureId;
 

namespace {
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes) {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes) {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input) {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array {
        private:
            T* array;
            mutable bool isReleased;
        public:
            explicit auto_array(T* array_ = NULL) :
                array(array_), isReleased(false) {
            }
            
            auto_array(const auto_array<T> &aarray) {
                array = aarray.array;
                isReleased = aarray.isReleased;
                aarray.isReleased = true;
            }
            
            ~auto_array() {
                if (!isReleased && array != NULL) {
                    delete[] array;
                }
            }
            
            T* get() const {
                return array;
            }
            
            T &operator*() const {
                return *array;
            }
            
            void operator=(const auto_array<T> &aarray) {
                if (!isReleased && array != NULL) {
                    delete[] array;
                }
                array = aarray.array;
                isReleased = aarray.isReleased;
                aarray.isReleased = true;
            }
            
            T* operator->() const {
                return array;
            }
            
            T* release() {
                isReleased = true;
                return array;
            }
            
            // void reset(T* array_ = NULL) {
            //     if (!isReleased && array != NULL) {
            //         delete[] array;
            //     }
            //     array = array_;
            // }
            
            T* operator+(int i) {
                return array + i;
            }
            
            T &operator[](int i) {
                return array[i];
            }
    };
}

Image* loadBMP(const char* filename) {
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    width = readInt(input);
    height = readInt(input);
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            for(int c = 0; c < 3; c++) {
                pixels2[3 * (width * y + x) + c] =
                    pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}

GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                 //Always GL_TEXTURE_2D
                 0,                             //0 for now
                 GL_RGB,                        //Format OpenGL uses for image
                 image->width, image->height,   //Width and height
                 0,                             //The border of the image
                 GL_RGB,                        //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,              //GL_UNSIGNED_BYTE, because pixels are stored
                                                //as unsigned numbers
                 image->pixels);                //The actual pixel data
    return textureId;                           //Returns the id of the texture
}


void initRendering() 
{
   	Image* image = loadBMP("Water-4.bmp");
  	_textureId = loadTexture(image);
    delete image;
}

void mouseclick(int button,int state,int x,int y )
{
    if(state== GLUT_UP )
    {
        int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
        int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
        float const window_aspect = (float)window_width / (float)window_height;
        // cout<<x<<'\t'<<y<<endl;
        float f1=window_width/1000.0;
        float f2=window_height/500.0;
        // cout<<(x>920*f1)<<"     "<<(x<998*f2)<<endl;
        if(x>920*f1 && x<998*f1 && y>435*f2 && y<498*f2)
        {
            PauseBoard=false;
            cout<<"Play Button"<<endl;
        }
        if(x>840*f1 && x<920*f1 && y>435*f2 && y<498*f2)
        {
            PauseBoard=true;
            cout<<"Pause Button"<<endl;
        }
        if(x>615*f1 && x<835*f1 && y>435*f2 && y<498*f2)
        {
            PauseBoard=true;
            Ball newBalltoAdd= Ball(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionY(),1);
            while (!CheckCorrect(FinalBoard.GetVectorBalls(), newBalltoAdd))
            {
                newBalltoAdd=Ball(FinalBoard.GetDimensionX(), FinalBoard.GetDimensionY(),1);
            }
            FinalBoard.AddBallToBoard(newBalltoAdd);
            PauseBoard=false;
            cout<<"Add Button"<<endl;
        }
        if(x>80*f1 && x<155*f1 && y>435*f2 && y<498*f2)
        {
            cout<<"SpeedUp Button"<<endl;
        }
        if(x>0*f1 && x<80*f1 && y>435*f2 && y<498*f2)
        {
            cout<<"SlowDown Button"<<endl;
        }
    
    }
    glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
            exit(0);
    }
}

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
    glOrtho(0-window_width, window_width,0- window_height,window_height,-200,200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat const light_pos[4]     = {float(FinalBoard.GetDimensionX()), float(0-FinalBoard.GetDimensionY()), 0    , 1.0  };
    GLfloat const light_color[4]   = { 0,  0,  1, 1.};
    GLfloat const light_ambient[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos),
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

    GLfloat const light_pos2[4]     = {float(0-FinalBoard.GetDimensionX()), float(0-FinalBoard.GetDimensionY()),  0  , 1.0  };
    GLfloat const light_color2[4]   = { 1,  0,  0, 1.};
    GLfloat const light_ambient2[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2),
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color2);

    GLfloat const light_pos3[4]     = {float(FinalBoard.GetDimensionX()),float(FinalBoard.GetDimensionY()),  0  , 1.0  };
    GLfloat const light_color3[4]   = { 0,  1,  0, 1.};
    GLfloat const light_ambient3[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos3),
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color3);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_color3);

    GLfloat const light_pos4[4]     = {float(0-FinalBoard.GetDimensionX()), float(FinalBoard.GetDimensionY()),  0  , 1.0  };
    GLfloat const light_color4[4]   = { 1,  1,  0, 1.};
    GLfloat const light_ambient4[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT3, GL_POSITION, light_pos4),
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color4);
    glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient4);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_color4);

    // GLfloat const light_pos5[4]     = {0,0, 300  , 1.0  };
    // GLfloat const light_color5[4]   = { 1,  1,  1, 1.};
    // GLfloat const light_ambient5[4] = { 0.10,  0.10,  0.30, 1.};
    // glLightfv(GL_LIGHT4, GL_POSITION, light_pos5),
    // glLightfv(GL_LIGHT4, GL_DIFFUSE, light_color5);
    // glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient5);
    // glLightfv(GL_LIGHT4, GL_SPECULAR, light_color5);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    // glEnable(GL_LIGHT2);
    // glEnable(GL_LIGHT3);
    // glEnable(GL_LIGHT4);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-window_width, window_height, 1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(window_width,window_height, 1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(window_width, -window_height, 1);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-window_width, -window_height, 1);
    
    glEnd();

    for( int i=0;i<FinalBoard.GetNumberBalls();i++ ) 
    {
        glPushMatrix();
        // cout<<FinalBoard.GetVectorBalls()[i].GetX()<<"  "<<FinalBoard.GetVectorBalls()[i].GetY()<<endl;
        glTranslatef(FinalBoard.GetBallFromId(i).GetX(), FinalBoard.GetBallFromId(i).GetY(), 0);
        glColor3f(FinalBoard.GetBallFromId(i).GetColor()[0],FinalBoard.GetBallFromId(i).GetColor()[1],FinalBoard.GetBallFromId(i).GetColor()[2]);
        GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
		GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
		GLfloat shininess[] = {50};
		// glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
		glMaterialfv(GL_FRONT, GL_SPECULAR, white);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
        glutSolidSphere(FinalBoard.GetBallFromId(i).GetRadius(), 31, 10);
        glPopMatrix();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int x, int y)
{
	int w=glutGet(GLUT_WINDOW_WIDTH);
    int h=glutGet(GLUT_WINDOW_HEIGHT);

    FinalBoard.SetDimensionX(w);
    FinalBoard.SetDimensionY(h);


    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0-w,w,0-h,h,-200,200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

int graphics(int argc,char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionY());
    glutCreateWindow("Team BabeMagnets");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseclick);
    glutKeyboardFunc(handleKeypress);
    initRendering();

    glutMainLoop();

    return 0;
}



// int counter=0

void *UpdateBoardThread(void* id)
{
	while (true)
	{
        if (!PauseBoard)
        {
    		pthread_mutex_lock (&UpdateLock);
    		long ballid = (long) id;
    		// cout <<"Starting for ball " <<ballid<<"\n";
    		
    		Ball BallConsidered = FinalBoard.GetBallFromId(ballid);
    
    		int BallConsidered_Coordx = BallConsidered.GetX(); 
    		int BallConsidered_Coordy = BallConsidered.GetY();
    		double BallConsidered_Radius = BallConsidered.GetRadius();
    		int BallConsidered_VelocityX=BallConsidered.GetVelocityX();
    		int BallConsidered_VelocityY=BallConsidered.GetVelocityY();
    		// BallConsidered.SetX(((BallConsidered_Coordx+BallConsidered_VelocityX)%(2*FinalBoard.GetDimensionX())) -FinalBoard.GetDimensionX());
    		if (BallConsidered_Coordx + BallConsidered_VelocityX + BallConsidered_Radius> FinalBoard.GetDimensionX())
    		{
    			BallConsidered.SetX(FinalBoard.GetDimensionX() -BallConsidered_Radius);
    			BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
    			BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());
    		}
    		else if (BallConsidered_Coordx+BallConsidered_VelocityX + FinalBoard.GetDimensionX() -BallConsidered_Radius<0)
    		{
    			BallConsidered.SetX(0-FinalBoard.GetDimensionX()+BallConsidered_Radius);
    			BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
    			BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());	
    		}
    		else
    		{
    			BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);
    		}
    
    		if (BallConsidered_Coordy+BallConsidered_VelocityY +BallConsidered_Radius> FinalBoard.GetDimensionY())
    		{
    			BallConsidered.SetY(FinalBoard.GetDimensionY()-BallConsidered_Radius);
    			BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);
    			BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());
    		}
    		else if (BallConsidered_Coordy+BallConsidered_VelocityY + FinalBoard.GetDimensionY() -BallConsidered_Radius <0)
    		{
    			BallConsidered.SetY(0-FinalBoard.GetDimensionY() + BallConsidered_Radius);
    			BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);	
    			BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());	
    		}
    		else
    		{
    			BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
    		}
    		
    
    
    
    		vector<Ball> Vector_Of_Balls = FinalBoard.GetVectorBalls();
    		double mass1 = BallConsidered.GetRadius()*BallConsidered.GetRadius()*BallConsidered.GetRadius();
    		// double mass1=1.0;
    		bool needforupdate=true;
    		// double uy1=0.0;
    		double ux1 =  BallConsidered.GetVelocityX();
    		double uy1 =  BallConsidered.GetVelocityY();
    		
    		for(int i=0;i<FinalBoard.GetNumberBalls();i++)
    		{
    			if (i != ballid)
    			{
    				// double dx = Vector_Of_Balls[i].GetX()+Vector_Of_Balls[i].GetVelocityX()-BallConsidered.GetX()-BallConsidered.GetVelocityX();
    				// double dy = Vector_Of_Balls[i].GetY()+Vector_Of_Balls[i].GetVelocityY()-BallConsidered.GetY()-BallConsidered.GetVelocityY();
    				ux1 =  BallConsidered.GetVelocityX();
    				uy1 =  BallConsidered.GetVelocityY();
    		
    				double dx = Vector_Of_Balls[i].GetX()-BallConsidered.GetX();
    				double dy = Vector_Of_Balls[i].GetY()-BallConsidered.GetY();
    				double distance = sqrt(dx*dx+dy*dy);
    				if(BallConsidered.GetRadius()+Vector_Of_Balls[i].GetRadius()>=distance)
    				{
    					needforupdate=false;
    					cout <<BallConsidered.GetRadius() <<"\t" <<Vector_Of_Balls[i].GetRadius()<<"\t"<<distance<<"\n";
    					double l=(BallConsidered.GetRadius()+Vector_Of_Balls[i].GetRadius() -distance)/2;
    
    					double costheta = (dx/distance);
    					double sintheta = (dy/distance);
    					
    					double mass2 = Vector_Of_Balls[i].GetRadius()*Vector_Of_Balls[i].GetRadius()*Vector_Of_Balls[i].GetRadius(); 
    					// double mass2=1.0;
    					double ux2 = Vector_Of_Balls[i].GetVelocityX();
    					double uy2 = Vector_Of_Balls[i].GetVelocityY();
    					// double uy2=0.0;
    
    					//Along tangent
    					double u3=uy1*costheta - ux1*sintheta;
    					double u4=uy2*costheta - ux2*sintheta;
    
    					// Along radial
    					double u1=ux1*costheta + uy1*sintheta;
    					double u2=ux2*costheta + uy2*sintheta;
    
    					//After collision radial
    					double v1=(mass1*u1 + 2*mass2*u2 - mass2*u1)/(mass1+mass2);
    					double v2=(mass2*u2 + 2*mass1*u1 - mass1*u2)/(mass1+mass2);
    
    
    					double vx1=v1*costheta - u3*sintheta;
    					double vx2=v2*costheta - u4*sintheta;
    
    					double vy1=u3*costheta + v1*sintheta;
    					double vy2=u4*costheta + v2*sintheta;
    
    					BallConsidered.SetX(BallConsidered.GetX() - l*costheta);
    					BallConsidered.SetY(BallConsidered.GetY() - l*sintheta);
    					
    
    					Vector_Of_Balls[i].SetX(Vector_Of_Balls[i].GetX() + l*costheta);
    					Vector_Of_Balls[i].SetY(Vector_Of_Balls[i].GetY() + l*sintheta);
    
    					BallConsidered.SetVelocity(vx1,vy1,0);
    					// BallConsidered.SetX(BallConsidered.GetX()+vx2*vx1/(vx2+vx1));
    					// BallConsidered.SetY(BallConsidered.GetY()+;
    					Vector_Of_Balls[i].SetVelocity(vx2,vy2,0);
    					// Vector_Of_Balls[i].SetX(Vector_Of_Balls[i].GetX()+vx2);
    					// Vector_Of_Balls[i].SetY(Vector_Of_Balls[i].GetY()+vy2);
    				}	
    			}
    		}
    		FinalBoard.SetVectorBalls(Vector_Of_Balls);
    
    		FinalBoard.SetBallFromId(ballid,BallConsidered);	
    		
    		// BallConsidered.SetY((BallConsidered_Coordy+BallConsidered_VelocityY)%FinalBoard.GetDimensionY());
    		// BallConsidered.SetX((BallConsidered_Coordx+BallConsidered_VelocityX +4*FinalBoard.GetDimensionX()) % 2*(FinalBoard.GetDimensionX()) -FinalBoard.GetDimensionX());
    		// BallConsidered.SetY((BallConsidered_Coordy+BallConsidered_VelocityY +4*FinalBoard.GetDimensionY()) % 2*(FinalBoard.GetDimensionY()) -FinalBoard.GetDimensionY());
    		// cout <<FinalBoard.GetBoardInformation()<<"\n";
    		pthread_mutex_unlock (&UpdateLock);	
    		usleep(50000);
    	}
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
    PauseBoard=false;

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
