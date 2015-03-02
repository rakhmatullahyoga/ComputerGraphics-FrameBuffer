#ifndef OBJECT_H
#define OBJECT_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Pattern.h"
#include <string>
#include <vector>
using namespace std;

class Object{
	public:
		Object(string filename);
		~Object();
		void SetWarna(RGBcolor warna);
		void Geser(int x, int y,FrameBuffer fBuff);
		void Draw(FrameBuffer fBuff);
		void Hapus(FrameBuffer fBuff);
		void RasterScanFill(RGBcolor warnaFill,FrameBuffer fBuff);
		void FloodFill(RGBcolor warnaFill,FrameBuffer fBuff);
		void DrawPattern(Pattern pola, FrameBuffer fBuff, RGBcolor warna);
		void Putar(float drj, int xpusat, int ypusat);
		void Skala(float skalax, float skalay);
		bool IsVPoint(int x, int y);
		void ScanLineFill(RGBcolor warna, FrameBuffer fBuff);
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