#include "DrawingObject.h"
#include <iostream>
using namespace std;
DrawingObject::DrawingObject(){
	
}
DrawingObject::~DrawingObject() {
}
void DrawingObject::plotLine(Point awal, Point akhir, RGBcolor warna, FrameBuffer fBuff) {
	int dx =  abs(akhir.GetAbsis()-awal.GetAbsis()), sx = awal.GetAbsis()<akhir.GetAbsis() ? 1 : -1;
	int dy = -abs(akhir.GetOrdinat()-awal.GetOrdinat()), sy = awal.GetOrdinat()<akhir.GetOrdinat() ? 1 : -1; 
	int err = dx+dy, e2; /* error value e_xy */
	int location;

	for(;;){  /* loop */
		location = awal.GetAbsis() * (fBuff.vinfo.bits_per_pixel/8) + awal.GetOrdinat() * fBuff.finfo.line_length;
		*(fBuff.fbp + location) = warna.getBlue(); // Some blue 
		*(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
		*(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
		*(fBuff.fbp + location + 3) = 0; // No transparency
		if (awal.GetAbsis()==akhir.GetAbsis() && awal.GetOrdinat()==akhir.GetOrdinat()) break;
		e2 = 2*err;
		if (e2 >= dy) { err += dy; awal.SetAbsis(awal.GetAbsis() + sx); } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; awal.SetOrdinat(awal.GetOrdinat() + sy); } /* e_xy+e_y < 0 */
	}
}
void DrawingObject::drawRectangle(Point top_left_corner, int height, int width, RGBcolor warna, FrameBuffer fBuff) {
	Point start, finish;

	heightRectangle = height;
	widthRectangle = width;
	topLeftRectangle = top_left_corner;
	
	start = top_left_corner;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()+heightRectangle);
	plotLine(start, finish, warna, fBuff);

	start = finish;
	finish.SetAbsis(start.GetAbsis()+widthRectangle);
	finish.SetOrdinat(start.GetOrdinat());
	plotLine(start, finish, warna, fBuff);

	start = finish;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()-heightRectangle);
	plotLine(start, finish, warna, fBuff);

	start = finish;
	finish.SetAbsis(start.GetAbsis()-widthRectangle);
	finish.SetOrdinat(start.GetOrdinat());
	plotLine(start, finish, warna, fBuff);
}
void DrawingObject::moveRectangle(RGBcolor warna, FrameBuffer fBuff, int x_move, int y_move) {
	Point top_left;
	RGBcolor hitam;

	hitam.setRGB(0,0,0);
	top_left = topLeftRectangle;
	drawRectangle(top_left, heightRectangle, widthRectangle, hitam, fBuff);
	top_left.SetAbsis(top_left.GetAbsis()+5*x_move);
	top_left.SetOrdinat(top_left.GetOrdinat()+5*y_move);
	drawRectangle(top_left, heightRectangle, widthRectangle, warna, fBuff);
	/*for(int i=0; i<500; i++) {
		if(x_move==1) {
			top_left.SetAbsis(top_left.GetAbsis()+1);
		}
		else if(x_move==-1) {
			top_left.SetAbsis(top_left.GetAbsis()-1);
		}
		if(y_move==1) {
			top_left.SetOrdinat(top_left.GetOrdinat()+1);
		}
		else if(y_move==-1) {
			top_left.SetOrdinat(top_left.GetOrdinat()-1);
		}
		drawRectangle(top_left, height, width, warna, fBuff);
	}*/
}
Point DrawingObject::GetPoint() {
	return topLeftRectangle;
}
void DrawingObject::plotCircle (Point pusat, int r, RGBcolor warna, FrameBuffer fBuff){
	int x, y, err, location;
	x = -r; y = 0; err = 2-2*r; /* II. Quadrant */ 
	   	do {
	   	  /*   I. Quadrant */
	   	  location = (pusat.GetAbsis()-x) * (fBuff.vinfo.bits_per_pixel/8) + (pusat.GetOrdinat()+y) * fBuff.finfo.line_length;
	      if ( fBuff.vinfo.bits_per_pixel == 32 ) {
		    *(fBuff.fbp + location) = warna.getBlue(); 
		    *(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
		    *(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
		  } 
		  /*  II. Quadrant */
	      location = (pusat.GetAbsis()-y) * (fBuff.vinfo.bits_per_pixel/8) + (pusat.GetOrdinat()-x) * fBuff.finfo.line_length;
	      if ( fBuff.vinfo.bits_per_pixel == 32 ) {
		    *(fBuff.fbp + location) = warna.getBlue(); // Some blue 
		    *(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
		    *(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
		  }
		  /* III. Quadrant */
	      location = (pusat.GetAbsis()+x) * (fBuff.vinfo.bits_per_pixel/8) + (pusat.GetOrdinat()-y) * fBuff.finfo.line_length;
	      if ( fBuff.vinfo.bits_per_pixel == 32 ) {
		    *(fBuff.fbp + location) = warna.getBlue(); // Some blue 
		    *(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
		    *(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
		  }
	      /*  IV. Quadrant */
	      location = (pusat.GetAbsis()+y) * (fBuff.vinfo.bits_per_pixel/8) + (pusat.GetOrdinat()+x) * fBuff.finfo.line_length;
	      if ( fBuff.vinfo.bits_per_pixel == 32 ) {
		    *(fBuff.fbp + location) = warna.getBlue(); // Some blue 
		    *(fBuff.fbp + location + 1) = warna.getGreen(); // A little green 
		    *(fBuff.fbp + location + 2) = warna.getRed(); // A lot of red
		  }
	      r = err;
	      if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
	      if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
   		}while (x < 0);
}

void DrawingObject::plotListOfPoint(vector<Point> kumpulantitik, RGBcolor warna, FrameBuffer fBuff){
	if(!kumpulantitik.empty()) {
		for(int i=0; i<kumpulantitik.size()-1;i++){
			plotLine(kumpulantitik.at(i),kumpulantitik.at(i+1), warna, fBuff);
		}
	}
}
void DrawingObject::RasterScan(int x_kiri, int x_kanan, int y_atas, int y_bawah, RGBcolor warna, FrameBuffer fBuff){
	//cout << x_kiri << " " << x_kanan << " " << endl << y_atas <<" "<<y_bawah; //udah bener
	int location;
	int i,j;
	bool pen_down;
	i = y_bawah-y_atas+1;
	j = x_kanan-x_kiri+1;
	//cout << i << endl << j;
	int** Matrix = new int*[i];
	for(int a = 0; a < i; ++a){
    	Matrix[a] = new int[j];
	}
	for(int a=0; a<i;a++){
		for(int b=0;b<j;b++){
			if(fBuff.isBlack(x_kiri+b,y_atas+a)){
				Matrix[a][b] = 0;
			}
			else{
				Matrix[a][b] = 1;	
			}
			//cout << Matrix[a][b];
		}
		//cout << endl;
	}
	for(int a=0; a<i;a++){
		int b = 0;
		bool ujungkanan = false;
		bool singular;
		pen_down = false;
		do{
			//cek singularitas
			if(a<(i-1)){
				//cek bawah
				int m;
				for(int n = 0;n<3;n++){
					if(Matrix[a+1][b-1+n]){
						m++;
					}
				}
				if(m>=2){
					singular=true;
				}
				else{singular=false;}
			}
			if((a>0) && (!singular)){
				int m;
				for(int n = 0;n<3;n++){
					if(Matrix[a-1][b-1+n]){
						m++;
					}
				}
				if(m>=2){
					singular=true;
				}
				else{singular=false;}	
			}
			//cek tebal
			if(b==(j-1)){
				ujungkanan = true;
			}
			if((Matrix[a][b] == 1)){
				if(!ujungkanan){
					if(Matrix[a][b+1]==0){
						if(pen_down){
							pen_down = false;
							b++;
						}
						else{
							pen_down = true;
							b++;
						}
					}
				}
				else{
					if(pen_down){
						pen_down = false;
						b++;
					}
					else{
						pen_down = true;
						b++;
					}
				}
			}
			if(pen_down){
				location = (x_kiri+b) * (fBuff.vinfo.bits_per_pixel/8) + (y_atas+a) * fBuff.finfo.line_length;
				if ( fBuff.vinfo.bits_per_pixel == 32 ) {
				   	*(fBuff.fbp + location) = warna.getBlue(); // biru 
				   	*(fBuff.fbp + location + 1) = warna.getGreen(); // hijau 
					*(fBuff.fbp + location + 2) = warna.getRed(); // merah
				}
			}
			b++;
		}while(b < j);
	}
	
}
void DrawingObject::FloodFill(int x, int y, RGBcolor oldColor, RGBcolor newColor, FrameBuffer fBuff){
	int location = x * (fBuff.vinfo.bits_per_pixel/8) + y * fBuff.finfo.line_length;
	if (fBuff.isSameColor(oldColor,x,y)){
		if ( fBuff.vinfo.bits_per_pixel == 32 ) {
		    *(fBuff.fbp + location) = newColor.getBlue();
		    *(fBuff.fbp + location + 1) = newColor.getGreen();
		    *(fBuff.fbp + location + 2) = newColor.getRed();
		}
		FloodFill(x+1,y,oldColor, newColor, fBuff);
		FloodFill(x-1,y,oldColor, newColor, fBuff);
		FloodFill(x,y+1,oldColor, newColor, fBuff);
		FloodFill(x,y-1,oldColor, newColor, fBuff);
	}
}