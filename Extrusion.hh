#ifndef __class_Extrusion_hh__
#define __class_Extrusion_hh__

#include "CellularComplex.hh"
#include "Axis.hh"
using namespace std;

/**
 * Extrusion
 *
 * Author: Kevin Peter Hickerson
 * Date: Aug 24, 2010
 */
template <dimension k>
class Extrusion : public CellularComplex<k>
{
	CellularComplex<k-1>* profile;		// The profile to be extruded
	//Axis* axis;						// the Axis along which to extrude
	CellularComplex<1>* axis;			// the 1-CellularComplex along which to extrude
	double length;						// the distance to extrude 
										// TODO this may only be needed for an explicit embedding

public:
	Extrusion<k>(Axis* _axis, CellularComplex<k-1> * _profile, double _length)
	{
		axis = _axis;
		profile = _profile;
		length = _length;
	}

	Extrusion<k>(const Extrusion<k> & copy)
	{
		axis = copy.axis;
		profile = copy.profile;
		length = copy.length;
	}

	~Extrusion();
};

#endif
