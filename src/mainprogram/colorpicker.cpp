#include "FrameBuffer.h"
#include <iostream>
using namespace std;
int main() {
	FrameBuffer frame;
	RGBcolor tes;
	frame.clear();
	tes = frame.drawColorPicker();
	cout << "Hasil" << endl;
	cout << "R=" << tes.getRed() << endl;
	cout << "G=" << tes.getGreen() << endl;
	cout << "B=" << tes.getBlue() << endl;
	return 0;
}
