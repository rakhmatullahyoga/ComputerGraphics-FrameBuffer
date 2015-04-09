#include "FrameBuffer.h"
#include <iostream>
using namespace std;

FrameBuffer::FrameBuffer() {
	initFrameBuffer();
}
FrameBuffer::~FrameBuffer() {
	close(fbfd);
}
void FrameBuffer::initFrameBuffer() {
	screensize = 0;
	fbfd = open("/dev/fb0",O_RDWR);
	if (!fbfd) {
		printf("Error: cannot open framebuffer device.\n");
		exit(1);
	}

	/* get the fixed screen information */
	if (ioctl (fbfd, FBIOGET_FSCREENINFO, &finfo)) {
		printf("Error reading fixed information.\n");
		exit(2);
	}

	/* get variable screen information */
	if (ioctl (fbfd, FBIOGET_VSCREENINFO, &vinfo)) {
		printf("Error reading variable information.\n");
		exit(3);
	}

	/* map the device to memory */
	fbp = (char*)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

	if ((int)fbp == -1) {
		printf ("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}
}

void FrameBuffer::putPixel(Point P, RGBcolor warna){
	location = P.GetAbsis() * (vinfo.bits_per_pixel/8) + P.GetOrdinat() * finfo.line_length;
	*(fbp + location) = warna.getBlue(); // Some blue 
	*(fbp + location + 1) = warna.getGreen(); // A little green 
	*(fbp + location + 2) = warna.getRed(); // A lot of red
	*(fbp + location + 3) = 0; // No transparency
}

void FrameBuffer::clear(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

bool FrameBuffer::isSameColor(RGBcolor oldCol, int x, int y) {
	location = x * (vinfo.bits_per_pixel/8) + y * finfo.line_length;
	int R = *(fbp+location+2);
	int G = *(fbp+location+1);
	int B = *(fbp+location);
	return ((R == oldCol.getRed()) && (G == oldCol.getGreen()) && (B == oldCol.getBlue()));
}

/* mungkin bakal dihapus */
bool FrameBuffer::isBlack(int x, int y){
	location = x * (vinfo.bits_per_pixel/8) + y * finfo.line_length;
	int R = *(fbp+location+2);
	int G = *(fbp+location+1);
	int B = *(fbp+location);
	return ((R == 1) && (G == 1) && (B == 1)) || ((R == 0) && (G == 0) && (B == 0));
}
RGBcolor FrameBuffer::getWarna(int x, int y) {
	RGBcolor selected;
	location = x * (vinfo.bits_per_pixel/8) + y * finfo.line_length;
	int R = *(fbp+location+2);
	int G = *(fbp+location+1);
	int B = *(fbp+location);
	selected.setRGB(R,G,B);
	return selected;
}
int FrameBuffer::plus255 (int z){
	while(z<0){
		z+=256;
	}
	return z;
}
void FrameBuffer::drawColorPelangi(){
	int x,y;
	for ( y = 0; y < 30; y++ ){
	    for ( x = 0; x < 384; x++ ) { 
	        location = (x+30) * (vinfo.bits_per_pixel/8) + (y+10) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x>=0) && (x <64)){ 
	            *(fbp + location) = 0; // Some blue 
	            *(fbp + location + 1) = 0+(4*x); // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	            }
	            else if((x>=64) && (x <128)){ 
	            *(fbp + location) = 0; // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 255-(4*x); // A lot of red
	            }
	            else if((x>=128) && (x <192)){ 
	            *(fbp + location) = 0+(4*x); // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 0; // A lot of red
	            }
	            else if((x>=192) && (x <256)){ 
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 255-(4*x); // A little green 
	            *(fbp + location + 2) = 0; // A lot of red
	            }
	            else if((x>=256) && (x <320)){ 
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 0; // A little green 
	            *(fbp + location + 2) = 0+(x*4); // A lot of red
	            }
	            else{
	            *(fbp + location) = 255-(4*x); // Some blue 
	            *(fbp + location + 1) = 0; // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            } 
	        }
	    }
	}
}
void FrameBuffer::hapusColorPelangi(){
	int x,y;
	for ( y = 0; y < 30; y++ ){
	    for ( x = 0; x < 384; x++ ) { 
	        location = (x+30) * (vinfo.bits_per_pixel/8) + (y+10) * finfo.line_length;
            *(fbp + location) = 1; // Some blue 
            *(fbp + location + 1) = 1; // A little green 
            *(fbp + location + 2) = 1; // A lot of red
	    }
	}
}
void FrameBuffer::drawColorPelangiPicker(int koord_x){
	int x,y;
	for ( y = 0; y < 30; y++ ){
	    for ( x = 0; x < 3; x++ ) { 
	        location = (x+29+koord_x) * (vinfo.bits_per_pixel/8) + (y+10) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x!=1) || ((x==1) && (y==0) || (y==29))){
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	            }
	        }
	    }
	}
	for ( y = 0; y < 6; y++ ){
		location = (30+koord_x) * (vinfo.bits_per_pixel/8) + (y+40) * finfo.line_length;
	    if ( vinfo.bits_per_pixel == 32 ) {
	        *(fbp + location) = 255; // Some blue 
	        *(fbp + location + 1) = 255; // A little green 
	        *(fbp + location + 2) = 255; // A lot of red
	    }
	}
}
void FrameBuffer::hapusColorPelangiPicker(int koord_x){
	int x,y;
	for ( y = 0; y < 30; y++ ){
	    for ( x = 0; x < 3; x++ ) { 
	        location = (x+29+koord_x) * (vinfo.bits_per_pixel/8) + (y+10) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x!=1) || ((x==1) && (y==0) || (y==29))){
	            *(fbp + location) = 0; // Some blue 
	            *(fbp + location + 1) = 0; // A little green 
	            *(fbp + location + 2) = 0; // A lot of red
	            }
	        }
	    }
	}
	for ( y = 0; y < 6; y++ ){
		location = (30+koord_x) * (vinfo.bits_per_pixel/8) + (y+40) * finfo.line_length;
	    if ( vinfo.bits_per_pixel == 32 ) {
	        *(fbp + location) = 0; // Some blue 
	        *(fbp + location + 1) = 0; // A little green 
	        *(fbp + location + 2) = 0; // A lot of red
	    }
	}
}
void FrameBuffer::drawColorGradien(int inputx){
	int x,y;
	for ( y = 0; y < 256; y++ ){
	    for ( x = 0; x < 256; x++ ) { 
		  location = (x+30) * (vinfo.bits_per_pixel/8) + (y+50) * finfo.line_length;
		  
		  int colmode = (inputx) / 64;
		  int persen = ((inputx) % 64) * 4;
		  int ia, ib, z;
		  double temp;
		  
		  int b = 0;
		  int g = 0;
		  int r = 0;
		  
		  ia = x % 256;
		  ib = y % 256;
		  z  = sqrt(ia*ia + ib*ib);	// warna yang tetap
		  if (z > 255) z = 255;
		  
		  
		  // fungsi naik atau turun
		  if (colmode % 2 == 0){
		      temp = (ia * (255-persen))/255;	// warna yang sedang naik
		  }else{
		      temp = (ia * (persen))/255;		// warna yang sedang turun
		  }
		  
		  temp = sqrt(temp*temp + ib*ib);
		  if (temp > 255) temp = 255;
		  
		  
		  switch (colmode){	// switch berdasarkan posisi warna pelangi (untuk menentukan warna mana yang naik dan turun)
		   case 0:
		   	b = 255 - z;
		    g = 255 - temp; 
		    r = 255 - (y % 256); 
		    break;  
		      
		   case 1:
		    b = 255 - z;
		    g = 255 - (y % 256); 
		    r = 255 - temp; 
		    break; 
		      
		   case 2:
		    b = 255 - temp;
		    g = 255 - (y % 256); 
		    r = 255 - z; 
		    break;
		   	
		   case 3:
		    b = 255 - (y % 256);
		    g = 255 - temp; 
		    r = 255 - z; 
		    break;
		   
		   case 4:
		    b = 255 - (y % 256);
		    g = 255 - z; 
		    r = 255 - temp; 
		    break;
		      
		   case 5: 
		    b = 255 - temp;
		    g = 255 - z; 
		    r = 255 - (y % 256); 
		    break;
		  }
		  
		  if ( vinfo.bits_per_pixel == 32 ) { 
			*(fbp + location) = 	b; 
			*(fbp + location + 1) = g; 
			*(fbp + location + 2) = r;
			*(fbp + location + 3) = 0; 
		    }
	    }
	}
}
void FrameBuffer::hapusColorGradien(){
	int x,y;
	for ( y = 0; y < 256; y++ ){
	    for ( x = 0; x < 256; x++ ) { 
		  location = (x+30) * (vinfo.bits_per_pixel/8) + (y+50) * finfo.line_length;
		  *(fbp + location) = 1; // Some blue 
          *(fbp + location + 1) = 1; // A little green 
          *(fbp + location + 2) = 1; // A lot of red
	    }
	}
}
void FrameBuffer::drawColorGradienPicker(int inputx, int inputy){
	int x,y;
	for ( y = 0; y < 3; y++ ){
	    for ( x = 0; x < 3; x++ ) { 
	        location = (x+29+inputx) * (vinfo.bits_per_pixel/8) + (y+49+inputy) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x!=1) || ((x==1) && (y==0) || (y==2))){
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	            }
	        }
	    }
	}
	for ( x = 0; x < 6; x++ ){
		location = (x+290) * (vinfo.bits_per_pixel/8) + (50+inputy) * finfo.line_length;
	    if ( vinfo.bits_per_pixel == 32 ) {
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	    }
	}
	for ( y = 0; y < 6; y++ ){
		location = (30+inputx) * (vinfo.bits_per_pixel/8) + (y+310) * finfo.line_length;
	    if ( vinfo.bits_per_pixel == 32 ) {
	        *(fbp + location) = 255; // Some blue 
	        *(fbp + location + 1) = 255; // A little green 
	        *(fbp + location + 2) = 255; // A lot of red
	    }
	}
}

