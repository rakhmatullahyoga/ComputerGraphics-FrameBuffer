#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Map::Map() {
	sumatra = new Object("maps/sumatra.txt");
	jawa = new Object("maps/jawa.txt");
	kalimantan = new Object("maps/kalimantan.txt");
	sulawesi = new Object("maps/sulawesi.txt");
	papua = new Object("maps/papua.txt");
	maluku = new Object("maps/maluku.txt");
	maluku2 = new Object("maps/maluku2.txt");
	maluku3 = new Object("maps/maluku3.txt");
	bali = new Object("maps/bali.txt");
	lombok = new Object("maps/lombok.txt");
	ntb = new Object("maps/ntb.txt");
	ntt = new Object("maps/ntt.txt");
}
Map::~Map(){
	delete sumatra;
	delete jawa;
	delete kalimantan;
	delete sulawesi;
	delete papua;
	delete maluku;
	delete maluku2;
	delete maluku3;
	delete bali;
	delete lombok;
	delete ntb;
	delete ntt;
}

void Map::Draw(FrameBuffer frame){
	sumatra->Draw(frame);
	jawa->Draw(frame);
	kalimantan->Draw(frame);
	sulawesi->Draw(frame);
	papua->Draw(frame);
	maluku->Draw(frame);
	maluku2->Draw(frame);
	maluku3->Draw(frame);
	bali->Draw(frame);
	lombok->Draw(frame);
	ntb->Draw(frame);
	ntt->Draw(frame);
}

Object Map::GetObject(string nama){
	if(nama == "sumatra")
		return *sumatra;
	if(nama == "jawa")
		return *jawa;
	if(nama == "kalimantan")
		return *kalimantan;
	if(nama == "sulawesi")
		return *sulawesi;
	if(nama == "papua")
		return *papua;
	if(nama == "maluku")
		return *maluku;
	if(nama == "maluku2")
		return *maluku2;
	if(nama == "maluku3")
		return *maluku3;
	if(nama == "bali")
		return *bali;
	if(nama == "lombok")
		return *lombok;
	if(nama == "ntt")
		return *ntt;
	if(nama == "ntb")
		return *ntb;
}
