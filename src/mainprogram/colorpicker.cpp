#include <unistd.h>
#include <fcntl.h>		/* for fcntl */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>		/* for mmap */
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RGBcolor.h"
#include "Point.h"

int plus255(int z);

int main() {
	long int screensize = 0;
	struct fb_var_screeninfo vinfo;
	struct fb_fix_screeninfo finfo;
	int fbfd;					/* frame buffer file descriptor */
	char* fbp;					/* pointer to framebuffer */
	int location;					/* iterate to location */

	int x, y;					/* x and y location */

	/* open the file for reading and writing */
	fbfd = open("/dev/fb0",O_RDWR);
	if (!fbfd) {
		printf("Error: cannot open framebuffer device.\n");
		exit(1);
	}
	printf ("The framebuffer device was opened successfully.\n");

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

	/* figure out the size of the screen in bytes */
	//screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

	/* map the device to memory */
	fbp = (char*)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
	/*fbp = (char*)mmap(0,
                    screensize,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    fbfd, 0);
	*/
	if ((int)fbp == -1) {
		printf ("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}
	printf ("Framebuffer device was mapped to memory successfully.\n");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	// Figure out where in memory to put the pixel
	for ( y = 0; y < 30; y++ )
	    for ( x = 0; x < 384; x++ ) { 
	        location = (x+30) * (vinfo.bits_per_pixel/8) + y * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	        	if((x>=0) && (x <64)){ 
	            *(fbp + location) = 0; // Some blue 
	            *(fbp + location + 1) = 0+(4*x); // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            }
	            else if((x>=64) && (x <128)){ 
	            *(fbp + location) = 0; // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 255-(4*x); // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            }
	            else if((x>=128) && (x <192)){ 
	            *(fbp + location) = 0+(4*x); // Some blue 
	            *(fbp + location + 1) = 255; // A little green 
	            *(fbp + location + 2) = 0; // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            }
	            else if((x>=192) && (x <256)){ 
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 255-(4*x); // A little green 
	            *(fbp + location + 2) = 0; // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            }
	            else if((x>=256) && (x <320)){ 
	            *(fbp + location) = 255; // Some blue 
	            *(fbp + location + 1) = 0; // A little green 
	            *(fbp + location + 2) = 0+(x*4); // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            }
	            else{
	            *(fbp + location) = 255-(4*x); // Some blue 
	            *(fbp + location + 1) = 0; // A little green 
	            *(fbp + location + 2) = 255; // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	            } 
	        } else { //assume 16bpp 
	            int b = 10; int g = (x-100)/6; // A little green 
	            int r = 31-(y-100)/16; // A lot of red 
	            unsigned short int t = r<<11 | g << 5 | b; 
	            *((unsigned short int*)(fbp + location)) = t; 
	        }
	    }

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
		    } else { //assume 16bpp 
			unsigned short int t = r<<11 | g << 5 | b; 
			*((unsigned short int*)(fbp + location)) = t; 
		    }
	      }
	}
	/*input user*/
	printf("\n");
	printf("Masukan koordinat x (0-255): ");scanf("%d",&inputx);
	printf("Masukan koordinat y (0-255): ");scanf("%d",&inputy);
	printf("\nSaturation = x/255 = %f\n", (float)inputx/255);
	printf("Lightness = (255-y)/255 = %f\n\n", (float)(255-inputy)/255);
	location = inputx * (vinfo.bits_per_pixel/8) + (inputy+50) * finfo.line_length;

	B = *(fbp + location);
	G = *(fbp + location + 1); 
	R = *(fbp + location + 2);
	printf("R = %d\n",plus255(R));
	printf("G = %d\n",plus255(G));
	printf("B = %d\n",plus255(B));
	for ( y = 0; y < 25; y++ ){
	    for ( x = 0; x < 25; x++ ) { 
	        location = x * (vinfo.bits_per_pixel/8) + (y+315) * finfo.line_length;
	        if ( vinfo.bits_per_pixel == 32 ) {
	            *(fbp + location) = B; // Some blue 
	            *(fbp + location + 1) = G; // A little green 
	            *(fbp + location + 2) = R; // A lot of red
	            *(fbp + location + 3) = 0; // No transparency
	        }
	        else { //assume 16bpp 
	            int b = 10; int g = (x-100)/6; // A little green 
	            int r = 31-(y-100)/16; // A lot of red 
	            unsigned short int t = r<<11 | g << 5 | b; 
	            *((unsigned short int*)(fbp + location)) = t; 
	        }
	    }
	}

	munmap(fbp, screensize);
	close(fbfd);

	return 0;
}

int plus255 (int z){
	while(z<0){
		z+=256;
	}
	return z;
}
