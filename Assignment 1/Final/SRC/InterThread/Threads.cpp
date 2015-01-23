#include "Board.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include "Image.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <fstream>  
#include <queue>
#include "Message.h"

struct Graph {
    int x1;
    char **s1;
};

pthread_mutex_t UpdateLock;
std::vector<pthread_t> BallThreads; //[NumberOfBalls];
Board FinalBoard;

bool PauseBoard;
int Ballid_From_Selection;
bool If_Ball_Selected;

int NumberOfBalls;
std::vector<queue<Message>> MessageVector;
std::vector<bool> BallInBoard;
// bool
bool Is_Sound1;
bool Is_Sound2;

void *sound_play1(void *x)
{
    while (true)
    {
        if (Is_Sound1)
        {
            //pthread_mutex_lock (&mutexsum);
            system("canberra-gtk-play -f sound1.wav");
            //pthread_mutex_unlock (&mutexsum);       
            Is_Sound1=false;
        }
    }
     
}

void *sound_play2(void *x)
{
    while (true)
    {
        if (Is_Sound2)
        {
            //pthread_mutex_lock (&mutexsum);
            system("canberra-gtk-play -f sound2.wav");
            //pthread_mutex_unlock (&mutexsum);       
            Is_Sound2=false;
        }
    }
     
}

std::vector<Ball> CollisionBalls;
std::vector<bool> TrackCollision;
int MaxCollRad=15;

void *UpdateBoardThread(void*);


GLuint _textureId;
 
