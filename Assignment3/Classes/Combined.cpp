#include "Combined.h"


GLuint _textureId;


void *sound_play1(void *x)
{
	std::cout <<"in sound play explosion\n";
	while (true)
	{
		if (Is_SoundExpl)
		{
			std::cout <<"playing found for missile\n";
			system("canberra-gtk-play -f explosion1.wav");
			Is_SoundExpl=false;
		}
	}
}

void *sound_play2(void *x)
{
	std::cout <<" In sound play bullet\n";
	while (true)
	{
		if (Is_SoundBullet)
		{
			std::cout << "playing sound for bullet\n";
			system("canberra-gtk-play -f bullet1.wav");
			Is_SoundBullet=false;
		}
	}
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
    int readInt(std::ifstream &input) {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(std::ifstream &input) {
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
    // Loads an image from a file location
    std::ifstream input;
    input.open(filename, std::ifstream::binary);
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
    input.seekg(dataOffset, std::ios_base::beg);
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
    // Loads texture from image
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
    // Initialises the rendering of all textures
    Image* image = loadBMP("bottom.bmp");
    _textureId = loadTexture(image);
    delete image;
}

std::vector<Faces> loadOBJ(char * path)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Faces> answer;
	std::vector<Points> temp_vertices;
	// std::vector<glm::vec2> temp_uvs;Missile
	// std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return answer;
	}
	// std::cout <<"Starting work\n";
	while( 1 )
	{
		// std::cout << "Here\n";
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			// std::cout <<"In v case\n";
			Points vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);

		}
		else if ( strcmp( lineHeader, "vt" ) == 0 )
		{
			// glm::vec2 uv;
			// fscanf(file, "%f %f\n", &uv.x, &uv.y );
			// uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			// temp_uvs.push_back(uv);
		}
		else if ( strcmp( lineHeader, "vn" ) == 0 )
		{
			// glm::vec3 normal;
			// fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			// temp_normals.push_back(normal);
		}
		else if ( strcmp( lineHeader, "f" ) == 0 )
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			unsigned int garbage[3];
			// int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			// int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &garbage[0], &normalIndex[0], &vertexIndex[1],&garbage[1], &normalIndex[1], &vertexIndex[2],&garbage[2], &normalIndex[2] );
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
			// if (matches != 9)
			if (matches != 6)
			{
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return answer;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			Faces NewF;
			// std::cout << vertexIndex[0] <<"\t"<< vertexIndex[1] <<"\t"<< vertexIndex[2] <<"\n";
			NewF.p1 = temp_vertices[vertexIndex[0]-1];
			NewF.p2 = temp_vertices[vertexIndex[1]-1];
			NewF.p3 = temp_vertices[vertexIndex[2]-1];
			answer.push_back(NewF);
			// uvIndices    .push_back(uvIndex[0]);
			// uvIndices    .push_back(uvIndex[1]);
			// uvIndices    .push_back(uvIndex[2]);
			// normalIndices.push_back(normalIndex[0]);
			// normalIndices.push_back(normalIndex[1]);
			// normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	return answer;
}

void ProcessKeys()
{
	if (newg.IsActive)
	{
		if (Keys[0])
		{
			// Move right
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,1);
		}
		if (Keys[1])
		{
			// Move left
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,0);
		}
		if (Keys[2])
		{
			// Move up
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,2);
		}
		if (Keys[3])
		{
			// Move down
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,3);
		}
		if (Keys[4])
		{
			// Rotate d
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,5);
		}
		if (Keys[5])
		{
			// Rotate a
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,4);
		}
		if (Keys[6])
		{
			// Fire Bullet
			// TODO: Incorporate multiple bullets
			// if (clock()-newg.LastBulletTime>75000)
			// {
			// 	newg.LastBulletTime=clock();
			// std::cout << SpaceBarFree <<"  number of times spacebar pressed\n";
			if (presentf-newg.LastBulletTime>5)
			{
				newg.LastBulletTime=presentf;
				Bullet newb = Bullet();
				Ship present = newg.PlayerBoard.GetNthShip(newg.PlayerId);
				float velx = 0- 10*sin(PI*present.GetAngle()/180);
				float vely = 10* cos(PI*present.GetAngle()/180);
				newb.SetXPos(present.GetXPos());
				newb.SetYPos(present.GetYPos());
				newb.SetVelX(velx);
				newb.SetVelY(vely);
				newb.SetShipID(newg.PlayerId);
				newb.SetTypeAI(false);
				newb.SetTypePlayer(true);
				newg.PlayerBoard.InsertBullet(newb);
				BulletsToAdd.push(newb);
				Is_SoundBullet=true;
				SpaceBarFree+=1;
			}
			// }
		}
		if (Keys[7])
		{
			// Fire Missile
			Bullet newb = Bullet();
			Ship present = newg.PlayerBoard.GetNthShip(newg.PlayerId);
			if (present.GetNumberMissiles()>0)
			{
				present.ReduceMissile();
	
				float velx = -10* sin(PI*present.GetAngle()/180);
				float vely = 10* cos(PI*present.GetAngle()/180);
	
				newb.SetTypeAI(true);
				newb.SetXPos(present.GetXPos());
				newb.SetYPos(present.GetYPos());
				newb.SetVelX(velx);
				newb.SetVelY(vely);
				newb.SetShipID(newg.PlayerId);
				newb.SetTypePlayer(true);
				newg.PlayerBoard.SetNthShip(newg.PlayerId,present);
				newg.PlayerBoard.InsertBullet(newb);
				BulletsToAdd.push(newb);
			}
		}
		if (Keys[8])
		{
			// Add random alien
			newg.PlayerBoard.AddRandomAlien();
		}
	}
}


