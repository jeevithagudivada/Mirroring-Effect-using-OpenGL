			//To simulate a mirroring effect
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glu.h>

#define TIMER 33

GLUquadric *quadSphere, *quadCyl;
int windowWidth;

int btn,state,x,y;

static float xrot;
static void initc();
static void inits();
void reshape(int w, int h);
static void timer (int value);

GLUquadric *quad;
GLUquadric *quadcone;

/***************************cylinder**********************************/
void drawScenec(GLenum order)
{
    GLfloat pos[4] = {-2.8, 5., 1.8, 1.};

    glLightfv (GL_LIGHT1, GL_POSITION, pos);

	glPushMatrix();

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (order);

	/* Draw the walls */
    glColor3f (1., 1., 1.);
	glBegin(GL_QUADS);
	  glNormal3f (1., 0., 0.);
	    glVertex3f (-3., 3., 4.);
	    glVertex3f (-3., -3., 4.);
	    glVertex3f (-3., -3., -3.);
	    glVertex3f (-3., 3., -3.);
	  glNormal3f (0., 0., 1.);
		glVertex3f (-3., 3., -3.);
		glVertex3f (-3., -3., -3.);
		glVertex3f (3., -3., -3.);
		glVertex3f (3., 3., -3.);
	  glNormal3f (-1., 0., 0.);
		glVertex3f (3., 3., -3.);
		glVertex3f (3., -3., -3.);
		glVertex3f (3., -3., 3.);
		glVertex3f (3., 3., 3.);
	glEnd();
	glDisable (GL_CULL_FACE);

	/* Draw the cylinder */
    glRotatef (xrot, 1., 0., 0.);//TO rotate a cylinder
    glTranslatef (0., 0., -1.);//TO translate a cylinder

	// glRotatef (-xrot, 0., 1., 0.);
    glColor3f (.5, .5, 1.);
    glPushMatrix ();
    glTranslatef (0., 0., 2.);//To translate a disk
    gluDisk (quad, 0., .25, 18, 1);//To create a disk
    glPopMatrix ();

    gluCylinder (quad, .25, .25, 2., 18, 8);//To create a cylinder

    glPushMatrix ();
    glScalef (1., 1., -1.);
    gluDisk (quad, 0., .25, 18, 1);
    glPopMatrix ();

	glPopMatrix();
}


static void displayc( void )
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 1., 7.,
               -1., 0., 0.,
               0., 1., 0.);
	glRotatef (-xrot*.35, 0., 1., 0.);

	/* Draw reflected scene first */

	glPushMatrix ();
	/* Mirrors lies in YZ plane, so scale by -1.0 in X axis */
	glScalef (-1., 1., 1.);
	/* Mirror is 2.0 units from origin, so translate by 4.0 */
	glTranslatef (4., 0., 0.);
    drawScenec(GL_CW);
	glPopMatrix ();

	/* draw mirror */
	glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib (0xffffffff);
	glDisable (GL_LIGHTING);
	/* Create imperfect reflector effect by blending a black
	   mirror over the reflected scene with alpha of 0.05 */
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f (0., 0., 0., 0.05);
	glBegin (GL_QUADS);
	glVertex3f (-2., 1., 3.);
	glVertex3f (-2., -1., 3.);
	glVertex3f (-2., -1., -2.5);
	glVertex3f (-2., 1., -2.5);
	glEnd ();
	glPopAttrib();

	/* Draw the real scene */
   drawScenec(GL_CCW);

    glutSwapBuffers();

	{
		int err = glGetError();
		if (err != GL_NO_ERROR)
			printf ("Error %x\n", err);
	}
}

