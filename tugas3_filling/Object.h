#ifndef OBJECT_H
#define OBJECT_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include <string>
#include <vector>
using namespace std;

class Object{
	public:
		Object(string filename);
		~Object();
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
		int x_kiri;
		int x_kanan;
		int y_atas;
		int y_bawah;
};

#endif