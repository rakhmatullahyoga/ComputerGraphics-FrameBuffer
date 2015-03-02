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
void Object::Geser(int x, int y, FrameBuffer fBuff){
	//Point currentp;
	Hapus(fBuff);
	for(int i=0; i<NTitik.size();i++){
		NTitik.at(i).SetAbsis(NTitik.at(i).GetAbsis()+x);
		NTitik.at(i).SetOrdinat(NTitik.at(i).GetOrdinat()+y);
	}
	/* Geser floodfill point */
	x_kiri += x;
	x_kanan += x;
	y_atas += y;
	y_bawah += y;
	Draw(fBuff);
}
void Object::Draw(FrameBuffer fBuff){
	gambar.plotListOfPoint(NTitik,warna,fBuff);
}
void Object::Hapus(FrameBuffer fBuff){
	// algo lama, cuma menghapus garis
	/*RGBcolor hitam;
	hitam.setRGB(0,0,0);
	gambar.plotListOfPoint(NTitik,hitam,fBuff);*/
	// algo baru, menghapus satu blok persegi
	for(int i=y_atas; i<=y_bawah; i++) {
		for(int j=x_kiri; j<=x_kanan; j++) {
			int location = j * (fBuff.vinfo.bits_per_pixel/8) + i * fBuff.finfo.line_length;
			if ( fBuff.vinfo.bits_per_pixel == 32 ) {
				*(fBuff.fbp + location) = 0;
				*(fBuff.fbp + location + 1) = 0;
				*(fBuff.fbp + location + 2) = 0;
			}
		}
	}
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
void Object::Putar(float drj, int xpusat, int ypusat){
	int x,y,xbaruInt,ybaruInt;
	float xbaru, ybaru;
	float sinus, cosinus;
	for(int i=0; i<NTitik.size();i++){
		x = NTitik.at(i).GetAbsis();
		y = NTitik.at(i).GetOrdinat();
		sinus = sin(drj*PI/180);
		cosinus = cos(drj*PI/180);
		xbaru = (x-xpusat)*cosinus - (y-ypusat)*sinus + xpusat;
		ybaru = (x-xpusat)*sinus + (y-ypusat)*cosinus + ypusat;
		if (xbaru>=0)
			xbaruInt = (int)(xbaru+0.5);
		else
			xbaruInt = (int)(xbaru-0.5);
		if (ybaru>=0)
			ybaruInt = (int)(ybaru+0.5);
		else
			ybaruInt = (int)(ybaru-0.5);
		NTitik.at(i).SetAbsis(xbaruInt);
		NTitik.at(i).SetOrdinat(ybaruInt);
	}
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
bool Object::IsVPoint(int x, int y) {
	int i = 0;
	bool found = false;
	bool v_point = false;
	while((i<NTitik.size())&&!found) {
		if(x==NTitik.at(i).GetAbsis()&&y==NTitik.at(i).GetOrdinat()) {
			if(((NTitik.at(i-1).GetOrdinat()<y)&&(NTitik.at(i+1).GetOrdinat()<y))||((NTitik.at(i-1).GetOrdinat()>y)&&(NTitik.at(i+1).GetOrdinat()>y))) {
				v_point = true;
			}
			else {
				if((NTitik.at(i-1).GetOrdinat()<y)&&(NTitik.at(i+1).GetOrdinat()==y))
					v_point = (NTitik.at(i+2).GetOrdinat()<y);
				else if((NTitik.at(i-1).GetOrdinat()>y)&&(NTitik.at(i+1).GetOrdinat()==y))
					v_point = (NTitik.at(i+2).GetOrdinat()>y);
				else if((NTitik.at(i-1).GetOrdinat()==y)&&(NTitik.at(i+1).GetOrdinat()>y))
					v_point = (NTitik.at(i-2).GetOrdinat()>y);
				else if((NTitik.at(i-1).GetOrdinat()==y)&&(NTitik.at(i+1).GetOrdinat()<y))
					v_point = (NTitik.at(i-2).GetOrdinat()<y);
			}
			found = true;
		}
		else {
			i++;
		}
	}
	return v_point;
}
void Object::ScanLineFill(RGBcolor warna, FrameBuffer fBuff) {
	bool filling;
	for(int i=y_atas; i<=y_bawah; i++) {
		filling = false;
		for(int j=x_kiri; j<=x_kanan; j++) {
			if(!fBuff.isBlack(j,i)) {
				if(!IsVPoint(j,i)) {
					filling = !filling;
				}
			}
			else {
				if(filling) {
					int location = j * (fBuff.vinfo.bits_per_pixel/8) + i * fBuff.finfo.line_length;
					*(fBuff.fbp + location) = warna.getBlue();
					*(fBuff.fbp + location + 1) = warna.getGreen();
					*(fBuff.fbp + location + 2) = warna.getRed();
				}
			}
		}
	}
}
void Object::Skala(float skalax, float skalay){
	int xpusat = (x_kiri+x_kanan)/2;
	int ypusat = (y_atas+y_bawah)/2;
	float xbaru, ybaru;
	int x,y, xbaruInt, ybaruInt;
	for(int i=0; i<NTitik.size();i++){
		x = NTitik.at(i).GetAbsis();
		y = NTitik.at(i).GetOrdinat();
		xbaru = xpusat + (x-xpusat)*skalax;
		ybaru = ypusat + (y-ypusat)*skalay;
		xbaruInt = (int)(xbaru+0.5);
		ybaruInt = (int)(ybaru+0.5);
		NTitik.at(i).SetAbsis(xbaruInt);
		NTitik.at(i).SetOrdinat(ybaruInt);
	}

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