void specialKeys( int key, int x, int y )
{
	if (key == GLUT_KEY_RIGHT)
	{
		Keys[0]=true;
		// Move the player ship to the right
		// rotate_x +=2;
	}
	if (key == GLUT_KEY_LEFT)
	{
		Keys[1]=true;
		// Move player ship to left
		// rotate_y +=2;
	}
	if (key == GLUT_KEY_UP)
	{
		Keys[2]=true;
		// Move player ship up
	}
	if (key == GLUT_KEY_DOWN)
	{
		Keys[3]=true;
		// Move player ship down
	}
	ProcessKeys();
	// std::cout << rotate_x <<"\t"<<rotate_y<<"\n";
	// glutPostRedisplay();
}


void specialKeysUp( int key, int x, int y )
{
	if (key == GLUT_KEY_RIGHT)
	{
		Keys[0]=false;
		// Move the player ship to the right
		// rotate_x +=2;
		// newg.PlayerBoard.MoveNthShip(newg.PlayerId,1);
	}
	if (key == GLUT_KEY_LEFT)
	{
		Keys[1]=false;
		// Move player ship to left
		// rotate_y +=2;
		// newg.PlayerBoard.MoveNthShip(newg.PlayerId,0);
	}
	if (key == GLUT_KEY_UP)
	{

		Keys[2]=false;
		// newg.PlayerBoard.MoveNthShip(newg.PlayerId,2);
		// Move player ship up
	}
	if (key == GLUT_KEY_DOWN)
	{
		Keys[3]=false;
		// std::cout << "down key left\n";
		// newg.PlayerBoard.MoveNthShip(newg.PlayerId,3);
		// Move player ship down
	}
	ProcessKeys();
	// std::cout << rotate_x <<"\t"<<rotate_y<<"\n";
	// glutPostRedisplay();
}


void handleKeypress(unsigned char key, int x, int y)
{
	// std::cout << key << "\n";
	switch (key)
	{
		case 'a':
		{
			// std::cout <<"a was pressed\n";
			Keys[4]=true;
			// glutPostRedisplay();
			// Rotate the ship to the left
			break;
		}
		case 'd':
		{
			// std::cout <<"d was pressed\n";
			Keys[5]=true;
			// newg.PlayerBoard.MoveNthShip(newg.PlayerId,5);
    		// glutPostRedisplay();
			// Rotate the ship to the right
			break;
		}
		case 'f':
		{
			// std::cout << "f was pressed\n";
			newg.PlayerBoard.AddRandomShip();
			// glutPostRedisplay();
			break;
		}

		case 32: //SpaceBar
		{
			// Fire bullet
			// TODO: incorporate multiplier
			Keys[6]=true;
			SpaceBarFree+=1;
			// std::cout << "space bar presed\n";

			break;
		}

		case 's':
		{
			// Fire Missile
			// std::cout << "space bar presed\n";
			Keys[7]=true;
			break;
		}
		case 'y':
		{
			Keys[8]=true;
			break;
		}
		case 43: //+ key
		{
			break;
		}
		case 'o':
		{
			GameActive=true;
			break;
		}
		case 27: //Escape key
		{
			exit(0);
		}
    }
    ProcessKeys();
}

void handleKeypressUp(unsigned char key, int x, int y)
{
	// std::cout << key << "\n";
	switch (key)
	{
		case 'a':
		{
			Keys[4]=false;
			// std::cout << " a lifted\n";
			// std::cout <<"a was pressed\n";
			// newg.PlayerBoard.MoveNthShip(newg.PlayerId,4);
			// glutPostRedisplay();
			// Rotate the ship to the left
			break;
		}
		case 'd':
		{
			Keys[5]=false;
			// std::cout <<"d was pressed\n";
			// newg.PlayerBoard.MoveNthShip(newg.PlayerId,5);
   			//glutPostRedisplay();
			// Rotate the ship to the right
			break;
		}
		case 32:
		{
			SpaceBarFree=0;
			// std::cout <<" In spacebar up case\n";
			Keys[6]=false;
			break;
		}
		case 's':
		{
			Keys[7]=false;
			break;
		}
		case 'y':
		{
			Keys[8]=false;
			break;
		}
	}
    ProcessKeys();
}

