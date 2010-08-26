#ifndef __class_Arc_hh__
#define __class_Arc_hh__

#include <string>
#include <iostream>

using namespace std;

/**
 * Arc
 *
 * Author: Kevin Peter Hickerson
 * Created: <DATE>
 */
class Arc
{
public:
	Arc();

	Arc(const Arc & copy)
	{
	}

	~Arc();
	
	Arc & operator = (const Arc & other)
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
