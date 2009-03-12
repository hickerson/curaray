#include "Sphere.hh"
#include "MonteCarlo.hh"

InteractionEvent* Sphere::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	return NULL;
}


double* Sphere::get_random_point(double time) const 
{
	double* p = new double[3];
	//randomBallVector(p, radius);
	randomSphereVector(p, radius);
	for (int i = 0; i < 3; i++)
		p[i] += center[i];
	return p;
}
