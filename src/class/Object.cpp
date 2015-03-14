#include "Object.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

#define PI 3.14159265

Object::Object() {
	point1_x=point1_y=point2_x=point2_y=0;
}
Object::Object(string filename){
	point1_x=point1_y=point2_x=point2_y=0;
	string line;
	string dir = "../src/assets/";
	int a,b;
	Point titik;

	dir.append(filename);
  	ifstream myfile (dir.c_str());
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
	else cout << "Unable to open file: " << dir << endl;
	warnaGaris.setRGB(255,255,255);
	fillColor.setRGB(1,1,1);
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
	warnaGaris.setRGB(warna.getRed(), warna.getGreen(), warna.getBlue());
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
	gambar.plotListOfPoint(NTitik,warnaGaris,fBuff);
}
void Object::Hapus(FrameBuffer fBuff){
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
	fillColor.setRGB(0,0,0);
}
void Object::RasterScanFill(RGBcolor warnaFill, FrameBuffer fBuff){
	gambar.RasterScan(x_kiri, x_kanan, y_atas, y_bawah,warnaFill,fBuff);
	fillColor.setRGB(warnaFill.getRed(), warnaFill.getGreen(), warnaFill.getBlue());
}
void Object::FloodFill(RGBcolor warnaFill,FrameBuffer fBuff){
	int x = (x_kiri+x_kanan)/2;
	int y = (y_bawah+y_atas)/2;
	gambar.FloodFill(x,y,fillColor, warnaFill,fBuff);
	fillColor.setRGB(warnaFill.getRed(), warnaFill.getGreen(), warnaFill.getBlue());
	//cout << "R: " << fillColor.getRed() << ", G: " << fillColor.getGreen() << ", B: " << fillColor.getBlue() << endl;
}
void Object::DrawPattern(Pattern pola, FrameBuffer fBuff, RGBcolor warna) {
	Point object_top_left, object_bottom_right;
	object_top_left.SetAbsis(x_kiri);
	object_top_left.SetOrdinat(y_atas);
	object_bottom_right.SetAbsis(x_kanan);
	object_bottom_right.SetOrdinat(y_bawah);

	pola.drawPattern(object_top_left, object_bottom_right, warna, fBuff);
}
void Object::Putar(float drj, int xpusat, int ypusat, FrameBuffer fBuff){
	int x,y,xbaruInt,ybaruInt;
	float xbaru, ybaru;
	float sinus, cosinus;
	Hapus(fBuff);
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
	Draw(fBuff);
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
	fillColor.setRGB(warna.getRed(), warna.getGreen(), warna.getBlue());
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
void Object::CreateRectangle(Point top_left_corner, int height, int width) {
	Point start, finish;

	start = top_left_corner;
	NTitik.push_back(start);
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()+height);
	NTitik.push_back(finish);

	start = finish;
	finish.SetAbsis(start.GetAbsis()+width);
	finish.SetOrdinat(start.GetOrdinat());
	NTitik.push_back(finish);

	start = finish;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()-height);
	NTitik.push_back(finish);

	start = finish;
	finish.SetAbsis(start.GetAbsis()-width);
	finish.SetOrdinat(start.GetOrdinat());
	NTitik.push_back(finish);
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
Point Object::GetKiriAtas(){
	Point a(x_kiri,y_atas);
	return a;
}
int Object::GetKiri() {
	return x_kiri;
}
int Object::GetKanan() {
	return x_kanan;
}
int Object::GetAtas() {
	return y_atas;
}
int Object::GetBawah() {
	return y_bawah;
}
RGBcolor Object::GetWarna() {
    return warnaGaris;
}
vector<Point> Object::GetNTitik(){
	return NTitik;
}
int Object::findRegion(int x, int y) {
	int code=0;
	if(y >= y_bawah)
		code |= 1; //top
	else if(y < y_atas)
		code |= 2; //bottom
	if(x >= x_kanan)
		code |= 4; //right
	else if(x < x_kiri)
		code |= 8; //left
	return(code);
}
void Object::clipLine(Point P1, Point P2, RGBcolor warna, FrameBuffer fBuff, Point view_topleft, Point legend_topleft) {
	int x1, x2, y1, y2;
    int code1, code2, codeout;
    bool accept = 0, done=0;

    x1 = P1.GetAbsis();
    y1 = P1.GetOrdinat();
    x2 = P2.GetAbsis();
    y2 = P2.GetOrdinat();
    code1 = findRegion(x1, y1); //the region outcodes for the endpoints
    code2 = findRegion(x2, y2);
    do  //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
        if(!(code1 | code2)) accept = done = 1;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2) done = 1; //the line isn't visible on screen, trivial reject
        else {  //if no trivial reject or accept, continue the loop
            int x, y;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) { //top
                x = x1 + (x2 - x1) * (y_bawah - y1) / (y2 - y1);
                y = y_bawah - 1;
            }
            else if(codeout & 2) { //bottom
                x = x1 + (x2 - x1) * (y_atas-y1) / (y2 - y1);
                y = y_atas;
            }
            else if(codeout & 4) { //right
                y = y1 + (y2 - y1) * (x_kanan - x1) / (x2 - x1);
                x = x_kanan - 1;
            }
            else { //left
                y = y1 + (y2 - y1) * (x_kiri-x1) / (x2 - x1);
                x = x_kiri;
            }

	        if(codeout == code1) { //first endpoint was clipped
	            x1 = x; y1 = y;
	            code1 = findRegion(x1, y1);
	        }
	        else { //second endpoint was clipped
	            x2 = x; y2 = y;
	            code2 = findRegion(x2, y2);
	        }
        }
    } while(done == 0);

    if(accept) {
    	Point clip1(x1,y1);
    	Point clip2(x2,y2);
    	point1_x= x1-view_topleft.GetAbsis()+legend_topleft.GetAbsis();
    	point1_y= y1-view_topleft.GetOrdinat()+legend_topleft.GetOrdinat();
    	point2_x= x2-view_topleft.GetAbsis()+legend_topleft.GetAbsis();
    	point2_y= y2-view_topleft.GetOrdinat()+legend_topleft.GetOrdinat();
    	Point legendclip1(point1_x,point1_y);
    	Point legendclip2(point2_x,point2_y);
        gambar.plotLine(clip1, clip2, warna, fBuff);
        gambar.plotLine(legendclip1, legendclip2, warna, fBuff);
      	TitikLegend.push_back(legendclip1);
      	TitikLegend.push_back(legendclip2);
    }
}
void Object::CreateClip(vector<Object> kumpulanobject, RGBcolor warna, FrameBuffer fBuff,Point view_topleft, Point legend_topleft) {
	for(int i=0; i<kumpulanobject.size(); i++) {
		for(int j=0; j<kumpulanobject.at(i).GetNTitik().size()-1; j++) {
			clipLine(kumpulanobject.at(i).GetNTitik().at(j),kumpulanobject.at(i).GetNTitik().at(j+1),warna,fBuff,view_topleft,legend_topleft);
		}
	}
}
void Object::DrawLegend(FrameBuffer fBuff){
	gambar.plotListOfPoint(TitikLegend,warnaGaris,fBuff);
}
void Object::HapusLegend(FrameBuffer fBuff){
	RGBcolor hitam;
	hitam.setRGB(1,1,1);
	gambar.plotListOfPoint(TitikLegend,hitam,fBuff);
	TitikLegend.clear();
}
void Object::SkalaLegend(float skalax, float skalay){
	int xpusat = (x_kiri+x_kanan)/2;
	int ypusat = (y_atas+y_bawah)/2;
	float xbaru, ybaru;
	int x,y, xbaruInt, ybaruInt;
	for(int i=0; i<NTitik.size();i++){
		x = TitikLegend.at(i).GetAbsis();
		y = TitikLegend.at(i).GetOrdinat();
		xbaru = xpusat + (x-xpusat)*skalax;
		ybaru = ypusat + (y-ypusat)*skalay;
		xbaruInt = (int)(xbaru+0.5);
		ybaruInt = (int)(ybaru+0.5);
		TitikLegend.at(i).SetAbsis(xbaruInt);
		TitikLegend.at(i).SetOrdinat(ybaruInt);
	}
}
