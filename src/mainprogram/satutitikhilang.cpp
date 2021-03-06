#include "Object3D.h"
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

FrameBuffer frame;
int main(){
	system("clear");
	Object3D box1("objects/box.txt");
	box1.Make3D();
	box1.Draw(frame);

	Object3D box2("objects/box2.txt");
	box2.Make3D();
	box2.Draw(frame);

	Object3D box3("objects/box3.txt");
	box3.Make3D();
	box3.Draw(frame);

	while(true) {
		int ch = _getch();
		if(ch == 0x41) { // up-arrow key
			box1.Geser(0, 10, frame);
			box2.Geser(0, 10, frame);
			box3.Geser(0, 10, frame);
		}
		else if(ch == 0x42) { // down-arrow key
			box1.Geser(0, -10, frame);
			box2.Geser(0, -10, frame);
			box3.Geser(0, -10, frame);
		}
		else if(ch == 0x43) { // right-arrow key
			box1.Geser(-10, 0, frame);
			box2.Geser(-10, 0, frame);
			box3.Geser(-10, 0, frame);
		}
		else if(ch == 0x44) { // left-arrow key
			box1.Geser(10, 0, frame);
			box2.Geser(10, 0, frame);
			box3.Geser(10, 0, frame);
		}
		else if(ch == 'w') {
			box1.GeserTitikHilang(0, -10, frame);
			box2.GeserTitikHilang(0, -10, frame);
			box3.GeserTitikHilang(0, -10, frame);
		}
		else if(ch == 's') {
			box1.GeserTitikHilang(0, 10, frame);
			box2.GeserTitikHilang(0, 10, frame);
			box3.GeserTitikHilang(0, 10, frame);
		}
		else if(ch == 'a') {
			box1.GeserTitikHilang(-10, 0, frame);
			box2.GeserTitikHilang(-10, 0, frame);
			box3.GeserTitikHilang(-10, 0, frame);
		}
		else if(ch == 'd') {
			box1.GeserTitikHilang(10, 0, frame);
			box2.GeserTitikHilang(10, 0, frame);
			box3.GeserTitikHilang(10, 0, frame);
		}
		else if(ch == 'q') {
			system("clear");
			break;
		}
	}
	return 0;
}