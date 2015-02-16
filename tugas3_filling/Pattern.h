#ifndef PATTERN_H
#define PATTERN_H

#include "Point.h"
#include "RGBcolor.h"
#include "FrameBuffer.h"
#include <string>
using namespace std;

class Pattern
{
public:
	Pattern(string filename);
	~Pattern();
	void drawPattern(Point top_left, Point bottom_right, RGBcolor warna, FrameBuffer fBuff);
private:
	int matriks[23][11];	
};

#endif