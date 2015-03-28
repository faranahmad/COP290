#include "Combined.h"

struct Points
{
	float x,y,z;
}
;
struct Faces
{
	Points p1,p2,p3;
}
;

double rotate_y=0.0; 
double rotate_x=0.0;

std::vector<Faces> alien;
std::vector<Faces> ship;
std::vector<Faces> missile;
std::vector<Faces> bullet;
std::vector<Points> Stars;

struct GamePlay
{
	Board PlayerBoard;
	int PlayerId;
};

GamePlay newg;


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
			// int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
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


void specialKeys( int key, int x, int y ) 
{
	if (key == GLUT_KEY_RIGHT)
	{
		// Move the player ship to the right
		// rotate_x +=2;
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,1);
	}
	else if (key == GLUT_KEY_LEFT)
	{
		// Move player ship to left
		// rotate_y +=2;
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,0);
	}
	else if (key == GLUT_KEY_UP)
	{
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,2);
		// Move player ship up
	}
	else if (key == GLUT_KEY_DOWN)
	{
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,3);
		// Move player ship down 
	}
	// std::cout << rotate_x <<"\t"<<rotate_y<<"\n";
	glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y) 
{
	std::cout << key << "\n";
	switch (key) 
	{
		case 'a':
		{
			std::cout <<"a was pressed\n";
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,4);
			glutPostRedisplay();
			// Rotate the ship to the left
			break;
		}
		case 'd':
		{
			std::cout <<"d was pressed\n";
			newg.PlayerBoard.MoveNthShip(newg.PlayerId,5);
    		glutPostRedisplay();
			// Rotate the ship to the right
			break;
		}
		case 'f':
		{
			std::cout << "f was pressed\n";
			newg.PlayerBoard.AddRandomShip();
			glutPostRedisplay();
			break;
		}

		case 32: //SpaceBar
		{
			// Fire bullet
			// TODO: incorporate multiplier
			std::cout << "space bar presed\n";
			Bullet newb = Bullet();
			newb.SetTypeAI(false);
			Ship present = newg.PlayerBoard.GetNthShip(newg.PlayerId);

			std::cout <<"angle: " <<present.GetAngle() <<"\n";
			float velx = 0- 10*sin(PI*present.GetAngle()/180);
			float vely = 10* cos(PI*present.GetAngle()/180);

			newb.SetXPos(present.GetXPos());
			newb.SetYPos(present.GetYPos());
			newb.SetVelX(velx);
			newb.SetVelY(vely);
			newb.SetShipID(newg.PlayerId);
			newb.SetTypeAI(false);
			newb.SetTypePlayer(true);

			std::cout <<"angle bullet: " << newb.GetAngle() <<"\n";
			std::cout <<"velocities " << newb.GetVelX() <<"\t" <<newb.GetVelY() <<"\n";
			newg.PlayerBoard.InsertBullet(newb);
			glutPostRedisplay();
			break;
		}
		
		case 's':
		{
			// Fire Missile
			std::cout << "space bar presed\n";
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
			}
			glutPostRedisplay();
			break;
		}
		case 'y':
		{
			newg.PlayerBoard.UpdateAllBullets();
			glutPostRedisplay();
			break;
		}
		case 43: //+ key
		{    
			break; 
		}      
		case 27: //Escape key
		{
			exit(0);
		}
    }
}

void ShowObject(std::vector<Faces> facevect)
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

void ShowBullet(Bullet b)
{
	std::cout <<"Showing bullet now\n";
	glPushMatrix();
	glTranslatef(b.GetXPos(),b.GetYPos(),0);
	glRotatef(b.GetAngle(),0,0,1);
	Color col_bul=b.GetColorOfBullet();
	glColor3f(col_bul.GetR(),col_bul.GetG(),col_bul.GetB());
	ShowObject(bullet);
	glPopMatrix();
}

