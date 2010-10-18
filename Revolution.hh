#ifndef __class_Revolution_hh__
#define __class_Revolution_hh__

#include "CellularComplex.hh"
#include "Axis.hh"
using namespace std;

/**
 * Revolution
 *
 * Author: Kevin Peter Hickerson
 * Date: Aug 24, 2010
 */
template <dimension k, codimension n>
//		  class ProfileType = CellularComplex<k-1,n> >
class Revolution : public CellularComplex<k,n>
{
  protected:
	CellularComplex<k-1,n>* profile;
	//ProfileType* profile;
	Axis<k+n>* axis;
	//double angle;

  public:
	Revolution(CellularComplex<k-1,n>* _profile, Axis<k+n>* _axis)
	//Revolution<k,n>(ProfileType* _profile, Axis<k+n>* _axis)
	{
		profile = _profile;
		axis = _axis;
		//angle = _angle;
	}

	Revolution<k,n>(const Revolution<k,n> & copy)
	{
		profile = copy.profile;
		axis = copy.axis;
		//angle = copy.angle;
	}

	~Revolution();
};

#endif
