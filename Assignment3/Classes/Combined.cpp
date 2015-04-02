#include "Combined.h"

#define NUM_PARTICLES    1000          /* Number of particles  */
#define NUM_DEBRIS       70            /* Number of debris     */

// struct Points
// {
// 	float x,y,z;
// }
// ;
struct Faces
{
	Points p1,p2,p3;
}
;


struct particleData
{
  float   position[3];
  float   speed[3];
  float   color[3];
};

bool Keys[8];

/* A piece of debris */

struct debrisData
{
  float   position[3];
  float   speed[3];
  float   orientation[3];        /* Rotation angles around x, y, and z axes */
  float   orientationSpeed[3];
  float   color[3];
  float   scale[3];
};

struct Expl
{
	particleData 	particles[NUM_PARTICLES];
	debrisData 		debris[NUM_DEBRIS];   
	int         	fuel = 0;                /* "fuel" of the explosion */
	float 			angle = 0.0;             /* camera rotation angle */
};


double rotate_y=0.0; 
double rotate_x=0.0;

std::vector<Faces> alien;
std::vector<Faces> ship;
std::vector<Faces> missile;
std::vector<Faces> bullet;
std::vector<Points> Stars;
std::vector<Expl> Explosions;

struct GamePlay
{
	Board PlayerBoard;
	int PlayerId;
};

GamePlay newg;


Expl newExplosion (float x, float y, float z);

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

void ProcessKeys()
{
	if (Keys[0])
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,1);
	if (Keys[1])
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,0);
	if (Keys[2])
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,2);
	if (Keys[3])
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,3);
	if (Keys[4])
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,4);
	if (Keys[5])
		newg.PlayerBoard.MoveNthShip(newg.PlayerId,5);
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
	glutPostRedisplay();
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
		std::cout << "down key left\n";
		// newg.PlayerBoard.MoveNthShip(newg.PlayerId,3);
		// Move player ship down 
	}
	ProcessKeys();
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
			Keys[4]=true;
			// glutPostRedisplay();
			// Rotate the ship to the left
			break;
		}
		case 'd':
		{
			std::cout <<"d was pressed\n";
			Keys[5]=true;
			// newg.PlayerBoard.MoveNthShip(newg.PlayerId,5);
    		// glutPostRedisplay();
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
			newg.PlayerBoard.AddRandomAlien();
			// glutPostRedisplay();
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
    if (key=='o')
    {
    	std::cout <<"o\n";
    }
    if (key=='l')
    {
    	std::cout <<"l\n";
    }
    ProcessKeys();
}

void handleKeypressUp(unsigned char key, int x, int y) 
{
	std::cout << key << "\n";
	switch (key) 
	{
		case 'a':
		{
			Keys[4]=false;
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
   //  		glutPostRedisplay();
			// Rotate the ship to the right
			break;
		}
	}
		// case 'f':
		// {
		// 	std::cout << "f was pressed\n";
		// 	newg.PlayerBoard.AddRandomShip();
		// 	glutPostRedisplay();
		// 	break;
		// }

		// case 32: //SpaceBar
		// {
		// 	// Fire bullet
		// 	// TODO: incorporate multiplier
		// 	std::cout << "space bar presed\n";
		// 	Bullet newb = Bullet();
		// 	Ship present = newg.PlayerBoard.GetNthShip(newg.PlayerId);

		// 	std::cout <<"angle: " <<present.GetAngle() <<"\n";
		// 	float velx = 0- 10*sin(PI*present.GetAngle()/180);
		// 	float vely = 10* cos(PI*present.GetAngle()/180);

		// 	newb.SetXPos(present.GetXPos());
		// 	newb.SetYPos(present.GetYPos());
		// 	newb.SetVelX(velx);
		// 	newb.SetVelY(vely);
		// 	newb.SetShipID(newg.PlayerId);
		// 	newb.SetTypeAI(false);
		// 	newb.SetTypePlayer(true);

		// 	std::cout <<"angle bullet: " << newb.GetAngle() <<"\n";
		// 	std::cout <<"velocities " << newb.GetVelX() <<"\t" <<newb.GetVelY() <<"\n";
		// 	newg.PlayerBoard.InsertBullet(newb);
		// 	glutPostRedisplay();
		// 	break;
		// }
		
		// case 's':
		// {
		// 	// Fire Missile
		// 	std::cout << "space bar presed\n";
		// 	Bullet newb = Bullet();
		// 	Ship present = newg.PlayerBoard.GetNthShip(newg.PlayerId);
		// 	if (present.GetNumberMissiles()>0)
		// 	{
		// 		present.ReduceMissile();
	
		// 		float velx = -10* sin(PI*present.GetAngle()/180);
		// 		float vely = 10* cos(PI*present.GetAngle()/180);
	
		// 		newb.SetTypeAI(true);
		// 		newb.SetXPos(present.GetXPos());
		// 		newb.SetYPos(present.GetYPos());
		// 		newb.SetVelX(velx);
		// 		newb.SetVelY(vely);
		// 		newb.SetShipID(newg.PlayerId);
		// 		newb.SetTypePlayer(true);

		// 		newg.PlayerBoard.SetNthShip(newg.PlayerId,present);
		// 		newg.PlayerBoard.InsertBullet(newb);	
		// 	}
		// 	glutPostRedisplay();
		// 	break;
		// }
		// case 'y':
		// {
		// 	newg.PlayerBoard.AddRandomAlien();
		// 	// glutPostRedisplay();
		// 	break;
		// }
		// case 43: //+ key
		// {    
		// 	break; 
		// }      
		// case 27: //Escape key
		// {
		// 	exit(0);
		// }
  //   }
  //   if (key=='o')
  //   {
  //   	std::cout <<"o\n";
  //   }
  //   if (key=='l')
  //   {
  //   	std::cout <<"l\n";
  //   }
    ProcessKeys();
}

