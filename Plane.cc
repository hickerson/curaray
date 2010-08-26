#include "Plane.hh"
#include "MonteCarlo.hh"
#define abs(x) (x>=0?x:-x)

InteractionEvent* Plane::interact(Pathlet* pathlet, double start_time, double stop_time) const
{
	polynomial p = 0;

	for (int i = 0; i < 3; i++)
	{
		polynomial q = pathlet->curve[i];
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
			t += start_time;
			if (t > stop_time)
				return 0;

			InteractionEvent* interaction = new InteractionEvent(t, this);
			interaction->set_normal(normal);
			return interaction;
		}
	}

	return 0;
}

InteractionEvent* Plane::selfinteract(Pathlet* pathlet, double start_time, double stop_time) const
{
	// TODO optimize
	return interact(pathlet, start_time, stop_time);
	/*
	polynomial p = 0;

	for (int i = 0; i < 3; i++)
	{
		polynomial q = pathlet->curve[i];
		q *= normal[i];
		p += q;

	}
	p += -nc;
	cout << p << endl;
	double* root = new double[p.get_degree()];
	int n_roots = p.solve_real_roots(root);
	if (n_roots < 2)
		return 0;

	double t = root[0];
	if (t < 0.000000001)
		return 0;

	t += start_time;
	if (t > stop_time)
		return 0;

	InteractionEvent* interaction = new InteractionEvent(t, this);
	interaction->set_normal(normal);
	return interaction;
	polynomial p = 0;
	*/
	/*

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
	if (n_roots > 1)
	{
		double t = root[1];
		if (t > 0)
			t += start_time;
		else
			return 0;

		if (t < stop_time)
			return new InteractionEvent(t, this);
		else
			return 0;
	}
	else 
		return 0;
	*/
}

double* Plane::get_random_point(double time) const 
{
	// XXX only compact geometries can support this
	return 0;
}

void Plane::writeMathematicaGraphics(ofstream & math_file) 
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
			  << "{x, -4, 4}, {y, -4, 4}]";
}

void Plane::writeMathematicaGraphics(ofstream &math_file, double start_time, double stop_stop)
{
	writeMathematicaGraphics(math_file);
}
