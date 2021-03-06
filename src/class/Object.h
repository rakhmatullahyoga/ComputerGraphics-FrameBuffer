#ifndef OBJECT_H
#define OBJECT_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Pattern.h"
#include "Line.h"
#include <string>
#include <vector>
using namespace std;

class Object{
	public:
		Object();
		Object(string filename);
		~Object();
		void setUpObject(vector<Point> points);
		void updateFillColor(FrameBuffer fBuff);
		void SetWarna(RGBcolor warna);
		void Geser(int x, int y,FrameBuffer fBuff);
		void Draw(FrameBuffer fBuff);
		void Hapus(FrameBuffer fBuff);
		void RasterScanFill(RGBcolor warnaFill,FrameBuffer fBuff);
		void FloodFill(RGBcolor warnaFill,FrameBuffer fBuff);
		void DrawPattern(Pattern pola, FrameBuffer fBuff, RGBcolor warna);
		void Putar(float drj, int xpusat, int ypusat, FrameBuffer fBuff);
		void Skala(float skalax, float skalay);
		bool IsVPoint(int x, int y);
		void ScanLineFill(RGBcolor warna, FrameBuffer fBuff);
		void CreateRectangle(Point top_left_corner, int height, int width);
		vector<Point> GetNTitik();
		Point GetKiriAtas();
		int GetKiri();
		int GetKanan();
		int GetAtas();
		int GetBawah();
		RGBcolor GetWarna();
		int findRegion(int x, int y);
		int findRegionAtas(int x, int y);
		int findRegionSamping(int x, int y);
		void DrawLegend(FrameBuffer fBuff);
		void HapusLegend(FrameBuffer fBuff);
		void SkalaLegend(float skalax, float skalay, Point legend_topleft, int sizex, int sizey);
		void clipLine(Point P1, Point P2, FrameBuffer fBuff,Point view_topleft, Point legend_topleft);
		void antiClip(Point P1, Point P2, FrameBuffer fBuff);
		void antiClipAtas(Point P1, Point P2, FrameBuffer fBuff);
		void antiClipSamping(Point P1, Point P2, FrameBuffer fBuff);
		void CreateClip(vector<Object> kumpulanobject, FrameBuffer fBuff,Point view_topleft, Point legend_topleft);
		void CreateAntiClip(vector<Object> kumpulanobject, FrameBuffer fBuff);
		void Make3D(FrameBuffer fBuff);
		void Hapus3D(FrameBuffer fBuff);
	private:
		RGBcolor warnaGaris;
		RGBcolor fillColor;
		vector<Point> NTitik;
		DrawingObject gambar;
		int x_kiri;
		int x_kanan;
		int y_atas;
		int y_bawah;
		int point1_x;
		int point1_y;
		int point2_x;
		int point2_y;
		vector<Point> TitikLegend;
};

#endif
