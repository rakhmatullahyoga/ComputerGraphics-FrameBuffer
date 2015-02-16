#include "Ikan.h"
#include <iostream>
#include <fstream>
using namespace std;

Ikan::Ikan() {
	string input;
	ifstream myfile ("ikan.txt");
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

Ikan::~Ikan() {

}

void Ikan::drawPattern(int x, int y, RGBcolor warna, FrameBuffer fBuff) {
	int location;
	int absis;
	int ordinat = y;
	for(int i=0; i<11; i++) {
		absis = x;
		for(int j=0; j<23; j++) {
			if(matriks[j][i]==1) {
				location = absis * (fBuff.vinfo.bits_per_pixel/8) + ordinat * fBuff.finfo.line_length;
				*(fBuff.fbp + location) = warna.getBlue(); // Some blue 
				*(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
				*(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
				*(fBuff.fbp + location + 3) = 0; // No transparency
			}
			absis++;
		}
		ordinat++;
	}
}