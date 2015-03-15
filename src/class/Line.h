#ifndef LINE_H
#define LINE_H

#include "Point.h"

class Line {
	public:
		Line(Point start, Point end);
		~Line();
		Point getIntersection();
	private:
		Point P1;
		Point P2;
		int a,b,c;
};

#endif