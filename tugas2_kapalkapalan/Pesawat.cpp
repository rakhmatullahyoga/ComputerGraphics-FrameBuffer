#include "Pesawat.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

Pesawat::Pesawat(){
	string line;
	int a,b;
	Point titik;
  	ifstream myfile ("pesawat.txt");
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
}
Pesawat::~Pesawat(){

}
void Pesawat::SetWarna(int R, int G, int B){
	warna.setRGB(R,G,B);	
}
void Pesawat::Geser(int x, int y){
	Point currentp;
	for(int i=0; i<NTitik.size();i++){
		NTitik.at(i).SetAbsis(NTitik.at(i).GetAbsis()+x);
		NTitik.at(i).SetOrdinat(NTitik.at(i).GetOrdinat()+y);
	}
}
void Pesawat::Draw(){
	gambar.plotListOfPoint(NTitik,warna,fBuff);
}
void Pesawat::Hapus(){
	RGBcolor hitam;
	hitam.setRGB(0,0,0);
	gambar.plotListOfPoint(NTitik,hitam,fBuff);	
}