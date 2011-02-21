#ifndef __class_MathematicaStream_hh__
#define __class_MathematicaStream_hh__

#include <string>
#include <fstream>

using namespace std;

/**
 * MathematicaStream
 *
 * Author: Kevin Peter Hickerson
 * Created: Mon Feb 14 14:25:07 PST 2011
 */
class MathematicaStream : public ofstream
{
public:
	MathematicaStream();

	MathematicaStream(const MathematicaStream & copy)
	{
	}

	~MathematicaStream();
	
	MathematicaStream & operator = (const MathematicaStream & other)
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
