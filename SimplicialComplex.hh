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
template <dimension k, codimension n>
class SimplicialComplex : public CellularComplex<k,n>
{
//	SimplicialComplex<k-1,n+1> sub_complex;

public:
	SimplicialComplex(const double roots[], int n_roots)
	{
		for (int i = 0; i < n_roots; i++)
			;//add_cell(new Singleton<1>(root[i]));
	}

	SimplicialComplex(const SimplicialComplex & copy)
	{
	}

	~SimplicialComplex();
	
	SimplicialComplex<k,n> & operator = (const SimplicialComplex<k,n> & other)
    {
        if (this != &other) // protect against invalid self-assignment
        {
            // 1: allocate new memory and copy the data
            // 2: deallocate old memory
            // 3: assign the new memory to the object
        }
        return *this;
    }

	//void add_cell(SimplicialSimplex* 
};
/*
template <0, codimension n>
class SimplicialComplex : public CellularComplex<0,n>
{
	vector<Point<n>>  point;
}
*/
#endif
