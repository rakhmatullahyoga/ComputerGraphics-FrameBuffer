#ifndef CIRCLE_H
#define CIRCLE_H

#include "Point.h"
#include "DrawingObject.h"
#include "FrameBuffer.h"
#include "RGBcolor.h"

using namespace std;

class Circle {
	public:
		Circle();
		~Circle();
		void setUpCircle(Point P, int rad);
		void Draw(RGBcolor warna, FrameBuffer fBuff);
		void setWarna(RGBcolor color);
	private:
		Point center;
		DrawingObject drawer;
		RGBcolor fill_color;
		int radius;
};

#endif