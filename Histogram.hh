#ifndef __class_Histogram_hh__
#define __class_Histogram_hh__

#include <string>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

/**
 * Histogram
 *
 * Author: Kevin Peter Hickerson
 */
class Histogram {
private:
	unsigned size;
	double start;
	double stop;

	int* histogram;

public:
	Histogram(unsigned _size, double _start, double _stop);
	~Histogram();

	double bin(unsigned i);
	//void out(string & filename);
	void out(const char * filename);
	void out(ofstream & histogram_file);
	// TODO add ostream operator
	
	unsigned index(double x);
	bool add(double x);
};

#endif
