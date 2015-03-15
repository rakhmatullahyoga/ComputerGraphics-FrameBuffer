#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line {
	public:
		Line(Point start, Point end);
		~Line();
		Point getIntersection(Line L);
		int getA();
		int getB();
		int getC();
	private:
		Point P1;
		Point P2;
		int A,B,C;	// untuk persamaan Ax+By=C
};

#endif