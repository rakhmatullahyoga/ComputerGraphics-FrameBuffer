#include "Object.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

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
void Object::SetWarna(int R, int G, int B){
	warna.setRGB(R,G,B);	
}
void Object::Geser(int x, int y){
	Point currentp;
	for(int i=0; i<NTitik.size();i++){
		NTitik.at(i).SetAbsis(NTitik.at(i).GetAbsis()+x);
		NTitik.at(i).SetOrdinat(NTitik.at(i).GetOrdinat()+y);
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