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
    pau->Make3D(frame);
    //pau->CreateAntiClip(getGedung(),frame);
    perpus->Make3D(frame);
    //perpus->CreateAntiClip(getGedung(),frame);
    oktagon->Make3D(frame);
    //oktagon->CreateAntiClip(getGedung(),frame);
    comlabs->Make3D(frame);
    //comlabs->CreateAntiClip(getGedung(),frame);
    tvst->Make3D(frame);
    //tvst->CreateAntiClip(getGedung(),frame);
    pln->Make3D(frame);
    //pln->CreateAntiClip(getGedung(),frame);
    lab6->Make3D(frame);
    //lab6->CreateAntiClip(getGedung(),frame);
    lab7->Make3D(frame);
    //lab7->CreateAntiClip(getGedung(),frame);
    lab5->Make3D(frame);
    //lab5->CreateAntiClip(getGedung(),frame);
    lab8->Make3D(frame);
    //lab8->CreateAntiClip(getGedung(),frame);
    ccbar->Make3D(frame);
    //ccbar->CreateAntiClip(getGedung(),frame);
    cctim->Make3D(frame);
    //cctim->CreateAntiClip(getGedung(),frame);
    albar->Make3D(frame);
    //albar->CreateAntiClip(getGedung(),frame);
    altim->Make3D(frame);
    //altim->CreateAntiClip(getGedung(),frame);
}

void MapItb::Geser(int x, int y, FrameBuffer frame) {
    pau->Geser(x,y,frame);
    perpus->Geser(x,y,frame);
    oktagon->Geser(x,y,frame);
    comlabs->Geser(x,y,frame);
    tvst->Geser(x,y,frame);
    pln->Geser(x,y,frame);
    lab6->Geser(x,y,frame);
    lab7->Geser(x,y,frame);
    lab5->Geser(x,y,frame);
    lab8->Geser(x,y,frame);
    ccbar->Geser(x,y,frame);
    cctim->Geser(x,y,frame);
    albar->Geser(x,y,frame);
    altim->Geser(x,y,frame);
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
