#ifndef __class_Sphere_hh__
#define __class_Sphere_hh__

#include <string>
#include <iostream>
#include "CellularComplex.hh"
#include "SimplicialComplex.hh"
#include "polynomial.hh"
using namespace std;


/**
 * k-Sphere
 *
 * Author: Kevin Peter Hickerson
 */
template <dimension k, codimension n = 1>
class Sphere : public CellularComplex<k,n> 
{
	double radius;
	//double r2;
	//double center[k+1];
	
public:
	Sphere(double r) // unit sphere
	: radius(r) {}

	Sphere() // unit sphere
	: radius(1)
	{
/*
		for (int i = 0; i < k+n; i++)
			center[i] = 0;
*/
	}
/*
	Sphere(double _center[k+n], double _radius) 
	: radius(_radius)
	{
		for (int i = 0; i < k+n; i++)
			center[i] = _center[i];
	}
*/	
	~Sphere();

	CellularComplex<1,1>* intersection(CellularComplex<1,k+n-1>* path)
	{
		for (int i = 0; i < k+1; i++)
			;
	}

	// temporary until I get my bearings... 
	//CellularComplex<0,1>* intersection(polynomial[k+n] path, time start, time stop)
	CellularComplex<0,1>* intersection(polynomial* path)//polynomial[k+n] path)
	{
		polynomial p = - radius * radius;
		for (int i = 0; i < k+n; i++)
		{	
			polynomial q = path[i];
			q *= q;
			p += q;
		}
		cout << p << endl;

		double roots[p.get_degree()];
		int n_roots = p.solve_real_roots(roots);

		return new SimplicialComplex<0,1>(roots, n_roots);
	}
/*
	{
		polynomial p = 0;
		for (int i = 0; i < k+n; i++)
		{
			polynomial q = path[i];
			q *= normal[i];
			p += q;
		}
		p += -nc;
		cout << p << endl;

		double* root = new double[p.get_degree()];
		int n_roots = p.solve_real_roots(root);
		//if (n_roots < 1)
		//	return 0;

		for (int i = 0; i < n_roots; i++)
		{
			double t = root[i];
			if (t > 0.00001)
			{
				t += start;
				if (t > stop)
					return 0;

				InteractionEvent* interaction = new InteractionEvent(t, this);
				interaction->set_normal(normal);
				return interaction;
			}
		}

		return 0;
	}
 
	InteractionEvent* interact(Pathlet* pathlet, double start_time, double stop_time) const;
	InteractionEvent* selfinteract(Pathlet* pathlet, double start_time, double stop_time) const;
*/
	//double* get_random_point(double time) const;
	double* get_random_point() const;
	void writeMathematicaGraphics(ofstream & of);
	void writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop);

	/**
	 * A Sphere has no boundary
	 */
	CellularComplex<k-1,n+1>* get_boundary() 
	{
		return 0; 
	}
};

/*
template <dimension k>
InteractionEvent* Sphere<k>::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}

template <dimension k>
InteractionEvent* Sphere<k>::selfinteract(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}
*/

template <dimension k, codimension n>
//double* Sphere<k,n>::get_random_point(double time) const 
double* Sphere<k,n>::get_random_point() const 
{
	double* p = new double[k+n];
	//randomSphereVector(p, radius);
	//for (int i = 0; i < k+n; i++)
	//	p[i] += center[i];
	return p;
}

template <dimension k, codimension n>
void Sphere<k,n>::writeMathematicaGraphics(ofstream & math_file) 
{
	math_file 
		<< "Graphics3D[ {Red, Opacity[0.3], Sphere [{" 
	    //<< center[0] << ", " << center[1] << ", " << center[2] 
        << "}, " << radius << "]}]";
}

template <dimension k, codimension n>
void Sphere<k,n>::writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
{
	writeMathematicaGraphics(math_file);
}

#endif