static void initc ()
{
 
    
    xrot = 0.;

    glDisable (GL_DITHER);
    glEnable (GL_DEPTH_TEST);

    {
        GLfloat white[4] = {1., 1., 1., 1.};
        GLfloat black[4] = {0., 0., 0., 0.};

        /* Set up light1 */
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT1);
        glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv (GL_LIGHT1, GL_SPECULAR, white);

        /* ambient and diffuse will track glColor */
        glEnable (GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv (GL_FRONT, GL_SPECULAR, white);
		glMaterialf (GL_FRONT, GL_SHININESS, 20.);
    }


	quad = gluNewQuadric ();

    glutDisplayFunc (displayc); //Display callback function
    glutReshapeFunc (reshape);//Reshape callback function
    glutTimerFunc (TIMER, timer, 0);//Timer callback function
    
  
}
/*********************************************end of cylinder object************************/


/*********************************************sphere object***********************************/

void drawScenes(GLenum order)
{
    GLfloat pos[4] = {-2.8, 5., 1.8, 1.};

    glLightfv (GL_LIGHT1, GL_POSITION, pos);

	glPushMatrix();

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (order);

	/* Draw the walls */
    glColor3f (1., 1., 1.);
	glBegin(GL_QUADS);
	  glNormal3f (1., 0., 0.);
	    glVertex3f (-3., 3., 4.);
	    glVertex3f (-3., -3., 4.);
	    glVertex3f (-3., -3., -3.);
	    glVertex3f (-3., 3., -3.);
	  glNormal3f (0., 0., 1.);
		glVertex3f (-3., 3., -3.);
		glVertex3f (-3., -3., -3.);
		glVertex3f (3., -3., -3.);
		glVertex3f (3., 3., -3.);
	  glNormal3f (-1., 0., 0.);
		glVertex3f (3., 3., -3.);
		glVertex3f (3., -3., -3.);
		glVertex3f (3., -3., 3.);
		glVertex3f (3., 3., 3.);
	glEnd();
	glDisable (GL_CULL_FACE);

	/* Draw the sphere */
    glRotatef (xrot, 1., 0., 0.);
    glTranslatef (0., 0., 1.);

    glColor3f (1.5, .5, 1.);
 /*  glPushMatrix ();
    glTranslatef (0., 0., 2.);
    gluDisk (quad, 0., .25, 18, 1);
    glPopMatrix ();*/

  // gluCylinder (quad, 0.0, .25, 2., 18, 8);
    gluSphere (quadSphere, .5, 24, 12);

  /* glPushMatrix ();
  glScalef (1., 1., -1.);
   gluDisk (quad, 0., .25, 18, 1);
    glPopMatrix ();*/

	glPopMatrix();
}


static void displays( void )
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 1., 7.,
               -1., 0., 0.,
               0., 1., 0.);
	glRotatef (-xrot*.35, 0., 1., 0.);

	/* Draw reflected scene first */

	glPushMatrix ();
	/* Mirrors lies in YZ plane, so scale by -1.0 in X axis */
	glScalef (-1., 1., 1.);
	/* Mirror is 2.0 units from origin, so translate by 4.0 */
	glTranslatef (4., 0., 0.);
    drawScenes(GL_CW);
	glPopMatrix ();

	/* draw mirror */
	glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib (0xffffffff);
	glDisable (GL_LIGHTING);
	/* Create imperfect reflector effect by blending a black
	   mirror over the reflected scene with alpha of 0.05 */
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f (0., 0., 0., 0.05);
	glBegin (GL_QUADS);
	glVertex3f (-2., 1., 3.);
	glVertex3f (-2., -1., 3.);
	glVertex3f (-2., -1., -2.5);
	glVertex3f (-2., 1., -2.5);
	glEnd ();
	glPopAttrib();

	/* Draw the real scene */
   drawScenes(GL_CCW);

    glutSwapBuffers();

	{
		int err = glGetError();
		if (err != GL_NO_ERROR)
			printf ("Error %x\n", err);
	}
}



