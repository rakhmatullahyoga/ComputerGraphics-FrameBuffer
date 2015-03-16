#ifndef MAPITB_H
#define MAPITB_H

#include "Object.h"
#include <string>
#include <vector>

using namespace std;

class MapItb {
    public:
        MapItb();
        ~MapItb();
        void Draw(FrameBuffer frame);
        void Geser(int x, int y, FrameBuffer frame);
        vector<Object> getGedung();

    private:
        Object *albar;
        Object *altim;
        Object *ccbar;
        Object *cctim;
        Object *lab5;
        Object *lab6;
        Object *lab7;
        Object *lab8;
        Object *tvst;
        Object *oktagon;
        Object *comlabs;
        Object *pln;
        Object *pau;
        Object *perpus;
};

#endif // MAPITB_H
