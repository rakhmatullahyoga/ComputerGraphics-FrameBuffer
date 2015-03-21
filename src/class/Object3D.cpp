#include "Object3D.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
Object3D::Object3D(){

}
Object3D::Object3D(string filename){
	string line;
	string dir = "../src/assets/";
	int a,b;
	Point titik;
	dir.append(filename);
  	ifstream myfile (dir.c_str());
  	if (myfile.is_open()){
  		getline (myfile,line);
  		a = atoi(line.substr (0,line.find(",")).c_str());
      	b = atoi(line.substr (line.find(",")+1).c_str());
      	LayerPoint.SetAbsis(a);
      	LayerPoint.SetOrdinat(b);
      	while ( getline (myfile,line) ){
      		a = atoi(line.substr (0,line.find(",")).c_str());
      		b = atoi(line.substr (line.find(",")+1).c_str());
      		titik.SetAbsis(a+LayerPoint.GetAbsis());
      		titik.SetOrdinat(b+LayerPoint.GetOrdinat());
      		NTitik.push_back(titik);
    	}
    	myfile.close();
  	}
	else cout << "Unable to open file: " << dir << endl;
	warnaGaris.setRGB(255,255,255);
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
	//set titik hilang
	vanishingPoint1.SetAbsis(450);
	vanishingPoint1.SetOrdinat(100);
}
Object3D::~Object3D(){

}
int Object3D::GetKiri() {
	return x_kiri;
}
int Object3D::GetKanan() {
	return x_kanan;
}
int Object3D::GetAtas() {
	return y_atas;
}
int Object3D::GetBawah() {
	return y_bawah;
}
void Object3D::Draw(FrameBuffer fBuff){
	gambar.plotListOfPoint(NTitik,warnaGaris,fBuff);
	gambar.plotListOfPoint(TitikProyeksi,warnaGaris,fBuff);
	for(int i=0;i<NTitik.size();i++){
		gambar.plotLine(NTitik.at(i),TitikProyeksi.at(i),warnaGaris,fBuff);
	}
}
void Object3D::Make3D(){
	if(!TitikProyeksi.empty()) {
		TitikProyeksi.clear();
	}
	Skala(0.9,0.9);
}
void Object3D::Skala(float skalax, float skalay){
	int xpusat = vanishingPoint1.GetAbsis();
	int ypusat = vanishingPoint1.GetOrdinat();
	float xbaru, ybaru;
	int x,y, xbaruInt, ybaruInt;
	for(int i=0; i<NTitik.size();i++){
		x = NTitik.at(i).GetAbsis();
		y = NTitik.at(i).GetOrdinat();
		xbaru = xpusat + (x-xpusat)*skalax;
		ybaru = ypusat + (y-ypusat)*skalay;
		xbaruInt = (int)(xbaru+0.5);
		ybaruInt = (int)(ybaru+0.5);
		Point A(xbaruInt,ybaruInt);
		TitikProyeksi.push_back(A);
	}
}
void Object3D::Geser(int x, int y, FrameBuffer fBuff){
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
	Make3D();
	Draw(fBuff);
}
void Object3D::GeserTitikHilang(int x, int y, FrameBuffer fBuff) {
	Hapus(fBuff);
	vanishingPoint1.SetAbsis(vanishingPoint1.GetAbsis()+x);
	vanishingPoint1.SetOrdinat(vanishingPoint1.GetOrdinat()+y);
	Make3D();
	Draw(fBuff);
}
void Object3D::Hapus(FrameBuffer fBuff){
 	RGBcolor hitam;
 	hitam.setRGB(1,1,1);
	gambar.plotListOfPoint(NTitik,hitam,fBuff);
	gambar.plotListOfPoint(TitikProyeksi,hitam,fBuff);
	for(int i=0;i<NTitik.size();i++){
		gambar.plotLine(NTitik.at(i),TitikProyeksi.at(i),hitam,fBuff);
	}
}