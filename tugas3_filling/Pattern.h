#ifndef PATTERN_H
#define PATTERN_H

#include "Point.h"
#include "RGBcolor.h"
#include "FrameBuffer.h"

class Pattern
{
public:
	Pattern();
	~Pattern();
	void drawPattern(Point top_left, Point bottom_right, RGBcolor warna, FrameBuffer fBuff);
private:
	int matriks[23][11];	
};

#endif