void FrameBuffer::hapusColorGradienPicker(int inputx, int inputy){
	int x,y;
	for ( y = 0; y < 3; y++ ){
	    for ( x = 0; x < 3; x++ ) { 
	        location = (x+29+inputx) * (vinfo.bits_per_pixel/8) + (y+49+inputy) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x!=1) || ((x==1) && (y==0) || (y==2))){
	            *(fbp + location) = 0; // Some blue 
	            *(fbp + location + 1) = 0; // A little green 
	            *(fbp + location + 2) = 0; // A lot of red
	            }
	        }
	    }
	}
	for ( x = 0; x < 6; x++ ){
		location = (x+290) * (vinfo.bits_per_pixel/8) + (50+inputy) * finfo.line_length;
	    if ( vinfo.bits_per_pixel == 32 ){
	        *(fbp + location) = 0; // Some blue 
	        *(fbp + location + 1) = 0; // A little green 
	        *(fbp + location + 2) = 0; // A lot of red
	    }
	}
	for ( y = 0; y < 6; y++ ){
		location = (30+inputx) * (vinfo.bits_per_pixel/8) + (y+310) * finfo.line_length;
	    if ( vinfo.bits_per_pixel == 32 ) {
	        *(fbp + location) = 0; // Some blue 
	        *(fbp + location + 1) = 0; // A little green 
	        *(fbp + location + 2) = 0; // A lot of red
	    }
	}
}

