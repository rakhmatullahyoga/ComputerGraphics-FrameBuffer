#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"

FrameBuffer frame;
void Meledak (int xpusat, int ypusat);
void antiLedak (int xpusat, int ypusat);
int main(int argc, char const *argv[])
{
	RGBcolor color,hapus;
	DrawingObject draw, Circle, pesawat;
	Point start, finish;
	int height = 50;
	int width = 100;
	hapus.setRed(0);
	hapus.setGreen(0);
	hapus.setBlue(0);
	color.setRed(255);
	color.setGreen(255);
	color.setBlue(255);
	start.SetAbsis(250);
	start.SetOrdinat(10);
	/*atribut Peluru*/
	RGBcolor warnaPeluru;
	Point peluruStart;
	int radpeluru = 5;
	warnaPeluru.setRed(255);
	warnaPeluru.setGreen(255);
	warnaPeluru.setBlue(0);
	peluruStart.SetAbsis(300);
	peluruStart.SetOrdinat(300);

	system("clear");
	pesawat.drawRectangle(start,50,100,color,frame);
	//draw.drawRectangle(start, height, width, color, frame);
	//draw.animateRectangle(start, height, width, color, frame, 1, 0);

	/*Objek Buatan*/


	bool meledak = false;
	while((peluruStart.GetOrdinat()>10) && !meledak){
		if(frame.isBlack(peluruStart.GetAbsis(),peluruStart.GetOrdinat()-radpeluru)){
			Circle.plotCircle(peluruStart,radpeluru,warnaPeluru,frame);
			usleep(5000);
			Circle.plotCircle(peluruStart,radpeluru,hapus,frame);
			peluruStart.SetOrdinat(peluruStart.GetOrdinat()-1);
		}
		else{
			Meledak(peluruStart.GetAbsis(),peluruStart.GetOrdinat());
			antiLedak(peluruStart.GetAbsis(),peluruStart.GetOrdinat());
			meledak = true;
		}
	}


	return 0;
}

void Meledak (int xpusat, int ypusat){
	DrawingObject Ledakan;
	RGBcolor warnaLedakan;
	warnaLedakan.setRed(255);
	warnaLedakan.setBlue(0);
	Point titikLedak;
	titikLedak.SetAbsis(xpusat);
	titikLedak.SetOrdinat(ypusat);
 	for(int radLedak=1; radLedak<=32; radLedak++){
 		warnaLedakan.setGreen(256-radLedak*7);
   		Ledakan.plotCircle(titikLedak,radLedak,warnaLedakan,frame);
   		usleep(10000);
 	}
}

void antiLedak (int xpusat, int ypusat){
	DrawingObject Ledakan;
	RGBcolor warnaLedakan;
	warnaLedakan.setRed(0);
	warnaLedakan.setGreen(0);
	warnaLedakan.setBlue(0);
	Point titikLedak;
	titikLedak.SetAbsis(xpusat);
	titikLedak.SetOrdinat(ypusat);
 	for(int radLedak=1; radLedak<=32; radLedak++){
   		Ledakan.plotCircle(titikLedak,radLedak,warnaLedakan,frame);
   		usleep(20000);
 	}
}