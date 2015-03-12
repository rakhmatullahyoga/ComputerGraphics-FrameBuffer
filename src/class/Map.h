#ifndef MAP_H
#define MAP_H

#include "Object.h"
#include <string>
#include <vector>
using namespace std;

class Map{
	public:
		Map();
		~Map();
		void Draw(FrameBuffer frame);
		vector<Object> getPulau();
	private:
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