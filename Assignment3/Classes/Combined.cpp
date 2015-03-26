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

std::vector<Faces> loadOBJ(char * path)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<Faces> answer;
	std::vector<Points> temp_vertices; 
	// std::vector<glm::vec2> temp_uvs;
	// std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return answer;
	}
	std::cout <<"Starting work\n";
	while( 1 )
	{
		std::cout << "Here\n";
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 )
		{
			std::cout <<"In v case\n";
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
			std::cout << vertexIndex[0] <<"\t"<< vertexIndex[1] <<"\t"<< vertexIndex[2] <<"\n";
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
		rotate_y += 2;
	else if (key == GLUT_KEY_LEFT)
    	rotate_y -= 2;
 	else if (key == GLUT_KEY_UP)
    	rotate_x += 2;
 	else if (key == GLUT_KEY_DOWN)
    	rotate_x -= 2;
 	std::cout << rotate_x <<"\t"<<rotate_y<<"\n";
	glutPostRedisplay();
}

void ShowBullet(float x,float y,float angle,Color color)
{
	glPushMatrix();
	glTranslatef(x,y,1000);
	glColor3f(color.GetR(),color.GetG(),color.GetB());
	GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
	GLfloat ambient[] = {0.7f,0.7f,0.7f,1.0f};
	GLfloat cyan[] = {0.8,0.8,0.8,1};
	GLfloat shininess[] = {100};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glutSolidSphere(10, 31, 10);	
	glPopMatrix();
}

void ShowMissile(float x, float y, float vx, float vy, Color color)
{
	GLUquadricObj *quadric=gluNewQuadric();
	
	int length=300;
	int radius=100;

	float vz = 0;
	float v = sqrt(vx*vx+vy*vy);
	float ax = 0;
	float rx = 57.29577*acos(vy/v);
	float ry = 57.29577*asin(vy/v);

	glPushMatrix();

	glTranslatef(x,y,1000);
	// glRotatef(-0.5,0.0,1.0,1.0);

	gluQuadricOrientation(quadric,GLU_OUTSIDE);
	gluCylinder(quadric,radius,radius,100,50,1);

	glPopMatrix();
	gluDeleteQuadric(quadric);
}

void ShowShip(float x, float y,float angle, Color color)
{
	glPushMatrix();
	int dimx=20;
	int dimy=40;
	int dimz=20;

	float sintheta = sin(angle);
	float costheta = cos(angle);

	float xcos = dimx*costheta;
	float xsin = dimx*sintheta;
	float ycos = dimy*costheta;
	float ysin = dimy*sintheta;

	glBegin(GL_QUADS);

	// glRotatef()

	glColor3f(0.0,1.0,0.0);
	glVertex3f(x+xcos/2 - ysin/2, y+xsin/2 + ycos/2 ,dimz/2);
	glVertex3f(x+xcos/2 - ysin/2, y+xsin/2 + ycos/2 ,-dimz/2);
	glVertex3f(x+xcos/2 + ysin/2, y+xsin/2 - ycos/2 ,-dimz/2);
	glVertex3f(x+xcos/2 + ysin/2, y+xsin/2 - ycos/2 ,dimz/2);

	glColor3f(0.0,1.0,0.0);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,dimz/2);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,dimz/2);

	glColor3f(0.0,1.0,0.0);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,dimz/2);
	glVertex3f(x-xcos/2 - ysin/2, y-xsin/2 + ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,-dimz/2);
	glVertex3f(x-xcos/2 + ysin/2, y-xsin/2 - ycos/2 ,dimz/2);
	glEnd();
	glPopMatrix();
}

void ShowObject(std::vector<Faces> facevect)
{
	glPushMatrix();
	glTranslatef(500,500,1000);
	glRotatef( rotate_x, 200, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 200, 0.0 );
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
	glPopMatrix();
}

void display(void)
{
	std::cout<<"In display\n";
	int const window_width  = glutGet(GLUT_WINDOW_WIDTH);
	int const window_height = glutGet(GLUT_WINDOW_HEIGHT);
	float const window_aspect = (float)window_width / (float)window_height;
	glRotatef( rotate_x, 200, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 200, 0.0 );
	glClearColor(0.5, 0.5, 1.0, 1.0);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_COLOR_MATERIAL);
	glViewport(0, 0, window_width, window_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0-window_width, window_width,0- window_height,window_height,-2000,2000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ShowObject(missile);

	ShowBullet(50,-60,5,Color(255,0,0));
	ShowBullet(-50,-60,5,Color(255,0,0));

	ShowMissile(-40.0,-40.0,10.0,10.0,Color(255,0,0));

	glPushMatrix();
	glTranslatef(100,100,1000);
	glColor3f(0.5,0.8,0.2);
	GLfloat white[] = {1.f, 1.f, 1.f, 1.0f};
	GLfloat ambient[] = {0.7f,0.7f,0.7f,1.0f};
	GLfloat cyan[] = {0.8,0.8,0.8,1};
	GLfloat shininess[] = {100};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glutSolidSphere(30, 31, 10);
	glPopMatrix();
	glutSwapBuffers();
	// glutPostRedisplay();
}

int main(int argc,char *argv[])
{
	std::cout << "Opening file\n";
	missile = loadOBJ("Bullet.obj");
	std::cout << "Opened file\n";
    // Wrapper function for graphics
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1600,900);
    glutCreateWindow("Team Babe Magnets");
    
    glutDisplayFunc(display);
    // glutReshapeFunc(reshape);
    // glutMouseFunc(mouseclick);
    glutSpecialFunc(specialKeys);
    // glutKeyboardFunc(handleKeypress);
    // initRendering();

    glutMainLoop();

    return 0;
}