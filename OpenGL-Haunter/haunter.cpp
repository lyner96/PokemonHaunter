#include <GL\glut.h>
#include <string>
#include <fstream>
#include <math.h>
#include "haunter.hpp"

using namespace haunter;

Haunter_Hand::Haunter_Hand()
{
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
}

Haunter_Hand::~Haunter_Hand()
{
    gluDeleteQuadric(pObj);
}

void ForceField::draw()
{
    glPointSize(1.0);
    srand(1);
    glColor3f(1.0f, 1.0f, 1.0f);
    GLfloat x, y, z;
    glBegin(GL_POINTS);
    for (int i = 0; i < 1000; ++i)
    {
        x = (rand() % 10000) / 10000.0 * 80.0 - 40.0;
        y = (rand() % 10000) / 10000.0 * 80.0 - 30.0;
        z = (rand() % 10000) / 10000.0 * 80.0 - 40.0;
        glVertex3f(x, y, z);
    }
    glEnd();
}

void GrassField::draw()
{
    glPushMatrix();
    for(int i = 0; i < 3600; i++)
    {
        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -35.0, 0.0);
        glVertex3f(20.0, -35, -25.0);
        glVertex3f(-20.0, -35, -25.0);
        glEnd();
        glRotatef(0.1f, 0.0f, 1.0f, 0.0f);
    }
    glPopMatrix();
}

void Moon::draw()
{
    glPushMatrix();
    glDisable(GL_CULL_FACE);
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(-40.0, 60.0, 0.0);

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
    glutSolidSphere(7, 50, 50);   //Display Moon as a solid object
    glLightfv(GL_LIGHT1, GL_POSITION, position);

    glEnable(GL_CULL_FACE);
    glPopMatrix();
}

void bezierSurface::setup(const GLfloat* controlPoints, GLint uOrder, GLint vOrder, const bool autonormal)
{
    controlpoints = controlPoints;
    uorder = uOrder;
    vorder = vOrder;
    //setup the bezier
    glMap2f(GL_MAP2_VERTEX_3, //to be generated data, surface vertex
    0.0f, //lower u range
    1.0f, //higher u range
    3, //u control point stride in array
    uorder, //order of u or number of u control point
    0.0f, //lower v range
    1.0f, //higher v range
    3 * uorder, //v control point stride in array
    vorder, //order of v or number of v control point
    controlpoints); //the control points array
    //enabling bezier evaluator
    glEnable(GL_MAP2_VERTEX_3);
    //enabling auto generation of normals for use with lighting
    if (autonormal)
        glEnable(GL_AUTO_NORMAL);

}

void bezierSurface::drawControlPoints()
{
    //draw the control points
    int index = 0;
    for(int j = 0; j < vorder; ++j)
    {
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < uorder; ++i)
        {
            glVertex3fv(controlpoints + index );
            index += 3;
        }
        glEnd();
    }
    for(int i = 0; i < uorder; ++i)
    {
        index = 3 * i;
        glBegin(GL_LINE_STRIP);
        for(int j = 0; j < vorder; ++j)
        {
            glVertex3fv(controlpoints + index );
            index += uorder*3;
        }
        glEnd();
    }
}

