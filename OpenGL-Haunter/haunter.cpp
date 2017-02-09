#include <GL\glut.h>
#include <string>
#include <fstream>
#include <math.h>
#include "haunter.hpp"

using namespace haunter;

void ForceField::draw()
{
    glPointSize(1.0);
    srand(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    GLfloat x,y,z;
    glBegin(GL_POINTS);
    for (int i=0; i<1000; ++i)
    {
    x = (rand()%10000)/10000.0 * 80.0 - 40.0;
    y = (rand()%10000)/10000.0 * 80.0 - 30.0;
    z = (rand()%10000)/10000.0 * 80.0 - 40.0;
    glVertex3f(x,y,z);
    }
    glEnd();
}

void GrassField::draw()
{
    glPushMatrix();
    for(int i=0;i<3600;i++)
    {
    glBegin(GL_TRIANGLES);
    glColor3f(0.0,1.0,0.0);
	glVertex3f(0.0,-35.0,0.0);
	glVertex3f(20.0,-35,-25.0);
	glVertex3f(-20.0,-35,-25.0);
	glEnd();
    glRotatef(0.1f, 0.0f, 1.0f,0.0f);
    }
    glPopMatrix();
}

void Moon::draw()
{
    glPushMatrix();
    glDisable(GL_CULL_FACE);
    glColor3f(1.0,1.0,0.0);
    glTranslatef(-40.0,60.0,0.0);

    //set up color
    static GLfloat mywhite[]  = { 0.3f, 0.3f, 0.3f, 1.0f };
    //set up spotlight
    glLightfv(GL_LIGHT3, GL_AMBIENT, mywhite);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, mywhite);
    glLightfv(GL_LIGHT3, GL_SPECULAR, mywhite);
    glLightf (GL_LIGHT3, GL_SPOT_CUTOFF, 35);
    glLightf (GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
    glLightf (GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.04);
    glEnable(GL_LIGHT3);
    //set up position
    static GLfloat position[] = {-40.0f, 60.0f, 0.0f, 1.0f };
    //draw object
    glutSolidSphere(7,50,50);   //Display Moon as a solid object
    glLightfv(GL_LIGHT1, GL_POSITION, position);

    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

void HaunterFace::drawFace()
{
    glDisable(GL_CULL_FACE);

    const float Deg2Rad = 3.14159/180 ;// convert degree into Rad

    glColor3f(0.5,0.0,0.75);
    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle( sphere, GLU_FILL);
    gluQuadricNormals( sphere, GLU_SMOOTH);
    gluQuadricOrientation( sphere, GLU_OUTSIDE);
    gluQuadricTexture( sphere, GL_TRUE);
    gluSphere( sphere, 12, 16, 16);

	//Try to use pytamid for the bottom spike
	glBegin(GL_POLYGON);
	glPolygonMode(GL_FRONT,GL_FILL);

	glBegin(GL_TRIANGLES);
	//glColor3f(1.0,1.0,0.0); //this is for testing usage
	//Left top spike
	glVertex3f(-5,8,7);
	glVertex3f(-20,15,-8);
	glVertex3f(-10,0,7);

	//left middle spike
	glVertex3f(-8,1,8);
	glVertex3f(-20,4,-10);
	glVertex3f(-7,-7,6);

    //left bottom spike
	glVertex3f(-8, -4, 5);
	glVertex3f(-16, -3, -5);
	glVertex3f(-8, -8, 4);

	//Start of right spike
	//right top spike
	glVertex3f(5,8,7);
	glVertex3f(20,15,-8);
	glVertex3f(10,0,7);

	//right middle spike
	glVertex3f(8,1,8);
	glVertex3f(20,4,-10);
	glVertex3f(7,-7,6);

    //right bottom spike
	glVertex3f(8, -4, 5);
	glVertex3f(16, -3, -5);
	glVertex3f(8, -8, 4);

	//Start of bottom spike
	//Bottom left spike 1
   // glColor3f(1,1,1); //color for testing

	//Bottom left spike 2
    glVertex3f(-6,-9,5);
    glVertex3f(-2,-20,-5);
    glVertex3f(-2,-10,5);
	//Bottom Middle spike
    glVertex3f(-2,-10,6);
    glVertex3f(0,-25,-8);
    glVertex3f(2,-10,6);

	//Bottom right spike 2
    glVertex3f(6,-9,5);
    glVertex3f(2,-20,-5);
    glVertex3f(2,-10,5);
	glEnd();
    glEnable(GL_CULL_FACE);
}

void HaunterFace::drawLeftEyes()
{
    //I left it first
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex3f(-2,0,12);
    glVertex3f(-9,6,9);
    glVertex3f(-10,0,9);
    glEnd();
}

void HaunterFace::drawRightEyes()
{
    glDisable(GL_CULL_FACE);

    glBegin(GL_TRIANGLES);
    glPolygonMode(GL_FRONT,GL_FILL);
    glVertex3f(2,0,12);
    glVertex3f(9,6,9);
    glVertex3f(10,0,9);
    glEnd();
    glEnable(GL_CULL_FACE);
}

void HaunterFace::drawMouth()
{
    //will draw later
    glDisable(GL_CULL_FACE);

    glBegin(GL_POLYGON);
    glPolygonMode(GL_FRONT,GL_FILL);

    glEnd();
    glEnable(GL_CULL_FACE);
}

void Haunter_Hand::draw()
{
    //will draw later

}
