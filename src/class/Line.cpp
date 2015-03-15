#include "Line.h"
#include <iostream>
using namespace std;

Line::Line(Point start, Point end) {
	P1.SetAbsis(start.GetAbsis());
	P1.SetOrdinat(start.GetOrdinat());
	P2.SetAbsis(end.GetAbsis());
	P2.SetOrdinat(end.GetOrdinat());
}
Line::~Line() {}