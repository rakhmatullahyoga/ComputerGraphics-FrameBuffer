#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Pattern.h"
#include "Object.h"
#include <iostream>
#include <termios.h>

using namespace std;

int _getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

int main(int argc, char const *argv[]) {
	FrameBuffer frame;
	DrawingObject map_canvas, view_port, legend;
	RGBcolor warna_border;
	Point canvas_topleft(50,50);
	Point view_topleft(200,200);
	Point legend_topleft(1016,516);

	system("clear");
	warna_border.setRGB(255,255,255);
	map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
	view_port.drawRectangle(view_topleft,200,200,warna_border,frame);
	legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
	while(true) {
		int ch = _getch();
		if(ch == 0x41) { // up-arrow key
			if(view_port.GetPoint().GetOrdinat()>canvas_topleft.GetOrdinat()) {
				view_port.moveRectangle(warna_border, frame, 0, -1);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			}
		}
		else if(ch == 0x42) { // down-arrow key
			if(view_port.GetPoint().GetOrdinat()+200<canvas_topleft.GetOrdinat()+666-1) {
				view_port.moveRectangle(warna_border, frame, 0, 1);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			}
		}
		else if(ch == 0x43) { // right-arrow key
			if(view_port.GetPoint().GetAbsis()+200<canvas_topleft.GetAbsis()+1266-1) {
				view_port.moveRectangle(warna_border, frame, 1, 0);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			}
		}
		else if(ch == 0x44) { // left-arrow key
			if(view_port.GetPoint().GetAbsis()>canvas_topleft.GetAbsis()) {
				view_port.moveRectangle(warna_border, frame, -1, 0);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			}
		}
	}

	return 0;
}