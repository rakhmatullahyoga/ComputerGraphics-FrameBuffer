#ifndef PESAWAT_H
#define PESAWAT_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include <vector>
using namespace std;

class Pesawat{
	public:
		Pesawat();
		~Pesawat();
		void SetWarna(int R, int G, int B);
		void Geser(int x, int y);
		void Draw();
		void Hapus();
	private:
		RGBcolor warna;
		vector<Point> NTitik;
		DrawingObject gambar;
		FrameBuffer fBuff;
};

#endif