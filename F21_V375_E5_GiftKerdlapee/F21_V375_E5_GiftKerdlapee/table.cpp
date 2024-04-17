
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <cstdlib>

// Include other classes required
#include "table.h"
#include "stdafx.h"
#include "Utility.h"

// Grab access to the global list of pointers to objects
extern Utility MySettings;

using namespace std;

Table::Table()
{
	gap = 0.05f;
	margin = 0.3f;
	tableSize = 1;
	variantPos[0] = 0;
	variantPos[1] = 1;
	variant = 0.1;

	boxSize = 0;
	xval = 0;
	yval = 0;

	correct = false;

	colourSwitch = 0;
	colour[0] = 1.0;
	colour[1] = 1.0;
	colour[2] = 0.0;
	srand(time(0));

	score = 0;
	error = 0;
}

void Table::initTable()
{
	if (tableSize < 8)
	{
		tableSize++;
	}
	switch (colourSwitch)
	{
	case 0:
		colour[0] = 0.95;
		colour[1] = 0.95;
		colour[2] = 0.0;
		break;
	case 1:
		colour[0] = 0.0;
		colour[1] = 0.7;
		colour[2] = 0.7;
		break;
	case 2:
		colour[0] = 0.7;
		colour[1] = 0.5;
		colour[2] = 0.5;
		break;
	}
	variantPos[0] = rand() % tableSize;
	variantPos[1] = rand() % tableSize;
	colourSwitch++;
	colourSwitch = colourSwitch % 3;
	if (variant > 0.014)
	{
		variant = variant / 1.15;
	}
	
	cout << "\n" << variant;
}

void Table::reset()
{
	tableSize = 1;
	variantPos[0] = 0;
	variantPos[1] = 1;
	variant = 0.1;

	boxSize = 0;
	xval = 0;
	yval = 0;

	correct = false;

	colourSwitch = 0;
	colour[0] = 1.0;
	colour[1] = 1.0;
	colour[2] = 0.0;
	srand(time(0));

	score = 0;
	error = 0;
}

void Table::drawTable()
{
	double colour1, colour2, colour3;
	float yvalCheck, xvalCheck;
	//table
	//everytime a table is created randomise x and y (ramdom x and y must be <= tableSize)
	for (int j = 0; j < tableSize; j++)
	{
		boxSize = (ORTHOHEIGHT - (tableSize + 1) * gap - margin*3) / tableSize;
		yvalCheck = j * boxSize + gap * (j + 1);
		for (int i = 0; i < tableSize; i++)
		{
			xvalCheck = i * boxSize + gap * (i + 1);
			glPushMatrix();
			glTranslatef(xvalCheck+margin*1.5, yvalCheck, 0.0);
			if (i == variantPos[0] && j == variantPos[1])
			{
				//cout << "true";
				//cout << variantPos[0] << ",  " << variantPos[1];
				colour1 = colour[0] - variant;
				colour2 = colour[1] - variant;
				colour3 = colour[2] - variant;
				//glutSolidSphere(0.5, 10, 10);
				yval = j * boxSize + gap * (j + 1);
				xval = i * boxSize + gap * (i + 1) + margin * 1.5;
			}
			else
			{
				colour1 = colour[0];
				colour2 = colour[1];
				colour3 = colour[2];
			}
			
			solidSquare(boxSize, colour1, colour2, colour3);
			glPopMatrix();
		}
	}
	/*glTranslatef(xval, yval, 0.0);
	glutSolidSphere(.3, 20, 20);*/
}

//
//solidSquare
//
//draw square
void solidSquare(float size, float colour1, float colour2, float colour3)
{
	// set the color for the rectangle
	glColor3f(colour1, colour2, colour3);

	// draw a rectangle with corners at ( .25, .25, 0 ) and ( .75, .75, 0 )
	glBegin(GL_POLYGON);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(size, 0.0, 0.0);
	glVertex3f(size, size, 0.0);
	glVertex3f(0.0, size, 0.0);
	glEnd();
}

void Table::checkClick()
{ 
	if (MySettings.nMousex > margin * 1.5 + gap && MySettings.nMousex < ORTHOHEIGHT - margin * 1.5 - gap &&
		MySettings.nMousey > gap && MySettings.nMousey < ORTHOHEIGHT - margin*3 - gap)
	{
		if (MySettings.nMousex > xval && MySettings.nMousex < xval + boxSize &&
			MySettings.nMousey > yval && MySettings.nMousey < yval + boxSize)
		{
			//cout << "\n" << xvalCheck + boxSize << ", " << xvalCheck << "\n" << yvalCheck + boxSize << ", " << yvalCheck;
			cout << "\nscore: " << score;
			correct = true;
			score++;
		}
		else
		{
			cout << "\nerror: " << error;
			correct = false;
			error++;
		}
	}

}