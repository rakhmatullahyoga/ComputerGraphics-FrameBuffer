#include "Line.h"
#include <iostream>
using namespace std;

Line::Line(Point start, Point end) {
	P1.SetAbsis(start.GetAbsis());
	P1.SetOrdinat(start.GetOrdinat());
	P2.SetAbsis(end.GetAbsis());
	P2.SetOrdinat(end.GetOrdinat());
	A = end.GetOrdinat() - start.GetOrdinat();
	B = start.GetAbsis() - end.GetAbsis();
	C = A*start.GetAbsis()+B*start.GetOrdinat();
}
Line::~Line() {}
Point Line::getIntersection(Line L) {
	Point P;
	int det = A*L.getB() - L.getA()*B;
    if(det == 0){
        P.SetAbsis(-1);
        P.SetOrdinat(-1);
    }else{
        int x = (L.getB()*C - B*L.getC())/det;
        int y = (A*L.getC() - L.getA()*C)/det;
        P.SetAbsis(x);
        P.SetOrdinat(y);
    }
	return P;
}
int Line::getA() {
	return A;
}
int Line::getB() {
	return B;
}
int Line::getC() {
	return C;
}