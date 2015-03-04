#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Pattern.h"
#include "Object.h"
#include "Map.h"
#include <iostream>
#include <termios.h>

using namespace std;

int _getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

int findRegion(int x, int y, int atas, int bawah, int kiri, int kanan)
{
    int code=0;
    if(y >= bawah)
    code |= 1; //top
    else if( y < atas)
    code |= 2; //bottom
    if(x >= kanan)
    code |= 4; //right
    else if ( x < kiri)
    code |= 8; //left
    return(code);
}

bool clipLine(int x1, int y1, int x2, int y2, int & x3, int & y3, int & x4, int & y4, int atas, int bawah, int kiri, int kanan)
{
    int code1, code2, codeout;
    bool accept = 0, done=0;
    code1 = findRegion(x1, y1, atas, bawah, kiri, kanan); //the region outcodes for the endpoints
    code2 = findRegion(x2, y2, atas, bawah, kiri, kanan);
    do  //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
    	//printf("tes");
        if(!(code1 | code2)) accept = done = 1;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2) done = 1; //the line isn't visible on screen, trivial reject
        else  //if no trivial reject or accept, continue the loop
        {
            int x, y;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) //top
            {
                x = x1 + (x2 - x1) * (bawah - y1) / (y2 - y1);
                y = bawah-1;
            }
            else if(codeout & 2) //bottom
            {
                x = x1 + (x2 - x1) * (atas - y1) / (y2 - y1);
                y = atas;
            }
            else if(codeout & 4) //right
            {
                y = y1 + (y2 - y1) * (kanan - x1) / (x2 - x1);
                x = kanan-1;
            }
            else //left
            {
                y = y1 + (y2 - y1) * (kiri - x1) / (x2 - x1);
                x = kiri;
            }

        if(codeout == code1) //first endpoint was clipped
            {
                x1 = x; y1 = y;
                code1 = findRegion(x1, y1, atas, bawah, kiri, kanan);
            }
            else //second endpoint was clipped
            {
                x2 = x; y2 = y;
                code2 = findRegion(x2, y2, atas, bawah, kiri, kanan);
            }
        }
        //done = 1;
    }
    while(done == 0);

    if(accept)
    {
        x3 = x1;
        x4 = x2;
        y3 = y1;
        y4 = y2;
        return 1;
    }
    else
    {
        x3 = x4 = y3 = y4 = 0;
        return 0;
    }
}

int main(int argc, char const *argv[]) {
	FrameBuffer frame;
	DrawingObject map_canvas, view_port, legend;
	Object viewport;
	RGBcolor warna_border;
	warna_border.setRGB(255,255,255);
	viewport.SetWarna(warna_border);
	Point canvas_topleft(50,50);
	Point view_topleft(200,200);
	Point legend_topleft(1016,516);
	Map Indonesia;

	system("clear");
	viewport.CreateRectangle(view_topleft, 200, 300);
	viewport.Draw(frame);
	map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
	//view_port.drawRectangle(view_topleft,200,200,warna_border,frame);
	legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
	Indonesia.Draw(frame);
	while(true) {
		int ch = _getch();
		if(ch == 0x41) { // up-arrow key
			if(viewport.GetAtas()>canvas_topleft.GetOrdinat()) {
				viewport.Geser(0,-5,frame);
				//view_port.moveRectangle(warna_border, frame, 0, -1);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
			}
		}
		else if(ch == 0x42) { // down-arrow key
			if(viewport.GetBawah()<canvas_topleft.GetOrdinat()+666-1) {
				viewport.Geser(0,5,frame);
				//view_port.moveRectangle(warna_border, frame, 0, 1);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
			}
		}
		else if(ch == 0x43) { // right-arrow key
			if(viewport.GetKanan()<canvas_topleft.GetAbsis()+1266-1) {
				viewport.Geser(5,0,frame);
				//view_port.moveRectangle(warna_border, frame, 1, 0);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
			}
		}
		else if(ch == 0x44) { // left-arrow key
			if(viewport.GetKiri()>canvas_topleft.GetAbsis()) {
				viewport.Geser(-5,0,frame);
				//view_port.moveRectangle(warna_border, frame, -1, 0);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
			}
		}
		else if(ch == 'z') { // zoom-in legend
			viewport.Hapus(frame);
			viewport.Skala(0.9,0.9);
			viewport.Draw(frame);
			Indonesia.Draw(frame);
		}
		else if(ch == 'c') { // zoom-out legend
			viewport.Hapus(frame);
			viewport.Skala(1.111,1.111);
			if(!((viewport.GetKiri()>canvas_topleft.GetAbsis())&&(viewport.GetKanan()<canvas_topleft.GetAbsis()+1266-1)&&(viewport.GetBawah()<canvas_topleft.GetOrdinat()+666-1)&&(viewport.GetAtas()>canvas_topleft.GetOrdinat()))) {
				viewport.Skala(0.9,0.9);
			}
			viewport.Draw(frame);
			Indonesia.Draw(frame);
		}

		Object kalimantan = Indonesia.GetObject("kalimantan"), kalimantan2;
		vector<Point> VTitik = kalimantan.GetNTitik();

		for(int i=0; i < VTitik.size(); i++)
		{
			//printf("ukuran %d\n", VTitik.size());
			//printf("masuk %d\n", i);
			int a1=VTitik.at(i).GetAbsis(), b1=VTitik.at(i).GetOrdinat(), a2=VTitik.at((i+1)%(int)VTitik.size()).GetAbsis(), b2=VTitik.at((i+1)%(int)VTitik.size()).GetOrdinat();
			//printf("%d %d %d %d\n", a1, b1, a2, b2);
			int aa1, bb1, aa2, bb2;
			if (clipLine(a1, b1, a2, b2, aa1, bb1, aa2, bb2, viewport.GetAtas(), viewport.GetBawah(), viewport.GetKiri(), viewport.GetKanan()) )
			{
				kalimantan2.AddPoint(aa1, bb1);
				kalimantan2.AddPoint(aa2, bb2);
			}
			//printf("%d %d %d %d\n", aa1, bb1, aa2, bb2);
			//printf("keluar %d\n", i);
		}

		kalimantan2.Skala(0.5, 0.5);
		//kalimantan2.Geser(100, 100, frame);
		kalimantan2.Draw(frame);
		//usleep(500);
	}

	return 0;
}