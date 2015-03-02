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
	Object viewport;
	RGBcolor warna_border;
	warna_border.setRGB(255,255,255);
	viewport.SetWarna(warna_border);
	Point canvas_topleft(50,50);
	Point view_topleft(200,200);
	Point legend_topleft(1016,516);

	system("clear");
	viewport.CreateRectangle(view_topleft, 200, 300);
	viewport.Draw(frame);
	map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
	//view_port.drawRectangle(view_topleft,200,200,warna_border,frame);
	legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
	Object sumatra("maps/sumatra.txt");
	sumatra.Draw(frame);
	Object jawa("maps/jawa.txt");
	jawa.Draw(frame);
	Object kalimantan("maps/kalimantan.txt");
	kalimantan.Draw(frame);
	Object sulawesi("maps/sulawesi.txt");
	sulawesi.Draw(frame);
	Object papua("maps/papua.txt");
	papua.Draw(frame);
	Object maluku("maps/maluku.txt");
	maluku.Draw(frame);
	Object maluku2("maps/maluku2.txt");
	maluku2.Draw(frame);
	Object maluku3("maps/maluku3.txt");
	maluku3.Draw(frame);
	Object bali("maps/bali.txt");
	bali.Draw(frame);
	Object lombok("maps/lombok.txt");
	lombok.Draw(frame);
	Object ntb("maps/ntb.txt");
	ntb.Draw(frame);
	Object ntt("maps/ntt.txt");
	ntt.Draw(frame);
	while(true) {
		int ch = _getch();
		if(ch == 0x41) { // up-arrow key
			// if(view_port.GetPoint().GetOrdinat()>canvas_topleft.GetOrdinat()) {
				viewport.Geser(0,-5,frame);
				//view_port.moveRectangle(warna_border, frame, 0, -1);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			// }
		}
		else if(ch == 0x42) { // down-arrow key
			// if(view_port.GetPoint().GetOrdinat()+200<canvas_topleft.GetOrdinat()+666-1) {
				viewport.Geser(0,5,frame);
				//view_port.moveRectangle(warna_border, frame, 0, 1);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			// }
		}
		else if(ch == 0x43) { // right-arrow key
			// if(view_port.GetPoint().GetAbsis()+200<canvas_topleft.GetAbsis()+1266-1) {
				viewport.Geser(5,0,frame);
				//view_port.moveRectangle(warna_border, frame, 1, 0);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			// }
		}
		else if(ch == 0x44) { // left-arrow key
			// if(view_port.GetPoint().GetAbsis()>canvas_topleft.GetAbsis()) {
				viewport.Geser(-5,0,frame);
				//view_port.moveRectangle(warna_border, frame, -1, 0);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			// }
		}
		else if(ch == 'z'){
			viewport.Hapus(frame);
			viewport.Skala(0.9,0.9);
			viewport.Draw(frame);
		}
		else if(ch == 'c'){
			viewport.Hapus(frame);
			viewport.Skala(1.111,1.111);
			viewport.Draw(frame);
		}
	}

	return 0;
}