#ifndef __class_Knot_hh__
#define __class_Knot_hh__

#include <string>
#include <iostream>
#include "Sphere.hh"

using namespace std;

/**
 * Knot
 *
 * Author: Kevin Peter Hickerson
 * Created: Wed Sep  1 22:45:43 PDT 2010
 */
template <dimension n>
class Knot : public Sphere<n, 2>
{
public:
	Knot();

	Knot(const Knot & copy)
	{
	}

	~Knot();
	
	Knot & operator = (const Knot & other)
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

#endif
