#pragma once
#ifndef __class_CellularComplex_hh__
#define __class_CellularComplex_hh__

//#include <boost/graph/adjacency_list.hpp>
//#include <boost/spirit/core.hpp>
#include <boost/spirit/include/classic_core.hpp>

#include <vector>
#include "Geometry.hh"
//#include "Cell.hh"
#include "Point.hh"

using namespace std;

//class InteractionEvent;

//class Point;

/**
 * n-CellularComplex
 *
 * Author: Kevin Peter Hickerson
 * Created: Aug 23, 2010
 */
template <dimension n, codimension m = 0>
class CellularComplex : public Geometry//<n,m>
{
protected:
	// The blob graph is only valid for k > 1
	
	//vector<Ball*> cells;
	//vector<Mates*> mates;
	//CellularComplex<n-1>* boundary;

public:
	CellularComplex() {};
	~CellularComplex() {};

public: 
	//virtual CellularComplex* get_union(CellularComplex* p) = 0;
	//virtual CellularComplex* boundary_and(CellularComplex* p) = 0;

	/**
	 * Get the sub-CellularComplex Component that contains Point p
	 */
	//virtual Point<n>* getRandomPoint(double time) const = 0;
	//virtual CellularComplex<m>* getComponent(CellularComplex<m>* p) = 0;
	//virtual CellularComplex<m>* getComponent(CellularComplex<m>* p) = 0;
	//virtual CellularComplex<m>* getComponent(CellularComplex<m-1>* p) = 0;
	virtual CellularComplex<n-1,m+1>* get_boundary() = 0;
	virtual CellularComplex<1,1>* intersection(CellularComplex<1,n+m-1>* p) = 0;

	/**
	 * Get the boundary of the sub-CellularComplex Component 
	 * that contains Point p.
	 *
	virtual CellularComplex<m-1>* getBoundary(CellularComplex<m>* p) 
	{
		return getComponent(p)->getBounrdary();
	}
	 */
	/**
	 * Get the boundary of the sub-CellularComplex Component Boundary
	 * that contains Point p
	 *
	virtual CellularComplex<n-1>* getBoundary(CellularComplex<n-1>* p) 
	{
		return getComponent(p)->getBounrdary();
	}
	 */
};

/**
 * (0,n)-CellularComplex
 * 
 * This is a disjoint union of Points in n dimension
template <>
class CellularComplex<0,codimension n> : public Geometry
{
	//...
	virtual (void*) get_boundary() = 0;
	{ 
		return 0;
	}
};
 */

#endif
