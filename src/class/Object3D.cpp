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
}
Object3D::~Object3D(){

}