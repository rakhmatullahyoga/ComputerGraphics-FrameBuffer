#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
using namespace std;

class Matrix
{
public:
	Matrix();
	~Matrix();

	void multiple(Matrix Mat2);
	/* data */
private:
	vector<vector<int> > Mat;
};

#endif 