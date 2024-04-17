#pragma once
const int ORTHOHEIGHT = 10;



class Utility
{
public:

	int windowWidth;
	int windowHeight;
	float remapx;
	float remapy;
	float nMousex, nMousey;

	bool pressedLB;

	Utility();
	void doGraphicsInit();
	void doCamera();
	void initWindow();
	void doCameraOrthographic(int w, int h);
	void mousebutton(int button, int state, int x, int y);
};