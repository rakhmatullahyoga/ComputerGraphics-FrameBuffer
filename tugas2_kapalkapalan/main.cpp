#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"

int main(int argc, char const *argv[])
{
	FrameBuffer frame;
	RGBcolor color;
	DrawingObject draw;
	Point start, finish;
	int height = 50;
	int width = 100;

	color.setRed(255);
	color.setGreen(255);
	color.setBlue(255);
	start.SetAbsis(50);
	start.SetOrdinat(50);
	//draw.drawRectangle(start, height, width, color, frame);
	draw.animateRectangle(start, height, width, color, frame, 1, 0);
	return 0;
}