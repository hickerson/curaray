#ifndef __class_Embeding_hh__
#define __class_Embeding_hh__

#include <string>
#include "CellularComplex.hh"
using namespace std;

/**
 * k-Embeding
 *
 * Author: Kevin Peter Hickerson
 * Created: Aug 24, 2010
 */
template <dimension k>
class Embeding : public CellularComplex<k>
{
public:
	Embeding();

	Embeding<k>(const Embeding<k> & copy)
	{
	}

	~Embeding();
	
	Embeding & operator = (const Embeding & other)
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
