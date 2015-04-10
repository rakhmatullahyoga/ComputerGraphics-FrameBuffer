#include "Circle.h"

using namespace std;

Circle::Circle() {}
Circle::~Circle() {}
void Circle::setUpCircle(Point P, int rad) {
	center = P;
	radius = rad;
}
void Circle::Draw(RGBcolor warna, FrameBuffer fBuff) {
	drawer.plotCircle(center,radius,warna,fBuff);
}
void Circle::setWarna(RGBcolor color) {
	fill_color = color;
}