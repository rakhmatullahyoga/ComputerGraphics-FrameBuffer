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

RGBcolor FrameBuffer::drawColorPicker(){
	int x,y;
	drawColorPelangi();
	/*tes gradasi*/
	int inputx, inputy;
	int R, G, B;
	printf("Masukan koordinat gradasi pelangi (skala 0-383): ");scanf("%d",&inputx);

	for ( y = 0; y < 255; y++ ){
	    for ( x = 0; x < 256; x++ ) { 
		  location = x * (vinfo.bits_per_pixel/8) + (y+50) * finfo.line_length;
		  
		  int colmode = (inputx+1)/64;
		  int persen = (inputx+1)% 64;
		  int ia, ib, z;
		  double tmp;
		  
		  int b = 0;
		  int g = 0;
		  int r = 0;
		  
		  ia = x % 256;
		  ib = y % 256;
		  z  = sqrt(ia*ia + ib*ib);	// warna yang tetap
		  if (z > 255) z = 255;
		  
		  
		  // fungsi naik atau turun
		  if (colmode % 2 == 0){
		      tmp = (ia * (255-persen))/255;	// warna yang sedang naik
		  }else{
		      tmp = (ia * (persen))/255;		// warna yang sedang turun
		  }
		  
		  tmp = sqrt(tmp*tmp + ib*ib);
		  if (tmp > 255) tmp = 255;
		  
		  
		  switch (colmode){	// switch berdasarkan posisi warna pelangi (untuk menentukan warna mana yang naik dan turun)
		   case 0:
		   	b = 255 - z;
		    g = 255 - tmp; 
		    r = 255 - (y % 256); 
		    break;  
		      
		   case 1:
		    b = 255 - z;
		    g = 255 - (y % 256); 
		    r = 255 - tmp; 
		    break; 
		      
		   case 2:
		    b = 255 - tmp;
		    g = 255 - (y % 256); 
		    r = 255 - z; 
		    break;
		   	
		   case 3:
		    b = 255 - (y % 256);
		    g = 255 - tmp; 
		    r = 255 - z; 
		    break;
		   
		   case 4:
		    b = 255 - (y % 256);
		    g = 255 - z; 
		    r = 255 - tmp; 
		    break;
		      
		   case 5: 
		    b = 255 - tmp;
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
	/*input user*/
	printf("\n");
	printf("Masukan koordinat x (0-255): ");scanf("%d",&inputx);
	printf("Masukan koordinat y (0-255): ");scanf("%d",&inputy);
	location = inputx * (vinfo.bits_per_pixel/8) + (inputy+50) * finfo.line_length;

	B = *(fbp + location);
	G = *(fbp + location + 1); 
	R = *(fbp + location + 2);
	
	R = plus255(R);
	G = plus255(G);
	B = plus255(B);

	RGBcolor RGBterpilih;
	RGBterpilih.setRGB(R,G,B);
	for ( y = 0; y < 25; y++ ){
	    for ( x = 0; x < 25; x++ ) { 
	        location = x * (vinfo.bits_per_pixel/8) + (y+315) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	            *(fbp + location) = B; // Some blue 
	            *(fbp + location + 1) = G; // A little green 
	            *(fbp + location + 2) = R; // A lot of red
	        }
	    }
	}
	return RGBterpilih;
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