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

pthread_mutex_t UpdateLock;
std::vector<pthread_t> BallThreads; //[NumberOfBalls];
Board FinalBoard;
std::vector<Ball> CollisionBalls;
std::vector<bool> TrackCollision;
int MaxCollRad=15;

bool PauseBoard;

int Ballid_From_Selection;
bool If_Ball_Selected;
// bool 


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
        // cout<<x<<'\t'<<y<<endl;
        // cout << window_width<<endl;
        // cout << window_height<<endl;
        float f1=window_width/1000.0;
        float f2=window_height/500.0;
        // cout<<(x>920*f1)<<"     "<<(x<998*f2)<<endl;
        if(x>453*f1 && x<501*f1 && y>462*f2 && y<499*f2)
        {
            PauseBoard=false;
            If_Ball_Selected=false;
            cout<<"Play Button"<<endl;
        }
        else if(x>505*f1 && x<552*f1 && y>462*f2 && y<499*f2)
        {
            PauseBoard=true;
            cout<<"Pause Button"<<endl;
        }
        else if(x>952*f1 && x<998*f1 && y>462*f2 && y<499*f2)
        {
            PauseBoard=true;
            Ball newBalltoAdd= Ball(FinalBoard.GetDimensionX(),FinalBoard.GetDimensionPosY(),FinalBoard.GetDimensionNegY(),1);
            while (!CheckCorrect(FinalBoard.GetVectorBalls(), newBalltoAdd))
            {
                newBalltoAdd=Ball(FinalBoard.GetDimensionX(), FinalBoard.GetDimensionPosY(),FinalBoard.GetDimensionNegY(),1);
            }
            pthread_t newthread;
            FinalBoard.AddBallToBoard(newBalltoAdd);
            pthread_create(&newthread,NULL,UpdateBoardThread,(void *) (FinalBoard.GetNumberBalls() -1));
            PauseBoard=false;
            cout<<"Add Button"<<endl;
        }
        else if(x>50*f1 && x<97*f1 && y>462*f2 && y<499*f2)
        {
            cout<<"SpeedUp Button"<<endl;
        }
        else if(x>0*f1 && x<47*f1 && y>462*f2 && y<499*f2)
        {
            cout<<"SlowDown Button"<<endl;
        }
        else if(x>901*f1 && x<950*f1 && y>462*f2 && y<499*f2)
        {
            // BallThreads.pop_back();
            cout<<"Remove Button  "<< BallThreads.size()<<endl;
        }
        if(PauseBoard==true)
        {
            //cout <<"i m here"<<endl;
            int no_of_balls=FinalBoard.GetNumberBalls();
            vector<Ball> vector_balls = FinalBoard.GetVectorBalls();
            double factor=1.5;
            for(int i=0;i<no_of_balls;i++)
            {
                //cout<<"reached here"<< endl;
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
                    cout << i << endl;
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
                    FinalBoard.SetBallFromId(Ballid_From_Selection,Ball_Selected);
                }
                else if(x>0*f1 && x<47*f1 && y>462*f2 && y<499*f2)       
                {
                    Ball Ball_Selected = vector_balls[Ballid_From_Selection];
                    Ball_Selected.SetVelocityX(Ball_Selected.GetVelocityX()/factor);
                    Ball_Selected.SetVelocityY(Ball_Selected.GetVelocityY()/factor);
                    FinalBoard.SetBallFromId(Ballid_From_Selection,Ball_Selected);    
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
    // cout<<"In display\n";
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

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);


    GLfloat const light_pos2[4]     = {float(0-FinalBoard.GetDimensionX()), float(0-FinalBoard.GetDimensionY()),  -200  , 1.0  };
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    // glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    GLfloat const light_pos3[4]     = {float(FinalBoard.GetDimensionX()),float(FinalBoard.GetDimensionY()),  -200  , 1.0  };
    GLfloat const light_color3[4]   = { 0,  1,  0, 1.};
    GLfloat const light_ambient3[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos3);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color);
    // glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
    // glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);

    GLfloat const light_pos4[4]     = {float(0-FinalBoard.GetDimensionX()), float(FinalBoard.GetDimensionY()),  -200  , 1.0  };
    GLfloat const light_color4[4]   = { 1,  1,  0, 1.};
    GLfloat const light_ambient4[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT3, GL_POSITION, light_pos4);
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
        // cout<<FinalBoard.GetVectorBalls()[i].GetX()<<"  "<<FinalBoard.GetVectorBalls()[i].GetY()<<endl;
        glTranslatef(FinalBoard.GetBallFromId(i).GetX(), FinalBoard.GetBallFromId(i).GetY(), 500);
        // glEnable(GL_COLOR_MATERIAL);
        glColor3f(FinalBoard.GetBallFromId(i).GetColor().GetR(),FinalBoard.GetBallFromId(i).GetColor().GetG(),FinalBoard.GetBallFromId(i).GetColor().GetB());
        // cout <<FinalBoard.GetBallFromId(i).GetColor().GetR()<<"\t"<<FinalBoard.GetBallFromId(i).GetColor().GetG()<<"\t"<<FinalBoard.GetBallFromId(i).GetColor().GetB()<<"\n";
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
    while (true)
    {
        if (!PauseBoard)
        {
            pthread_mutex_lock (&UpdateLock);
            long ballid = (long) id;
            // cout <<"Starting for ball " <<ballid<<"\n";
            
            Ball BallConsidered = FinalBoard.GetBallFromId(ballid);
    
            double BallConsidered_Coordx = BallConsidered.GetX(); 
            double BallConsidered_Coordy = BallConsidered.GetY();
            double BallConsidered_Radius = BallConsidered.GetRadius();
            double BallConsidered_VelocityX=BallConsidered.GetVelocityX();
            double BallConsidered_VelocityY=BallConsidered.GetVelocityY();
            // BallConsidered.SetX(((BallConsidered_Coordx+BallConsidered_VelocityX)%(2*FinalBoard.GetDimensionX())) -FinalBoard.GetDimensionX());
            if (BallConsidered_Coordx + BallConsidered_VelocityX + BallConsidered_Radius> FinalBoard.GetDimensionX())
            {
                BallConsidered.SetX(FinalBoard.GetDimensionX() -BallConsidered_Radius);
                BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
                BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());
                Is_Sound2=true;
            }
            else if (BallConsidered_Coordx+BallConsidered_VelocityX + FinalBoard.GetDimensionX() -BallConsidered_Radius<0)
            {
                BallConsidered.SetX(0-FinalBoard.GetDimensionX()+BallConsidered_Radius);
                BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
                BallConsidered.SetVelocityX(0-BallConsidered.GetVelocityX());
                Is_Sound2=true;   
            }
            else
            {
                BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);
            }
    
            if (BallConsidered_Coordy+BallConsidered_VelocityY +BallConsidered_Radius> FinalBoard.GetDimensionPosY())
            {
                BallConsidered.SetY(FinalBoard.GetDimensionPosY()-BallConsidered_Radius);
                BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);
                BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());
                Is_Sound2=true;
            }
            else if (BallConsidered_Coordy+BallConsidered_VelocityY + FinalBoard.GetDimensionNegY() -BallConsidered_Radius <0)
            {
                BallConsidered.SetY(0-FinalBoard.GetDimensionNegY() + BallConsidered_Radius);
                BallConsidered.SetX(BallConsidered_Coordx+BallConsidered_VelocityX);    
                BallConsidered.SetVelocityY(0-BallConsidered.GetVelocityY());   
                Is_Sound2=true;
            }
            else
            {
                BallConsidered.SetY(BallConsidered_Coordy+BallConsidered_VelocityY);
            }
            
    
    
    
            vector<Ball> Vector_Of_Balls = FinalBoard.GetVectorBalls();
            double mass1 = BallConsidered.GetRadius()*BallConsidered.GetRadius()*BallConsidered.GetRadius();
            
            bool needforupdate=true;
            
            double ux1 =  BallConsidered.GetVelocityX();
            double uy1 =  BallConsidered.GetVelocityY();
            
            for(int i=0;i<FinalBoard.GetNumberBalls();i++)
            {
                if (i != ballid)
                {
                    // double dx = glVertex3fector_Of_Balls[i].GetX()+Vector_Of_Balls[i].GetVelocityX()-BallConsidered.GetX()-BallConsidered.GetVelocityX();
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
                        double l=(BallConsidered.GetRadius()+Vector_Of_Balls[i].GetRadius() -distance);
    
                        double costheta = (dx/distance);
                        double sintheta = (dy/distance);
                        
                        double CollisionX=BallConsidered.GetX()+BallConsidered.GetRadius()*costheta;
                        double CollisionY=BallConsidered.GetY() +BallConsidered.GetRadius()*sintheta;
                        CollisionBalls.push_back(Ball(CollisionX,CollisionY));
                        TrackCollision.push_back(true);
                        Is_Sound1=true;
                        //pthread_cancel(newthread);
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
                        // cout <<l<<"\n";
                        // while (l>0)
                        // {
                        //     BallConsidered.SetX(BallConsidered.GetX() - ux1/sqrt(ux1*ux1 + uy1*uy1));
                        //     BallConsidered.SetY(BallConsidered.GetY() - uy1/sqrt(ux1*ux1 + uy1*uy1));
                        //     Vector_Of_Balls[i].SetX(Vector_Of_Balls[i].GetX() - (ux2)/sqrt(ux2*ux2 +uy2*uy2));
                        //     Vector_Of_Balls[i].SetY(Vector_Of_Balls[i].GetY() - (uy2)/sqrt(ux2*ux2 +uy2*uy2));
                            
                        //     dx = Vector_Of_Balls[i].GetX()-BallConsidered.GetX();
                        //     dy = Vector_Of_Balls[i].GetY()-BallConsidered.GetY();
                        //     distance = sqrt(dx*dx + dy*dy);
                            
                        //     l=(BallConsidered.GetRadius()+Vector_Of_Balls[i].GetRadius() -distance);
                        // }
                        // cout <<l<<"\n";

                        BallConsidered.SetX(BallConsidered.GetX() - l*costheta);
                        BallConsidered.SetY(BallConsidered.GetY() - l*sintheta);
                        
    
                        Vector_Of_Balls[i].SetX(Vector_Of_Balls[i].GetX() + l*costheta);
                        Vector_Of_Balls[i].SetY(Vector_Of_Balls[i].GetY() + l*sintheta);
    
                        BallConsidered.SetVelocity(vx1,vy1);
                        // BallConsidered.SetX(BallConsidered.GetX()+vx2*vx1/(vx2+vx1));
                        // BallConsidered.SetY(BallConsidered.GetY()+;
                        Vector_Of_Balls[i].SetVelocity(vx2,vy2);
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
    Is_Sound1=false;
    Is_Sound2=false;
    #ifdef DEBUG
        cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
    #else
        cout<<"#########################"<<endl;
    #endif
    srand(time(NULL));
    const int NumberOfBalls = atoi(argv[1]);
    BallThreads=std::vector<pthread_t> (NumberOfBalls);
    pthread_mutex_init(&UpdateLock,NULL);
    FinalBoard=Board(1000,300,300,NumberOfBalls);
    // cout <<FinalBoard.Get
    //pthread_t BallThreads [NumberOfBalls];
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
        // cout <<"Creating thread i: " <<i <<"\n";
        pthread_create(&BallThreads[i],NULL,UpdateBoardThread,(void *)i);
    
    }
    cout <<"out of for loop\n";

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
    // create a display thread 
    // run the threads 
    pthread_exit(NULL);
    return 0;
}
