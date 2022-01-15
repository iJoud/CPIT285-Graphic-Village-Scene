// the main reasone of include iostream, windows.h and MMSystem.h labraries to for playing sound
#include <iostream>
#include <windows.h>
#include <MMSystem.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define PI 3.1416
// day and night variables to control display mode wither during the day or the night
#define DAY 1
#define NIGHT 2
//for controling house chimney smoke
GLfloat SmokeUp = 0;

// boolean variable to control displaying the interface
bool ShowInterface = true;

// i variable for circle raduis,  
GLint i, j, k;
GLfloat sun_spin = 0, sun_x = 0, sun_y = 0;
GLfloat ax = 0, bx = 0, cx = 0, dx = 0, str = 500.0, mn = 500.0;
GLfloat sr = 0.0f, sg = 0.749f, sb = 1.0f;
GLfloat spin = 0.0;
float zoom = 1.f;
int cam_x = 0, cam_y = 0;
int star_angle = 0;
bool night = false;



GLfloat ambient_light[4] =
{
    1, 1, 1, 1.0
};

void init(void)
{
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
}


///============================================================================================================///
///============================================================================================================///

void drawText(float x, float y, std::string text)
{
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)text.c_str());
}

void drawInterface()
{
    glPushMatrix();
    glClearColor(1.f, 1.f, 1.f, 1.f);
    drawText(400.f, 290.f, "         Village Scene Project\n      For: Dr. Suaad Baawidan\n\n By: Alanoud, Jood \n\n\n          Press 'L' to start!");
    glPopMatrix();
}

///=================///
///*** All_Model ***///
///=================///

void star(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(star_angle, 1, 1, 1);
    glColor3f(1, 1, 1);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(3, 10, 32, 32);
    glRotatef(-180, 0, 1, 0);
    glutSolidCone(3, 10, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(star_angle, 1, 1, 1);
    glColor3f(1, 1, 1);
    glRotatef(90, 1, 0, 0);
    glutSolidCone(3, 10, 32, 32);
    glRotatef(-180, 1, 0, 0);
    glutSolidCone(3, 10, 32, 32);
    glPopMatrix();
}

// Moon
void Moon_Model() {
    glPushMatrix();
    glColor3f(1.25, 0.924, 0.930);
    glTranslatef(900, 430, -16);
    glutSolidSphere(48, 32, 32);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.2, 0.30588, 0.50196);
    glTranslatef(880, 440, -16);
    glutSolidSphere(40, 32, 32);
    glPopMatrix();

}



/// *** Sun_Model **///
void Sun_Model() {
    glPushMatrix();
    glTranslatef(500, 0, -16);
    glutSolidSphere(30, 32, 32);
    glPopMatrix();

}
void Moving_Sun_Model() {
    glPushMatrix();
    glRotatef(-sun_spin, 0, 0, -.009);
    Sun_Model();
    glPopMatrix();

}



// drawing airplane model 
void Airplane_Model()
{
    // static because we need the value between frames
    static float xx = -500;
    float y = 400;
    xx += 4;
    if (xx >= 500) xx = -500;
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);

    // drawing the maing part of the airplane
    glLoadIdentity();
    glTranslatef(500 + xx, y, 0);
    glRotatef(90, 0, 0, 1);
    glScalef(5, 30, 10);
    glutSolidSphere(3, 20, 20);

    // drawing black windows
    glColor3f(0.f, 0.f, 0.f);
    for (int x = -30; x <= 30; x += 30)
    {
        glLoadIdentity();
        glTranslatef(500 + x + xx, y + 7, 0);
        glScalef(20, 10, 10);
        glutSolidCube(1);
    }
    // drawing black window (the big one)
    glLoadIdentity();
    glTranslatef(500 + 60 + xx, y + 2, 0);
    glScalef(24, 14, 14);
    glutSolidCube(1);

    glColor3f(0.5f, 0.5f, 0.5f);
    glLoadIdentity();
    glTranslatef(500 + xx, y - 4, 0);
    glScalef(40, 20, 60);

    // wings
    glBegin(GL_TRIANGLES);
    glVertex3f(-1, 0, -0);
    glVertex3f(1, 0, -0);
    glVertex3f(2, -1, 2);

    glVertex3f(-2, 0.6f, -0);
    glVertex3f(-1, 1.0f, -0);
    glVertex3f(-2.5, 1.5, 0);
    glEnd();


    glPopMatrix();

}

///*** Circle_Model***///
void circle(GLdouble rad)
{
    GLint points = 50;
    GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
    GLdouble theta = 0.0;

    glBegin(GL_POLYGON);
    {
        for (i = 0; i <= 50; i++, theta += delTheta)
        {
            glVertex2f(rad * cos(theta), rad * sin(theta));
        }
    }
    glEnd();
}



///*** Lamp ***///
void lamp_stand(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90, 1, 0, 0);
    GLUquadricObj* quadratic;
    quadratic = gluNewQuadric();
    glColor3f(0.7f, 0.7f, 0.7f);
    gluCylinder(quadratic, 3, 6, 128, 32, 32);
    glPopMatrix();
}

void lamp(GLfloat x, GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1, 1, 0);
    glutSolidSphere(16, 32, 32);
    glPopMatrix();
}







