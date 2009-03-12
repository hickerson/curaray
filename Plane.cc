#include "Plane.hh"
#include "MonteCarlo.hh"

InteractionEvent* Plane::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	polynomial p = 0;

	for (int i = 0; i < 3; i++)
	{
		polynomial q = pathlet->curve[0];
		q *= normal[i];
		p += q;
	}
	p += -nc;
	cout << p << endl;
	double* root = new double[p.get_degree()];
	int n_roots = p.solve_real_roots(root);
	if (n_roots)
		return new InteractionEvent(root[0], this);
	else 
		return 0;
}


double* Plane::get_random_point(double time) const 
{
	// ERROR only compact geometries can support this
	return 0;
}
