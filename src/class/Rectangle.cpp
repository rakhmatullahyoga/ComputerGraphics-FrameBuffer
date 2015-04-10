#include "Rectangle.h"
#include <iostream>

using namespace std;

Rectangle::Rectangle() {
	fill_color.setRGB(1,1,1);
}
Rectangle::~Rectangle() {}
void Rectangle::setUpRectangle(Point P, int lx, int ly) {
	top_left = P;
	x_length = lx;
	y_length = ly;
	fire_point.SetAbsis(top_left.GetAbsis()+lx/2);
	fire_point.SetOrdinat(top_left.GetOrdinat()+ly/2);
}
void Rectangle::Draw(RGBcolor warna, FrameBuffer fBuff) {
	drawer.drawRectangle(top_left,y_length,x_length,warna,fBuff);
}
void Rectangle::floodFill(FrameBuffer fBuff) {
	int x = fire_point.GetAbsis();
	int y = fire_point.GetOrdinat();
	int location = x * (fBuff.vinfo.bits_per_pixel/8) + y * fBuff.finfo.line_length;

	if (fBuff.isSameColor(fBuff.getWarna(x,y),x,y)){
		if ( fBuff.vinfo.bits_per_pixel == 32 ) {
		    *(fBuff.fbp + location) = fill_color.getBlue();
		    *(fBuff.fbp + location + 1) = fill_color.getGreen();
		    *(fBuff.fbp + location + 2) = fill_color.getRed();
		}
		drawer.FloodFill(x+1,y,fBuff.getWarna(x,y), fill_color, fBuff);
		drawer.FloodFill(x-1,y,fBuff.getWarna(x,y), fill_color, fBuff);
		drawer.FloodFill(x,y+1,fBuff.getWarna(x,y), fill_color, fBuff);
		drawer.FloodFill(x,y-1,fBuff.getWarna(x,y), fill_color, fBuff);
	}
}
void Rectangle::updateFillColor(FrameBuffer fBuff) {
	fill_color = fBuff.getWarna(fire_point.GetAbsis(), fire_point.GetOrdinat());
	floodFill(fBuff);
}
void Rectangle::setWarna(RGBcolor color) {
	fill_color = color;
}