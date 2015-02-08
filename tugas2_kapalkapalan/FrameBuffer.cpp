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

	/* map the device to memory */
	fbp = (char*)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

	if ((int)fbp == -1) {
		printf ("Error: failed to map framebuffer device to memory.\n");
		exit(4);
	}
	printf ("Framebuffer device was mapped to memory successfully.\n");
}

bool FrameBuffer::isBlack(int x, int y){
	location = x * (vinfo.bits_per_pixel/8) + y * finfo.line_length;
	int R = *(fbp+location+2);
	int G = *(fbp+location+1);
	int B = *(fbp+location);
	/*cout << "R=" << R << endl;
	cout << "G=" << G << endl;
	cout << "B=" << B << endl;*/
	return (R == 0) && (G == 0) && (B == 0);
}