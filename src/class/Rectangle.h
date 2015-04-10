#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Point.h"
#include "DrawingObject.h"
#include "FrameBuffer.h"
#include "RGBcolor.h"

using namespace std;

class Rectangle {
	public:
		Rectangle();
		~Rectangle();
		void setUpRectangle(Point P, int lx, int ly);
		void Draw(RGBcolor warna, FrameBuffer fBuff);
		void floodFill(FrameBuffer fBuff);
		void updateFillColor(FrameBuffer fBuff);
		void setWarna(RGBcolor color);
	private:
		Point top_left, fire_point;
		DrawingObject drawer;
		RGBcolor fill_color;
		int x_length, y_length;
};

#endif