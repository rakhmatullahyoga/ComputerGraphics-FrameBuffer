#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Pattern.h"
#include "Object.h"
#include <iostream>

using namespace std;

FrameBuffer frame;
void Meledak (int xpusat, int ypusat);
void antiLedak (int xpusat, int ypusat);

int main(int argc, char const *argv[])
{
	int x_center = 560;
	int y_center = 130;
	DrawingObject Peluru, Peluru2, Roda;
	RGBcolor black, white;
	black.setRGB(0,0,0);
	white.setRGB(255,255,255);
	/*atribut Peluru*/
	RGBcolor warnaPeluru;
	Point peluruStart,peluru2Start,roda_fall;
	int radpeluru = 5, rad_roda = 10;
	warnaPeluru.setRGB(255,255,0);

	peluruStart.SetAbsis(280);
	peluruStart.SetOrdinat(650);
	peluru2Start.SetAbsis(400);
	peluru2Start.SetOrdinat(195);

	/*Atribut Kapal*/
	Point kapalP, turretP;
	kapalP.SetAbsis(50);
	kapalP.SetOrdinat(400);
	turretP.SetAbsis(120);
	turretP.SetOrdinat(350);
	RGBcolor kapalCol;
	kapalCol.setRGB(234,34,74);
	//Kapal kapal;
	//kapal = Kapal(kapalP,turretP,50,15,50,150,kapalCol,frame);
	
	frame.clear();
	bool meledak = false;
	/*Objek Pesawat*/
	Point pesawatP_top_left, pesawatP_bottom_right;
	pesawatP_top_left.SetAbsis(300);
	pesawatP_top_left.SetOrdinat(30);
	pesawatP_bottom_right.SetAbsis(560);
	pesawatP_bottom_right.SetOrdinat(140);
	
	Object pswt("objects/pesawat2.txt");
	Pattern pattern("pattern/burung.txt");
	pswt.Draw(frame);
	//pswt.ScanLineFill(kapalCol,frame);
	//pswt.DrawPattern(pattern, frame, warnaPeluru);

	/*Baling-baling*/
	Object baling("objects/baling2.txt");
	baling.Draw(frame);
	/*Objek Kapal*/
	
	Point kapalP_top_left, kapalP_bottom_right;
	kapalP_top_left.SetAbsis(370);
	kapalP_top_left.SetOrdinat(650);
	kapalP_bottom_right.SetAbsis(550);
	kapalP_bottom_right.SetOrdinat(690);
	RGBcolor kapal2Col;
	kapal2Col.setRGB(0,0,200);
	Object kapal("objects/Kapal2.txt"); 	
	Pattern pattern2("pattern/ikan.txt");
	kapal.Draw(frame);
	//kapal.ScanLineFill(kapal2Col,frame);
	//kapal.DrawPattern(pattern2, frame, warnaPeluru);

	/*Objek Buatan*/
	for(int i=1;i<50;i++){
		//pswt.Draw(frame);
		//baling.Draw(frame);
		//pswt.ScanLineFill(kapalCol,frame);
		//pswt.DrawPattern(pattern, frame, warnaPeluru);
		//kapal.SetWarna(kapalCol);
		//kapal.Draw(frame);
		//kapal.ScanLineFill(kapal2Col,frame);
		//kapal.DrawPattern(pattern2, frame, warnaPeluru);
		usleep(10000);
		//pswt.Hapus(frame);
		//kapal.Hapus(frame);
		//baling.Hapus(frame);
		//kapal geser
		kapal.Geser(3,0,frame);
		pswt.Geser(-1,0,frame);
		baling.Geser(-1,0,frame);
		x_center--;
		baling.Putar(12,x_center,y_center,frame);
	}

	while((peluruStart.GetOrdinat()>10) && !meledak){
		pswt.Draw(frame);
		baling.Draw(frame);
		//pswt.ScanLineFill(kapalCol,frame);
		//pswt.DrawPattern(pattern, frame, warnaPeluru);
		kapal.SetWarna(kapalCol);
		kapal.Draw(frame);
		//kapal.ScanLineFill(kapal2Col,frame);
		//kapal.DrawPattern(pattern2, frame, warnaPeluru);
		if(frame.isBlack(peluruStart.GetAbsis(),peluruStart.GetOrdinat()-radpeluru)){
			Peluru.plotCircle(peluruStart,radpeluru,warnaPeluru,frame);
			//Peluru.FloodFill(peluruStart.GetAbsis(), peluruStart.GetOrdinat(), warnaPeluru, frame);
			Peluru2.plotCircle(peluru2Start,radpeluru,warnaPeluru,frame);
			//Peluru2.FloodFill(peluru2Start.GetAbsis(), peluruStart.GetOrdinat(), warnaPeluru, frame);
			usleep(10000);
			Peluru.plotCircle(peluruStart,radpeluru,black,frame);
			Peluru2.plotCircle(peluru2Start,radpeluru,black,frame);
			peluruStart.SetOrdinat(peluruStart.GetOrdinat()-5);
			peluru2Start.SetOrdinat(peluru2Start.GetOrdinat()+5);
			//pswt.Hapus(frame);
			//baling.Hapus(frame);
			pswt.Geser(-1,0,frame);
			//kapal.Hapus(frame);
			//kapal.SetWarna(black);
			//kapal.drawKapal();
			//kapal geser
			//kapal.setBodyPoint(kapal.getBodyPos().GetAbsis()+1, kapal.getBodyPos().GetOrdinat());
			//kapal.setTurretPoint(kapal.getTurretPos().GetAbsis()+1, kapal.getTurretPos().GetOrdinat());
			kapal.Geser(3,0,frame);
			baling.Geser(-1,0,frame);
			x_center--;
			baling.Putar(12,x_center,y_center,frame);
		}
		else{
			Meledak(peluruStart.GetAbsis(),peluruStart.GetOrdinat());
			antiLedak(peluruStart.GetAbsis(),peluruStart.GetOrdinat());
			roda_fall.SetAbsis(peluruStart.GetAbsis());
			roda_fall.SetOrdinat(peluruStart.GetOrdinat()+rad_roda);
			int t= 400, c = 1;
			int y = roda_fall.GetOrdinat();
			Point roda_bouncing = roda_fall;
			int g = 15;
			for (int x = roda_fall.GetAbsis()+1; x<roda_fall.GetAbsis()+63; x++) {
				usleep(10000);
				Roda.plotCircle(roda_bouncing, rad_roda, black, frame);
				if(y >= roda_fall.GetOrdinat()+490) {
					c = 0;
					t -= 20;
					g -= 5;
				}
				if (y <=roda_fall.GetOrdinat()+750-t) {
					c=1;
				}
				y = y + (c?g: -g);
				roda_bouncing.SetAbsis(x);
				roda_bouncing.SetOrdinat(y);
				Roda.plotCircle(roda_bouncing, rad_roda, white, frame);
			}
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
 	for(int radLedak=1; radLedak<=50; radLedak++){
 		warnaLedakan.setGreen(256-radLedak*4.48);
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
 	for(int radLedak=1; radLedak<=50; radLedak++){
   		Ledakan.plotCircle(titikLedak,radLedak,warnaLedakan,frame);
   		usleep(20000);
 	}
}