void mouseclick(int button,int state,int x,int y )
{
    // Functions for the mouse click locations
    if(state== GLUT_UP )
    {
  //   	Bullet newb = Bullet();
		// Ship present = newg.PlayerBoard.GetNthShip(newg.PlayerId);
		// float velx = 0- 10*sin(PI*present.GetAngle()/180);
		// float vely = 10* cos(PI*present.GetAngle()/180);
		// newb.SetXPos(present.GetXPos());
		// newb.SetYPos(present.GetYPos());
		// newb.SetVelX(velx);
		// newb.SetVelY(vely);
		// newb.SetShipID(newg.PlayerId);
		// newb.SetTypeAI(false);
		// newb.SetTypePlayer(true);
		// newg.PlayerBoard.InsertBullet(newb);
		// BulletsToAdd.push(newb);
  //   	// Explosions.push_back(newExplosion(2*x-newg.PlayerBoard.GetPosXDimension(),-2*y+newg.PlayerBoard.GetPosYDimension(),0));
    }
}

void ShowObject(std::vector<Faces> &facevect)
{
	// glPushMatrix();
	// glTranslatef(500,500,1000);
	glRotatef (90,1,0,0);
	for (int i=0; i<facevect.size() ; i++)
	{
		Faces currentface= facevect[i];
		Points point1,point2,point3;
		point1= currentface.p1;
		point2= currentface.p2;
		point3= currentface.p3;
		glBegin(GL_POLYGON);
		glVertex3f(point1.x,point1.y,point1.z);
		glVertex3f(point2.x,point2.y,point2.z);
		glVertex3f(point3.x,point3.y,point3.z);
		glEnd();
	}
	// glPopMatrix();
}

void ShowBullet(Bullet &b)
{
	// std::cout <<"Showing bullet now\n";
	glPushMatrix();
	glTranslatef(b.GetXPos(),b.GetYPos(),0);
	glRotatef(b.GetAngle(),0,0,1);
	Color col_bul=b.GetColorOfBullet();
	glColor3f(col_bul.GetR(),col_bul.GetG(),col_bul.GetB());
	ShowObject(bullet);
	glPopMatrix();
}

void ShowMissile(Bullet &b)
{
	// std::cout <<"Showing missile now\n";
	glPushMatrix();
	glTranslatef(b.GetXPos(),b.GetYPos(),0);
	glRotatef(b.GetAngle(),0,0,1);
	// std::cout << b.GetXPos() <<"\t"<< b.GetYPos() <<"\n";
	Color col_bul=b.GetColorOfBullet();
	glColor3f(col_bul.GetR(),col_bul.GetG(),col_bul.GetB());
	ShowObject(missile);
	glPopMatrix();

	glPushMatrix();
	SmokePointsMissile.push_back(NewSmokePoint(b.GetXPos(),b.GetYPos()));
	// SmokePointsMissile.push_back(NewSmokePoint(b.GetXPos(),b.GetYPos()));
	// SmokePointsMissile.push_back(NewSmokePoint(b.GetXPos(),b.GetYPos()));
	// SmokePointsMissile.push_back(NewSmokePoint(b.GetXPos(),b.GetYPos()));
	SmokePointsMissile.push_back(NewSmokePoint(b.GetXPos(),b.GetYPos()));
	glTranslatef(b.GetXPos(),b.GetYPos(),0);
	glRotatef(b.GetAngle(),0,0,1);
	glTranslatef(0,-110,0);
	DisplaySmokePoints(SmokePointsMissile);
	// std::cout << SmokePointsMissile.size() <<"\n";
	glPopMatrix();
	UpdateAllSmokePoints(SmokePointsMissile);
}

void ShowShip(Ship &shiptodisplay)
{
	if (shiptodisplay.GetLives()>0)
	{
		glPushMatrix();
		glTranslatef(shiptodisplay.GetXPos(),shiptodisplay.GetYPos(),0);
		glRotatef(shiptodisplay.GetAngle(),0,0,1);
		Color col_ship=shiptodisplay.GetColor();
		glColor3f(col_ship.GetR(), col_ship.GetG(), col_ship.GetB());
		// std::cout << shiptodisplay.GetXPos() << "\t" << shiptodisplay.GetYPos() <<"\n";
		ShowObject(ship);
		glPopMatrix();
	
		glPushMatrix();
		SmokePoints.push_back(NewSmokePoint(shiptodisplay.GetXPos(),shiptodisplay.GetYPos()));
		SmokePoints.push_back(NewSmokePoint(shiptodisplay.GetXPos(),shiptodisplay.GetYPos()));
		SmokePoints.push_back(NewSmokePoint(shiptodisplay.GetXPos(),shiptodisplay.GetYPos()));
		SmokePoints.push_back(NewSmokePoint(shiptodisplay.GetXPos(),shiptodisplay.GetYPos()));
		SmokePoints.push_back(NewSmokePoint(shiptodisplay.GetXPos(),shiptodisplay.GetYPos()));
		glTranslatef(shiptodisplay.GetXPos(),shiptodisplay.GetYPos(),0);
		glRotatef(shiptodisplay.GetAngle(),0,0,1);
		glTranslatef(0,-67,0);
		DisplaySmokePoints(SmokePoints);
		glPopMatrix();
		UpdateAllSmokePoints(SmokePoints);
	}
}

