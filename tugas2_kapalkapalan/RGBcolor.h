#ifndef RGBCOLOR_H
#define RGBCOLOR_H

class RGBcolor {
	private:
		int red, green, blue;
	public:
		RGBcolor();
		~RGBcolor();
		void setRed(int new_red);
		void setGreen(int new_green);
		void setBlue(int new_blue);
		int getRed();
		int getGreen();
		int getBlue();
};

#endif