void *UpdateBoardThread(void *);

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
        #ifdef DEBUG
            cout<<x<<'\t'<<y<<endl;
            cout << window_width<<"\t"<<window_height<<endl;
        #endif
        float f1=window_width/1000.0;
        float f2=window_height/500.0;
        if(x>453*f1 && x<501*f1 && y>462*f2 && y<499*f2)
        {
            PauseBoard=false;
            If_Ball_Selected=false;
            #ifdef DEBUG
                cout<<"Play Button"<<endl;
            #endif
        }
        else if(x>505*f1 && x<552*f1 && y>462*f2 && y<499*f2)
        {
            PauseBoard=true;
            #ifdef DEBUG
                cout<<"Pause Button"<<endl;
            #endif
        }
        else if(x>952*f1 && x<998*f1 && y>462*f2 && y<499*f2)
        {
            PauseBoard=true;
            NumberOfBalls+=1;
            Ball newBalltoAdd= Ball(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionPosY(),FinalBoard.GetDimensionNegY(),1);
            while (!CheckCorrect(FinalBoard.GetVectorBalls(), newBalltoAdd))
            {
                newBalltoAdd=Ball(FinalBoard.GetDimensionX(), FinalBoard.GetDimensionPosY(),FinalBoard.GetDimensionNegY(),1);
            }
            pthread_t newthread;
            BallThreads.push_back(newthread);
            FinalBoard.AddBallToBoard(newBalltoAdd);
            queue<Message> newqueue;
            MessageVector.push_back(newqueue);
            for (int k=0; k<FinalBoard.GetNumberBalls() ; k++)
            {
                MessageVector[k].push(Message(newBalltoAdd,0,FinalBoard.GetNumberBalls()-1));
            }
            BallInBoard.push_back(true);
            pthread_create(&newthread,NULL,UpdateBoardThread,(void *) ((long) (FinalBoard.GetNumberBalls() -1)));
            PauseBoard=false;
            #ifdef DEBUG
                cout<<"Add Button"<<endl;
            #endif
        }
        else if(x>50*f1 && x<97*f1 && y>462*f2 && y<499*f2)
        {
            #ifdef DEBUG
                cout<<"SpeedUp Button"<<endl;
            #endif
        }
        else if(x>0*f1 && x<47*f1 && y>462*f2 && y<499*f2)
        {
            #ifdef DEBUG
                cout<<"SlowDown Button"<<endl;
            #endif
        }
        else if(x>901*f1 && x<950*f1 && y>462*f2 && y<499*f2)
        {
            #ifdef DEBUG
                cout <<"In remove  button\n";
            #endif
            if (If_Ball_Selected)
            {
                #ifdef DEBUG
                    cout <<"id: "<<Ballid_From_Selection<<"\n";
                #endif
                BallInBoard[Ballid_From_Selection]=false;
                #ifdef DEBUG
                    cout <<"id: "<<Ballid_From_Selection<<"\n";
                #endif
                Ball ballcons=FinalBoard.GetBallFromId(Ballid_From_Selection);
                #ifdef DEBUG
                    cout <<"id: "<<Ballid_From_Selection<<"\n";
                #endif
                ballcons.SetRadius(0.0);

                for (int k=0;k<NumberOfBalls;k++)
                {
                    #ifdef DEBUG
                        cout <<"push for message" <<k<<"\n";
                    #endif
                    MessageVector[k].push(Message(ballcons,1,Ballid_From_Selection));
                }
                FinalBoard.SetBallFromId(Ballid_From_Selection,ballcons);
            }
            glutPostRedisplay();
            // BallThreads.pop_back()
            #ifdef DEBUG
                cout<<"Remove Button  "<< BallThreads.size()<<endl;
            #endif
        }
        if(PauseBoard==true)
        {
            #ifdef DEBUG
                cout <<"i m here"<<endl;
            #endif
            int no_of_balls=FinalBoard.GetNumberBalls();
            vector<Ball> vector_balls = FinalBoard.GetVectorBalls();
            double factor=1.5;
            for(int i=0;i<no_of_balls;i++)
            {
                #ifdef DEBUG
                    cout<<"reached here"<< endl;
                #endif
                double width_of_window = (2*(1/0.949)*FinalBoard.GetDimensionX()/4.0);
                double height_of_window = ((1/0.940)*FinalBoard.GetDimensionPosY()+(1/0.780)*FinalBoard.GetDimensionNegY())/4.0;
                double x_modified = x - width_of_window;
                double y_modified = height_of_window - y;
                double coordi_x=vector_balls[i].GetX()/2;
                double coordi_y=vector_balls[i].GetY()/2;
                if(sqrt(double((coordi_x-x_modified)*(coordi_x-x_modified)+(coordi_y-y_modified)*(coordi_y-y_modified)))<=vector_balls[i].GetRadius()/2.0)
                {
                    If_Ball_Selected = true;
                    Ballid_From_Selection=i;
                    #ifdef DEBUG
                        cout << i << endl;
                    #endif
                    break;
                }                    
            }
            if(If_Ball_Selected==true)
            {
                if(x>50*f1 && x<97*f1 && y>462*f2 && y<499*f2)
                {
                    Ball Ball_Selected = vector_balls[Ballid_From_Selection];
                    Ball_Selected.SetVelocityX(factor*Ball_Selected.GetVelocityX());
                    Ball_Selected.SetVelocityY(factor*Ball_Selected.GetVelocityY());
                    for (int k=0;k<NumberOfBalls;k++)
                    {
                    #ifdef DEBUG
                        cout <<"push for message" <<k<<"\n";
                    #endif
                    MessageVector[k].push(Message(Ball_Selected,1,Ballid_From_Selection));
                    }
                    // FinalBoard.SetBallFromId(Ballid_From_Selection,Ball_Selected);
                }
                else if(x>0*f1 && x<47*f1 && y>462*f2 && y<499*f2)       
                {
                    Ball Ball_Selected = vector_balls[Ballid_From_Selection];
                    Ball_Selected.SetVelocityX(Ball_Selected.GetVelocityX()/factor);
                    Ball_Selected.SetVelocityY(Ball_Selected.GetVelocityY()/factor);
                    for (int k=0;k<NumberOfBalls;k++)
                    {
                    #ifdef DEBUG
                        cout <<"push for message" <<k<<"\n";
                    #endif
                    MessageVector[k].push(Message(Ball_Selected,1,Ballid_From_Selection));
                    }
                    // FinalBoard.SetBallFromId(Ballid_From_Selection,Ball_Selected);    
                }  
            }
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
    #ifdef DEBUG
        cout<<"In display\n";
    #endif
    int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
    int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
    float const window_aspect = (float)window_width / (float)window_height;

    glClearColor(0.5, 0.5, 1.0, 1.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_COLOR_MATERIAL);

    // glDisable(GL_COLOR_MATERIAL);
    // glEnable(GL_NORMALIZE);
    glViewport(0, 0, window_width, window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0-window_width, window_width,0- window_height,window_height,-2000,2000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat const light_pos[4]     = {0, 0, 1000    , 1.0  };
    GLfloat const light_color[4]   = { 1,  1,  1, 1.};
    GLfloat const light_ambient[4] = { 0.,  0., 0., 1.};
    GLfloat const light_specular[4] = { 1,  1, 1, 1};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos),
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    GLfloat const light_pos2[4]     = {float(0-FinalBoard.GetDimensionX()), float(0-FinalBoard.GetDimensionY()),  -200  , 1.0  };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2),
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    // glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    GLfloat const light_pos3[4]     = {float(FinalBoard.GetDimensionX()),float(FinalBoard.GetDimensionY()),  -200  , 1.0  };
    GLfloat const light_color3[4]   = { 0,  1,  0, 1.};
    GLfloat const light_ambient3[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos3),
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    // glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

    GLfloat const light_pos4[4]     = {float(0-FinalBoard.GetDimensionX()), float(FinalBoard.GetDimensionY()),  -200  , 1.0  };
    GLfloat const light_color4[4]   = { 1,  1,  0, 1.};
    GLfloat const light_ambient4[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT3, GL_POSITION, light_pos4),
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient4);
    // glLightfv(GL_LIGHT3, GL_SPECULAR, light_color4);

    // GLfloat const light_pos5[4]     = {0,0, 300  , 1.0  };
    // GLfloat const light_color5[4]   = { 1,  1,  1, 1.};
    // GLfloat const light_ambient5[4] = { 0.10,  0.10,  0.30, 1.};
    // glLightfv(GL_LIGHT4, GL_POSITION, light_pos5),
    // glLightfv(GL_LIGHT4, GL_DIFFUSE, light_color5);
    // glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient5);
    // glLightfv(GL_LIGHT4, GL_SPECULAR, light_color5);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
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
    glVertex3f(-window_width, window_height, -1000);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(window_width,window_height, -1000);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(window_width, -window_height, -1000);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-window_width, -window_height, -1000);
    
    glEnd();


    glDisable(GL_TEXTURE_2D);
    for( int i=0;i<FinalBoard.GetNumberBalls();i++ ) 
    {
        glPushMatrix();
        #ifdef DEBUG
            cout<<FinalBoard.GetVectorBalls()[i].GetX()<<"  "<<FinalBoard.GetVectorBalls()[i].GetY()<<endl;
        #endif
        glTranslatef(FinalBoard.GetBallFromId(i).GetX(), FinalBoard.GetBallFromId(i).GetY(), 500);
        // glEnable(GL_COLOR_MATERIAL);
        glColor3f(FinalBoard.GetBallFromId(i).GetColor().GetR(),FinalBoard.GetBallFromId(i).GetColor().GetG(),FinalBoard.GetBallFromId(i).GetColor().GetB());
        #ifdef DEBUG
            cout <<FinalBoard.GetBallFromId(i).GetColor().GetR()<<"\t"<<FinalBoard.GetBallFromId(i).GetColor().GetG()<<"\t"<<FinalBoard.GetBallFromId(i).GetColor().GetB()<<"\n";
        #endif
        // glColor3f(0.9,0.5,0.5);


        GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
        GLfloat ambient[] = {0.7f,0.7f,0.7f,1.0f};
        GLfloat cyan[] = {0.8,0.8,0.8,1};
        GLfloat shininess[] = {100};

        glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glutSolidSphere(FinalBoard.GetBallFromId(i).GetRadius(), 31, 10);
        glPopMatrix();
    }
     glDisable(GL_LIGHTING);
    for(int i=0;i<CollisionBalls.size();i++)
    {
        if(CollisionBalls[i].GetRadius()<=0)
        {
            CollisionBalls.erase(CollisionBalls.begin()+i);
            TrackCollision.erase(TrackCollision.begin()+i);
        }
        if(TrackCollision[i] && CollisionBalls[i].GetRadius()<MaxCollRad)
        {
            CollisionBalls[i].SetRadius(CollisionBalls[i].GetRadius()+1);
        }
        else
        {
           if(CollisionBalls[i].GetRadius()>=MaxCollRad)
           {
            TrackCollision[i]=false;
           }
           CollisionBalls[i].SetRadius(CollisionBalls[i].GetRadius()-1);
        }
    }


    for( int i=0;i<CollisionBalls.size();i++ ) 
    {
        glPushMatrix();
        glTranslatef(CollisionBalls[i].GetX(), CollisionBalls[i].GetY(), 1000);
        glColor3f(CollisionBalls[i].GetColor().GetR(),CollisionBalls[i].GetColor().GetG(),CollisionBalls[i].GetColor().GetB());
     
        GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
        GLfloat ambient[] = {1,1,1,1};
        GLfloat cyan[] = {1,1,1,1};
        GLfloat shininess[] = {100000};

        glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);   
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

        glutSolidSphere(CollisionBalls[i].GetRadius(), 31, 10);
        glPopMatrix();
    }
    glutSwapBuffers();
    glutPostRedisplay();
}

