#ifndef PROD_V_H
#define PROD_V_H

#include <iostream>
using namespace std;

class v {
private:
	int size;
	double** A;
	double* Y;
	double E;
public:
	void FromCin();
	double Norma();
};


#endif 
