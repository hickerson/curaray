#ifndef __class_SimplicialComplex_hh__
#define __class_SimplicialComplex_hh__

#include <string>
#include <iostream>
#include "CellularComplex.hh"

using namespace std;

/**
 * k-SimplicialComplex
 *
 * Author: Kevin Peter Hickerson
 * Created: Aug 25, 2010
 */
template <dimension k>
class SimplicialComplex : public CellularComplex<k>
{
public:
	SimplicialComplex<k>(const SimplicialComplex<k> & copy)
	{
	}

	~SimplicialComplex();
	
	SimplicialComplex<k> & operator = (const SimplicialComplex<k> & other)
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
