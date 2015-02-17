#ifndef KAPAL_H
#define KAPAL_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include <vector>
using namespace std;

class Kapal{
	public:
		Kapal();
		~Kapal();
		void SetWarna(int R, int G, int B);
		void Geser(int x, int y);
		void Draw(FrameBuffer fBuff);
		void Hapus(FrameBuffer fBuff);
		void RasterScanFill(RGBcolor warnaFill,FrameBuffer fBuff);
		void FloodFill(RGBcolor warnaFill,FrameBuffer fBuff);
	private:
		RGBcolor warna;
		vector<Point> NTitik;
		DrawingObject gambar;
		//FrameBuffer fBuff;
		int x_kiri;
		int x_kanan;
		int y_atas;
		int y_bawah;
};

#endif