static void inits ()
{
 
    
    xrot = 0.;

    glDisable (GL_DITHER);
    glEnable (GL_DEPTH_TEST);

    {
        GLfloat white[4] = {1., 1., 1., 1.};
        GLfloat black[4] = {0., 0., 0., 0.};

        /* Set up light1 */
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT1);
        glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv (GL_LIGHT1, GL_SPECULAR, white);

        /* ambient and diffuse will track glColor */
        glEnable (GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv (GL_FRONT, GL_SPECULAR, white);
		glMaterialf (GL_FRONT, GL_SHININESS, 20.);
    }


	quad = gluNewQuadric ();
	 quadSphere = gluNewQuadric ();
    quadCyl = gluNewQuadric ();

    glutDisplayFunc (displays); 
    glutReshapeFunc (reshape);
    glutTimerFunc (TIMER, timer, 0);
    
  
}
/***********************************end of sphere object**************************/

/**********************************cone object********************/

void drawSceneco(GLenum order)
{
    GLfloat pos[4] = {-2.8, 5., 1.8, 1.};

    glLightfv (GL_LIGHT1, GL_POSITION, pos);

	glPushMatrix();

	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glFrontFace (order);

	/* Draw the walls */
    glColor3f (1., 1., 1.);
	glBegin(GL_QUADS);
	  glNormal3f (1., 0., 0.);
	    glVertex3f (-3., 3., 4.);
	    glVertex3f (-3., -3., 4.);
	    glVertex3f (-3., -3., -3.);
	    glVertex3f (-3., 3., -3.);
	  glNormal3f (0., 0., 1.);
		glVertex3f (-3., 3., -3.);
		glVertex3f (-3., -3., -3.);
		glVertex3f (3., -3., -3.);
		glVertex3f (3., 3., -3.);
	  glNormal3f (-1., 0., 0.);
		glVertex3f (3., 3., -3.);
		glVertex3f (3., -3., -3.);
		glVertex3f (3., -3., 3.);
		glVertex3f (3., 3., 3.);
	glEnd();
	glDisable (GL_CULL_FACE);

	/* Draw the cylinder */
    glRotatef (xrot, 1., 0., 0.);
    glTranslatef (0., 1., -1.);

	// glRotatef (-xrot, 0., 1., 0.);
    glColor3f (0.0, 0.5, 1.);
   /* glPushMatrix ();
    glTranslatef (0., 0., 2.);
    gluDisk (quadcone, 0., .25, 18, 1);
    glPopMatrix ();*/

    gluCylinder (quadcone, 0.0, .50, 2., 18, 8);

   /* glPushMatrix ();
    glScalef (1., 1., -1.);
    gluDisk (quadcone, 0., .25, 18, 1);
    glPopMatrix ();*/

	glPopMatrix();
}


static void displayco( void )
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity ();
    gluLookAt (0., 1., 7.,
               -1., 0., 0.,
               0., 1., 0.);
	glRotatef (-xrot*.35, 0., 1., 0.);

	/* Draw reflected scene first */

	glPushMatrix ();
	/* Mirrors lies in YZ plane, so scale by -1.0 in X axis */
	glScalef (-1., 1., 1.);
	/* Mirror is 2.0 units from origin, so translate by 4.0 */
	glTranslatef (4., 0., 0.);
    drawSceneco(GL_CW);
	glPopMatrix ();

	/* draw mirror */
	glClear (GL_DEPTH_BUFFER_BIT);
	glPushAttrib (0xffffffff);
	glDisable (GL_LIGHTING);
	/* Create imperfect reflector effect by blending a black
	   mirror over the reflected scene with alpha of 0.05 */
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f (0., 0., 0., 0.05);
	glBegin (GL_QUADS);
	glVertex3f (-2., 1., 3.);
	glVertex3f (-2., -1., 3.);
	glVertex3f (-2., -1., -2.5);
	glVertex3f (-2., 1., -2.5);
	glEnd ();
	glPopAttrib();

	/* Draw the real scene */
   drawSceneco(GL_CCW);

    glutSwapBuffers();

	{
		int err = glGetError();
		if (err != GL_NO_ERROR)
			printf ("Error %x\n", err);
	}
}