void reshape(int x, int y)
{
    int w=glutGet(GLUT_WINDOW_WIDTH);
    int h=glutGet(GLUT_WINDOW_HEIGHT);

    FinalBoard.SetDimensionX(0.949*w);
    FinalBoard.SetDimensionY(h);
    FinalBoard.SetDimensionPosY(0.940*h);
    FinalBoard.SetDimensionNegY(0.780*h);


    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0-w,w,0-h,h,-2000,2000);

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
    vector<Ball> VectorBallsConsidered (NumberOfBalls);
    long ballid = (long) id;
    Ball BallConsidered = FinalBoard.GetBallFromId(ballid);
    double BallConsidered_Coordx = BallConsidered.GetX(); 
    double BallConsidered_Coordy = BallConsidered.GetY();
    double BallConsidered_Radius = BallConsidered.GetRadius();
    double BallConsidered_VelocityX=BallConsidered.GetVelocityX();
    double BallConsidered_VelocityY=BallConsidered.GetVelocityY();
    VectorBallsConsidered=FinalBoard.GetVectorBalls();
    while (true)
    {
        if (!PauseBoard)
        {
            #ifdef DEBUG
                cout <<ballid<<endl;
            #endif
            pthread_mutex_lock (&UpdateLock);
            BallConsidered_Coordx = BallConsidered.GetX(); 
            BallConsidered_Coordy = BallConsidered.GetY();
            BallConsidered_Radius = BallConsidered.GetRadius();
            BallConsidered_VelocityX=BallConsidered.GetVelocityX();
            BallConsidered_VelocityY=BallConsidered.GetVelocityY();
            
            while (!MessageVector[ballid].empty())
            {
                Message current=MessageVector[ballid].front();
                MessageVector[ballid].pop();
                while (current.GetId()>=VectorBallsConsidered.size())
                {
                    VectorBallsConsidered.push_back(Ball());   
                }
                // if ((current.GetId()==ballid)  && (current.GetType()==1))
                // {
                //     break;    
                // }
                VectorBallsConsidered[current.GetId()]=current.GetBall();
            }
            BallConsidered=VectorBallsConsidered[ballid];
            BallConsidered_Coordx = BallConsidered.GetX(); 
            BallConsidered_Coordy = BallConsidered.GetY();
            BallConsidered_Radius = BallConsidered.GetRadius();
            BallConsidered_VelocityX=BallConsidered.GetVelocityX();
            BallConsidered_VelocityY=BallConsidered.GetVelocityY();
            

            if (BallConsidered_Coordx + BallConsidered_VelocityX + BallConsidered_Radius> FinalBoard.GetDimensionX())
            {
                BallConsidered.SetX(FinalBoard.GetDimensionX() -BallConsidered_Radius);
                BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());
                if (BallInBoard[ballid])
                    Is_Sound2=true;
            }
            else if (BallConsidered_Coordx+BallConsidered_VelocityX + FinalBoard.GetDimensionX() -BallConsidered_Radius<0)
            {
                BallConsidered.SetX(0-FinalBoard.GetDimensionX()+BallConsidered_Radius);
                BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());
                if (BallInBoard[ballid])
                    Is_Sound2=true;
   
            }
            else
            {
                BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);
            }
    
            if (BallConsidered_Coordy+BallConsidered_VelocityY +BallConsidered_Radius> FinalBoard.GetDimensionPosY())
            {
                BallConsidered.SetY(FinalBoard.GetDimensionPosY()-BallConsidered_Radius);
                BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());
                if (BallInBoard[ballid])
                    Is_Sound2=true;

            }
            else if (BallConsidered_Coordy+BallConsidered_VelocityY + FinalBoard.GetDimensionNegY() -BallConsidered_Radius <0)
            {
                BallConsidered.SetY(0-FinalBoard.GetDimensionNegY() + BallConsidered_Radius);
                BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY()); 
                if (BallInBoard[ballid])
                    Is_Sound2=true;
  
            }
            else
            {
                BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
            }

            VectorBallsConsidered[ballid]=BallConsidered;


            double mass1 = BallConsidered.GetRadius()*BallConsidered.GetRadius()*BallConsidered.GetRadius();
            double ux1,uy1,uz1; 

            for(int i=0;i<VectorBallsConsidered.size();i++)
            {
                if ((i != ballid) && (BallInBoard[i]) && (BallInBoard[ballid]))
                {
                    ux1 =  BallConsidered.GetVelocityX();
                    uy1 =  BallConsidered.GetVelocityY();

                    double dx = VectorBallsConsidered[i].GetX()-BallConsidered.GetX();
                    double dy = VectorBallsConsidered[i].GetY()-BallConsidered.GetY();
                    
                    double distance = sqrt(dx*dx + dy*dy);

                    if(BallConsidered.GetRadius()+VectorBallsConsidered[i].GetRadius()>=distance)
                    {
                        double l=(BallConsidered.GetRadius()+VectorBallsConsidered[i].GetRadius() -distance);
    
                        double mass2 = VectorBallsConsidered[i].GetRadius()*VectorBallsConsidered[i].GetRadius()*VectorBallsConsidered[i].GetRadius(); 
                        
                        double ux2 = VectorBallsConsidered[i].GetVelocityX();
                        double uy2 = VectorBallsConsidered[i].GetVelocityY();

                        // Along radial
                        double u1=(ux1*dx + uy1*dy)/distance;
                        double u2=(ux2*dx + uy2*dy)/distance;
                        
                        //After collision radial
                        double v1=(mass1*u1 + 2*mass2*u2 - mass2*u1)/(mass1+mass2);
                        double v2=(mass2*u2 + 2*mass1*u1 - mass1*u2)/(mass1+mass2);
                        
                        //Along XYZ unchanged (tangential)
                        double vx1=ux1 + ((v1-u1) *dx)/distance;
                        double vy1=uy1 + ((v1-u1) *dy)/distance;
                        double vx2=ux2 + ((v2-u2) *dx)/distance;
                        double vy2=uy2 + ((v2-u2) *dy)/distance;

                        BallConsidered.SetX(BallConsidered.GetX() - (l*dx)/distance);
                        BallConsidered.SetY(BallConsidered.GetY() - (l*dy)/distance);
                           
                        VectorBallsConsidered[i].SetX(VectorBallsConsidered[i].GetX() + (l*dx)/distance);
                        VectorBallsConsidered[i].SetY(VectorBallsConsidered[i].GetY() + (l*dy)/distance);
                       
                        BallConsidered.SetVelocity(vx1,vy1);
                        VectorBallsConsidered[i].SetVelocity(vx2,vy2);

                        double costheta = (dx/distance);
                        double sintheta = (dy/distance);
                        double CollisionX=BallConsidered.GetX()+BallConsidered.GetRadius()*costheta;
                        double CollisionY=BallConsidered.GetY() +BallConsidered.GetRadius()*sintheta;
                        CollisionBalls.push_back(Ball(CollisionX,CollisionY));
                        TrackCollision.push_back(true);
                        Is_Sound1=true;

                        for (int k=0;k<NumberOfBalls;k++)
                        {
                            MessageVector[k].push(Message(VectorBallsConsidered[i],0,i));
                        }
                    }   
                }
            }

            for (int k=0;k<NumberOfBalls;k++)
            {
                MessageVector[k].push(Message(BallConsidered,0,ballid));
            }

            pthread_mutex_unlock (&UpdateLock);
            if (ballid==0)
            {
                FinalBoard.SetVectorBalls(VectorBallsConsidered);
            }
            usleep(30000);
        }
    }
}   

