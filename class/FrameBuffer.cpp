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