#ifndef __class_Surface_hh__
#define __class_Surface_hh__

#include <string>
#include <iostream>
#include "loadSTL.hh"
#include "Geometry.hh"

using namespace std;

/**
 * Surface
 *
 * Author: Kevin Peter Hickerson
 */
class Surface : public Geometry
{
	//Surface();
	//~Surface();

	//void member();
};

class STLSurface : Surface
{
public:
	STLfile *stl_file;

	STLSurface(const char * filename);
	//STLSurface(string filename);
	//~STLSurface();

	//void member();
};

#endif
