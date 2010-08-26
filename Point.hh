#ifndef __class_Point_hh__
#define __class_Point_hh__

#include "Complex.hh"


using namespace std;

/**
 * Point
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension k>
class Point : public Complex<0>// Geometry
{
	double x[k];

public:
	Point() {};
	~Point() {};

public: 
	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	
	virtual void writeMathematicaGraphics(ofstream & of) = 0;
	virtual void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop) = 0;

	virtual double* get_random_point(double time) const = 0;
};

#endif