RGBcolor FrameBuffer::drawColorPicker(){
	int x,y;
	int koord_x=0;
	int ch;
	drawColorPelangi();
	drawColorPelangiPicker(koord_x);
	drawColorGradien(koord_x);
	//clear();
	cout << "press 's' button to select" << endl;
	while(ch!='s'){
		ch = _getch();
		if((ch == 0x43)&&(koord_x<383))/*geser kanan*/{
			hapusColorPelangiPicker(koord_x);
			drawColorPelangi();
			koord_x++;
			drawColorPelangiPicker(koord_x);
			drawColorGradien(koord_x);
		}
		else if((ch == 0x44)&&(koord_x>0))/*geser kiri*/{
			hapusColorPelangiPicker(koord_x);
			drawColorPelangi();
			koord_x--;
			drawColorPelangiPicker(koord_x);
			drawColorGradien(koord_x);
		}
	}
	/*tes gradasi*/
	int inputx=255;
	int inputy=0;
	int R, G, B;
	ch = 0;
	//printf("Masukan koordinat gradasi pelangi (skala 0-383): ");scanf("%d",&inputx);
	drawColorGradienPicker(inputx,inputy);
	drawPointedColor(&R, &G, &B, inputx, inputy);
	while(ch!='s'){
		ch = _getch();
		if((ch == 0x41)&&(inputy>0))/*geser atas*/{
			hapusColorGradienPicker(inputx,inputy);
			drawColorGradien(koord_x);
			inputy--;
			drawColorGradienPicker(inputx,inputy);
			drawPointedColor(&R, &G, &B, inputx, inputy);
		}
		else if((ch == 0x42)&&(inputy<255))/*geser bawah*/{
			hapusColorGradienPicker(inputx,inputy);
			drawColorGradien(koord_x);
			inputy++;
			drawColorGradienPicker(inputx,inputy);
			drawPointedColor(&R, &G, &B, inputx, inputy);
		}
		if((ch == 0x43)&&(inputx<255))/*geser kanan*/{
			hapusColorGradienPicker(inputx,inputy);
			drawColorGradien(koord_x);
			inputx++;
			drawColorGradienPicker(inputx,inputy);
			drawPointedColor(&R, &G, &B, inputx, inputy);
		}
		if((ch == 0x44)&&(inputx>0))/*geser kiri*/{
			hapusColorGradienPicker(inputx,inputy);
			drawColorGradien(koord_x);
			inputx--;
			drawColorGradienPicker(inputx,inputy);
			drawPointedColor(&R, &G, &B, inputx, inputy);
		}
	}
	
	RGBcolor RGBterpilih;
	RGBterpilih.setRGB(R,G,B);
	return RGBterpilih;
}
void FrameBuffer::drawPointedColor(int *R, int *G, int *B, int inputx, int inputy){
	location = (inputx+30) * (vinfo.bits_per_pixel/8) + (inputy+50) * finfo.line_length;
	*B = *(fbp + location);
	*G = *(fbp + location + 1); 
	*R = *(fbp + location + 2);
	
	*R = plus255(*R);
	*G = plus255(*G);
	*B = plus255(*B);

	int x,y;
	for ( y = 0; y <27; y++ ){
	    for ( x = 0; x < 27; x++ ) { 
	        location = (x+310) * (vinfo.bits_per_pixel/8) + (y+50) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x==0)||(x==26)||(y==0)||(y==26)){
	        		*(fbp + location) = 255-*B; // Some blue 
		            *(fbp + location + 1) = 255-*G; // A little green 
		            *(fbp + location + 2) = 255-*R; // A lot of red
	        	}
	        	else{
		            *(fbp + location) = *B; // Some blue 
		            *(fbp + location + 1) = *G; // A little green 
		            *(fbp + location + 2) = *R; // A lot of red
		        }
	        }
	    }
	}
}

int FrameBuffer::_getch() {
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