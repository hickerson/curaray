#ifndef __class_Point_hh__
#define __class_Point_hh__

#include "Geometry.hh"


using namespace std;

/**
 * Point
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension n>//, codimension m = 0>
//class Point : CellularComplex<0,n>
class Point : public Geometry//<n,m>
{
	double x[n];

public:
	Point() {};
	~Point() {};

public: 
	virtual InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	virtual InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const = 0;
	
	virtual void writeMathematicaGraphics(ofstream & of) = 0;
	virtual void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop) = 0;

	//virtual double* get_random_point(double time) const = 0;
	virtual Point<n>* get_random_point() const
	{
		return this;
	}
};

#endif
