/* File : point.h*/
/* Author : 13512053 - Rakhmatullah Yoga Sutrisna */
#ifndef _POINT_H
#define _POINT_H
class Point {
	public:
		Point(); // constructor defaut tanpa parameter
		Point(int new_x, int new_y); // constructor dengan parameter
		Point(const Point& p); // copy constructor
		Point& operator=(const Point& p); // assignment
		~Point(); // destructor
		virtual int GetAbsis();
		virtual int GetOrdinat();
		virtual void SetAbsis(int x);
		virtual void SetOrdinat(int y);
	private:
		int x;
		int y;
};
#endif