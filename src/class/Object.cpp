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
				*(fBuff.fbp + location) = 1;
				*(fBuff.fbp + location + 1) = 1;
				*(fBuff.fbp + location + 2) = 1;
			}
		}
	}
	fillColor.setRGB(1,1,1);
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
	Point temp = NTitik.back();
	NTitik.pop_back();

	int i = 0, size=(int) NTitik.size();
	bool found = false;
	bool v_point = false;
	while((i<NTitik.size())&&!found) {
		if(x==NTitik.at(i).GetAbsis()&&y==NTitik.at(i).GetOrdinat()) {
			if(((NTitik.at((i-1+size)%size).GetOrdinat()<y)&&(NTitik.at((i+1+size)%size).GetOrdinat()<y))||((NTitik.at((i-1+size)%size).GetOrdinat()>y)&&(NTitik.at((i+1+size)%size).GetOrdinat()>y))) {
				v_point = true;
			}
			else {
				if((NTitik.at((i-1+size)%size).GetOrdinat()<y)&&(NTitik.at((i+1+size)%size).GetOrdinat()==y))
					v_point = (NTitik.at((i+2+size)%size).GetOrdinat()<y);
				else if((NTitik.at((i-1+size)%size).GetOrdinat()>y)&&(NTitik.at((i+1+size)%size).GetOrdinat()==y))
					v_point = (NTitik.at((i+2+size)%size).GetOrdinat()>y);
				else if((NTitik.at((i-1+size)%size).GetOrdinat()==y)&&(NTitik.at((i+1+size)%size).GetOrdinat()>y))
					v_point = (NTitik.at((i-2+size)%size).GetOrdinat()>y);
				else if((NTitik.at((i-1+size)%size).GetOrdinat()==y)&&(NTitik.at((i+1+size)%size).GetOrdinat()<y))
					v_point = (NTitik.at((i-2+size)%size).GetOrdinat()<y);
			}
			found = true;
		}
		else {
			i++;
		}
	}
	NTitik.push_back(temp);
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
	finish.SetAbsis(start.GetAbsis()+width);
	finish.SetOrdinat(start.GetOrdinat());
	NTitik.push_back(finish);

	start = finish;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()+height);
	NTitik.push_back(finish);

	start = finish;
	finish.SetAbsis(start.GetAbsis()-width);
	finish.SetOrdinat(start.GetOrdinat());
	NTitik.push_back(finish);

	start = finish;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()-height);
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
	if(y >= NTitik.at(2).GetOrdinat())
		code |= 1; //bottom
	else if(y < NTitik.at(0).GetOrdinat())
		code |= 2; //top
	if(x >= NTitik.at(1).GetAbsis())
		code |= 4; //right
	else if(x < NTitik.at(0).GetAbsis())
		code |= 8; //left
	return(code);
}
int Object::findRegionAtas(int x, int y) {
	int code = 0;
	Line L1(NTitik.at(5),NTitik.at(6));
	Line L2(NTitik.at(6),NTitik.at(1));
	Line L3(NTitik.at(1),NTitik.at(0));
	Line L4(NTitik.at(0),NTitik.at(5));
	if(y>NTitik.at(2).GetOrdinat()) //bawah
		code |= 1;
	else if(y<NTitik.at(0).GetOrdinat()) //atas
		code |= 2;
	if(L2.getA()*x+L2.getB()*y<L2.getC()) //kanan
		code |= 4;
	else if(L4.getA()*x+L4.getB()*y>L4.getC()) //kiri
		code |= 8;
	return code;
}
int Object::findRegionSamping(int x, int y) {
	int code = 0;
	Line L1(NTitik.at(1),NTitik.at(6));
	Line L2(NTitik.at(6),NTitik.at(7));
	Line L3(NTitik.at(7),NTitik.at(2));
	Line L4(NTitik.at(2),NTitik.at(1));
	if(L3.getA()*x+L3.getB()*y<L3.getC()) //bawah
		code |= 1;
	else if(L1.getA()*x+L1.getB()*y>L1.getC()) //atas
		code |= 2;
	if(x>NTitik.at(6).GetAbsis()) //kanan
		code |= 4;
	else if(x<NTitik.at(1).GetAbsis()) //kiri
		code |= 8;
	return code;
}
void Object::clipLine(Point P1, Point P2, FrameBuffer fBuff, Point view_topleft, Point legend_topleft) {
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
        TitikLegend.push_back(legendclip1);
      	TitikLegend.push_back(legendclip2);
    }
}
void Object::antiClip(Point P1, Point P2, FrameBuffer fBuff) {
	int x1, x2, y1, y2;
    int code1, code2, codeout;
    bool accept = 0, done=0;
    RGBcolor black;

    black.setRGB(1,1,1);
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
    	gambar.plotLine(clip1, clip2, black, fBuff);
    }
}
void Object::antiClipAtas(Point P1, Point P2, FrameBuffer fBuff) {
	int x1, x2, y1, y2;
    int code1, code2, codeout;
    bool accept = 0, done=0;
    RGBcolor black;

    black.setRGB(1,1,1);
	x1 = P1.GetAbsis();
    y1 = P1.GetOrdinat();
    x2 = P2.GetAbsis();
    y2 = P2.GetOrdinat();
    code1 = findRegionAtas(x1, y1); //the region outcodes for the endpoints
    code2 = findRegionAtas(x2, y2);
    Line L(P1,P2);
    do  //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
    	if(!(code1 | code2)) accept = done = 1;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2) done = 1; //the line isn't visible on screen, trivial reject
        else {  //if no trivial reject or accept, continue the loop
            int x, y;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) { //bottom
            	Line L_bawah(NTitik.at(0),NTitik.at(1));
                x = L_bawah.getIntersection(L).GetAbsis();
                y = L_bawah.getIntersection(L).GetOrdinat();
            }
            else if(codeout & 2) { //top
                Line L_atas(NTitik.at(5),NTitik.at(6));
                x = L_atas.getIntersection(L).GetAbsis();
                y = L_atas.getIntersection(L).GetOrdinat();
            }
            else if(codeout & 4) { //right
            	Line L_kanan(NTitik.at(6),NTitik.at(1));
                x = L_kanan.getIntersection(L).GetAbsis();
                y = L_kanan.getIntersection(L).GetOrdinat();
            }
            else { //left
            	Line L_kiri(NTitik.at(0),NTitik.at(5));
            	x = L_kiri.getIntersection(L).GetAbsis();
                y = L_kiri.getIntersection(L).GetOrdinat();
            }

	        if(codeout == code1) { //first endpoint was clipped
	            x1 = x; y1 = y;
	            code1 = findRegionAtas(x1, y1);
	        }
	        else { //second endpoint was clipped
	            x2 = x; y2 = y;
	            code2 = findRegionAtas(x2, y2);
	        }
	        cout << "x1: " << x1 << ", x2: " << x2 << endl;
	        cout << "y1: " << y1 << ", y2: " << y2 << endl;
        }
    } while(done == 0);

    if(accept) {
    	Point clip1(x1,y1);
    	Point clip2(x2,y2);
    	gambar.plotLine(clip1, clip2, black, fBuff);
    }
}
void Object::antiClipSamping(Point P1, Point P2, FrameBuffer fBuff) {
	int x1, x2, y1, y2;
    int code1, code2, codeout;
    bool accept = 0, done=0;
    RGBcolor black;

    black.setRGB(1,1,1);
	x1 = P1.GetAbsis();
    y1 = P1.GetOrdinat();
    x2 = P2.GetAbsis();
    y2 = P2.GetOrdinat();
    code1 = findRegionSamping(x1, y1); //the region outcodes for the endpoints
    code2 = findRegionSamping(x2, y2);
    Line L(P1,P2);
    do  //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
        if(!(code1 | code2)) accept = done = 1;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2) done = 1; //the line isn't visible on screen, trivial reject
        else {  //if no trivial reject or accept, continue the loop
            int x, y;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) { //bottom
            	Line L_bawah(NTitik.at(2),NTitik.at(7));
                x = L_bawah.getIntersection(L).GetAbsis();
                y = L_bawah.getIntersection(L).GetOrdinat();
            }
            else if(codeout & 2) { //top
            	Line L_atas(NTitik.at(1),NTitik.at(6));
                x = L_atas.getIntersection(L).GetAbsis();
                y = L_atas.getIntersection(L).GetOrdinat();
            }
            else if(codeout & 4) { //right
            	Line L_kanan(NTitik.at(6),NTitik.at(7));
                y = L_kanan.getIntersection(L).GetAbsis();
                x = L_kanan.getIntersection(L).GetOrdinat();
            }
            else { //left
            	Line L_kiri(NTitik.at(1),NTitik.at(2));
                y = L_kiri.getIntersection(L).GetAbsis();
                x = L_kiri.getIntersection(L).GetOrdinat();
            }

	        if(codeout == code1) { //first endpoint was clipped
	            x1 = x; y1 = y;
	            code1 = findRegionSamping(x1, y1);
	        }
	        else { //second endpoint was clipped
	            x2 = x; y2 = y;
	            code2 = findRegionSamping(x2, y2);
	        }
        }
    } while(done == 0);

    if(accept) {
    	Point clip1(x1,y1);
    	Point clip2(x2,y2);
        gambar.plotLine(clip1, clip2, black, fBuff);
    }
}
void Object::CreateClip(vector<Object> kumpulanobject, FrameBuffer fBuff,Point view_topleft, Point legend_topleft) {
	for(int i=0; i<kumpulanobject.size(); i++) {
		for(int j=0; j<kumpulanobject.at(i).GetNTitik().size()-1; j++) {
			clipLine(kumpulanobject.at(i).GetNTitik().at(j),kumpulanobject.at(i).GetNTitik().at(j+1),fBuff,view_topleft,legend_topleft);
		}
	}
}
void Object::CreateAntiClip(vector<Object> kumpulanobject, FrameBuffer fBuff) {
	//cout << "cek1" << endl;
	for(int i=0; i<kumpulanobject.size(); i++) {
		for(int j=0; j<kumpulanobject.at(i).GetNTitik().size()-1; j++) {
			antiClip(kumpulanobject.at(i).GetNTitik().at(j),kumpulanobject.at(i).GetNTitik().at(j+1),fBuff);
		}
	}
	//cout << "cek2" << endl;
	for(int i=0; i<kumpulanobject.size(); i++) {
		cout << "size: " << kumpulanobject.at(i).GetNTitik().size() << endl;
		for(int j=0; j<kumpulanobject.at(i).GetNTitik().size()-1; j++) {
			cout << "cek" << i << "," << j << endl;
			antiClipAtas(kumpulanobject.at(i).GetNTitik().at(j),kumpulanobject.at(i).GetNTitik().at(j+1),fBuff);
		}
	}
	cout << "cek3" << endl;
	for(int i=0; i<kumpulanobject.size(); i++) {
		for(int j=0; j<kumpulanobject.at(i).GetNTitik().size()-1; j++) {
			antiClipSamping(kumpulanobject.at(i).GetNTitik().at(j),kumpulanobject.at(i).GetNTitik().at(j+1),fBuff);
		}
	}
	cout << "cek4" << endl;
}
void Object::DrawLegend(FrameBuffer fBuff){
	for(int i=0; i<TitikLegend.size(); i+=2) {
		gambar.plotLine(TitikLegend.at(i),TitikLegend.at(i+1),warnaGaris,fBuff);
	}
}
void Object::HapusLegend(FrameBuffer fBuff){
	RGBcolor hitam;
	hitam.setRGB(1,1,1);
	gambar.plotListOfPoint(TitikLegend,hitam,fBuff);
	TitikLegend.clear();
}
void Object::SkalaLegend(float skalax, float skalay, Point legend_topleft, int sizex, int sizey){
	int xpusat = legend_topleft.GetAbsis();
	int ypusat = legend_topleft.GetOrdinat();
	float xbaru, ybaru;
	int x,y, xbaruInt, ybaruInt;
	for(int i=0; i<TitikLegend.size();i++){
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
void Object::Make3D(FrameBuffer fBuff) {
	vector<Point> projection3D;
	Point P;
	for(int i=0; i<3; i++) {
		//cout << "cek" << i << endl;
		if(!(NTitik.at(i).GetAbsis()==x_kiri&&NTitik.at(i).GetOrdinat()==y_bawah)) {
			P.SetAbsis(NTitik.at(i).GetAbsis()+10);
			P.SetOrdinat(NTitik.at(i).GetOrdinat()-30);
			NTitik.push_back(P);
		}
	}
	NTitik.push_back(NTitik.at(2));
	NTitik.push_back(NTitik.at(1));
	NTitik.push_back(NTitik.at(6));
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
	gambar.plotListOfPoint(NTitik,warnaGaris,fBuff);
}
void Object::Hapus3D(FrameBuffer fBuff) {
	RGBcolor black;
	black.setRGB(1,1,1);
	gambar.plotListOfPoint(NTitik,black,fBuff);
}