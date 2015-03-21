#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Line.h"
#include <string>
#include <vector>

class Object3D{
	public:
		Object3D();
		Object3D(string filename);
		~Object3D();
		void SetWarna(RGBcolor warna);
		void Geser(int x, int y,FrameBuffer fBuff);
		void Draw(FrameBuffer fBuff);
		void Hapus(FrameBuffer fBuff);
		vector<Point> GetNTitik();
		Point GetKiriAtas();
		int GetKiri();
		int GetKanan();
		int GetAtas();
		int GetBawah();
	private:
		RGBcolor warnaGaris;
		vector<Point> NTitik;
		vector<Point> TitikProyeksi;
		DrawingObject gambar;
		Point LayerPoint;
		Point vanishingPoint1;
		int x_kiri;
		int x_kanan;
		int y_atas;
		int y_bawah;
};

#endif