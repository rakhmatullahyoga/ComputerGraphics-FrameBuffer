#include "Object.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
#define PI 3.14159265

Object::Object(string filename){
	string line;
	int a,b;
	Point titik;
  	ifstream myfile (filename.c_str());
  	if (myfile.is_open()){
    	while ( getline (myfile,line) ){

      		a = atoi(line.substr (0,line.find(",")).c_str());
      		b = atoi(line.substr (line.find(",")+1).c_str());
      		titik.SetAbsis(a);
      		titik.SetOrdinat(b);
      		NTitik.push_back(titik);
    	}
    	myfile.close();
  	}
	else cout << "Unable to open file";
	warna.setRGB(255,255,255);
	x_kiri = x_kanan = NTitik.at(0).GetAbsis();
	y_atas = y_bawah = NTitik.at(0).GetOrdinat();
	for(int i=1; i<NTitik.size();i++){
		if(x_kiri > NTitik.at(i).GetAbsis()){
			x_kiri = NTitik.at(i).GetAbsis();
		}
		else if(x_kanan <NTitik.at(i).GetAbsis()){
			x_kanan = NTitik.at(i).GetAbsis();	
		}
		if(y_atas > NTitik.at(i).GetOrdinat()){
			y_atas = NTitik.at(i).GetOrdinat();
		}
		else if(y_bawah < NTitik.at(i).GetOrdinat()){
			y_bawah = NTitik.at(i).GetOrdinat();	
		}
	}
}
Object::~Object(){

}
void Object::SetWarna(RGBcolor warna){
	warna.setRGB(warna.getRed(), warna.getGreen(), warna.getBlue());	
}
void Object::Geser(int x, int y){
	Point currentp;
	for(int i=0; i<NTitik.size();i++){
		NTitik.at(i).SetAbsis(NTitik.at(i).GetAbsis()+x);
		NTitik.at(i).SetOrdinat(NTitik.at(i).GetOrdinat()+y);
		/* Geser floodfill point */
		x_kiri = x_kanan = NTitik.at(0).GetAbsis();
		y_atas = y_bawah = NTitik.at(0).GetOrdinat();
		for(int i=1; i<NTitik.size();i++){
			if(x_kiri > NTitik.at(i).GetAbsis()){
				x_kiri = NTitik.at(i).GetAbsis();
			}
			else if(x_kanan <NTitik.at(i).GetAbsis()){
				x_kanan = NTitik.at(i).GetAbsis();	
			}
			if(y_atas > NTitik.at(i).GetOrdinat()){
				y_atas = NTitik.at(i).GetOrdinat();
			}
			else if(y_bawah < NTitik.at(i).GetOrdinat()){
				y_bawah = NTitik.at(i).GetOrdinat();	
			}
		}
	}
}
void Object::Draw(FrameBuffer fBuff){
	gambar.plotListOfPoint(NTitik,warna,fBuff);
}
void Object::Hapus(FrameBuffer fBuff){
	RGBcolor hitam;
	hitam.setRGB(0,0,0);
	gambar.plotListOfPoint(NTitik,hitam,fBuff);
}
void Object::RasterScanFill(RGBcolor warnaFill, FrameBuffer fBuff){
	gambar.RasterScan(x_kiri, x_kanan, y_atas, y_bawah,warnaFill,fBuff);
}
void Object::FloodFill(RGBcolor warnaFill,FrameBuffer fBuff){
	int x = (x_kiri+x_kanan)/2;
	int y = (y_bawah+y_atas)/2;
	gambar.FloodFill(x,y,warnaFill,fBuff);
}
void Object::DrawPattern(Pattern pola, FrameBuffer fBuff, RGBcolor warna) {
	Point object_top_left, object_bottom_right;
	object_top_left.SetAbsis(x_kiri);
	object_top_left.SetOrdinat(y_atas);
	object_bottom_right.SetAbsis(x_kanan);
	object_bottom_right.SetOrdinat(y_bawah);

	pola.drawPattern(object_top_left, object_bottom_right, warna, fBuff);
}
void Object::Putar(int drj, int xpusat, int ypusat){
	int x,y;
	double xbaru, ybaru;
	double sinus, cosinus;
	for(int i=0; i<NTitik.size();i++){
		x = NTitik.at(i).GetAbsis();
		y = NTitik.at(i).GetOrdinat();
		sinus = sin(drj*PI/180);
		cosinus = cos(drj*PI/180);
		xbaru = (x-xpusat)*cosinus - (y-ypusat)*sinus + xpusat;
		ybaru = (x-xpusat)*sinus + (y-ypusat)*cosinus + ypusat;
		NTitik.at(i).SetAbsis((int)(xbaru+0.5));
		NTitik.at(i).SetOrdinat((int)(ybaru+0.5));
	}
}