void ShowAlien(Alien &alientodisplay)
{
	// std::cout << "displaying alien\n";
	// std::cout << alientodisplay.GetSummary() <<"\n";
	glPushMatrix();
	glTranslatef(alientodisplay.GetXPos(),alientodisplay.GetYPos(),0);
	glRotatef(alientodisplay.GetAngle(),0,0,1);
	Color col_ship=alientodisplay.GetColor();
	glColor3f(col_ship.GetR(), col_ship.GetG(), col_ship.GetB());
	ShowObject(alien);
	glPopMatrix();
}

void ShowBorders()
{
	glPushMatrix();
	float tk=30.0;  // Thickness of the border
	glColor3f(0,0,1.0);

	glBegin(GL_POLYGON);
	glVertex3f( -NX -tk, PY +tk , 0.0);
	glVertex3f( PX +tk , PY +tk , 0.0);
	glVertex3f( PX +tk , PY  , 0.0);
	glVertex3f( -NX -tk, PY  , 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f( -NX -tk , PY + tk , 0.0);
	glVertex3f( -NX -tk , -NY -tk , 0.0);
	glVertex3f( -NX , -NY -tk , 0.0);
	glVertex3f( -NX , PY +tk , 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f( -NX -tk , -NY , 0.0);
	glVertex3f( -NX -tk , -NY -tk , 0.0);
	glVertex3f(  PX +tk , -NY -tk , 0.0);
	glVertex3f(  PX +tk , -NY , 0.0);
	glEnd();
	
	glBegin(GL_POLYGON);
	glVertex3f( PX , PY , 0.0);
	glVertex3f( PX , -NY , 0.0);
	glVertex3f( PX + tk , -NY , 0.0);
	glVertex3f( PX + tk, PY , 0.0);
	glEnd();

	glPopMatrix();
}

void ShowTitle()
{
	glPushMatrix();
	glRasterPos2f(  50+ PX, PY -50);
	glColor3f(0,0,1);
	// glutStrokeString(GLUT_STROKE_ROMAN, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, titleptr);
	glPopMatrix();
}

void ShowIp()
{
	unsigned char *y123= (unsigned char*) ("IP: "+ GetIP()).c_str();

	// std::cout <<GetIP() <<"\n";
	glPushMatrix();
	glRasterPos2f(  50+ PX, PY -150);
	glColor3f(1,0,1);
	// glutStrokeString(GLUT_STROKE_ROMAN, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, y123);
	glPopMatrix();
}

void ShowLives()
{
	const char * livesS="Lives: ";
	unsigned char *y= (unsigned char*) livesS;

	int lives= newg.PlayerBoard.GetNthShip(newg.PlayerId).GetLives();
	std::string s1 = std::to_string(lives);
	// std::cout <<s1 <<"\n";
	unsigned char *pchar1 = (unsigned char*) s1.c_str();
	
	const char * MissilesS="Missiles: ";
	unsigned char *y2= (unsigned char*) MissilesS;

	int nummis= newg.PlayerBoard.GetNthShip(newg.PlayerId).GetNumberMissiles();
	std::string s2 = std::to_string(nummis);
	unsigned char *pchar2 = (unsigned char*) s2.c_str();
	


	glPushMatrix();
	glRasterPos2f(   PX+100, 0 );
	// glColor3f(0,1,1);
	// glutStrokeString(GLUT_STROKE_ROMAN, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, pchar1);
	glPopMatrix();

	glPushMatrix();
	glRasterPos2f( PX +100,-50);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, y2);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, pchar2);
	glPopMatrix();
}

void ShowScores()
{
	// const char * kg="kartikeya";
	// unsigned char *y= (unsigned char*) kg;
	
	float iniy = -200;

	for (int i=0; i<newg.PlayerBoard.GetNumberShips(); i++)
	{
		std::string l1 = newg.PlayerBoard.GetNthPlayerScore(i);
		unsigned char *pchar3= (unsigned char*) l1.c_str();
	
		glPushMatrix();
		glRasterPos3f( PX +100, iniy,-1000 );
		glColor3f(0,0,1);
		iniy -=60;
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, pchar3);
		glPopMatrix();
	}
}

