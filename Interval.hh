#ifndef __class_Interval_hh__
#define __class_Interval_hh__

//#include <string>
//#include <iostream>
#include "CellularComplex.hh"

//using namespace std;

/**
 * Interval
 *
 * A k-Interval is a k-direct product of the 1-Interval.
 * 
 * Author: Kevin Peter Hickerson
 * Date:   Aug 23, 2010
 */
template <dimension k>
class Interval : public CellularComplex<k>
{
	double x[k][2];
	//Cube<k-1> boundary;

public:	
	Interval<k>(const double _x[2*k])
	{
		for (unsigned i = 0; i < k; i++)
		{
			x[i][0] = _x[2*i];
			x[i][1] = _x[2*i+1];
		}
	}

	Interval<k>(const double _x[k][2])
	{
		for (unsigned i = 0; i < k; i++)
			for (unsigned j = 0; j < 2; j++)
				x[i][j] = _x[i][j];
	}

	Interval<k>(const double min[k], const double max[k])
	{
		for (unsigned i = 0; i < k; i++)
		{
			x[i][0] = min[i];
			x[i][1] = min[i];
		}	
	}

	Interval<k>(const Interval<k> &copy)
	{
		for (unsigned i = 0; i < k; i++)
			for (unsigned j = 0; j < 2; j++)
				x[i][j] = copy.x[i][j];
	}
	~Interval() {}
		
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const
	{
		return NULL;
	}

	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const
	{
		return NULL;
	}

	double* get_random_point(double time) const 
	{
		double* p = new double[k];
		for (unsigned i = 0; i < k; i++)
			p[i] = randomRange(x[i][0], x[i][1]);
		return p;
	}

	void writeMathematicaGraphics(ofstream & of) 
	{
		// TODO
		abort();
	}

	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
	{
		// TODO
		abort();
	}
/*
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	InteractionEvent* self_interact(Pathlet* pathlet, double start_time, double stop_time) const;
	double* get_random_point(double time) const;
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop);
*/
};

#endif
