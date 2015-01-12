#include <GL/glut.h>
#include <GL/gl.h>
#include <list>
// #include <windows.h>
#include <iostream>
#include <stdio.h>

#include <assert.h>
#include <fstream>

using namespace std;

GLuint _textureId;
class Image {
    public:
        Image(char* ps, int w, int h);
        ~Image();
        
        /* An array of the form (R1, G1, B1, R2, G2, B2, ...) indicating the
         * color of each pixel in image.  Color components range from 0 to 255.
         * The array starts the bottom-left pixel, then moves right to the end
         * of the row, then moves up to the next column, and so on.  This is the
         * format in which OpenGL likes images.
         */
        char* pixels;
        int width;
        int height;
};

//Reads a bitmap image from file.
Image* loadBMP(const char* filename);   
Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h) {
    
}

Image::~Image() {
    delete[] pixels;
}

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
            
            void reset(T* array_ = NULL) {
                if (!isReleased && array != NULL) {
                    delete[] array;
                }
                array = array_;
            }
            
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
    // switch(headerSize) {
    //     case 40:
    //         //V3
    //         width = readInt(input);
    //         height = readInt(input);
    //         input.ignore(2);
    //         assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
    //         assert(readShort(input) == 0 || !"Image is compressed");
    //         break;
    //     case 12:
    //         //OS/2 V1
    //         width = readShort(input);
    //         height = readShort(input);
    //         input.ignore(2);
    //         assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
    //         break;
    //     case 64:
    //         //OS/2 V2
    //         assert(!"Can't load OS/2 V2 bitmaps");
    //         break;
    //     case 108:
    //         //Windows V4
    //         assert(!"Can't load Windows V4 bitmaps");
    //         break;
    //     case 124:
    //         //Windows V5
    //         assert(!"Can't load Windows V5 bitmaps");
    //         break;
    //     default:
    //         assert(!"Unknown bitmap format");
    // }
    
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

int x=0;
int y=0;
    
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




    // if (y == 0 || x == 0) return;   
    // glMatrixMode(GL_PROJECTION);  
    // glLoadIdentity(); 
    // gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    // glMatrixMode(GL_MODELVIEW);
    // glViewport(0,0,x,y);  //Use the whole window for rendering
}



void handleKeypress(unsigned char key, int x, int y) {
    switch (key) {
        case 27: //Escape key
            exit(0);
    }
}

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
    glOrtho(0-window_width,window_width,0-window_height,window_height,-2000,2000);
    // if(window_aspect > 1.) {
        // glOrtho(-1200, 1200, -600, 600, -1200, 1200);
    // }
    // else {
    //     glOrtho(-1, 1, -1/window_aspect, 1/window_aspect, -1, 1);
    // }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat const light_pos[4]     = {1200, 0, 200   , 1.0  };
    GLfloat const light_color[4]   = { 0,  0,  1, 1.};
    GLfloat const light_ambient[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos),
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

        GLfloat const light_pos2[4]     = {-1200, 0, 200  , 1.0  };
    GLfloat const light_color2[4]   = { 1,  0,  0, 1.};
    GLfloat const light_ambient2[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos2),
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_color2);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_color2);

    GLfloat const light_pos3[4]     = {0, 0, 200 , 1.0  };
    GLfloat const light_color3[4]   = { 1,  1,  1, 1.};
    GLfloat const light_ambient3[4] = { 0.10,  0.10,  0.30, 1.};
    glLightfv(GL_LIGHT2, GL_POSITION, light_pos3),
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light_color3);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient3);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_color3);

    

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_LIGHT1);
    // glEnable(GL_LIGHT2);


    glEnable(GL_DEPTH_TEST);



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    
    //Bottom
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glColor3f(1.0f, 0.2f, 0.2f);
    // glBegin(GL_QUADS);
    
    // glNormal3f(0, 1.0f, 0.0f);
    // glTexCoord2f(0.0f, 0.0f);
    // glVertex3f(-250, -250, 250);
    // glTexCoord2f(1.0f, 0.0f);
    // glVertex3f(250, -250, 250);
    // glTexCoord2f(1.0f, 1.0f);
    // glVertex3f(250, -250, -250);
    // glTexCoord2f(0.0f, 1.0f);
    // glVertex3f(-250, -250, -250);
    
    // glEnd();
    
    //Back
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
    
    // //Left
    // glDisable(GL_TEXTURE_2D);
    // glColor3f(1.0f, 0.7f, 0.3f);
    // glBegin(GL_QUADS);
    
    // glNormal3f(1.0f, 0.0f, 0.0f);
    // glVertex3f(-2.5f, -2.5f, 2.5f);
    // glVertex3f(-2.5f, -2.5f, -2.5f);
    // glVertex3f(-2.5f, 2.5f, -2.5f);
    // glVertex3f(-2.5f, 2.5f, 2.5f);
    
    glEnd();

    glPushMatrix();
    glTranslatef(x/100, y/100, 1);
    // glColor3f(0.75, 0.5, 0); 
    // GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
    // GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
    // glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, cyan);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    // GLfloat shininess[] = {50};
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    // x+=1;
    // y+=1; 
    // glutSolidSphere(100, 100, 100);
        glPopMatrix();

//     glPushMatrix();
//         glTranslatef(300, 0, 0);
//         // x+=1;
//         // y+=1;
//         glColor3f(0.2,0.8,0.3);
//         glutSolidSphere(100, 31, 10);
//         glPopMatrix();
    // for(  ) 
    // {

    //     glPushMatrix();
    //     glTranslatef(sc->x, sc->y, 0);
    //     glutSolidSphere(0.1, 31, 10);
    //     glPopMatrix();
    // }

    glutSwapBuffers();

    // reshape(window_width,window_height);
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
GLuint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

void initRendering() {
    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_NORMALIZE);
    // glEnable(GL_COLOR_MATERIAL);
    
    Image* image = loadBMP("Water-4.bmp");
    _textureId = loadTexture(image);
    delete image;
}


int main(int argc,char *argv[] )
{
    x=atoi(argv[1]);
    y=atoi(argv[2]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1200,600);
    glutCreateWindow("Yo");
    
    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);

    glutReshapeFunc(reshape);
    initRendering();
    // glutMouseFunc(mouseclick);

    glutMainLoop();

    return 0;
}