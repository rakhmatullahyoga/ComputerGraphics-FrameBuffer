#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

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

vector<Point> Map::getTitik() {
	vector<Point> titik = sumatra->GetNTitik();
	vector<Point> a,b,c,d,e,f,g,h,i,j,k,l;
	a = jawa->GetNTitik();
	b = kalimantan->GetNTitik();
	c = sulawesi->GetNTitik();
	d = papua->GetNTitik();
	e = maluku->GetNTitik();
	f = maluku2->GetNTitik();
	g = maluku3->GetNTitik();
	h = bali->GetNTitik();
	i = lombok->GetNTitik();
	j = ntb->GetNTitik();
	k = ntt->GetNTitik();
	
	titik.reserve(titik.size() + a.size() 
		+ b.size() + c.size() + d.size() + e.size()
		+ f.size()
		+ g.size()
		+ h.size()
		+ i.size()
		+ j.size()
		+ k.size()
		);

	titik.insert(titik.end(), a.begin(), a.end());
	titik.insert(titik.end(), b.begin(), b.end());
	titik.insert(titik.end(), c.begin(), c.end());
	titik.insert(titik.end(), d.begin(), d.end());
	titik.insert(titik.end(), e.begin(), e.end());
	titik.insert(titik.end(), f.begin(), f.end());
	titik.insert(titik.end(), g.begin(), g.end());
	titik.insert(titik.end(), h.begin(), h.end());
	titik.insert(titik.end(), i.begin(), i.end());
	titik.insert(titik.end(), j.begin(), j.end());
	titik.insert(titik.end(), k.begin(), k.end());

	return titik;
}

