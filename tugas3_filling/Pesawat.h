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
		void RasterScanFill(RGBcolor warnaFill);
		void FloodFill(RGBcolor warnaFill);
	private:
		RGBcolor warna;
		vector<Point> NTitik;
		DrawingObject gambar;
		FrameBuffer fBuff;
		int x_kiri;
		int x_kanan;
		int y_atas;
		int y_bawah;
};

#endif