void ShowAllText()
{
	ShowTitle();
	ShowIp();
	ShowLives();
	ShowScores();
}

void ShowBoard(Board &boardtodisplay)
{
	std::vector<Ship> ShipsToDisplay= boardtodisplay.GetVectorShips();
	std::vector<Alien> AliensToDisplay= boardtodisplay.GetVectorAliens();
	std::vector<Bullet> BulletsToDisplay= boardtodisplay.GetVectorBullets();

	for (int i = 0; i < ShipsToDisplay.size(); i++)
	{
		ShowShip(ShipsToDisplay[i]);
	}

	for (int i=0; i< AliensToDisplay.size() ; i++)
	{
		ShowAlien(AliensToDisplay[i]);
	}

	for (int i=0; i< BulletsToDisplay.size() ; i++)
	{
		if (BulletsToDisplay[i].GetTypeAI())
		{
			ShowMissile(BulletsToDisplay[i]);
		}
		else
		{
			ShowBullet(BulletsToDisplay[i]);
		}
	}

	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f( PX , 1080 , 0);
	glVertex3f( 1920 , 1080 , 0);
	glVertex3f( 1920 , -1080  ,0);
	glVertex3f( PX, -1080  , 0);
	glEnd();
	glPopMatrix();

}

void newSpeed (float dest[3])
{
	float v = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 10.0;
	float theta1= (PI* (((GLfloat) rand ()) / ((GLfloat) RAND_MAX)));
	float x= v*cos(theta1);
	float y= v*sin(theta1); 
	float z = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 10.0;

	dest[0] = x;
	dest[1] = y;
	dest[2] = z;
}

Expl newExplosion (float x, float y, float z)
{
	Expl newexpl;
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		newexpl.particles[i].position[0] = x;
		newexpl.particles[i].position[1] = y;
		newexpl.particles[i].position[2] = z;

		newexpl.particles[i].color[0] = 1.0;
		newexpl.particles[i].color[1] = 1.0;
		newexpl.particles[i].color[2] = 0.5;

		newSpeed (newexpl.particles[i].speed);
	}

	for (int i = 0; i < NUM_DEBRIS; i++)
	{
		newexpl.debris[i].position[0] = x;
		newexpl.debris[i].position[1] = y;
		newexpl.debris[i].position[2] = z;

		newexpl.debris[i].orientation[0] = 1.0;
		newexpl.debris[i].orientation[1] = 0.0;
		newexpl.debris[i].orientation[2] = 1.0;

		newexpl.debris[i].color[0] = 0.7;
		newexpl.debris[i].color[1] = 0.7;
		newexpl.debris[i].color[2] = 0.7;

		newexpl.debris[i].scale[0] = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
		newexpl.debris[i].scale[1] = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
		newexpl.debris[i].scale[2] = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

		newSpeed (newexpl.debris[i].speed);
		newSpeed (newexpl.debris[i].orientationSpeed);
	}
	newexpl.fuel = 200;
	return newexpl;
}

void ShowExplosion(Expl &exptodisplay)
{
	if (exptodisplay.fuel == 0)
	{
		// std::cout << "fuel is 0\n";
		// glEnable (GL_LIGHTING);
		// glDisable (GL_LIGHT0);
		// glEnable (GL_DEPTH_TEST);
		// glutSolidCube (1.0);
	}
	else
	{
		glPushMatrix ();
		glBegin (GL_POINTS);

		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			glColor3fv  (exptodisplay.particles[i].color);
			glVertex3fv (exptodisplay.particles[i].position);
		}
		glEnd ();

		glPopMatrix ();
		for (int i = 0; i < NUM_DEBRIS; i++)
		{
			glColor3fv (exptodisplay.debris[i].color);

			glPushMatrix ();

	  		glTranslatef (exptodisplay.debris[i].position[0],
			exptodisplay.debris[i].position[1],
			exptodisplay.debris[i].position[2]);

			glRotatef (exptodisplay.debris[i].orientation[0], 1.0, 0.0, 0.0);
			glRotatef (exptodisplay.debris[i].orientation[1], 0.0, 1.0, 0.0);
			glRotatef (exptodisplay.debris[i].orientation[2], 0.0, 0.0, 1.0);

	  		glScalef ( exptodisplay.debris[i].scale[0],
			exptodisplay.debris[i].scale[1],
			exptodisplay.debris[i].scale[2]);

			glBegin (GL_TRIANGLES);
			glVertex3f (0.0, 0.5, 0.0);
			glVertex3f (-0.25, 0.0, 0.0);
			glVertex3f (0.25, 0.0, 0.0);
			glEnd ();

	  		glPopMatrix ();
		}
    }
}

