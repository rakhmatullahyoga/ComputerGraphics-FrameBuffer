#ifndef IKAN_H
#define IKAN_H

#include "RGBcolor.h"
#include "FrameBuffer.h"

class Ikan
{
public:
	Ikan();
	~Ikan();
	void drawPattern(int x, int y, RGBcolor warna, FrameBuffer fBuff);
private:
	int matriks[23][11];	
};

#endif