void ShowMissile(Bullet b)
{
	std::cout <<"Showing missile now\n";
	glPushMatrix();
	glTranslatef(b.GetXPos(),b.GetYPos(),0);
	glRotatef(b.GetAngle(),0,0,1);
	std::cout << b.GetXPos() <<"\t"<< b.GetYPos() <<"\n";
	Color col_bul=b.GetColorOfBullet();
	glColor3f(col_bul.GetR(),col_bul.GetG(),col_bul.GetB());
	ShowObject(missile);
	glPopMatrix();
}

void ShowShip(Ship shiptodisplay)
{
	glPushMatrix();
	glTranslatef(shiptodisplay.GetXPos(),shiptodisplay.GetYPos(),0);
	glRotatef(shiptodisplay.GetAngle(),0,0,1);
	Color col_ship=shiptodisplay.GetColor();
	glColor3f(col_ship.GetR(), col_ship.GetG(), col_ship.GetB());
	std::cout << shiptodisplay.GetXPos() << "\t" << shiptodisplay.GetYPos() <<"\n";
	ShowObject(ship);
	glPopMatrix();
}

void ShowAlien(Alien alientodisplay)
{
	glPushMatrix();
	glTranslatef(alientodisplay.GetXPos(),alientodisplay.GetYPos(),0);
	glRotatef(alientodisplay.GetAngle(),0,0,1);
	Color col_ship=alientodisplay.GetColor();
	glColor3f(col_ship.GetR(), col_ship.GetG(), col_ship.GetB());
	ShowObject(alien);
	glPopMatrix();	
}


void ShowBoard(Board boardtodisplay)
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
}

void display(void)
{
	std::cout<<"In display\n";
	int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
	int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
	float const window_aspect = (float)window_width / (float)window_height;
	// glRotatef( rotate_x, 200, 0.0, 0.0 );
	// glRotatef( rotate_y, 0.0, 200, 0.0 );
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

	// ShowObject(missile);
	// ShowBullet(50,-60,5,Color(255,0,0));
	// ShowBullet(-50,-60,5,Color(255,0,0));
	// ShowMissile(-40.0,-40.0,10.0,10.0,Color(255,0,0));

	ShowBoard(newg.PlayerBoard);

	glPushMatrix();
	// glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'a' );
	// glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'b' );
	// glutBitmapCharacter( GLUT_BITMAP_TIMES_ROMAN_24, 'c' );
	for (int i=0; i<Stars.size() ; i++)
	{
		glPushMatrix();
		glColor3f(0.5,0.8,0.2);
		glTranslatef(Stars[i].x,Stars[i].y,Stars[i].z);
		glutSolidSphere(3, 31, 10);
		glPopMatrix();
	}
	glPopMatrix();
	glutSwapBuffers();
	newg.PlayerBoard.UpdateAllBullets();
	glutPostRedisplay();
}


int main(int argc,char *argv[])
{
	srand (time(NULL));
	std::cout << "Opening file\n";
	missile = loadOBJ("Missile.obj");
	bullet = loadOBJ("Bullet.obj");
	alien = loadOBJ("Alien1.obj");
	ship = loadOBJ("Ship.obj");
	std::cout << "Opened file\n";

	int limt = rand()%500;

	for (int i =0 ; i<limt ; i++)
	{
		int X,Y,Z;
		X = (rand()%3200) -1600;
		Y = (rand()%1800) -900;
		Z = 500;
		Points p;
		p.x=X;
		p.y=Y;
		p.z=Z;
		Stars.push_back(p);	
	}

	std::cout <<"Generated stars: " << Stars.size() <<"\n";

	newg.PlayerId = 0;
	newg.PlayerBoard = Board(1600,1600,900,900);

	Ship news= Ship();
	news.SetColorFloat(30,170,65);
	news.SetXPos(500);
	news.SetYPos(45);
	newg.PlayerBoard.InsertShip(news);

	// Wrapper function for graphics
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1600,900);
	glutCreateWindow("Team Babe Magnets");
	
	glutDisplayFunc(display);
	// glutReshapeFunc(reshape);
	// glutMouseFunc(mouseclick);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(handleKeypress);
	// initRendering();

	glutMainLoop();
	
	return 0;
}