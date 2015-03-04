#ifndef MAP_H
#define MAP_H

#include "FrameBuffer.h"
#include "DrawingObject.h"
#include "RGBcolor.h"
#include "Point.h"
#include "Pattern.h"
#include "Object.h"
#include <string>
#include <vector>
using namespace std;

class Map{
	public:
		Map();
		~Map();
		void Draw(FrameBuffer frame);
		vector<Point> getTitik();
	private:
		vector<Point> titik;
		Object *sumatra;
		Object *jawa;
		Object *kalimantan;
		Object *sulawesi;
		Object *papua;
		Object *maluku;
		Object *maluku1;
		Object *maluku2;
		Object *maluku3;
		Object *bali;
		Object *lombok;
		Object *ntb;
		Object *ntt;
};

#endif