void bezierSurface::init(int num)
{
    //Pink Mouth
    static GLfloat controlpoints1[] =
    {
        -9.0f,-3.0f, 6.8f,
        -6.0f, -4.0f, 13.15f,
        6.0f, -4.0f, 13.15f,
        9.0f,-3.0f, 6.8f,


        -6.0f,-5.0f, 9.0f,
        -6.0f, -8.0f, 9.9f,
        6.0f, -8.0f, 9.9f,
        6.0f,-5.0f, 9.0f,
    };

    //Top first left teeth
    static GLfloat controlpoints2[] =
    {
        -5.7f,-5.0f, 9.57f, // Lower
        -7.0f, -3.39f, 9.35f, // Top left

        -5.0f,-3.58f, 10.57f, // Top right
        -6.2f, -3.46f, 9.98f, // top center
    };

    //Top first right teeth
    static GLfloat controlpoints3[] =
    {
        5.7f, -5.0f, 9.57f, // Lower
        7.0f, -3.39f, 9.35f, // Top right

        5.0f, -3.58f, 10.57f, // Top left
        6.2f, -3.46f, 9.98f, // top center
    };

    //Top second left teeth
    static GLfloat controlpoints4[] =
    {
        -2.3f, -5.13f, 10.67f, // Lower
        -3.5f, -3.67f, 11.13f, // Top left

        -1.5f, -3.73f, 11.5f, // Top right
        -2.7f, -3.69f, 11.33f, // top center
    };

    //Top second right teeth
    static GLfloat controlpoints5[] =
    {
        2.3f, -5.13f, 10.67f, // Lower
        3.5f, -3.67f, 11.13f, // Top right

        1.5f, -3.73f, 11.5f, // Top left
        2.7f, -3.69f, 11.33f, // top center
    };

    //Bottom right first teeth
    static GLfloat controlpoints6[] =
    {
        4.6f, -5.5f, 9.85f, // Higher
        5.55f, -6.0f, 9.3f, // Bottom right

        4.0f, -6.76f, 9.52f, // Bottom left
        4.9f, -6.45f, 9.45f, // Bottom center
    };

    //Bottom right second teeth
    static GLfloat controlpoints7[] =
    {
        3.1f, -5.8f, 10.15f, // Higher
        4.0f, -6.75f, 9.52f, // Bottom right

        2.3f, -7.13f, 9.66f, // Bottom left
        3.3f, -6.95f, 9.57f, // Bottom center
    };

    //Bottom right third teeth
    static GLfloat controlpoints8[] =
    {
        1.4f, -6.2f, 10.2f, // Higher
        2.3f, -7.13f, 9.64f, // Bottom right

        0.6f, -7.28f, 9.68f, // Bottom left
        1.4f, -7.24f, 9.66f, // Bottom center
    };

    //Bottom right fourth teeth
    static GLfloat controlpoints9[] =
    {
        -0.52f, -6.0f, 10.37f, // Higher
        0.6f, -7.28f, 9.7f, // Bottom right

        -1.55f, -7.22f, 9.67f, // Bottom left
        -0.5f, -7.29f, 9.67f, // Bottom center
    };

    //Bottom right fifth teeth
    static GLfloat controlpoints10[] =
    {
        -2.72f, -6.0f, 10.16f, // Higher
        -1.55f, -7.22f, 9.65f, // Bottom right

        -4.1f, -6.74f, 9.52f, // Bottom left
        -2.82f, -7.03f, 9.62f, // Bottom center
    };

    bezierSurface bso;
    HaunterFace hfo;

    switch (num)
    {
        case 1:
            bso.setup(controlpoints1, 4, 2);
            glColor3f(1,0.41,0.71);
            hfo.drawMouth(GL_FILL);
            break;
        case 2:
            bso.setup(controlpoints2, 2, 2);
            glColor3f(0.5,0.0,0.75);
            hfo.drawMouth(GL_FILL);
            break;
        case 3:
            bso.setup(controlpoints3, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 4:
            bso.setup(controlpoints4, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 5:
            bso.setup(controlpoints5, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 6:
            bso.setup(controlpoints6, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 7:
            bso.setup(controlpoints7, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 8:
            bso.setup(controlpoints8, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 9:
            bso.setup(controlpoints9, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
        case 10:
            bso.setup(controlpoints10, 2, 2);
            hfo.drawMouth(GL_FILL);
            break;
    }
}

void HaunterFace::drawFace()
{
    glDisable(GL_CULL_FACE);

    const float Deg2Rad = 3.14159/180 ;// convert degree into Rad

    glColor3f(0.5, 0.0, 0.75);
    //glColor3f(1, 0.0, 0.0);
    GLUquadricObj *sphere;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricOrientation(sphere, GLU_OUTSIDE);
    gluQuadricTexture(sphere, GL_TRUE);
    gluSphere(sphere, 12, 16, 16);

	//Try to use pytamid for the bottom spike
	glBegin(GL_POLYGON);
	glPolygonMode(GL_FRONT,GL_FILL);

	glBegin(GL_TRIANGLES);
	//glColor3f(1.0,1.0,0.0); //this is for testing usage
	glColor3f(0.48, 0.0, 0.72);
	//Left top spike
	glVertex3f(-5, 8, 7);
	glVertex3f(-20, 15, -8);
	glVertex3f(-10, 0, 7);

	//left middle spike
	glVertex3f(-8, 1, 8);
	glVertex3f(-20, 4, -10);
	glVertex3f(-7, -7, 6);

    //left bottom spike
	glVertex3f(-8, -4, 5);
	glVertex3f(-16, -3, -5);
	glVertex3f(-8, -8, 4);

	//Start of right spike
	//right top spike
	glVertex3f(5, 8, 7);
	glVertex3f(20, 15, -8);
	glVertex3f(10, 0, 7);

	//right middle spike
	glVertex3f(8, 1, 8);
	glVertex3f(20, 4, -10);
	glVertex3f(7, -7, 6);

    //right bottom spike
	glVertex3f(8, -4, 5);
	glVertex3f(16, -3, -5);
	glVertex3f(8, -8, 4);

	//Start of bottom spike
	//Bottom left spike 1

	//Bottom left spike 2
    glVertex3f(-6, -9, 5);
    glVertex3f(-2, -20, -5);
    glVertex3f(-2, -10, 5);
	//Bottom Middle spike
    glVertex3f(-2,-10,6);
    glVertex3f(0,-25,-8);
    glVertex3f(2,-10,6);

	//Bottom right spike 2
    glVertex3f(6, -9, 5);
    glVertex3f(2, -20, -5);
    glVertex3f(2, -10, 5);
	glEnd();
    glEnable(GL_CULL_FACE);
}

void HaunterFace::drawLeftEyes()
{
    glDisable(GL_CULL_FACE);
    //I left it first
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex3f(-2, 0, 12);
    glVertex3f(-9, 6, 9);
    glVertex3f(-10, 0, 9);
    glEnd();
    glEnable(GL_CULL_FACE);
}

void HaunterFace::drawRightEyes()
{
    glDisable(GL_CULL_FACE);

    glBegin(GL_TRIANGLES);
    glPolygonMode(GL_FRONT,GL_FILL);
    glVertex3f(2, 0, 12);
    glVertex3f(9, 6, 9);
    glVertex3f(10, 0, 9);
    glEnd();
    glEnable(GL_CULL_FACE);
}

void HaunterFace::drawMouth(GLenum draw_mode, GLint ures,GLint vres)
{
    glDisable(GL_CULL_FACE);
    //setting the 2D grid map containing ures * vres points
    //map to u range 0.0 - 1.0, v range 0.0 - 1.0
    glMapGrid2f(ures, 0.0f, 1.0f, vres, 0.0f, 1.0f);
    //evaluate the bezier surface
    glEvalMesh2(draw_mode, 0, ures, 0, vres);
    glEnable(GL_CULL_FACE);
}

void Haunter_Hand::draw()
{
    glDisable(GL_CULL_FACE);

    glColor3f(0.47, 0.0, 0.72);

    //Left fingernails
    glPushMatrix();
    glTranslatef(-14.0f, -8.0f, 14.5f);
    glRotatef(105.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.0f, 1.1f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.0f, -8.0f, 13.0f);
    glRotatef(115.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.0f, 1.1f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.0f, -8.0f, 12.0f);
    glRotatef(125.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.0f, 1.0f, 26, 13);
    glPopMatrix();

    //Right fingernails
    glPushMatrix();
    glTranslatef(14.0f, -8.0f, 15.0f);
    glRotatef(110.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.0f, 1.1f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0f, -6.5f, 15.0f);
    glRotatef(15.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.0f, 1.1f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.0f, -8.0f, 15.05f);
    glRotatef(95.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.0f, 1.0f, 26, 13);
    glPopMatrix();

    //Left section after fingernail
    //Left center
    glPushMatrix();
    glTranslatef(-14.0f, -7.54f, 14.5f);
    glRotatef(90.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.5f, 0.6f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.0f, -6.6f, 13.2f);
    glRotatef(40.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.7f, 0.4f, 1.9f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-14.0f, -6.25f, 10.3f);
    glRotatef(10.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.8f, 0.7f, 3.2f, 26, 13);
    glPopMatrix();

    //Left right
    glPushMatrix();
    glTranslatef(-12.0f, -7.54f, 13.0f);
    glRotatef(90.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.5f, 0.6f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.0f, -6.6f, 11.7f);
    glRotatef(40.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.7f, 0.4f, 1.9f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-12.0f, -6.4f, 9.9f);
    glRotatef(10.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.8f, 0.7f, 2.1f, 26, 13);
    glPopMatrix();

    //Left left
    glPushMatrix();
    glTranslatef(-16.0f, -7.6f, 12.1f);
    glRotatef(95.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.4f, 0.6f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.0f, -6.8f, 11.4f);
    glRotatef(50.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.7f, 0.4f, 1.4f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-16.0f, -6.75f, 10.2f);
    glRotatef(10.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.8f, 0.6f, 1.7f, 26, 13);
    glPopMatrix();

    //Right section after fingernail
    //Right center
    glPushMatrix();
    glTranslatef(14.0f, -7.55f, 15.05f);
    glRotatef(95.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.5f, 0.6f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.0f, -6.5f, 13.88f);
    glRotatef(45.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.7f, 0.4f, 1.9f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(14.0f, -5.95f, 11.1f);
    glRotatef(15.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.8f, 0.6f, 3.3f, 26, 13);
    glPopMatrix();

    //Right left
    glPushMatrix();
    glTranslatef(13.0f, -6.4f, 14.5f);
    glRotatef(10.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.5f, 0.6f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0f, -6.2f, 13.5f);
    glRotatef(5.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.7f, 0.4f, 1.4f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(13.0f, -6.3f, 11.2f);
    glRotatef(0.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.8f, 0.65f, 2.8f, 26, 13);
    glPopMatrix();

    //Right right
    glPushMatrix();
    glTranslatef(16.0f, -7.55f, 15.1f);
    glRotatef(95.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.5f, 0.5f, 0.6f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.0f, -6.5f, 13.93f);
    glRotatef(45.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.7f, 0.4f, 1.9f, 26, 13);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.0f, -6.5f, 11.15f);
    glRotatef(5.0f, 9.0f, 0.0f, 0.0f);
    gluCylinder(pObj, 0.8f, 0.6f, 3.3f, 26, 13);
    glPopMatrix();

    //Left Palm - 4 surface
    float topboty, topbotx, topbotx1, zaxis, zaxis2;
    float lengthdif, widthdif, heightdif,  //Length(Z), Height(y) and Width(X) difference

    glDisable(GL_CULL_FACE);
    glBegin(GL_POLYGON);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.47, 0.0, 0.72);

    topbotx = -11.1;
    topbotx1 = -16.8;
    topboty = -5.5;
    zaxis = 10.5;

    lengthdif = 4;
    widthdif = 1.2;
    heightdif = 1.8;
    zaxis2 = zaxis - lengthdif;

    //top
    glVertex3f(topbotx1 + widthdif, topboty, zaxis2);
    glVertex3f(topbotx - widthdif, topboty, zaxis2);
    glVertex3f(topbotx, topboty, zaxis);
    glVertex3f(topbotx1, topboty, zaxis);

    glEnd();
    glBegin(GL_POLYGON);
    //bottom
    glVertex3f(topbotx1 + widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx - widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx, topboty - heightdif, zaxis);
    glVertex3f(topbotx1, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //left
    glVertex3f(topbotx1 + widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx1 + widthdif, topboty, zaxis2);
    glVertex3f(topbotx1, topboty, zaxis);
    glVertex3f(topbotx1, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //right
    glVertex3f(topbotx - widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx - widthdif, topboty, zaxis2);
    glVertex3f(topbotx, topboty, zaxis);
    glVertex3f(topbotx, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //front
    glVertex3f(topbotx1, topboty, zaxis);
    glVertex3f(topbotx, topboty, zaxis);
    glVertex3f(topbotx, topboty - heightdif, zaxis);
    glVertex3f(topbotx1, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //back
    glVertex3f(topbotx - widthdif, topboty, zaxis2);
    glVertex3f(topbotx1 + widthdif, topboty, zaxis2);
    glVertex3f(topbotx1 + widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx - widthdif, topboty - heightdif, zaxis2);

    glEnd();

    //Right Palm
    glBegin(GL_POLYGON);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3f(0.47, 0.0, 0.72);

    topbotx = 12.2;
    topbotx1 = 17.0;
    topboty = -5.5;
    zaxis = 11.5;

    lengthdif = 4;
    widthdif = -1;
    heightdif = 1.8;
    zaxis2 = zaxis - lengthdif;

    //top
    glVertex3f(topbotx1 + widthdif, topboty, zaxis2);
    glVertex3f(topbotx - widthdif, topboty, zaxis2);
    glVertex3f(topbotx, topboty, zaxis);
    glVertex3f(topbotx1, topboty, zaxis);

    glEnd();
    glBegin(GL_POLYGON);
    //bottom
    glVertex3f(topbotx1 + widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx - widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx, topboty - heightdif, zaxis);
    glVertex3f(topbotx1, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //left
    glVertex3f(topbotx1 + widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx1 + widthdif, topboty, zaxis2);
    glVertex3f(topbotx1, topboty, zaxis);
    glVertex3f(topbotx1, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //right
    glVertex3f(topbotx - widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx - widthdif, topboty, zaxis2);
    glVertex3f(topbotx, topboty, zaxis);
    glVertex3f(topbotx, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //front
    glVertex3f(topbotx1, topboty, zaxis);
    glVertex3f(topbotx, topboty, zaxis);
    glVertex3f(topbotx, topboty - heightdif, zaxis);
    glVertex3f(topbotx1, topboty - heightdif, zaxis);

    glEnd();
    glBegin(GL_POLYGON);

    //back
    glVertex3f(topbotx - widthdif, topboty, zaxis2);
    glVertex3f(topbotx1 + widthdif, topboty, zaxis2);
    glVertex3f(topbotx1 + widthdif, topboty - heightdif, zaxis2);
    glVertex3f(topbotx - widthdif, topboty - heightdif, zaxis2);

    glEnd();
    glEnable(GL_CULL_FACE);
}
