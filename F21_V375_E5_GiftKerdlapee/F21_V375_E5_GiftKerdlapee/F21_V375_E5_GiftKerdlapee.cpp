// F21_V375_E5_GiftKerdlapee.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "table.h"
#include "Utility.h"

#include <iostream>
#include <GL/freeglut.h>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

int gDrawMode = 1;

Utility MySettings;
Table MyTable;

void display();
void handleResize( int w, int h);
void myMenu(int value);
void handleKeypress(unsigned char key, int x, int y);
void mousebutton(int button, int state, int x, int y);
void update();



int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    MySettings.initWindow();

	// Add a Menu
	glutCreateMenu(myMenu);
	glutAddMenuEntry("Pause", 1);
	glutAddMenuEntry("Reset", 2);
	glutAddMenuEntry("Exit", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Add Mouse
	glutMouseFunc(mousebutton);

	MyTable.initTable();

	// draw scene
    glutDisplayFunc(display);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(handleKeypress);
    glutMainLoop();

    return 0;
}

// display()
// 
// This is were the action is taking place for drawing
//

void display()
{
	MySettings.doGraphicsInit();

	if (gDrawMode == 1)
	{
		MySettings.doCamera();
		
		//DRAWTABLE HERE
		MyTable.drawTable();

	}

	// Sends the scene to the screen, without this you will have a blank screen - comment it out and try it
	glutSwapBuffers();

}


// Reshape Callback Function
void handleResize(int w, int h)
{
	MySettings.windowWidth = w;
	MySettings.windowHeight = h;
	MySettings.doCameraOrthographic(w,h);
}



//// Note that mousebutton will detect both up and down of the mouse button click
void mousebutton(int button, int state, int x, int y)
{
	if (gDrawMode = 1)
	{
		MySettings.mousebutton(button, state, x, y);
	}

}

// myMenu
//
// Handles cases of user input from keyboard for menu choices
//
void myMenu(int value)
{
	switch (value)
	{
	case 1:
		gDrawMode = 0;
		glutPostRedisplay(); // Marks the current window for needing re-display
		break;
	case 2:
		MyTable.reset();
		MyTable.initTable();
		gDrawMode = 1;
		glutPostRedisplay(); // Marks the current window for needing re-display
		break;
	case 3:
		exit(0);
		break;
	}
}

// handleKeypress
// function to handle any key pressed by the user, for now just quits the program when user types ESC
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // Escape Key
		exit(0);
	}
}