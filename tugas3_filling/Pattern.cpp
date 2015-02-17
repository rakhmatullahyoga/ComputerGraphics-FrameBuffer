#include "Pattern.h"
#include <iostream>
#include <fstream>
using namespace std;

Pattern::Pattern(string filename) {
	string input;
	ifstream myfile (filename.c_str());
	if (myfile.is_open()) {
		for(int i=0; i<11; i++) {
			for(int j=0; j<23; j++) {
				myfile >> matriks[j][i];
				//matriks[i][j] = atoi(input);
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file" << endl;
}

Pattern::~Pattern() {

}

void Pattern::drawPattern(Point top_left, Point bottom_right, RGBcolor warna, FrameBuffer fBuff) {
	int location;
	int tla, tlo;
	tla = 0;
	tlo = 0;
	for(int i=top_left.GetOrdinat(); i<=bottom_right.GetOrdinat(); i++) {
		tla = 0;
		for(int j=top_left.GetAbsis(); j<bottom_right.GetAbsis(); j++) {
			if((matriks[tla%23][tlo%11]==1)&&(!fBuff.isBlack(j,i))) {
				location = j * (fBuff.vinfo.bits_per_pixel/8) + i * fBuff.finfo.line_length;
				*(fBuff.fbp + location) = warna.getBlue(); // Some blue 
				*(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
				*(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
				*(fBuff.fbp + location + 3) = 0; // No transparency
			}
			tla++;
		}
		tlo++;
	}
}