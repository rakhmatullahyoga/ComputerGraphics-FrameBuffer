#include "RGBcolor.h"

RGBcolor::RGBcolor(){
}
RGBcolor::~RGBcolor(){
}
void RGBcolor::setRed(int new_red) {
	red = new_red;
}
void RGBcolor::setGreen(int new_green) {
	green = new_green;
}
void RGBcolor::setBlue(int new_blue) {
	blue = new_blue;
}
int RGBcolor::getRed() {
	return red;
}
int RGBcolor::getGreen() {
	return green;
}
int RGBcolor::getBlue() {
	return blue;
}