
#include <GL/glut.h>
#include <GL/gl.h>
//#include <iostream>
#include <GL/glui.h>
using namespace std;
void myGlutInit();
//void myGlutKeyboard(unsigned char Key, int x, int y)
//void myGlutMenu( int value )
//void myGlutIdle( void )
//void myGlutMouse(int button, int button_state, int x, int y )
//void myGlutMotion(int x, int y )
//void myGlutReshape( int x, int y )
//void myGlutDisplay( void );
//void control_cb( int ID );

int main(int argc, char* argv[])
{
int main_window;
/*
* Initialize GLUT and create window - This **/
/*
* is all regular GLUT code so far **/
glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
glutInitWindowPosition( 50, 50 );
glutInitWindowSize( 300, 300 );
main_window = glutCreateWindow( "GLUI test app" );
//glutKeyboardFunc();
//glutDisplayFunc();
//glutReshapeFunc();
//glutMotionFunc();
//glutMouseFunc();
//myGlutInit();
/** Now create a GLUI user interface window and add controls **/
GLUI *glui = GLUI_Master.create_glui
( "GLUI", 0 );
glui->add_statictext( "Simple GLUI Example" );
glui->add_separator();
glui->add_checkbox( "Wireframe");
GLUI_Spinner *segment_spinner =
glui->add_spinner( "Segments:",GLUI_SPINNER_INT, &segments );
segment_spinner->set_int_limits( 3, 60, GLUI_LIMIT_WRAP );
GLUI_EditText *edittext =
glui->add_edittext( "Text:", GLUI_EDITTEXT_TEXT, text );
glui->add_column(true);
/** Begin new column - 'true' indicates **/
/*
* a vertical bar should be drawn **/
GLUI_Panel *obj_panel = glui->add_panel
( "Object Type" );
GLUI_RadioGroup *group1 =
glui->add_radiogroup_to_panel(obj_panel,&obj,3,control_cb);
glui->add_radiobutton_to_group( group1, "Sphere" );
glui->add_radiobutton_to_group( group1, "Torus" );
glui->add_button( "Quit", 0,(GLUI_Update_CB)exit );
/** Tell GLUI window which other window to recognize as the main gfx window **/
//glui->set_main_gfx_window( main_window );
/** Register the Idle callback with GLUI (instead of with GLUT) **/
//GLUI_Master.set_glutIdleFunc
//( myGlutIdle );
/** Now call the regular GLUT main loop **/
glutMainLoop();
return 0;
}