#include "Object3D.h"
#include <iostream>

using namespace std;
FrameBuffer frame;
int main(){
	system("clear");
	Object3D box("objects/box.txt");
	box.Make3D();
	box.Draw(frame);
	return 0;
}