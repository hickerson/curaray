#include "Histogram.hh"

Histogram::Histogram(unsigned _size, double _start, double _stop)
	: size(_size), start(_start), stop(_stop) {
    histogram = new int[size]; 
    for (unsigned i = 0; i < size; i++)
        histogram[i] = 0;
}

Histogram::~Histogram() {
	delete[] histogram;
}

double Histogram::bin(unsigned i) {
	return start + i*(stop - start) / size;
}

/*
void Histogram::out(string & filename) {
    ofstream histogram_file; 
    histogram_file.open(filename.c_str());
    out(histogram_file);
}
*/

void Histogram::out(const char * filename) {
    ofstream histogram_file; 
    histogram_file.open(filename);
    out(histogram_file);
}

void Histogram::out(ofstream & histogram_file) {
    for (unsigned i = 0; i < size; i++)
        cout << bin(i) << '\t' << histogram[i] << endl;
    for (unsigned i = 0; i < size; i++)
        histogram_file << bin(i) << '\t' << histogram[i] << endl;
}

unsigned Histogram::index(double x) {
	return (unsigned)((double)size) * (x - start) / (stop - start);
}

// if the index is in range then add a point to the right bin
bool Histogram::add(double x) {
	unsigned i = index(x);
	if(0 <= i and i < size)
		histogram[i]++;
        else
		cerr << "value " << x << " is not in historgram range." << endl;
}
