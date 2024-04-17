
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include <ctime>

// Include other classes required
#include "table.h"
#include "stdafx.h"
#include "Utility.h"

// Grab access to the global list of pointers to objects
extern Table MyTable;
using namespace std;

Utility::Utility()
{
	windowWidth = 512;
	windowHeight = 512;
	remapx = 0;
	remapy = 0;
	nMousex = 0;
	nMousey = 0;

	pressedLB = false;
}

void Utility::doGraphicsInit()
{
	glMatrixMode(GL_MODELVIEW); // Switch to the drawing perspective
	doCamera();

    // Clear information from last draw
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Utility::doCamera()
{
    glLoadIdentity(); // Reset the drawing perspective
}

// Sets up a Window 
//
// The default is a window with center  0, 0, 0 and goes out to -1 and 1, 
// this is the default glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0 );
//
// By default it will open in the top left corner, small size 300 by 300
//
// To change these defaults you can use the functions, for example
// glutInitWindowSize( 500, 500 );
// glutInitWindowPosition( 100, 100 );
//
void Utility::initWindow()
{
	// This creates the window with a given title
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Hello");
	glOrtho(0, ORTHOHEIGHT, 0, ORTHOHEIGHT, 0, 1.0);

	// select clearing background color
	glClearColor(0.0, 1.0, 0.0, 0.0);
	
}

void Utility::doCameraOrthographic(int w, int h)
{
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float aspect = (float)w / (float)h;
		float left, bottom;
		bottom = left = 0;

		if (w <= h)
			glOrtho(left, ORTHOHEIGHT, bottom / aspect, ORTHOHEIGHT / aspect, 0.0, 1.0);
		else
			glOrtho(left * aspect, ORTHOHEIGHT * aspect, bottom, ORTHOHEIGHT, 0.0, 1.0);

}

// Note that mousebutton will detect both up and down of the mouse button click
void Utility::mousebutton(int button, int state, int x, int y)
{
	remapx = windowWidth / ORTHOHEIGHT;
	remapy = windowHeight / ORTHOHEIGHT;

	//cout << "\nMouse values are (x,y): " << x << " " << y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//cout << "\nMouse values are (x,y): " << x << " " << y;
		nMousex = x / remapx;
		nMousey = ORTHOHEIGHT - y / remapy;
		cout << "\nNew ouse values are (x,y): " << nMousex << " " << nMousey;
		MyTable.checkClick();
		if (MyTable.correct)
		{
			MyTable.initTable();
			MyTable.correct = false;
		}
	}
}

