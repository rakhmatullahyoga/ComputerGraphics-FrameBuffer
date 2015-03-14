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
    albar->Draw(frame);
    altim->Draw(frame);
    ccbar->Draw(frame);
    cctim->Draw(frame);
    lab5->Draw(frame);
    lab6->Draw(frame);
    lab7->Draw(frame);
    lab8->Draw(frame);
    tvst->Draw(frame);
    oktagon->Draw(frame);
    comlabs->Draw(frame);
    pln->Draw(frame);
    pau->Draw(frame);
    perpus->Draw(frame);
}

vector<Object> MapItb::getGedung()
{
    vector<Object> gedung;
    gedung.push_back(*albar);
    gedung.push_back(*altim);
    gedung.push_back(*ccbar);
    gedung.push_back(*cctim);
    gedung.push_back(*lab5);
    gedung.push_back(*lab6);
    gedung.push_back(*lab7);
    gedung.push_back(*lab8);
    gedung.push_back(*tvst);
    gedung.push_back(*oktagon);
    gedung.push_back(*comlabs);
    gedung.push_back(*pln);
    gedung.push_back(*pau);
    gedung.push_back(*perpus);
    return gedung;
}
