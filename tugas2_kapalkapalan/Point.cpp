/* File : point.cpp */
/* Author : 13512053 - Rakhmatullah Yoga Sutrisna */

#include <iostream>
#include "Point.h"
using namespace std;
Point::Point() {
	x=0;
	y=0;
}
Point::Point(int new_x, int new_y) {
	x=new_x;
	y=new_y;
}
Point::Point(const Point& p) {
	x=p.x;
	y=p.y;
}
Point& Point::operator=(const Point& p) {
	x=p.x;
	y=p.y;
	return *this;
}
Point::~Point() {
}
int Point::GetAbsis() {
	return x;
}
int Point::GetOrdinat() {
	return y;
}
void Point::SetAbsis(int x) {
	this->x=x;
}
void Point::SetOrdinat(int y) {
	this->y=y;
}