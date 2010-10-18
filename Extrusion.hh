#ifndef __class_Extrusion_hh__
#define __class_Extrusion_hh__

#include "CellularComplex.hh"
#include "Axis.hh"
#include "Interval.hh"
using namespace std;

/**
 * Extrusion
 *
 * Author: Kevin Peter Hickerson
 * Date: Aug 24, 2010
 */
template <dimension k, codimension n>
class Extrusion : public CellularComplex<k, n>
{
	CellularComplex<k-1,n>* profile;	// The profile to be extruded
	//CellularComplex<1,n>* axis;		// the 1-CellularComplex along which to extrude
	Axis<n>* 				axis;		// the n-Axis along which to extrude
	Interval<1,0>			interval;	// the distance to extrude 
										// TODO this may only be needed for an explicit embedding

public:
	//Extrusion(Axis<n>* copy_axis, CellularComplex<k-1, n> * copy_profile, double copy_length)
	Extrusion(Axis<n>* copy_axis, CellularComplex<k-1, n> * copy_profile, Interval<1,0> copy_interval)
	{
		axis = 		copy_axis;
		profile = 	copy_profile;
		interval = 	copy_interval;
		//length = 	copy_length;
	}

	Extrusion<k,n>(const Extrusion<k,n> & copy)
	{
		axis = 		copy.axis;
		profile = 	copy.profile;
		interval = 	copy.interval;
		//length = 	copy.length;
	}

	~Extrusion();
};

#endif