// Our House 
void HOUSE() {




    glPushMatrix();
    glScalef(1.1, 1.1, 1.1);
    glTranslatef(166, 80, 0);

    ///////////////////////
    //small house
    glPushMatrix();
    glTranslatef(-5, 34, 0);
    glScalef(.6, .6, .6);
    // house skelton
    glColor3f(.898, .7333, .349);
    glRectf(204, 90, 394, 204);
    glColor3f(1, .796, .2235);
    glRectf(210, 90, 388, 204);
    // house yellow roof
    glColor3f(1, .796, .2235);
    glBegin(GL_POLYGON);
    {
        glVertex2f(210, 204);
        glVertex2f(390, 204);
        glVertex2f(298, 290);
    }
    glEnd();

    // house red roof

    glPushMatrix(); {

        glTranslatef(-30, -32, 0);
        glScalef(1.1, 1.1, 1.1);
        glLineWidth(200);
        glColor3f(.796, .2705, .2235);
        glBegin(GL_LINES);
        glVertex2f(298, 290);
        glVertex2f(192, 200);
        glVertex2f(406, 200);
        glVertex2f(298, 290);
        glEnd();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 10, 0);

        glColor3f(.905, .26, .2156);
        glLineWidth(160);
        glBegin(GL_LINES);
        glVertex2f(298, 290);
        glVertex2f(192, 200);
        glVertex2f(406, 200);
        glVertex2f(298, 290);
        glEnd();

        glPopMatrix();

        glPushMatrix();
        {
            glTranslatef(-223, -81, 0);
            glScalef(1.5, 1.5, 1.5);
            //left window
            glColor3f(.898, .7333, .349);
            glRectf(366, 198, 324, 142);
            // inner withe window 
            glColor3f(1, 1, 1);
            glRectf(364, 196, 326, 144);
            // inner blue window
            glPushMatrix();
            glTranslatef(0, -1, 0);
            glColor3f(.2823, .78, .94);
            glRectf(328, 146, 344, 161);
            glRectf(362, 146, 346, 161);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0, 16, 0);
            glRectf(328, 146, 344, 161);
            glRectf(362, 146, 346, 161);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0, 33, 0);
            glRectf(328, 146, 344, 161);
            glRectf(362, 146, 346, 161);
            glPopMatrix();

            glPushMatrix();
            glTranslatef(7, 6, 0);
            glColor3f(.4352, .3176, .286);
            glRectf(316, 134, 360, 144);

            glColor3f(.478, .4, .2784);
            glRectf(318, 136, 358, 142);

            glPopMatrix();

        }glPopMatrix();

    }glPopMatrix();
    /////////////////////




    // translating chimney smoke
    glPushMatrix();
    glTranslatef(0, SmokeUp, 0);
    glPushMatrix();
    glTranslatef(370, 330, 0);
    glColor3f(.7, .7, .7);
    circle(15);
    glTranslatef(-20, -10, 0);
    glColor3f(.7, .7, .7);
    circle(15);
    glTranslatef(0, 27, 0);
    glColor3f(.7, .7, .7);
    circle(15);
    glTranslatef(18, 12, 0);
    glColor3f(.7, .7, .7);
    circle(15);
    glPopMatrix();
    glPopMatrix();



    //House chimney 
    glColor3f(1, .696, .1);
    glRectf(340, 220, 380, 300);
    glColor3f(.796, .2705, .2235);
    glRectf(330, 290, 390, 310 - 5);
    glColor3f(.905, .26, .2156);
    glRectf(333, 292, 390 - 2, 310 - 2 - 5);

    glColor3f(1, .796, .2235);

    glBegin(GL_POLYGON);
    {
        glVertex2f(400 + 10, 210);
        glVertex2f(396 - 10, 200);
        glVertex2f(396 - 10, 85);
        glVertex2f(400 + 10, 110);
    }    glEnd();


    // house skelton
    glColor3f(.898, .7333, .349);
    glRectf(204, 90, 394, 204);
    glColor3f(1, .796, .2235);
    glRectf(210, 90, 388, 204);
    // house yellow roof
    glColor3f(1, .796, .2235);
    glBegin(GL_POLYGON);
    {
        glVertex2f(210, 204);
        glVertex2f(390, 204);
        glVertex2f(298, 290);
    }
    glEnd();

    // house red roof

    glPushMatrix();
    glTranslatef(-30, -32, 0);
    glScalef(1.1, 1.1, 1.1);
    glLineWidth(200);
    glColor3f(.796, .2705, .2235);
    glBegin(GL_LINES);
    glVertex2f(298, 290);
    glVertex2f(192, 200);
    glVertex2f(406, 200);
    glVertex2f(298, 290);
    glEnd();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 10, 0);

    glColor3f(.905, .26, .2156);
    glLineWidth(160);
    glBegin(GL_LINES);
    glVertex2f(298, 290);
    glVertex2f(192, 200);
    glVertex2f(406, 200);
    glVertex2f(298, 290);
    glEnd();

    glPopMatrix();



    // upper window
    glColor3f(.898, .7333, .349);
    glRectf(320, 250, 274, 212);
    // inner withe window 
    glColor3f(1, 1, 1);
    glRectf(318, 248, 276, 214);
    // inner blue window
    glColor3f(.2823, .78, .94);
    glRectf(278, 246, 296, 232);
    glRectf(278, 216, 296, 230);
    glRectf(298, 232, 316, 246);
    glRectf(298, 230, 316, 216);

    //left window
    glColor3f(.898, .7333, .349);
    glRectf(366, 198, 324, 142);
    // inner withe window 
    glColor3f(1, 1, 1);
    glRectf(364, 196, 326, 144);
    // inner blue window
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glColor3f(.2823, .78, .94);
    glRectf(328, 146, 344, 161);
    glRectf(362, 146, 346, 161);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 16, 0);
    glRectf(328, 146, 344, 161);
    glRectf(362, 146, 346, 161);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 33, 0);
    glRectf(328, 146, 344, 161);
    glRectf(362, 146, 346, 161);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, 6, 0);
    glColor3f(.4352, .3176, .286);
    glRectf(316, 134, 360, 144);

    glColor3f(.478, .4, .2784);
    glRectf(318, 136, 358, 142);

    glPopMatrix();

    glColor3f(.7, .7, .7);
    glRectf(220, 90, 312, 102);
    glRectf(226, 100, 306, 112);
    glColor3f(.6, .6, .6);
    glRectf(222, 92, 310, 100);
    glRectf(228, 102, 304, 110);


    // the door
    glColor3f(.796, .2705, .2235);
    glRectf(232, 112, 298, 202);

    glColor3f(.905, .36, .2156);
    glRectf(232 + 3, 112 + 3, 298 - 3, 202 - 3);


    glPushMatrix();
    glTranslatef(-2, 0, 0);
    glColor3f(.9, .25, .235);
    glRectf(244, 118, 290, 154);
    glTranslatef(0, 40, 0);
    glRectf(244, 118, 290, 154);
    glPopMatrix();

    glColor3f(.796, .2705, .2235);
    glPointSize(28);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glVertex2f(284, 156);
    glEnd();

    glColor3f(.9, 1, 0.2);
    glPointSize(10);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glVertex2f(284, 156);
    glEnd();

    glPopMatrix();




}
///*** Cloud_Model***///
void cloud_model_one() {

    glColor3f(1.25, 0.924, 0.930);

    ///Top_Left

    glPushMatrix();
    glTranslatef(320, 210, 0);
    circle(15);
    glPopMatrix();

    ///Top

    glPushMatrix();
    glTranslatef(340, 225, 0);
    circle(16);
    glPopMatrix();

    ///Right

    glPushMatrix();
    glTranslatef(360, 210, 0);
    circle(16);
    glPopMatrix();


    ///middle_Fill
    glPushMatrix();
    glTranslatef(355, 210, 0);
    circle(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(350, 210, 0);
    circle(16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(345, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(340, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(335, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(330, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(325, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(320, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(315, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(310, 204, 0);
    circle(10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(305, 204, 0);
    circle(10);
    glPopMatrix();

    ///****Fill End****

}

void cloud_model_Two() {
    glColor3f(1.25, 0.924, 0.930);

    ///Left_Part
    glPushMatrix();
    glTranslatef(305, 205, 0);
    circle(10);
    glPopMatrix();

    ///Top

    glPushMatrix();
    glTranslatef(320, 210, 0);
    circle(15);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(334, 207, 0);
    circle(10);
    glPopMatrix();

    ///Bottom_Part
    glPushMatrix();
    glTranslatef(320, 207, 0);
    circle(10);
    glPopMatrix();

}

void cloud_model_Three() {
    glColor3f(1.25, 0.924, 0.930);

    ///Left_Part
    glPushMatrix();
    glTranslatef(300, 200, 0);
    circle(15);
    glPopMatrix();

    ///Top_Left

    glPushMatrix();
    glTranslatef(320, 210, 0);
    circle(15);
    glPopMatrix();

    ///Top
    glPushMatrix();
    glTranslatef(340, 220, 0);
    circle(16);
    glPopMatrix();

    ///Top_Right
    glPushMatrix();
    glTranslatef(360, 210, 0);
    circle(15);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(380, 200, 0);
    circle(15);
    glPopMatrix();

    ///Bottom_Right
    glPushMatrix();
    glTranslatef(360, 190, 0);
    circle(20);
    glPopMatrix();

    ///Bottom_Left
    glPushMatrix();
    glTranslatef(320, 190, 0);
    circle(20);
    glPopMatrix();

    ///Bottom
    glPushMatrix();
    glTranslatef(340, 190, 0);
    circle(20);
    glPopMatrix();




    ///****Fill End****

}
///*** Hill_Model***///
void hill_big() {

    ///Hill
    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.41, 0.36);
    glVertex2i(70, 70);
    glVertex2i(200, 225);
    glVertex2i(330, 70);

    glEnd();

    ///Hill_Snow
    glBegin(GL_POLYGON);
    glColor3f(1.25, 0.924, 0.930);

    glVertex2i(200, 225);
    glVertex2i(230, 190);
    glVertex2i(220, 180);
    glVertex2i(200, 190);
    glVertex2i(190, 180);
    glVertex2i(170, 190);

    glEnd();

}
void hill_small() {
    ///Hill_Small
    glBegin(GL_POLYGON);
    glColor3f(0.11, 0.23, 0.36);
    glVertex2i(250, 100);
    glVertex2i(310, 175);
    glVertex2i(370, 100);

    glEnd();

    ///Hill_Small_Snow
    glBegin(GL_POLYGON);
    glColor3f(1.25, 0.924, 0.930);
    glVertex2i(290, 150);
    glVertex2i(310, 175);
    glVertex2i(330, 150);
    glVertex2i(325, 140);
    glVertex2i(310, 150);
    glVertex2i(300, 140);


    glEnd();
}
///*** Tilla_Model ***///
void Tilla_One_Model() {
    ///Tilla
    glBegin(GL_POLYGON);
    glColor3f(0.1, 1.293, 0.0);
    glVertex2i(125, 70);
    glVertex2i(150, 80);
    glVertex2i(160, 90);
    glVertex2i(170, 90);
    glVertex2i(180, 100);
    glVertex2i(190, 105);
    glVertex2i(200, 108);
    glVertex2i(300, 110);
    glVertex2i(300, 70);

    glEnd();

}

void Tilla_Two_Model() {

    glColor3f(0.1, 1.293, 0.0);
    /// Left_Part
    glPushMatrix();
    glTranslatef(430, 90, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(420, 87, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(410, 80, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(400, 80, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(390, 70, 0);
    circle(30);
    glPopMatrix();

    ///Right_Part
    glPushMatrix();
    glTranslatef(445, 80, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(455, 75, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(465, 70, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(470, 65, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(480, 60, 0);
    circle(30);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(485, 55, 0);
    circle(20);
    glPopMatrix();



}
///*** House_Model ***///
void house() {
    ///House_Roof
    glBegin(GL_POLYGON);
    glColor3f(.990, 0.0, 0.0);
    glVertex2i(285, 105);
    glVertex2i(285, 130);
    glVertex2i(380, 115);
    glVertex2i(380, 105);

    glEnd();

    ///House_Roof_Shadow
    glBegin(GL_POLYGON);
    glColor3f(.890, 0.0, 0.0);
    glVertex2i(285, 105);
    glVertex2i(285, 120);
    glVertex2i(380, 105);
    glVertex2i(380, 105);

    glEnd();



    //house roof right-side wall
    glBegin(GL_POLYGON);
    glColor3f(.890, .0, 0.0);
    glVertex3f(380, 115, 0);
    glVertex3f(380, 105, 0);
    glVertex3i(385, 114, 0);
    glEnd();

    //House right-side wall
    glBegin(GL_POLYGON);
    glColor3f(.555, 1.0, 1.0);
    glVertex3i(375, 104, 0);
    glVertex3i(375, 70, 0);
    glVertex3i(385, 80, 0);
    glVertex3i(385, 114, 0);
    glEnd();


    ///House_Fence
    glBegin(GL_POLYGON);
    glColor3f(.555, 1.0, 1.0);
    glVertex2i(290, 70);
    glVertex2i(290, 104);
    glVertex2i(375, 104);
    glVertex2i(375, 70);

    glEnd();

    ///House_Fence_Shadow
    glBegin(GL_POLYGON);
    glColor3f(.555, 0.924, 0.930);
    glVertex2i(310, 70);
    glVertex2i(350, 104);
    glVertex2i(375, 104);
    glVertex2i(375, 70);

    glEnd();

    ///House_Door
    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.41, 0.36);
    glVertex2i(330, 70);
    glVertex2i(330, 100);
    glVertex2i(350, 100);
    glVertex2i(350, 70);

    glEnd();

    ///House_Window1
    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex2i(295, 75);
    glVertex2i(295, 90);
    glVertex2i(310, 90);
    glVertex2i(310, 75);

    glEnd();

    ///House_Window2
    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex2i(312, 75);
    glVertex2i(312, 90);
    glVertex2i(327, 90);
    glVertex2i(327, 75);

    glEnd();

    ///House_Window3
    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex2i(355, 75);
    glVertex2i(355, 90);
    glVertex2i(370, 90);
    glVertex2i(370, 75);

    glEnd();

    ///House_Small_Roof
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(250, 90);
    glVertex2i(257, 104);
    glVertex2i(290, 104);
    glVertex2i(290, 90);

    glEnd();

    ///House_Small_Fence
    glBegin(GL_POLYGON);
    glColor3f(.555, .724, .930);
    glVertex2i(255, 70);
    glVertex2i(255, 90);
    glVertex2i(290, 90);
    glVertex2i(290, 70);

    glEnd();

    ///House_Small_Door
    glBegin(GL_POLYGON);
    glColor3f(0.11, 0.23, 0.36);
    glVertex2i(260, 70);
    glVertex2i(260, 80);
    glVertex2i(285, 80);
    glVertex2i(285, 70);

    glEnd();


}
///*** Field_Model ***///
void field() {
    ///Field
    glBegin(GL_POLYGON);
    glColor3f(0.533, 1.293, 0.0);
    glVertex2i(0, 50);
    glVertex2i(0, 70);
    glVertex2i(1000, 70);
    glVertex2i(1000, 50);

    glEnd();


    ///Field_Shadow
    glBegin(GL_POLYGON);
    glColor3f(0.1, 1.293, 0.0);
    glVertex2i(0, 0);
    glVertex2i(0, 50);
    glVertex2i(1000, 50);
    glVertex2i(1000, 0);

    glEnd();

}
///*** Tree_Model ***///
void Tree_Model_One() {


    glPushMatrix();
    glTranslatef(110, 110, 0);
    circle(15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(110, 100, 0);
    circle(15);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex3f(109, 70, -16);
    glVertex3f(109, 90, -16);
    glVertex3f(111, 90, -16);
    glVertex3f(111, 70, -16);

    glEnd();

}
void Tree_Model_Two() {

    glPushMatrix();
    glTranslatef(130, 130, 0);
    circle(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(125, 126, 0);
    circle(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(135, 126, 0);
    circle(5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(130, 125, 0);
    circle(5);
    glPopMatrix();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex3f(129, 110, -16);
    glVertex3f(129, 124, -16);
    glVertex3f(131, 124, -16);
    glVertex3f(131, 110, -16);

    glEnd();
}

void Tree_Model_Three() {


    glBegin(GL_POLYGON);

    glVertex3f(125, 123, -16);
    glVertex3f(133, 145, -16);
    glVertex3f(141, 123, -16);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.38, 0.21, 0.26);
    glVertex3f(132, 110, -16);
    glVertex3f(132, 124, -16);
    glVertex3f(134, 124, -16);
    glVertex3f(134, 110, -16);

    glEnd();
}

/// *** Windmill_Stand_Model ***///
void Windmill_Stand_Model() {

    glColor3f(0.38, 0.41, 0.36);
    glBegin(GL_POLYGON);
    glVertex3f(375, 100, -16);
    glVertex3f(380, 240, -16);
    glVertex3f(384, 240, -16);
    glVertex3f(390, 100, -16);
    glEnd();
}

///*** Windmill_Blades_Model ***///

void Windmill_Blade() {

    ///Blade_One
    glPushMatrix();
    glRotatef(spin, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(-5, 0, -16);
    glVertex3f(-85, -36, -16);
    glVertex3f(-83, -37, -16);
    glVertex3f(-3, -8, -16);
    glEnd();
    glPopMatrix();

    ///Blade_Two
    glPushMatrix();
    glRotatef(spin, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(0, 5, -16);
    glVertex3f(45, 70, -16);
    glVertex3f(50, 73, -16);
    glVertex3f(5, 0, -16);
    glEnd();
    glPopMatrix();

    ///Blade_Three
    glPushMatrix();
    glRotatef(spin, 0, 0, 1);
    glBegin(GL_POLYGON);
    glVertex3f(68, -78, -16);
    glVertex3f(0, 0, -16);
    glVertex3f(5, 5, -16);
    glVertex3f(70, -77, -16);
    glEnd();
    glPopMatrix();

}
///*** Windmill_Final_Model ***///
void Windmill() {

    ///Windmill_Stand
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    Windmill_Stand_Model();
    glPopMatrix();

    ///Windmill_Motor
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(380, 250, 0);
    circle(10);
    glPopMatrix();

    ///Windmill_Rotary_Blades
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(380, 251, 0);
    Windmill_Blade();
    glPopMatrix();

}


///Model_End
///=======================================================================================================///


///=================///
///***   Object  ***///
///=================///

///*** Sun ***///
void Sun() {
    glColor3f(1, 1, 0);
    glPushMatrix();
    Moving_Sun_Model();
    glPopMatrix();
}
///*** Cloud_One_Model_One ***///
void cloud_one() {
    glPushMatrix();
    glTranslatef(cx, -40, 0);
    cloud_model_one();
    glPopMatrix();

}

///*** Cloud_Two_Model_one ***///

void cloud_two() {
    glPushMatrix();
    glTranslatef(bx + 100, 150, 0);
    cloud_model_one();
    glPopMatrix();

}

///*** Cloud_Three_Model_Two ***///

void cloud_three() {
    glPushMatrix();
    glTranslatef(ax - 80, 80, 0);
    cloud_model_Two();
    glPopMatrix();

}
///*** Cloud_Four_Model_Two ***///

void cloud_four() {
    glPushMatrix();
    glTranslatef(dx + 300, 125, 0);
    cloud_model_Two();
    glPopMatrix();

}
///*** Cloud_Five_Model_Three ***///
void cloud_five() {

    glPushMatrix();
    glTranslatef(ax + -300, 170, 0);
    cloud_model_Three();
    glPopMatrix();
}
///*** Cloud_Six_Model_Three ***///
void cloud_six() {

    glPushMatrix();
    glTranslatef(cx + -500, 20, 0);
    cloud_model_Three();
    glPopMatrix();
}

///*** House_One ***///
void house_one() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    house();
    glPopMatrix();
}
//House_Two 
void house_two() {
    glPushMatrix();
    glScalef(1.5, 1.5, 1.5);
    glTranslatef(166, -40, 0);
    house();
    glPopMatrix();
}

///*** House_Two ***///
void house_three() {
    glPushMatrix();
    glTranslatef(450, 30, 0);
    glScalef(.4, .4, .4);
    HOUSE();
    glPopMatrix();
}
///*** Hill_big_One ***///
void Hill_Big_One() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    hill_big();
    glPopMatrix();
}
///*** Hill_big_Two ***///
void Hill_Big_Two() {
    glPushMatrix();
    glTranslatef(550, -20, 0);
    hill_big();
    glPopMatrix();
}
///*** Hill_Small_One ***///
void Hill_Small_One() {
    glPushMatrix();
    glTranslatef(0, 0, 0);
    hill_small();
    glPopMatrix();

}
/// *** Tilla_One_Model_One ***///

void Tilla_One() {

    glPushMatrix();
    glTranslatef(0, 0, 0);
    Tilla_One_Model();
    glPopMatrix();

}
/// *** Tilla_Two_Model_Two ***///
void Tilla_Two() {

    glPushMatrix();
    glTranslatef(0, 0, 0);
    Tilla_Two_Model();
    glPopMatrix();


}
/// *** Tilla_Three_Model_Two ***///
void Tilla_Three() {

    glPushMatrix();
    glTranslatef(400, 0, 0);
    Tilla_Two_Model();
    glPopMatrix();


}
/// *** Tilla_Four_Model_One ***///
void Tilla_Four() {

    glColor3f(0.833, 1., 0.0);
    glPushMatrix();
    glTranslatef(380, 0, 0);
    Tilla_One_Model();
    glPopMatrix();


}
///*** Tree_1 ***///
void Tree_One() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(0, 0, 0);
    Tree_Model_One();
    glPopMatrix();
}

///*** Tree_2 ***///
void Tree_Two() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(540, 0, 0);
    Tree_Model_One();
    glPopMatrix();
}

///*** Tree_3 ***///
void Tree_Three() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(750, 0, 0);
    Tree_Model_One();
    glPopMatrix();
}
///*** Tree_4 ***///
void Tree_Four() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(292, 40, 0);
    Tree_Model_One();
    glPopMatrix();
}

///*** Tree_5 ***///
void Tree_Five() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(30, -20, 0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_6 ***///
void Tree_Six() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(50, -10, 0);
    Tree_Model_Two();
    glPopMatrix();
}
///*** Tree_7 ***///
void Tree_Seven() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(322, 0, 0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_8 ***///
void Tree_Eight() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(350, -15, 0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_9 ***///
void Tree_Nine() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(760, -25, 0);
    Tree_Model_Two();
    glPopMatrix();
}

///*** Tree_10 ***///
void Tree_Ten() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(90, -2, 0);
    Tree_Model_Three();
    glPopMatrix();
}

///*** Tree_11 ***///
void Tree_Eleven() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(125, 0, 0);
    Tree_Model_Three();
    glPopMatrix();
}

///*** Tree_12 ***///
void Tree_Twelve() {
    glColor3f(0.533, 1.293, 0.0);
    glPushMatrix();
    glTranslatef(408, -22, 0);
    Tree_Model_Three();
    glPopMatrix();
}

/// *** Windmill ***///
void Windmill_One() {
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(0, -10, 0);
    Windmill();
    glPopMatrix();

}

void Windmill_Two() {
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(508, -70, 0);
    Windmill();
    glPopMatrix();

}
void Windmill_Three() {
    glColor3f(0.11, 0.23, 0.36);
    glPushMatrix();
    glTranslatef(108, -90, 0);
    Windmill();
    glPopMatrix();

}


// flowers model 
void GrassFlowers() {

    glPushMatrix();
    glColor3f(0.3, 0.6, 0.1);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(80, 80);
    glVertex2f(0, 0);
    glVertex2f(0, 120);
    glVertex2f(0, 0);
    glVertex2f(-80, 80);
    glEnd();
    glColor3f(0.3, 0.6, 0.1);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(45, 77);
    glVertex2f(0, 0);
    glVertex2f(25, 77);
    glVertex2f(0, 0);
    glVertex2f(-45, 77);
    glVertex2f(0, 0);
    glVertex2f(-25, 77);
    glVertex2f(0, 0);

    glEnd();


    glPushMatrix();
    glTranslatef(0, 115, 0);
    glColor3f(0.9, 1, 0.3);
    circle(19);
    glTranslatef(-75, -35, 0);
    glColor3f(1, 0, 0);
    circle(19);
    glTranslatef(150, 0, 0);
    glColor3f(1, 0.4, 1);
    circle(19);

    glPopMatrix();



    glPopMatrix();


}

// draw and sets the positions of the flowers
void drawingFlowers() {
    glPushMatrix();
    glTranslatef(110, 30, -16);
    glScalef(.25, .25, .25);
    GrassFlowers();

    glTranslatef(-250, -80, -16);
    GrassFlowers();

    glTranslatef(+700, 60, -16);
    GrassFlowers();

    glTranslatef(750, 80, -16);
    GrassFlowers();

    glTranslatef(300, -70, -16);
    GrassFlowers();


    glPopMatrix();

    glPushMatrix();

    glScalef(.25, .25, .25);
    glTranslatef(2300, 200, -16);
    GrassFlowers();

    glTranslatef(850, -160, -16);
    GrassFlowers();

    glTranslatef(550, 160, -16);
    GrassFlowers();

    glTranslatef(-200, -100, -16);
    GrassFlowers();

    glPopMatrix();


}
void SnowMan_Model()
{
    const float PI1 = 3.1415926f;
    float radius = 0.35f;										// Radius of cirlce = How big you want your circle to be.

    glPushMatrix();
    glTranslatef(100, 100, 0);
    glScalef(100, 100, 1);

    glBegin(GL_TRIANGLE_FAN);									// Create Triangle

    glVertex2f(0.0f, -0.5f);									// origin = centre of circle

    int segments = 20;
    float dTheta = (float)(2.0f * PI1) / segments;

    for (int i = 0; i <= segments; i++)
    {
        glColor3f(1.0f, 1.0f, 1.0f);							// Circle Inner Color
        float x = (float)cos(i * dTheta) * radius + 0.0f;		// + 0.0f position of X Axis // Need to convert i to radians 

        glColor3f(0.6f, 0.6f, 0.6f);							// Circle Outter Color
        float y = (float)sin(i * dTheta) * radius + -0.5f;		// + 0.4f position of Y Axis // Need to convert i to radians 
        glVertex2f(x, y);
    }

    glEnd();

    radius = 0.25f;										// Radius of cirlce = How big you want your circle to be.

    glBegin(GL_TRIANGLE_FAN);									// Create Triangle

    glColor3f(1.0f, 1.0f, 1.0f);							// Circle Inner Color
    glVertex2f(0.0f, -0.1f);									// origin = centre of circle

    float dTheta1 = (float)(2.0f * PI1) / segments;

    for (int i = 0; i <= segments; i++)
    {
        glColor3f(0.8f, 0.8f, 0.8f);							// Circle Inner Color
        float x = (float)cos(i * dTheta1) * radius + 0.0f;		// + 0.0f position of X Axis // Need to convert i to radians 

        glColor3f(0.6f, 0.6f, 0.6f);							
        float y = (float)sin(i * dTheta1) * radius + -0.1f;		 
        glVertex2f(x, y);
    }

    glEnd();
    radius = 0.035f;										

    glBegin(GL_TRIANGLE_FAN);								

    glColor3f(1.0f, 1.0f, 1.0f);							
    glVertex2f(-0.1f, -0.05f);									

    dTheta = (float)(2.0f * PI) / segments;

    glColor3f(0.0f, 0.0f, 0.0f);							
    for (int i = 0; i <= segments; i++)
    {
        float x = (float)cos(i * dTheta) * radius + -0.1f;		
        float y = (float)sin(i * dTheta) * radius + -0.05f;		
        glVertex2f(x, y);
    }
    glEnd();
    radius = 0.035f;										

    glBegin(GL_TRIANGLE_FAN);									

    glColor3f(1.0f, 1.0f, 1.0f);							
    glVertex2f(0.1f, -0.05f);									

    dTheta = (float)(2.0f * PI) / segments;

    glColor3f(0.0f, 0.0f, 0.0f);							
    for (int i = 0; i <= segments; i++)
    {
        float x = (float)cos(i * dTheta) * radius + 0.1f;		
        float y = (float)sin(i * dTheta) * radius + -0.05f;		
        glVertex2f(x, y);
    }
    glEnd();
    radius = 0.03f;										

    glBegin(GL_TRIANGLE_FAN);									
    glColor3f(1.0f, 1.0f, 1.0f);							
    glVertex2f(0.0f, -0.15f);									

    dTheta = (float)(2.0f * PI) / segments;

    for (int i = 0; i <= segments; i++)
    {
        glColor3f(1.0f, 0.5f, 0.0f);							
        float x = (float)cos(i * dTheta) * radius + 0.0f;	
        float y = (float)sin(i * dTheta) * radius + -0.15f;		
        glVertex2f(x, y);
    }
    glEnd();

    float x = -0.35f, y = -0.4f, d = 0.1f;
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.3f, 0.1f);
    glVertex2f(x - d, y - 0.5f * d);
    glVertex2f(x + d, y - 0.5f * d);
    glVertex2f(x + d, y + 0.5f * d);
    glVertex2f(x - d, y + 0.5f * d);
    glEnd();
    x = -x;
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.3f, 0.1f);
    glVertex2f(x - d, y - 0.5f * d);
    glVertex2f(x + d, y - 0.5f * d);
    glVertex2f(x + d, y + 0.5f * d);
    glVertex2f(x - d, y + 0.5f * d);
    glEnd();


    glPopMatrix();
}



// drawing bird model and controls its position and movement
void Draw_Bird()
{
    static float x = 800;
    static float y = 0;
    y += rand() % 3 - 1;
    x -= 2;

    if (x < -150)
    {
        x = 800;
        y = 0;
    }
    glPushMatrix();
    glTranslatef(200 + x, 200 + y, 0);

    // head
    glScalef(-10, 10, 10);
    glColor3ub(220, 88, 35);
    glBegin(GL_QUADS);
    glVertex3f(1.7f, 0, 0);
    glVertex3f(3.0f, 0.5f, 0);
    glVertex3f(2.5f, 1.0f, 0);
    glVertex3f(1.3f, 1.0f, 0);

    // body
    glColor3ub(227, 181, 76);
    glVertex3f(1.7f, 0, 0);
    glVertex3f(1.3f, 1.0f, 0);
    glVertex3f(1.0f, -0.8f, 0);
    glVertex3f(-0.8f, -0.8f, 0);

    // green wings
    glColor3ub(16, 124, 61);
    glVertex3f(1.0f, 0.2f, 0);
    glVertex3f(-0.5f, 1.2f, 0);
    glVertex3f(-2.2f, 1.2f, 0);
    glVertex3f(-0.5f, -0.4f, 0);

    glVertex3f(2.4f, 2.6f, -1);
    glVertex3f(0.5f, 1.5f, -1);
    glVertex3f(0.5f, 0.5f, -1);
    glVertex3f(1.6f, 1.0f, -1);

    glEnd();

    glBegin(GL_TRIANGLES);

    // mouth
    glColor3ub(210, 162, 54);
    glVertex3f(3.0f, 0.5f, -1);
    glVertex3f(3.5f, -0.2f, -1);
    glVertex3f(2.5f, 0.2f, -1);

    // tail
    glColor3ub(237, 115, 35);
    glVertex3f(-2.0f, -2.5f, 0);
    glVertex3f(-0.0f, -0.8f, 0);
    glVertex3f(-0.8f, -0.8f, 0);
    glEnd();

    glPopMatrix();
}

void OurHouse() {
    glPushMatrix();
    glTranslatef(60, -50, 0);
    glScalef(.5, .5, .5);
    HOUSE();
    glPopMatrix();




}
/****************************************************************/
/*    OBJECTS DRAWS AND MODELING ENDS     */
/****************************************************************/


/****************************************************************/
/*    Displaying on the screen "display function"     */
/****************************************************************/

void display(void)
{
    // enable the depth buffer so we can use 3d objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set background color and multiplies it by lighting matrixe array to control view mode
    glClearColor(.40 * ambient_light[0], .610 * ambient_light[1], 1 * ambient_light[2], 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // enable ortho method to display on 3d mode and adds cameras and zooming variables so we can controls it all
    glOrtho((0.0 + cam_x) / zoom, (1000.0 + cam_x) / zoom, (0.0 + cam_y) / zoom, (500.0 + cam_y) / zoom, -100, 100);
    glMatrixMode(GL_MODELVIEW);

    // to control which screen to display ( main screen or start screen )
    // here we will show interface screen (start screen) when the boolean variable ShowInterface value equal TRUE
    if (ShowInterface)
    {
        drawInterface();
    }
    // here we will show main screen (scene screen) when the boolean variable ShowInterface value equal FALSE
    else if (!ShowInterface)
    {

        ///*** Object_Layer ***///
        if (!night)
        {
            // hiding the models that i want it to disappear at night mode
            // and ONLY show it at the day
            Sun();
            Airplane_Model();
            Draw_Bird();
        }
        glEnable(GL_LIGHTING);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT);

        Windmill_Three();

        Hill_Big_One();
        Tilla_Four();

        house_three();

        Hill_Big_Two();
        Hill_Small_One();
        if (!night)
        {
            // hiding the models that i want it to disappear at night mode
            // and ONLY show it at the day
            cloud_three();
            cloud_four();
        }
        Windmill_One();
        Windmill_Two();

        Tilla_One();
        Tilla_Two();
        Tilla_Three();



        if (!night)
        {
            // hiding the models that i want it to disappear at night mode
            // and ONLY show it at the day
            cloud_one();
        }

        Tree_One();
        Tree_Two();
        Tree_Three();
        Tree_Four();
        Tree_Five();
        Tree_Six();
        Tree_Seven();
        Tree_Eight();
        Tree_Nine();
        Tree_Ten();
        Tree_Eleven();
        Tree_Twelve();

        if (!night)
        {
            // hiding the models that i want it to disappear at night mode
            // and ONLY show it at the day
            cloud_two();
            cloud_five();
            cloud_six();
        }

        field();
        house_two();
        OurHouse();
        drawingFlowers();
        lamp_stand(50, 175, -16);
        lamp_stand(980, 175, -16);

        //***************************************************************************************************//
        // here we disable the light, because we dont want the next objects (stars, lamp, moon and snowman)
        // to be affected by the dark light at midnight
        // by disableing the light before drawing the objects, we allowes to shine at the dark mode 
        // and doesnot affected darklly at night 
        //***************************************************************************************************//

        glDisable(GL_LIGHTING);
        glDisable(GL_COLOR_MATERIAL);

        lamp(50, 175, -16);
        lamp(980, 175, -16);

        if (night) {
            // displaying the models that i want it to appear only at night mode
            glPushMatrix();
            star(500, 450, -16);
            star(100, 400, -16);
            star(400, 475, -16);
            star(300, 425, -16);
            star(200, 350, -16);
            star(970, 470, -16);
            star(460, 400, -16);
            star(770, 475, -16);
            star(660, 425, -16);
            star(730, 350, -16);
            star(860, 425, -16);
            star(50, 350, -16);
            star(30, 450, -16);
            star(170, 480, -16);
            star(550, 330, -16);
            star(850, 330, -16);
            star(850, 330, -16);
            star(780, 410, -16);
            Moon_Model();
            glPopMatrix();
            SnowMan_Model();
        }
    }
    glFlush();
    glutSwapBuffers();
    Sleep(1000 / 60);
}
///========================///
///*** Speed & Movement ***///
///========================///
///the method  controls the sun movement
void sun_move() {
    sun_spin = sun_spin + 0.02;
    if (star_angle < 360)
    {
        star_angle++;
    }
    else
    {
        star_angle = 0;
    }
}

// the method controls the clouds and Windmills movement
void move_right() {

    sun_move();

    spin = spin + .1;
    ax = ax + .05;
    bx = bx + .08;
    cx = cx + .10;
    dx = dx + .15;

    if (cx > 1000) {
        cx = -300;
    }
    if (bx > 1000) {
        bx = -400;

    }
    if (cx > 1000) {
        cx = -400;

    }
    if (dx > 1000) {
        dx = -500;

    }

    if (SmokeUp < 20) {
        SmokeUp += .2;
    }
    else {
        SmokeUp = 0;
    }


    glutPostRedisplay();
}

void processKeyboard(unsigned char key, int x, int y) {
    if (key == 'q')
    {
        if (zoom < 1.2)
        {
            zoom += 0.1;
        }
    }
    if (key == 'e')
    {
        if (zoom > 0.8)
        {
            zoom -= 0.1;
        }
    }
    if (key == 'g')
    {
        glutIdleFunc(move_right);
    }
    if (key == 'h')
    {
        glutIdleFunc(NULL);
    }
    if (key == 'w')
    {
        cam_y += 5.f;
    }
    if (key == 's')
    {
        cam_y -= 5.f;
    }
    if (key == 'a')
    {
        cam_x -= 5.f;
    }
    if (key == 'd')
    {
        cam_x += 5.f;
    }
    if (key == 'n')
    {
        ambient_light[0] = 0.5;
        ambient_light[1] = 0.5;
        ambient_light[2] = 0.5;
        night = true;
    }
    if (key == 'm')
    {
        ambient_light[0] = 1.f;
        ambient_light[1] = 1.f;
        ambient_light[2] = 1.f;
        night = false;
    }

    if (key == 'l')
    {
        if (ShowInterface)
        {
            glClearColor(.40, .610, 1, 0);

            ShowInterface = false;
            glutPostRedisplay();

        }
        glutPostRedisplay();
    }



}

void processMenu(int option) {
    switch (option) {
    case DAY:
        ambient_light[0] = 1.f;
        ambient_light[1] = 1.f;
        ambient_light[2] = 1.f;
        night = false;
        break;
    case NIGHT:
        ambient_light[0] = 0.5;
        ambient_light[1] = 0.5;
        ambient_light[2] = 0.5;
        night = true;
        break;
    case 11:
        if (zoom < 1.2)
        {
            zoom += 0.1;
        }        break;
    case 22:
        if (zoom > 0.8)
        {
            zoom -= 0.1;
        }
        break;
    }
}


int main(int argc, char** argv)
{
    sndPlaySound(TEXT("RingtoneSound.wav"), SND_ASYNC);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1200, 1200);
    glEnable(GL_DEPTH_TEST);
    glutCreateWindow("Smart Village");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(processKeyboard);
    int menu;
    menu = glutCreateMenu(processMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("Switch to day", DAY);
    glutAddMenuEntry("Switch to night", NIGHT);
    glutAddMenuEntry("Zoom in", 11);
    glutAddMenuEntry("Zoom out", 22);
    glutMainLoop();
    return 0;
}