Expl UpdateExplosion(Expl exptoupdate)
{
	if (exptoupdate.fuel > 0)
	{
		for (int i = 0; i < NUM_PARTICLES; i++)
		{
			exptoupdate.particles[i].position[0] += exptoupdate.particles[i].speed[0] * 0.3;
			exptoupdate.particles[i].position[1] += exptoupdate.particles[i].speed[1] * 0.3;
			exptoupdate.particles[i].position[2] += exptoupdate.particles[i].speed[2] * 0.3;

			exptoupdate.particles[i].color[0] -= 1.0 / 500.0;
			if (exptoupdate.particles[i].color[0] < 0.0)
			{
		  		exptoupdate.particles[i].color[0] = 0.0;
			}

	      	exptoupdate.particles[i].color[1] -= 1.0 / 100.0;
	      	if (exptoupdate.particles[i].color[1] < 0.0)
			{
		  		exptoupdate.particles[i].color[1] = 0.0;
			}

	      	exptoupdate.particles[i].color[2] -= 1.0 / 50.0;
	      	if (exptoupdate.particles[i].color[2] < 0.0)
			{
		  		exptoupdate.particles[i].color[2] = 0.0;
			}
	    }
	    for (int i = 0; i < NUM_DEBRIS; i++)
	    {
	    	exptoupdate.debris[i].position[0] += exptoupdate.debris[i].speed[0] * 0.3;
	    	exptoupdate.debris[i].position[1] += exptoupdate.debris[i].speed[1] * 0.3;
	    	exptoupdate.debris[i].position[2] += exptoupdate.debris[i].speed[2] * 0.3;

	      	exptoupdate.debris[i].orientation[0] += exptoupdate.debris[i].orientationSpeed[0] * 10;
	      	exptoupdate.debris[i].orientation[1] += exptoupdate.debris[i].orientationSpeed[1] * 10;
	      	exptoupdate.debris[i].orientation[2] += exptoupdate.debris[i].orientationSpeed[2] * 10;
	    }
	  	exptoupdate.fuel -= 1;
	}
    exptoupdate.angle += 0.3;  /* Always continue to rotate the camera */
    return exptoupdate;
}

void UpdateAllExplosions()
{
	for (int i=0; i<Explosions.size(); i++)
	{
		Explosions[i]=UpdateExplosion(Explosions[i]);
	}
}

void ShowSmokePoint(SmokePoint &p)
{
	// glTranslatef(-,0,0);
	glPushMatrix();
	glTranslatef(p.position[0],p.position[1],p.position[2]);
	glColor3f(p.color[0],p.color[1],p.color[2]);
	glutSolidSphere(p.radius, 31, 10);
	glPopMatrix();
}

