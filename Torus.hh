#ifndef __class_Torus_hh__
#define __class_Torus_hh__

#include <string>
#include <iostream>
#include "Revolution.hh"
#include "Sphere.hh"
#include "Axis.hh"
using namespace std;

/**
 * Torus
 *
 * Author: Kevin Peter Hickerson
 * Created: Fri Sep  3 19:08:56 PDT 2010
//template <int n> class Torus<int n = 2> : public Revolution<n,1>
class Torus : public Revolution<2,1>
{
public:
	Torus(Sphere<1>* copy_sphere, Axis<3>* axis_copy) 
	{
		profile = copy_sphere;
		axis = copy_axis;
	}

	Torus(const Torus & copy)
	{
		profile = (Sphere<1>*) copy.profile;
		axis = copy.axis;
	}

	~Torus();
	
	Torus & operator = (const Torus & other)
    {
        if (this != &other) // protect against invalid self-assignment
        {
            // 1: allocate new memory and copy the data
            // 2: deallocate old memory
            // 3: assign the new memory to the object
        }
        return *this;
    }
};
 */

#endif
