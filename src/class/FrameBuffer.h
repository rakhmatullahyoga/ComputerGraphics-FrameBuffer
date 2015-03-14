#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

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
#include "Point.h"
#include "RGBcolor.h"
#include <termios.h>

class FrameBuffer {
	public:

		FrameBuffer();
		~FrameBuffer();
		int _getch();
		void initFrameBuffer();
		void putPixel(Point P, RGBcolor warna);
		void clear();
		RGBcolor drawColorPicker();
		void drawColorPelangi();
		void drawColorGradien(int inputx);
		void drawPointedColor(int *R, int *G, int *B, int inputx, int inputy);
		bool isSameColor(RGBcolor oldCol, int x, int y);
		bool isBlack(int x, int y);
		int plus255 (int z);
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;
		char* fbp;					/* pointer to framebuffer */
	private:
		long int screensize;
		int fbfd;
		int location;					/* frame buffer file descriptor */
		void drawColorPelangiPicker(int koord_x);
		void hapusColorPelangiPicker(int koord_x);
		void drawColorGradienPicker(int inputx, int inputy);
		void hapusColorGradienPicker(int inputx, int inputy);
};

#endif