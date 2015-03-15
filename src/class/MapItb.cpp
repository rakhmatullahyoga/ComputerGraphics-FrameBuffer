#include "MapItb.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

MapItb::MapItb()
{
    albar = new Object("maps/albar.txt");
    altim = new Object("maps/altim.txt");
    ccbar = new Object("maps/ccbar.txt");
    cctim = new Object("maps/cctim.txt");
    lab5 = new Object("maps/lab5.txt");
    lab6 = new Object("maps/lab6.txt");
    lab7 = new Object("maps/lab7.txt");
    lab8 = new Object("maps/lab8.txt");
    tvst = new Object("maps/tvst.txt");
    oktagon = new Object("maps/oktagon.txt");
    comlabs = new Object("maps/comlabs.txt");
    pln = new Object("maps/pln.txt");
    pau = new Object("maps/pau.txt");
    perpus = new Object("maps/perpus.txt");

}

MapItb::~MapItb()
{
    delete albar;
    delete altim;
    delete ccbar;
    delete cctim;
    delete lab5;
    delete lab6;
    delete lab7;
    delete lab8;
    delete tvst;
    delete oktagon;
    delete comlabs;
    delete pln;
    delete pau;
    delete perpus;
}

void MapItb::Draw(FrameBuffer frame)
{
    pau->Draw(frame);
    pau->Make3D(frame);
    perpus->Draw(frame);
    perpus->Make3D(frame);
    oktagon->Draw(frame);
    oktagon->Make3D(frame);
    comlabs->Draw(frame);
    comlabs->Make3D(frame);
    tvst->Draw(frame);
    tvst->Make3D(frame);
    pln->Draw(frame);
    pln->Make3D(frame);
    lab6->Draw(frame);
    lab6->Make3D(frame);
    lab7->Draw(frame);
    lab7->Make3D(frame);
    lab5->Draw(frame);
    lab5->Make3D(frame);
    lab8->Draw(frame);
    lab8->Make3D(frame);
    ccbar->Draw(frame);
    ccbar->Make3D(frame);
    cctim->Draw(frame);
    cctim->Make3D(frame);
    albar->Draw(frame);
    albar->Make3D(frame);
    altim->Draw(frame);
    altim->Make3D(frame);
}

vector<Object> MapItb::getGedung()
{
    vector<Object> gedung;
    gedung.push_back(*pau);
    gedung.push_back(*perpus);
    gedung.push_back(*oktagon);
    gedung.push_back(*comlabs);
    gedung.push_back(*tvst);
    gedung.push_back(*pln);
    gedung.push_back(*lab6);
    gedung.push_back(*lab7);
    gedung.push_back(*lab5);
    gedung.push_back(*lab8);
    gedung.push_back(*ccbar);
    gedung.push_back(*cctim);
    gedung.push_back(*albar);
    gedung.push_back(*altim);
    return gedung;
}
