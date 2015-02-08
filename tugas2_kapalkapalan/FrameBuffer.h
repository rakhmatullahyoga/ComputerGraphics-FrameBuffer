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

class FrameBuffer {
	public:
		FrameBuffer();
		~FrameBuffer();
		void initFrameBuffer();
		bool isBlack(int x, int y);
		struct fb_var_screeninfo vinfo;
		struct fb_fix_screeninfo finfo;
		char* fbp;					/* pointer to framebuffer */
	private:
		long int screensize;
		int fbfd;
		int location;					/* frame buffer file descriptor */
};

#endif