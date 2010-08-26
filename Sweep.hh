#ifndef __class_Sweep_hh__
#define __class_Sweep_hh__

#include "CellularComplex.hh"
#include "Axis.hh"
using namespace std;

/**
 * Sweep
 *
 * Author: Kevin Peter Hickerson
 * Date: Aug 24, 2010
 */
template <dimension k>
class Sweep : public CellularComplex<k>
{
	Axis* axis;
	CellularComplex<k-1>* profile;
	double angle;

public:
	Sweep<k>(Axis* _axis, CellularComplex<k-1> * _profile, double _angle)
	{
		axis = _axis;
		profile = _profile;
		angle = _angle;
	}

	Sweep<k>(const Sweep<k> & copy)
	{
		axis = copy.axis;
		profile = copy.profile;
		angle = copy.angle;
	}

	~Sweep();
};

#endif