void mouseclick(int button,int state,int x,int y )
{
    // Functions for the mouse click locations
    if(state== GLUT_UP )
    {
    	Explosions.push_back(newExplosion(2*x-newg.PlayerBoard.GetPosXDimension(),-2*y+newg.PlayerBoard.GetPosYDimension(),0));
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
	// std::cout <<"Showing bullet now\n";
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
	// std::cout <<"Showing missile now\n";
	glPushMatrix();
	glTranslatef(b.GetXPos(),b.GetYPos(),0);
	glRotatef(b.GetAngle(),0,0,1);
	// std::cout << b.GetXPos() <<"\t"<< b.GetYPos() <<"\n";
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
	// std::cout << shiptodisplay.GetXPos() << "\t" << shiptodisplay.GetYPos() <<"\n";
	ShowObject(ship);
	glPopMatrix();
}

void ShowAlien(Alien alientodisplay)
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

void newSpeed (float dest[3])
{

	float x = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 10.0;
	float y = (20.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 10.0;
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

void ShowExplosion(Expl exptodisplay)
{
  	if (exptodisplay.fuel == 0)
    {
    	std::cout << "fuel is 0\n";
		// glEnable (GL_LIGHTING);
		// glDisable (GL_LIGHT0);
		// glEnable (GL_DEPTH_TEST);
		// glutSolidCube (1.0);
    }
	else
    {
    	std::cout <<"in else case\n";
		glPushMatrix ();

      // glDisable (GL_LIGHTING);
      // glDisable (GL_DEPTH_TEST);

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
	  	std::cout << "fuel was: " <<exptoupdate.fuel <<"\n";	  
	  	exptoupdate.fuel -= 1;
	  	std::cout << "fuel is now: " <<exptoupdate.fuel <<"\n";
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

void DisplayExplosions(std::vector<Expl> v)
{
	for (int i=0;i<v.size() ; i++)
	{
		ShowExplosion(v[i]);
	}
}

void display(void)
{
	// std::cout<<Keys[0]<<"\n";
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

	ShowBoard(newg.PlayerBoard);
	DisplayExplosions(Explosions);

	glutSwapBuffers();
	std::vector<Points> p = newg.PlayerBoard.UpdateAllBullets();
	for (int j=0; j<Explosions.size(); j++)
	{
		if (Explosions[j].fuel==0)
		{		
			Explosions.erase(Explosions.begin()+j);
		}
	}
	for (int j=0; j<p.size(); j++)
	{
		// 2*x-newg.PlayerBoard.GetPosXDimension(),-2*y+newg.PlayerBoard.GetPosYDimension()
		Explosions.push_back(newExplosion(p[j].x,p[j].y,0));
		std::cout << p[j].x <<"\t" <<p[j].y << "\n";
	}

	UpdateAllExplosions();
	// UpdatePlayerAI(newg.PlayerBoard);
	// UpdateAIBoard(newg.PlayerBoard);
	//Update AI
	glutPostRedisplay();
}


int main(int argc,char *argv[])
{
	for (int i=0; i<8; i++)
	{
		Keys[i]=false;
	}

	srand (time(NULL));
	// newExplosion();
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


	Alien newa= Alien();
	newg.PlayerBoard.InsertAlien(newa);

	// Wrapper function for graphics
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1600,900);
	glutCreateWindow("Team Babe Magnets");
	
	glutDisplayFunc(display);
	// glutReshapeFunc(reshape);
	glutMouseFunc(mouseclick);
	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(handleKeypress);
	glutKeyboardUpFunc(handleKeypressUp);
	glutSpecialUpFunc(specialKeysUp);
	// initRendering();

	glutMainLoop();
	
	return 0;
}