void *DisplayUpdate(void* id)
{
    Graph  *pa= (Graph *)id;
    graphics(pa->x1,pa->s1);
    // usleep(10000);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    NumberOfBalls = atoi(argv[1]);
    BallThreads=std::vector<pthread_t> (NumberOfBalls);
    for (int k=0;k<NumberOfBalls;k++)
    {
        BallInBoard.push_back(true);
    }
    pthread_mutex_init(&UpdateLock,NULL);
    FinalBoard=Board(1000,300,300,NumberOfBalls);
    MessageVector=std::vector<queue<Message>> (NumberOfBalls);
    //pthread_t BallThreads [NumberOfBalls];
    pthread_t DisplayThread;
    PauseBoard=false;
    #ifdef DEBUG
        cout<<FinalBoard.GetBoardInformation()<<"\n";
    #endif
    Graph graphics1;
    graphics1.x1=argc;
    graphics1.s1=argv;
    #ifdef DEBUG
        std::cout <<"Ball threas" <<NumberOfBalls <<"\n";
    #endif
    for (long i=0; i<NumberOfBalls ;i++)
    {
        pthread_create(&BallThreads[i],NULL,UpdateBoardThread,(void *)i);
    
    }
    

    pthread_t soundthread1;
    pthread_t soundthread2;
    pthread_create(&soundthread1,NULL,sound_play1,NULL);
    pthread_create(&soundthread2,NULL,sound_play2,NULL);
    pthread_create(&DisplayThread,NULL,DisplayUpdate,&graphics1);
    

    for (int i=0; i<NumberOfBalls ;i++)
    {
        pthread_join(BallThreads[i],NULL);
    }


    pthread_join(DisplayThread,NULL);

    pthread_join(soundthread1,NULL);
    pthread_join(soundthread2,NULL);
    pthread_exit(NULL);
    return 0;
}
