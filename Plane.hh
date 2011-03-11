#ifndef __class_Plane_hh__
#define __class_Plane_hh__

#include <string>
#include <iostream>
#include "Geometry.hh"
#include "MonteCarlo.hh"

#define abs(x) (x>=0?x:-x)
using namespace std;

/**
 * k-Plane
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension n, codimension k=1>
//class Plane : public Geometry<n,k>
class Plane : public Geometry
{
	double normal[n+k];
	double center[n+k];
	double nc;
		
public:
	// a plane perpendicular to axis passing though origin
	Plane(int axis)
	{
		normal[axis] = 1;
		for (int i=1; i < n+k; i++)
			center[(axis+i)%(n+k)] = 0;
		nc = 0;
	}
	
	// defaults to passing through the origin
	Plane(double _normal[n+k]) 
	{
		if (k != 1)
			abort ();
		for (int i=0; i < n+k; i++)
		{
			normal[i] = _normal[i];
			center[i] = 0;
		}
		nc = 0;
	}
	
	Plane(double _normal[n+k], double _center[n+k]) 
		: nc(0)
	{
		for (int i=0; i < n+k; i++)
		{
			// TODO iterate through instead of index
			normal[i] = _normal[i];
			center[i] = _center[i];
			nc += normal[i] * center[i];
		}
	}
	
	~Plane();

/*
public:
	// TODO this doesn't belong here because an infinite plane is not compact
	// for now this can return the projection of a 2-Sphere point onto the plane
	double* get_random_point(double time) const;

	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const;
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_time);
*/

public:
	/*
	CellularComplex<1,n+1>* get_boundary() 
	{
		return 0; // without boundary
	}

	CellularComplex<1,1>* intersection(CellularComplex<1,n+1>* p)
	{
		assert (false);
		return 0; 
		// ...
	}
	*/

	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const
	{
		polynomial p = 0;
		for (int i = 0; i < 3; i++)
		{
			polynomial q = pathlet->curve[i];
			q *= normal[i];
			p += q;
		}
		p -= nc;

		double* root = new double[p.get_degree()];
		int n_roots = p.solve_real_roots(root);

		for (int i = 0; i < n_roots; i++)
		{
			double t = root[i] + pathlet->start_time;
			cout << root[i] << " + ";
			cout << pathlet->start_time << endl;
			if (t > stop_time)
				return 0;

			if (t > start_time)
				return new InteractionEvent(t, this, normal, pathlet, 0);
		}

		/*
		for (int i = 0; i < n_roots; i++)
		{
			double t = root[i];
			if (t > 0.00001)
			{
				t += start_time;
				if (t > stop_time)
					return 0;

				InteractionEvent* interaction = new InteractionEvent(t, this);
				interaction->set_normal(normal);
				return interaction;
			}
		}
		*/
		return 0;
	}

	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const
	{

		cout << "looking for self-interaction" << endl;
		// TODO optimize
		/* TODO 
		1. check degree
		if (degree < 2)
			return 0
		
		2. shift down degree to remove x=0 solution
		*/

		polynomial p = 0;
		for (int i = 0; i < 3; i++)
		{
			polynomial q = pathlet->curve[i];
			q *= normal[i];
			p += q;
		}
		p -= nc; // no longer needed
		p <<= 1;

		double* root = new double[p.get_degree()];
		int n_roots = p.solve_real_roots(root);

		for (int i = 0; i < n_roots; i++)
		{
			double t = root[i] + pathlet->start_time;
			if (t > stop_time)
				return 0;

			if (t > start_time)
				return new InteractionEvent(t, this, normal, pathlet, 0);
		}

		return 0;
	}

	// TODO this doesn't belong here because an infinite plane is not compact
	// for now this can return the projection of a 2-Sphere point onto the plane
	//double* get_random_point(double time) const 
	double* get_random_point() const 
	{
		// XXX only compact geometries can support uniformly distributed points
		return 0;
	}

	void writeMathematicaGraphics(ofstream & math_file) 
	{
		// TODO principle axis
		/*
		int axis = 0;
		double max_value = 0;
		for (int i = 0; i < 3; i++)
		{
			double value = abs(normal[i]);
			if (value > max_value)
			{
				max_value = value;
				axis = i;
			}
		}

		math_file << "ParametricPlot3D[ "
				  << "(nc -" << center[(axis+1)%3] << "*u - " << center[(axis+2)%3] << "*v) / " << center[axis] << ", "
				  << "{u, -1, 1}, {v, -1, 1}];";
				  */
		math_file << "Plot3D[ "
				  << "(" << nc << " - " << normal[0] << "*x - " << normal[1] << "*y) / " << normal[2] << ", "
				  << "{x, -4, 4}, {y, -4, 4}, Mesh -> None,"
				  << "PlotStyle -> Directive[LightGray, Specularity[White, 30]] ]";
	}

	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
	{
		writeMathematicaGraphics(math_file);
	}
};

#endif
