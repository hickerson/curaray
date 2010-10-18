#ifndef __class_Solid_hh__
#define __class_Solid_hh__

#include <string>
#include <iostream>
#include "loadSTL.hh"
#include "CellularComplex.hh"

using namespace std;

/**
 * Solid
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension n = 3>
class Solid : public CellularComplex<3, n-3>
{
	//Solid();
	//~Solid();

	//void member();
};

#endif
