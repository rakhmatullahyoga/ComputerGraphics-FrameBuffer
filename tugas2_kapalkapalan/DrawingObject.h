#ifndef DRAWINGOBJECT_H
#define DRAWINGOBJECT_H

#include "Point.h"
#include "RGBcolor.h"
#include "FrameBuffer.h"
#include <vector>
using namespace std;

class DrawingObject {
	public:
		DrawingObject();
		~DrawingObject();
		void plotLine(Point awal, Point akhir, RGBcolor warna, FrameBuffer fBuff);
		void plotCircle (Point pusat, int r, RGBcolor warna, FrameBuffer fBuff);
		void drawRectangle(Point top_left_corner, int height, int width, RGBcolor warna, FrameBuffer fBuff);
		void animateRectangle(Point start_top_left_corner, int height, int width, RGBcolor warna, FrameBuffer fBuff, int x_move, int y_move);
		void plotListOfPoint(vector<Point> kumpulantitik, RGBcolor warna, FrameBuffer fBuff);
};

#endif