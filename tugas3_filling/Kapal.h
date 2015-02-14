#ifndef KAPAL_H
#define KAPAL_H
#include "Point.h"
#include "RGBcolor.h"
#include "FrameBuffer.h"
class Kapal {
public:
	Kapal();
	Kapal(Point body, Point turret, int ht, int wt, int hb, int wb, RGBcolor color,FrameBuffer fBuff);
	~Kapal();
	Point getTurretPos();
	Point getBodyPos();
	int getBodyHeight();
	int getTurretHeight();
	int getBodyWidth();
	int getTurretWidth();
	void setBodyPoint(int x, int y);
	void setTurretPoint(int x, int y);
	void setColor(RGBcolor color);
	RGBcolor getColor();
	FrameBuffer getFbuffer();
	void drawKapal();
private:
	int ht, wt, hb, wb;
	Point body, turret;
	RGBcolor color;
	FrameBuffer fBuff;
};

#endif