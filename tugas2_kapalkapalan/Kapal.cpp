#include "Kapal.h"
#include "DrawingObject.h"
Kapal::Kapal() {}

Kapal::Kapal(Point body, Point turret, int ht, int wt, int hb, int wb, RGBcolor color,FrameBuffer fBuff) {
	this->ht = ht;
	this->wt = wt;
	this->hb = hb;
	this->wb = wb;
	this->body = body;
	this->turret = turret;
	this->color = color;
	this->fBuff = fBuff;
}

Kapal::~Kapal() {}

Point Kapal::getTurretPos() {
	return turret;
}

Point Kapal::getBodyPos() {
	return body;
}

int Kapal::getBodyHeight() {
	return hb;
}

int Kapal::getBodyWidth() {
	return wb;
}

int Kapal::getTurretHeight() {
	return ht;
}

int Kapal::getTurretWidth() {
	return wt;
}


void Kapal::setBodyPoint(int x, int y) {
	Point point;
	point.SetAbsis(x);
	point.SetOrdinat(y);

	body = point;
}
void Kapal::setTurretPoint(int x, int y) {
	Point point;
	point.SetAbsis(x);
	point.SetOrdinat(y);

	turret = point;
}

void Kapal::setColor(RGBcolor color) {
	this->color = color;
}

RGBcolor Kapal::getColor() {
	return color;
}

FrameBuffer Kapal::getFbuffer() {
	return fBuff;
}

void Kapal::drawKapal() {
	DrawingObject draw;
	draw.drawRectangle(getBodyPos(),getBodyHeight(),getBodyWidth(),getColor(),getFbuffer());
	draw.drawRectangle(getTurretPos(),getTurretHeight(),getTurretWidth(),getColor(),getFbuffer());
}