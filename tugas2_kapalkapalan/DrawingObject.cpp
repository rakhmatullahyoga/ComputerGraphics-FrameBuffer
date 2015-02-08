#include "DrawingObject.h"

DrawingObject::DrawingObject() {
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

	//system("clear");

	start = top_left_corner;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()+height);
	plotLine(start, finish, warna, fBuff);

	start = finish;
	finish.SetAbsis(start.GetAbsis()+width);
	finish.SetOrdinat(start.GetOrdinat());
	plotLine(start, finish, warna, fBuff);

	start = finish;
	finish.SetAbsis(start.GetAbsis());
	finish.SetOrdinat(start.GetOrdinat()-height);
	plotLine(start, finish, warna, fBuff);

	start = finish;
	finish.SetAbsis(start.GetAbsis()-width);
	finish.SetOrdinat(start.GetOrdinat());
	plotLine(start, finish, warna, fBuff);
}
void DrawingObject::animateRectangle(Point start_top_left_corner, int height, int width, RGBcolor warna, FrameBuffer fBuff, int x_move, int y_move) {
	Point top_left;

	top_left = start_top_left_corner;
	drawRectangle(top_left, height, width, warna, fBuff);
	for(int i=0; i<500; i++) {
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
	}
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
	for(int i=0; i<kumpulantitik.size()-1;i++){
		plotLine(kumpulantitik.at(i),kumpulantitik.at(i+1), warna, fBuff);
	}
}