static void initco ()
{
 
    
    xrot = 0.;

    glDisable (GL_DITHER);
    glEnable (GL_DEPTH_TEST);

    {
        GLfloat white[4] = {1., 1., 1., 1.};
        GLfloat black[4] = {0., 0., 0., 0.};

        /* Set up light1 */
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT1);
        glLightfv (GL_LIGHT1, GL_DIFFUSE, white);
        glLightfv (GL_LIGHT1, GL_SPECULAR, white);

        /* ambient and diffuse will track glColor */
        glEnable (GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glMaterialfv (GL_FRONT, GL_SPECULAR, white);
		glMaterialf (GL_FRONT, GL_SHININESS, 20.);
    }


	quadcone = gluNewQuadric ();

    glutDisplayFunc (displayco); 
    glutReshapeFunc (reshape);
    glutTimerFunc (TIMER, timer, 0);
    
  
}

/****************************************end of cone object********************************/
void reshape(int w, int h)
{
    glViewport (0, 0, w, h);       
    glMatrixMode (GL_PROJECTION);  
    glLoadIdentity ();
    gluPerspective (50., (float)w/(float)h, 1., 20.);
}

 void cbMainMenu (int id)
{
  
    glClearColor(0.95,0.67,0.35,0.15);
    switch(id)
    {
    	case 1:
    		if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    		{
    		
    			glutInitWindowSize(500 , 500);
    				 //Set the window position
    				glutInitWindowPosition(0,0);//Create the window
    				glutCreateWindow("Mirror");
				//glClearColor(1.0,1.0,1.0,1.0);
    				 initc();
    				
    		}	// glutPostRedisplay();
    		           break;
    		
    	case 2:	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    		{
    		
    			glutInitWindowSize(500 , 500);
    				 //Set the window position
    				glutInitWindowPosition(0,0);//Create the window
    				glutCreateWindow("Camera Position");
				//glClearColor(1.0,1.0,1.0,1.0);
    				 inits();
    				  
   
    			
    		           break;
    		           }
    		           
    	case 3:
    				if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    		{
    		
    			glutInitWindowSize(500 , 500);
    				 //Set the window position
    				glutInitWindowPosition(0,0);//Create the window
    				glutCreateWindow("Camera Position");
				//glClearColor(1.0,1.0,1.0,1.0);
    				 initco();
    				  
       			
    		           break;
    		           }
    		
    	case 4:exit(0);
    		break;
    	}
    //	glClearColor(0.95,0.67,0.35,0.15); 
	glutPostRedisplay();
	
}


static void timer (int value)
{
    xrot += 1.f;
    if (xrot > 360.f) xrot -= 360.f;

    glutPostRedisplay ();
    glutTimerFunc (TIMER, timer, 0);
}

 
void display1(void)
{
    //select clearing (background) color
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0,0.0,1.0,1.0); //0.95,0.67,0.35,0.15
//    glColor3f(1.0,1.0,0.0);
    
	glFlush();
   }
int MenuFunctions()
{
	glutCreateMenu(cbMainMenu);//To create a menu
	glutAddMenuEntry("CYLINDER",1);
	glutAddMenuEntry("SPHERE",2);
	glutAddMenuEntry("CONE",3);
	glutAddMenuEntry("QUIT",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int  main(int argc, char** argv)
{
    glutInit (&argc,argv);
    glutInitDisplayMode (GLUT_DOUBLE| GLUT_DEPTH); 
    glutInitWindowSize (500,500);
    glutInitWindowPosition (0,0); 
    glutCreateWindow ("simulation");
        glutDisplayFunc(display1);
        MenuFunctions();  
        glutMainLoop ();
      return 0;
      
}