SmokePoint NewSmokePoint(float x, float y)
{
	SmokePoint p;
	p.position[0]=0;
	p.position[1]=0;
	p.position[2]=0;


	p.speed[0] = (5.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 2.0;
	p.speed[1] = - (10.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) ;
	p.speed[2] = (5.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 10.0;

	p.color[0] = 0.5;
	p.color[1] = 0.5;
	p.color[2] = 1.0;

	p.radius = rand()%10;

	p.life = 49;

	return p;
}

void UpdateSmokePoint(SmokePoint &p)
{
	p.position[0] += p.speed[0];
	p.position[1] += p.speed[1];
	p.position[2] += p.speed[2];

	p.speed[0] *=0.98;
	p.speed[1] *=0.98;
	p.speed[2] *=0.98;

	p.color[0] +=0.01;
	p.color[1] -=0.01;
	p.color[2] -=0.02;

	p.life -= 1;

	// return p;
}

void UpdateAllSmokePoints(std::vector<SmokePoint> &v)
{
	for (int i=0; i<v.size(); i++)
	{
		UpdateSmokePoint(v[i]);
	}

	for (int i=0; i<v.size(); i++)
	{
		if (v[i].life==0)
		{
			v.erase(v.begin()+i);
			i-=1;
		}
	}
}

void DisplaySmokePoints(std::vector<SmokePoint> &v)
{
	for (int i=0; i<v.size(); i++)
	{
		// std::cout << "Showing point:" << i <<"\n";
		ShowSmokePoint(v[i]);
	}
}

void DisplayExplosions(std::vector<Expl> &v)
{
	for (int i=0;i<v.size() ; i++)
	{
		ShowExplosion(v[i]);
	}
}

void *networkmainhelper(void* inp)
{
	Graph *pa= (Graph *)inp;
	networkmain(pa->x1,pa->s1);
}

void ShowGameOver()
{
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);

	glBegin(GL_POLYGON);
	glVertex3f( -NX, PY, 0.0);
	glVertex3f(  PX , PY, 0.0);
	glVertex3f( PX , -NY  , 0.0);
	glVertex3f( -NX, -NY  , 0.0);
	glEnd();
	glPopMatrix();
	
}

void display(void)
{
	// std::cout << "starting display\n";
	presentf+=1;
	newg.IsActive=(newg.PlayerBoard.GetNthShip(newg.PlayerId).GetLives()>0);
	while (!Instructions.empty())
	{
		// std::cout <<"in instructions\n";
		std::string s=Instructions.front();
		Instructions.pop();
		std::vector<Points> newexp= newg.PlayerBoard.ApplyInstructions(s,newg.PlayerId);
		if (newexp.size()>0)
		{
			Is_SoundExpl=true;
		}
		for (int j=0; j<Explosions.size(); j++)
		{
			if (Explosions[j].fuel==0)
			{
				Explosions.erase(Explosions.begin()+j);
				j-=1;
			}
		}
		// std::cout <<"erased any explosions\n";
		for (int j=0; j<newexp.size(); j++)
		{
			Explosions.push_back(newExplosion(newexp[j].x,newexp[j].y,0));
		}
		// std::cout << "pushed new explosions\n";
	}
	// std::cout <<"applied instructions if any\n";
	std::vector<Bullet> bulltoadd;
	while (!BulletsToAdd.empty())
	{
		bulltoadd.push_back(BulletsToAdd.front());
		BulletsToAdd.pop();
	}
	std::string message1 = newg.PlayerBoard.GenerateOnlyPlayerInstructions(newg.PlayerId,bulltoadd);
	// std::cout << "sending" << message1 <<"\n";
	SendMessageToAll(message1);

	// std::cout << "Starting display work\n";
	int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
	int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
	// float const window_aspect = (float)window_width / (float)window_height;
	glClearColor(0, 0, 0.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0-window_width, window_width,0- window_height,window_height,-2000,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// std::cout<<"here before the if\n";
	if (!GameActive)
	{
	
	    std::cout <<"displaying image\n";
		glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D, _textureId);
	    
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glColor3f(1.0f, 1.0f, 1.0f);
	
	
	    glBegin(GL_QUADS);
	
	    glNormal3f(0.0, 1.0f, 0.0f);
	    glTexCoord2f(0.0f, 1.0f);
	    glVertex3f(-window_width, window_height, 1000);
	    glTexCoord2f(1.0f, 1.0f);
	    glVertex3f(window_width,window_height, 1000);
	    glTexCoord2f(1.0f, 0.0f);
	    glVertex3f(window_width, -window_height, 1000);
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex3f(-window_width, -window_height, 1000);
	    
	    glEnd();
	
	
	    glDisable(GL_TEXTURE_2D);
	
	}
	else
	{
		std::cout << "in else\n";
		for (int i=0; i<Stars.size() ; i++)
		{
			glPushMatrix();
			glColor3f(0.5,0.8,0.2);
			glTranslatef(Stars[i].x,Stars[i].y,Stars[i].z);
			glutSolidSphere(3, 31, 10);
			glPopMatrix();
		}
		ShowBoard(newg.PlayerBoard);
		ShowBorders();
		ShowAllText();
		DisplayExplosions(Explosions);
	}
	// for (int i=0; i<newg.PlayerBoard.GetVectorBullets().size();i++)
	// {
	// 	std::cout << "bullets info: "<< newg.PlayerBoard.GetNthBullet(i).GetSummary()<<"\n";
	// }
	
	// for (int i=0; i<newg.PlayerBoard.GetNumberShips();i++)
	// {
	// 	std::cout << "players info: "<< newg.PlayerBoard.GetNthShip(i).GetSummary()<<"\n";
	// }
	glutSwapBuffers();
	// std::cout <<"Buffers swapped\n";
	if (IsBaap() && GameActive)
	{
		// std::cout << "in baap\n";
		// std::cout<<"Lives before: " <<newg.PlayerBoard.GetNthShip(newg.PlayerId).GetLives()<<"\n";
		std::cout << "It is in the baap case\n";
		UpdateAIBoard(newg.PlayerBoard);
		std::vector<Points> p = newg.PlayerBoard.UpdateAllBullets();
		if (p.size()>0)
		{
			Is_SoundExpl=true;
		}
		// std::cout<<"Lives after: " <<newg.PlayerBoard.GetNthShip(newg.PlayerId).GetLives()<<"\n";

		// std::cout << "starting for loop\n";
		for (int j=0; j<Explosions.size(); j++)
		{
			if (Explosions[j].fuel==0)
			{
				Explosions.erase(Explosions.begin()+j);
				j-=1;
			}
		}
		// std::cout <<"done with for 1\n";
		for (int j=0; j<p.size(); j++)
		{
			Explosions.push_back(newExplosion(p[j].x,p[j].y,0));
			// std::cout << p[j].x <<"\t" <<p[j].y << "\n";
		}

		while (newg.PlayerBoard.GetNumberAliens()<=newg.LastBulletTime/50)
		{
			newg.PlayerBoard.AddRandomAlien();
		}
		// std::cout << "starting ins gen\n";
		message1 = newg.PlayerBoard.GenerateAllInstructions(newg.PlayerId,p);
		// std::cout <<" generated instructions\n";
		// std::cout << message1;
		SendMessageToAll(message1);
		// std::cout << "done sent\n";
	}
	else if (GameActive)
	{
		newg.PlayerBoard.UpdateBulletsWithoutKilling();
	}
	// std::cout << "starting explosion update\n";
	UpdateAllExplosions();
	// std::cout << "Updated\n";
	// std::cout << "Done operations, time for re display\n";
	// UpdatePlayerAI(newg.PlayerBoard);
	// Update AI
	glutPostRedisplay();
}

void mousepos(int x, int y)
{
	// double convx=2*x-1920;
	// double convy=-2*y+1080;
	// Ship n1=newg.PlayerBoard.GetNthShip(newg.PlayerId);
	// double dy=convy-n1.GetYPos();
	// double dx=convx-n1.GetXPos();
	// float theta1;
	// if (dx == 0.0)
	// {
	// 	if (dy>0)
	// 	{
	// 		theta1=0;
	// 	}
	// 	else
	// 	{
	// 		theta1=180;
	// 	}
	// }
	// else
	// {
	// 	if (dx>0)
	// 	{
	// 		theta1 = (float) (atan(dy/dx)*180/PI) -90.0 ;
	// 	}
	// 	else
	// 	{
	// 		theta1 = (float) (atan(dy/dx)*180/PI) +90.0 ;
	// 	}
	// }
	// n1.SetAngle(theta1);
	// newg.PlayerBoard.SetNthShip(newg.PlayerId,n1);
	// std::cout<< "Mouse is at: "<<convx <<"\t" <<convy <<"\n";
}

int main(int argc,char *argv[])
{
	initRendering();
	GameActive=false;
	GameOver=false;
	Is_SoundExpl=false;
	Is_SoundBullet=false;
	pthread_t networkthread;
	Graph datagraph;
	datagraph.x1=argc-1;
	datagraph.s1=argv;

	pthread_create(&networkthread,NULL,networkmainhelper,&datagraph);

	for (int i=0; i<8; i++)
	{
		Keys[i]=false;
	}

	srand (time(NULL));
	std::cout << "Opening file\n";
	missile = loadOBJ("Missile.obj");
	bullet = loadOBJ("Bullet.obj");
	alien = loadOBJ("Alien1.obj");
	ship = loadOBJ("Ship3.obj");
	std::cout << "Opened file\n";
	PX=1400;
	NX=1850;
	PY=1040;
	NY=1040;
	POSX=1400;
	NEGX=1850;
	POSY=1040;
	NEGY=1040;

	pthread_t soundthread1;
	pthread_t soundthread2;
	pthread_create(&soundthread1,NULL,sound_play1,NULL);
	pthread_create(&soundthread2,NULL,sound_play2,NULL);
    

	std::string title ="Space Invaders";
	titleptr= (unsigned char*) title.c_str();

	SpaceBarFree=0;
	int limt = rand()%500 +250;

	IPAddress= GetIP();

	std::cout <<"pushing stars\n";
	for (int i =0 ; i<limt ; i++)
	{
		int X,Y,Z;
		X = (rand()%int(PX+NX)) -NX;
		Y = (rand()%int(PY+NY)) -NY;
		Z = 500;
		Points p;
		p.x=X;
		p.y=Y;
		p.z=Z;
		Stars.push_back(p);
	}
	std::cout <<"pushed stars: " <<isOffline <<"\n";
	int numplayers;
	if (!isOffline)
	{
		while (!playersReady)
		{
			// Keep waiting
		}
		numplayers=GetNumPlayers();
	}
	else
	{
		numplayers=1;
	}
	

	std::cout <<"Generated stars: " << Stars.size() <<"\n";

	newg.PlayerId = numplayers-1;
	newg.PlayerBoard = Board(PX,NX,PY,NY);

	for (int k=0; k<numplayers; k++)
	{
		Ship news= Ship(k);
		news.SetColorFloat(rand()%255,rand()%255,rand()%255);
		newg.PlayerBoard.InsertShip(news);
	}
	Ship Pship=newg.PlayerBoard.GetNthShip(newg.PlayerId);
	Pship.SetName(argv[argc-1]);
	newg.PlayerBoard.SetNthShip(newg.PlayerId,Pship);

	std::cout << "board is set up: " <<newg.PlayerId<<"\n";

	// Alien newa= Alien();
	// newg.PlayerBoard.InsertAlien(newa);
	newg.LastBulletTime=0;
	presentf=0;

	// Wrapper function for graphics
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1920,1080);
	glutCreateWindow("Space Invaders Co-op");

	glutDisplayFunc(display);
	// glutReshapeFunc(reshape);
	glutMouseFunc(mouseclick);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleKeypressUp);
	glutSpecialUpFunc(specialKeysUp);
	glutPassiveMotionFunc(mousepos);
	initRendering();
	glutMainLoop();

	return 0;
}
