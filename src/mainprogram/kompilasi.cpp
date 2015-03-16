#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Map.h"
#include "MapItb.h"
#include "Pattern.h"
#include "Object.h"
#include <iostream>
#include <termios.h>

#include <string>
#include <unistd.h>

using namespace std;

FrameBuffer frame;
void Meledak (int xpusat, int ypusat);
void antiLedak (int xpusat, int ypusat);
void Perang2an();
void Judul();
void PetaIndonesia();
void PetaITB();
int _getch();

int main(int argc, char const *argv[])
{
	system("clear");
	Judul();
	Perang2an();
	
	// text
	string s;
	s = "Pesawat musuh berhasil dihancurkan! Kini Indonesia bebas dari ancaman penjajah.";
	system("clear");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t";
	for (int i=0; i<s.length(); i++) {
		cout << s[i];
		cout.flush();
		usleep(30000);
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(1);

	system("clear");

	/*------------ PETA INDONESIA ------------*/
	PetaIndonesia();


	// text
	string s2;
	s2 = "Beberapa tahun kemudian, setelah Indonesia merdeka dari penjajah, di Bandung, salah satu kota besar di Indonesia,\n\t\t\t\t\tdibangunlah sebuah institut teknologi.";
	system("clear");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t";
	for (int i=0; i<s2.length(); i++) {
		cout << s2[i];
		cout.flush();
		usleep(30000);
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(1);

	system("clear");


	// buat 3D
	PetaITB();
	return 0;
}

void Meledak (int xpusat, int ypusat){
	DrawingObject Ledakan;
	RGBcolor warnaLedakan;
	warnaLedakan.setRed(255);
	warnaLedakan.setBlue(0);
	Point titikLedak;
	titikLedak.SetAbsis(xpusat);
	titikLedak.SetOrdinat(ypusat);
 	for(int radLedak=1; radLedak<=50; radLedak++){
 		warnaLedakan.setGreen(256-radLedak*4.48);
   		Ledakan.plotCircle(titikLedak,radLedak,warnaLedakan,frame);
   		usleep(10000);
 	}
}

void antiLedak (int xpusat, int ypusat){
	DrawingObject Ledakan;
	RGBcolor warnaLedakan;
	warnaLedakan.setRed(0);
	warnaLedakan.setGreen(0);
	warnaLedakan.setBlue(0);
	Point titikLedak;
	titikLedak.SetAbsis(xpusat);
	titikLedak.SetOrdinat(ypusat);
 	for(int radLedak=1; radLedak<=50; radLedak++){
   		Ledakan.plotCircle(titikLedak,radLedak,warnaLedakan,frame);
   		usleep(20000);
 	}
}
void Judul(){
	// SPLASHIE
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "\t\t\t\t\t\t\t\t"; cout << " __          ____          _______ " << endl;
		cout << "\t\t\t\t\t\t\t\t"; cout << " \\ \\        / /\\ \\        / / ____|" << endl;
		cout << "\t\t\t\t\t\t\t\t"; cout << "  \\ \\  /\\  / /  \\ \\  /\\  / /| |__  " << endl;
		cout << "\t\t\t\t\t\t\t\t"; cout << "   \\ \\/  \\/ /    \\ \\/  \\/ / |___ \\ " << endl;
		cout << "\t\t\t\t\t\t\t\t"; cout << "    \\  /\\  /      \\  /\\  /   ___) |" << endl;
		cout << "\t\t\t\t\t\t\t\t"; cout << "     \\/  \\/        \\/  \\/   |____/ " << endl << endl;
		cout << "\t\t\t\t\t\t\t\t\t"; cout << "Press <ENTER> to continue" << endl;
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	while (!(cin.get() == '\n')) {}
}

void Perang2an(){
	int inputkey;
	/*atribut Peluru, Roda*/
	int x_center = 560;
	int y_center = 130;
	DrawingObject Peluru, Peluru2, Roda;
	RGBcolor black, white;
	black.setRGB(1,1,1);
	white.setRGB(255,255,255);

	/*atribut Peluru*/
	RGBcolor warnaPeluru;
	Point peluruStart,peluru2Start,roda_fall;
	int radpeluru = 5, rad_roda = 10;
	warnaPeluru.setRGB(255,255,0);
	peluruStart.SetAbsis(280);
	peluruStart.SetOrdinat(650);
	peluru2Start.SetAbsis(400);
	peluru2Start.SetOrdinat(195);
	bool meledak = false;

	/*Objek Pesawat*/
	Point pesawatP_top_left, pesawatP_bottom_right;
	pesawatP_top_left.SetAbsis(300);
	pesawatP_top_left.SetOrdinat(30);
	pesawatP_bottom_right.SetAbsis(560);
	pesawatP_bottom_right.SetOrdinat(140);
	Object pswt("objects/pesawat2.txt");
	Pattern pattern("pattern/burung.txt");
	RGBcolor pswtCol;
	//pswtCol.setRGB(234,34,74);
	
	/*Baling-baling*/
	Object baling("objects/baling2.txt");
	
	/*Objek Kapal*/
	Point kapalP_top_left, kapalP_bottom_right;
	kapalP_top_left.SetAbsis(370);
	kapalP_top_left.SetOrdinat(650);
	kapalP_bottom_right.SetAbsis(550);
	kapalP_bottom_right.SetOrdinat(690);
	Object kapal("objects/Kapal2.txt");
	Pattern pattern2("pattern/ikan.txt");
	kapal.SetWarna(white);
	RGBcolor kapal2Col;
	//kapal2Col.setRGB(0,0,200);

	/*Pilih warna kapal dan pesawat*/
	system("clear");
	//frame.clear();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	cout << "Pilih warna dasar kapal perangmu!" << endl;
	kapal2Col = frame.drawColorPicker();
	cout << "Warna yang kamu pilih:" << endl;
	cout << "R=" << kapal2Col.getRed();
	cout << ", G=" << kapal2Col.getGreen();
	cout << ", B=" << kapal2Col.getBlue() << endl;
	cout << "Tekan apapun" << endl;
	inputkey = frame._getch();
	
	system("clear");
	//frame.clear();
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	cout << "Pilih warna dasar pesawat musuh." << endl;
	pswtCol = frame.drawColorPicker();
	cout << "Warna yang kamu pilih:" << endl;
	cout << "R=" << pswtCol.getRed();
	cout << ", G=" << pswtCol.getGreen();
	cout << ", B=" << pswtCol.getBlue() << endl;
	cout << "Tekan apapun" << endl;
	inputkey = frame._getch();

	// text
	string s1;
	s1 = "Kapal perang Indonesia pun berperang melawan pesawat penjajah.";
	system("clear");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t\t\t\t\t";
	for (int i=0; i<s1.length(); i++) {
		cout << s1[i];
		cout.flush();
		usleep(30000);
	}
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	sleep(1);

	system("clear");

	/*Draw semua Object*/
	pswt.Draw(frame);
	pswt.FloodFill(pswtCol,frame);
	pswt.DrawPattern(pattern, frame, warnaPeluru);

	baling.Draw(frame);

	kapal.Draw(frame);
	kapal.FloodFill(kapal2Col,frame);
	kapal.DrawPattern(pattern2, frame, warnaPeluru);

	/*Pesawat dan Kapal maju duluan*/
	for(int i=1;i<50;i++){
		usleep(10000);
		kapal.Geser(3,0,frame);
		kapal.FloodFill(kapal2Col,frame);
		kapal.DrawPattern(pattern2, frame, warnaPeluru);
		pswt.Geser(-1,0,frame);
		pswt.FloodFill(pswtCol,frame);
		pswt.DrawPattern(pattern, frame, warnaPeluru);
		baling.Geser(-1,0,frame);
		x_center--;
		baling.Putar(12,x_center,y_center,frame);
	}

	while((peluruStart.GetOrdinat()>10) && !meledak){
		pswt.Draw(frame);
		baling.Draw(frame);
		kapal.SetWarna(white);
		kapal.Draw(frame);
		if(frame.isSameColor(black,peluruStart.GetAbsis(),peluruStart.GetOrdinat()-radpeluru)){
			Peluru.plotCircle(peluruStart,radpeluru,warnaPeluru,frame);
			//Peluru.FloodFill(peluruStart.GetAbsis(), peluruStart.GetOrdinat(), warnaPeluru, frame);
			Peluru2.plotCircle(peluru2Start,radpeluru,warnaPeluru,frame);
			//Peluru2.FloodFill(peluru2Start.GetAbsis(), peluruStart.GetOrdinat(), warnaPeluru, frame);
			usleep(10000);
			Peluru.plotCircle(peluruStart,radpeluru,black,frame);
			Peluru2.plotCircle(peluru2Start,radpeluru,black,frame);
			peluruStart.SetOrdinat(peluruStart.GetOrdinat()-5);
			peluru2Start.SetOrdinat(peluru2Start.GetOrdinat()+5);
			pswt.Geser(-1,0,frame);
			pswt.FloodFill(pswtCol,frame);
			pswt.DrawPattern(pattern, frame, warnaPeluru);
			kapal.Geser(3,0,frame);
			kapal.FloodFill(kapal2Col,frame);
			kapal.DrawPattern(pattern2, frame, warnaPeluru);

			baling.Geser(-1,0,frame);
			x_center--;
			baling.Putar(12,x_center,y_center,frame);
		}
		else{
			Meledak(peluruStart.GetAbsis(),peluruStart.GetOrdinat());
			antiLedak(peluruStart.GetAbsis(),peluruStart.GetOrdinat());
			roda_fall.SetAbsis(peluruStart.GetAbsis());
			roda_fall.SetOrdinat(peluruStart.GetOrdinat()+rad_roda);
			int t= 400, c = 1;
			int y = roda_fall.GetOrdinat();
			Point roda_bouncing = roda_fall;
			int g = 15;
			for (int x = roda_fall.GetAbsis()+1; x<roda_fall.GetAbsis()+63; x++) {
				usleep(10000);
				Roda.plotCircle(roda_bouncing, rad_roda, black, frame);
				if(y >= roda_fall.GetOrdinat()+490) {
					c = 0;
					t -= 20;
					g -= 5;
				}
				if (y <=roda_fall.GetOrdinat()+750-t) {
					c=1;
				}
				y = y + (c?g: -g);
				roda_bouncing.SetAbsis(x);
				roda_bouncing.SetOrdinat(y);
				Roda.plotCircle(roda_bouncing, rad_roda, white, frame);
			}
			meledak = true;
		}
	}
}

void PetaIndonesia(){
	//FrameBuffer frame;
	DrawingObject map_canvas, view_port, legend, petunjuk;
	Object viewport;
	RGBcolor warna_border;
	warna_border.setRGB(255,255,255);
	viewport.SetWarna(warna_border);
	Point canvas_topleft(50,50);
	Point petunjuk_topleft(70,600);
	Point view_topleft(200,200);
	Point legend_topleft(1016,516);
	Map Indonesia;
	float legend_zoom = 1.00;

	//system("clear");
	viewport.CreateRectangle(view_topleft, 200, 300);
	viewport.Draw(frame);
	viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
	viewport.DrawLegend(frame);

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "\t  "; cout << "---- Petunjuk ---- " << endl;
	cout << "\t  "; cout << "Gerakin viewport: tombol arrow" << endl;
	cout << "\t  "; cout << "Zoom in: z" << endl;
	cout << "\t  "; cout << "Zoom out: c" << endl;

	petunjuk.drawRectangle(petunjuk_topleft,100,300,warna_border,frame);

	map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
	legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
	Indonesia.Draw(frame);

	while(true) {
		int ch = frame._getch();
		if(ch == 0x41) { // up-arrow key
			if(viewport.GetAtas()>canvas_topleft.GetOrdinat()) {
				viewport.HapusLegend(frame);
				viewport.Geser(0,-5,frame);
				viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
				viewport.SkalaLegend(legend_zoom,legend_zoom,legend_topleft,300,200);
				viewport.DrawLegend(frame);
			}
		}
		else if(ch == 0x42) { // down-arrow key
			if(viewport.GetBawah()<canvas_topleft.GetOrdinat()+666-1) {
				viewport.HapusLegend(frame);
				viewport.Geser(0,5,frame);
				viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
				viewport.SkalaLegend(legend_zoom,legend_zoom,legend_topleft,300,200);
				viewport.DrawLegend(frame);
			}
		}
		else if(ch == 0x43) { // right-arrow key
			if(viewport.GetKanan()<canvas_topleft.GetAbsis()+1266-1) {
				viewport.HapusLegend(frame);
				viewport.Geser(5,0,frame);
				viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
				viewport.SkalaLegend(legend_zoom,legend_zoom,legend_topleft,300,200);
				viewport.DrawLegend(frame);
			}
		}
		else if(ch == 0x44) { // left-arrow key
			if(viewport.GetKiri()>canvas_topleft.GetAbsis()) {
				viewport.HapusLegend(frame);
				// frame.clear();
				viewport.Geser(-5,0,frame);
				viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
				map_canvas.drawRectangle(canvas_topleft,666,1266,warna_border,frame);
				legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
				Indonesia.Draw(frame);
				viewport.SkalaLegend(legend_zoom,legend_zoom,legend_topleft,300,200);
				viewport.DrawLegend(frame);
			}
		}
		else if((ch == 'z') && (legend_zoom<= pow(1.0*10/9, 10))) { // zoom-in legend
			viewport.Hapus(frame);
			viewport.Skala(1.0*9/10,1.0*9/10);
			viewport.Draw(frame);
			viewport.HapusLegend(frame);
			viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
			// viewport.SkalaLegend((viewport.GetKanan()-viewport.GetKiri())/200,(viewport.GetBawah()-viewport.GetAtas())/300);
			legend_zoom = legend_zoom*10/9;
			viewport.SkalaLegend(legend_zoom,legend_zoom,legend_topleft,300,200);
			viewport.DrawLegend(frame);
			legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
			Indonesia.Draw(frame);
		}
		else if(ch == 'c') { // zoom-out legend
			viewport.Hapus(frame);
			viewport.Skala(1.0*10/9,1.0*10/9);
			if(!((viewport.GetKiri()>canvas_topleft.GetAbsis())&&(viewport.GetKanan()<canvas_topleft.GetAbsis()+1266-1)&&(viewport.GetBawah()<canvas_topleft.GetOrdinat()+666-1)&&(viewport.GetAtas()>canvas_topleft.GetOrdinat()))) {
				viewport.Skala(1.0*9/10,1.0*9/10);
			}
			else{
				legend_zoom = legend_zoom*9/10;	
			}
			viewport.Draw(frame);
			viewport.HapusLegend(frame);
			viewport.CreateClip(Indonesia.getPulau(),frame,viewport.GetKiriAtas(),legend_topleft);
			Indonesia.Draw(frame);
			viewport.SkalaLegend(legend_zoom,legend_zoom,legend_topleft,300,200);
			viewport.DrawLegend(frame);
			legend.drawRectangle(legend_topleft,200,300,warna_border,frame);
		}
		else if(ch == 'q') {
			system("clear");
			break;
		}
	}
}

void PetaITB() {
	MapItb Ganesha;
	Ganesha.Draw(frame);

	while(true) {
		int ch = frame._getch();
		if(ch == 0x41) // up
			Ganesha.Geser(0,-5,frame);
		else if(ch == 0x42) // down
			Ganesha.Geser(0,5,frame);
		else if(ch == 0x43) // right
			Ganesha.Geser(5,0,frame);
		else if(ch == 0x44) // left
			Ganesha.Geser(-5,0,frame);
		else if(ch == 'q')
			break;
	}	
}