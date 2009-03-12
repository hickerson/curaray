#include "Octree.hh"
#include <stdio.h>
#define abs(x) (x>=0?x:-x)

#define meters 1 
#define seconds 1 
#define x_epsilon 0.000001*meters
#define t_epsilon 0.00001*seconds

Octree::Octree(double x_min,double x_max,
           double y_min,double y_max,
           double z_min,double z_max,
	   unsigned n_fields,
	   unsigned max_depth)
	: _x_min(x_min), _x_max(x_max),
	  _y_min(y_min), _y_max(y_max),
	  _z_min(z_min), _z_max(z_max),
	  _n_fields(n_fields),
	  _max_depth(max_depth),
	  _root(new OctreeNode)
{
}

void
Octree::deepen_octree_at_point (const double *xyz)
{
    OctreeIterator iter(this);
    while (iter.depth < _max_depth)
    {
	if (iter.node->is_leaf)
	    iter.split();
	iter.descend(xyz[0] < ((iter.x_min+iter.x_max) / 2) ? 0 : 1,
	             xyz[1] < ((iter.y_min+iter.y_max) / 2) ? 0 : 1,
	             xyz[2] < ((iter.z_min+iter.z_max) / 2) ? 0 : 1);
    }
}

void
Octree::setup_vector_fields_recursive (OctreeIterator *iter)
{
    double position[3];
    double range = iter->get_range();
    iter->get_center(position);
    if (iter->node->is_leaf)
    {
	bool must_subdivide = false;
	if (iter->depth >= _max_depth)
	    must_subdivide = false;
	else
	{
	    for (unsigned f = 0; f < _n_fields; f++)
	    {
		if (_fields[f]->should_subdivide(position,range))
		{
		    must_subdivide = true;
		    break;
		}
	    }
	}

	if (must_subdivide)
	{
	    iter->split();
	}
	else
	{
	    if (iter->node->leaf.fields == 0)
	    	iter->node->leaf.fields = new double[_n_fields*3];
	    for (unsigned f = 0; f < _n_fields; f++)
		_fields[f]->compute_field(position, iter->node->leaf.fields + 3*f);
	}
    }
    

    if (!iter->node->is_leaf)
    {
	for (unsigned x = 0; x < 2; x++)
	    for (unsigned y = 0; y < 2; y++)
		for (unsigned z = 0; z < 2; z++)
		{
		    OctreeIterator it(*iter);
		    it.descend(x,y,z);
		    setup_vector_fields_recursive(&it);
		}
    }
}


void
Octree::setup_vector_fields(VectorField **fields)
{
    OctreeIterator iter(this);
    _fields = new VectorField *[_n_fields];
    for (unsigned i = 0; i < _n_fields; i++)
	_fields[i] = fields[i];
    setup_vector_fields_recursive(&iter);
}

void
Octree::determine_interior_recursive(SolidObject *object,
	                             OctreeIterator *iter)
{
    if (iter->node->is_leaf)
    {
	double position[3];
	iter->get_center(position);
	iter->node->leaf.is_interior = object->is_interior(position);
    }
    else
    {
	for (unsigned x = 0; x < 2; x++)
	    for (unsigned y = 0; y < 2; y++)
		for (unsigned z = 0; z < 2; z++)
		{
		    OctreeIterator it(*iter);
		    it.descend(x,y,z);
		    determine_interior_recursive(object, &it);
		}
    }
}

void Octree::determine_interior(SolidObject *object)
{
    OctreeIterator iter(this);
    determine_interior_recursive(object, &iter);
}

void Octree::step_particle(Particle *particle)
{
    double field_strength = 1; // XXX total hack!
    step_particle(particle, &field_strength);
}

void Octree::step_particle(Particle *particle,
                           ParticlePath *path)
{
    double field_strength = 1; // XXX total hack
    step_particle(particle, &field_strength);
    // TODO copy path info from particle
}

void Octree::step_particle(Particle *particle, ParticlePathSample & sample)
{
    double fineness = 1;
    double delta_t;
    double force[3] = {0,0,0};
    double accel[3];
    OctreeIterator iter(this);

    // Find cell that contains particle
    iter.find(particle->position);

    // Compute force.
    for (unsigned f = 0; f < _n_fields; f++)
    {
	double subforce[3];
	_fields[f]->get_force(particle, iter.node->leaf.fields + (3*f), subforce);
	for (unsigned i = 0; i < 3; i++)
	    force[i] += subforce[i];
    }

    // Compute acceleration.
    for (unsigned i = 0; i < 3; i++)
	accel[i] = force[i] / particle->mass;
    double acceleration_mag = sqrt (accel[0] * accel[0]
                                  + accel[1] * accel[1]
                                  + accel[2] * accel[2]);

    // Determine timestep
    double velo_delta_t = fineness
	                * iter.get_range()
	                / particle->get_speed();
    double force_delta_t = particle->get_speed()
	                 / acceleration_mag;
    if (isnan (velo_delta_t))
	if (isnan (force_delta_t)) {
	    delta_t = 1;		// XXX
	    fprintf(stderr, "undefined force delta t\n");
	}
        else
	    delta_t = force_delta_t;
    else
	if (isnan (force_delta_t))
	    delta_t = velo_delta_t;
        else if (force_delta_t < velo_delta_t)
	    delta_t = force_delta_t;
	else
	    delta_t = velo_delta_t;

    // XXX: do we need a maximum delta_t????

    // Check intersection with wall
    double t_min = delta_t;
    double t_min_normal[3];
    //for (each facet in cell)
    for (unsigned i = 0; i < walls->count; i++)
    {
#if 1
	float *Vf0 = walls->facet[i].v[0];
	float *Vf1 = walls->facet[i].v[1];
	float *Vf2 = walls->facet[i].v[2];
	double V0[3] = {Vf0[0], Vf0[1], Vf0[2]};
	double V1[3] = {Vf1[0], Vf1[1], Vf1[2]};
	double V2[3] = {Vf2[0], Vf2[1], Vf2[2]};
		    
	#if 1
	//float *normalf = walls->facet[i].normal;
	//double normal[3] = {normalf[0], normalf[1], normalf[2]};
	//float *normal = walls->facet[i].normal;
	double normal[3] = 
	{-(V1[2]*V2[1]) + V0[2]*(-V1[1] + V2[1]) + V0[1]*(V1[2] - V2[2]) + V1[1]*V2[2], 
	   V0[2]*(V1[0] - V2[0]) + V1[2]*V2[0] - V1[0]*V2[2] + V0[0]*(-V1[2] + V2[2]), 
	 -(V1[1]*V2[0]) + V0[1]*(-V1[0] + V2[0]) + V0[0]*(V1[1] - V2[1]) + V1[0]*V2[1]};
	double normal_norm = sqrt(dot(normal,normal));
	normal[0] /= normal_norm;
	normal[1] /= normal_norm;
	normal[2] /= normal_norm;
        #else
	//TODO compute the normals first in an outside function then run off cached
	double normal[3]; 
	if (facet is new)
	{
	    normal[0] = -(V1[2]*V2[1]) + V0[2]*(-V1[1] + V2[1]) + V0[1]*(V1[2] - V2[2]) + V1[1]*V2[2];
	    normal[1] =   V0[2]*(V1[0] - V2[0]) + V1[2]*V2[0] - V1[0]*V2[2] + V0[0]*(-V1[2] + V2[2]);
	    normal[2] = -(V1[1]*V2[0]) + V0[1]*(-V1[0] + V2[0]) + V0[0]*(V1[1] - V2[1]) + V1[0]*V2[1];
	    double normal_norm = sqrt(dot(normal,normal));
	    normal[0] /= normal_norm;
	    normal[1] /= normal_norm;
	    normal[2] /= normal_norm;
	    for (int j = 0; j < 3; j++)
                walls->facet[i].normal[j] = normal[j];
	}
	else
	    for (int j = 0; j < 3; j++)
                normal[j] = walls->facet[i].normal[j];
        #endif

	float absnormal[3] = {abs(normal[0]), abs(normal[1]), abs(normal[2])};
	unsigned j0 = 0;
	if (absnormal[1] > absnormal[0])
	    if (absnormal[2] > absnormal[1])
	        j0 = 2;
	    else
	        j0 = 1;
	unsigned j1 = (j0 + 1) % 3;
	unsigned j2 = (j0 + 2) % 3;

	// Sovle 1/2*a*t^2 + b*t + c using quadratic eqn.
	double a = dot(accel, normal);
	double b = dot(particle->velocity, normal);
	double c = dot(particle->position, normal) 
	         -(dot(V0, normal) + dot(V1, normal) + dot(V2, normal))/3;
	double discriminate = b*b - 2*a*c;
	if (discriminate >= 0)
	{ // test discriminate for any real solutions
	    double t_values[2];
	    int root_count;
	    //if (abs(a) > 2 * epsilon / (t_min * t_min))
	    if (a != 0)
	    { // found two real solutions
		root_count = 2;
	        double s = sqrt(discriminate);
	        t_values[0] = (-b - s) / a;
	        t_values[1] = (-b + s) / a;
	    }
	    else
	    { // found one real linear solution
		root_count = 1;
		t_values[0] = -c/b;
	    }
	    for (unsigned which_t = 0; which_t < root_count; which_t++)
	    {
		double t = t_values[which_t]; // distance to facet
		if (t < t_min && t > t_epsilon)
		{
		    // from "Graphic Gems" (pg. 393)
		    double u[3], v[3];
		    {
			double velocity = t * accel[j1];
			double position = t * (0.5 * velocity + particle->velocity[j1]);
			position += particle->position[j1];
			u[0] = position - V0[j1];
			u[1] = V1[j1] - V0[j1];
			u[2] = V2[j1] - V0[j1];
			velocity = t * accel[j2];
			position = t * (0.5 * velocity + particle->velocity[j2]);
			position += particle->position[j2];
			v[0] = position - V0[j2];
			v[1] = V1[j2] - V0[j2];
			v[2] = V2[j2] - V0[j2];
		    }

		    double alpha, beta;
		    if (u[1] == 0)
		    {
			beta = u[0]/u[2];
			if (-x_epsilon < beta and beta < 1 + x_epsilon)
			    alpha = (v[0] - beta*v[2]) / v[1];
		    }
		    else
		    {
			beta = (v[0]*u[1] - u[0]*v[1]) / (v[2]*u[1] - u[2]*v[1]);
			if (-x_epsilon < beta and beta < 1 + x_epsilon)
			    alpha = (u[0] - beta*u[2]) / u[1];
		    }
		    //if (alpha >= 0 and beta >= 0 and (alpha + beta) <= 1)
		    if (alpha > -x_epsilon and beta > -x_epsilon and (alpha + beta) < 1 + x_epsilon)
		    { //if (intersects inside barrycentric coords)
			t_min = t; // the best time
			//t_min_normal = normal; // stored normal = curr normal
			for (unsigned j = 0; j < 3; j++)
			    t_min_normal[j] = normal[j];
		    }
		}
	    }
	}
    }
#else
    // check_intersection();
#endif 

    particle->advance(accel, t_min); // Advance particle.
    if (t_min < delta_t) 
    {
        // found intersection
    	particle->reflect(t_min_normal);
	// TODO get rid of particle reflection - just do sample reflection
	sample.reflect(t_min_normal);
    }
    else
    	sample.noreflect();
}

void Octree::step_particle(Particle *particle,
			   const double *field_strengths, // XXX what is this crap?
			   double fineness) // XXX what is this crap?
{
    double delta_t;
    double force[3] = {0,0,0};
    double accel[3];
    OctreeIterator iter(this);

    // Find cell that contains particle
    iter.find(particle->position);

    // Compute force.
    for (unsigned f = 0; f < _n_fields; f++)
    {
	double subforce[3];
	_fields[f]->get_force(particle, iter.node->leaf.fields + (3*f), subforce);
	for (unsigned i = 0; i < 3; i++)
	    force[i] += subforce[i];
    }

    // Compute acceleration.
    for (unsigned i = 0; i < 3; i++)
	accel[i] = force[i] / particle->mass;
    double acceleration_mag = sqrt (accel[0] * accel[0]
                                  + accel[1] * accel[1]
                                  + accel[2] * accel[2]);

    // Determine timestep
    double velo_delta_t = fineness
	                * iter.get_range()
	                / particle->get_speed();
    double force_delta_t = particle->get_speed()
	                 / acceleration_mag;
    if (isnan (velo_delta_t))
	if (isnan (force_delta_t)) {
	    delta_t = 1;		// XXX
	    fprintf(stderr, "undefined force delta t\n");
	}
        else
	    delta_t = force_delta_t;
    else
	if (isnan (force_delta_t))
	    delta_t = velo_delta_t;
        else if (force_delta_t < velo_delta_t)
	    delta_t = force_delta_t;
	else
	    delta_t = velo_delta_t;

    // XXX: do we need a maximum delta_t????

    // Check intersection with wall
    double t_min = delta_t;
    double t_min_normal[3];
    //for (each facet in cell)
    for (unsigned i = 0; i < walls->count; i++)
    {
#if 1
	float *Vf0 = walls->facet[i].v[0];
	float *Vf1 = walls->facet[i].v[1];
	float *Vf2 = walls->facet[i].v[2];
	double V0[3] = {Vf0[0], Vf0[1], Vf0[2]};
	double V1[3] = {Vf1[0], Vf1[1], Vf1[2]};
	double V2[3] = {Vf2[0], Vf2[1], Vf2[2]};
		    
	#if 1
	//float *normalf = walls->facet[i].normal;
	//double normal[3] = {normalf[0], normalf[1], normalf[2]};
	//float *normal = walls->facet[i].normal;
	double normal[3] = 
	{-(V1[2]*V2[1]) + V0[2]*(-V1[1] + V2[1]) + V0[1]*(V1[2] - V2[2]) + V1[1]*V2[2], 
	   V0[2]*(V1[0] - V2[0]) + V1[2]*V2[0] - V1[0]*V2[2] + V0[0]*(-V1[2] + V2[2]), 
	 -(V1[1]*V2[0]) + V0[1]*(-V1[0] + V2[0]) + V0[0]*(V1[1] - V2[1]) + V1[0]*V2[1]};
	double normal_norm = sqrt(dot(normal,normal));
	normal[0] /= normal_norm;
	normal[1] /= normal_norm;
	normal[2] /= normal_norm;
        #else
	//TODO compute the normals first in an outside function then run off cached
	double normal[3]; 
	if (facet is new)
	{
	    normal[0] = -(V1[2]*V2[1]) + V0[2]*(-V1[1] + V2[1]) + V0[1]*(V1[2] - V2[2]) + V1[1]*V2[2];
	    normal[1] =   V0[2]*(V1[0] - V2[0]) + V1[2]*V2[0] - V1[0]*V2[2] + V0[0]*(-V1[2] + V2[2]);
	    normal[2] = -(V1[1]*V2[0]) + V0[1]*(-V1[0] + V2[0]) + V0[0]*(V1[1] - V2[1]) + V1[0]*V2[1];
	    double normal_norm = sqrt(dot(normal,normal));
	    normal[0] /= normal_norm;
	    normal[1] /= normal_norm;
	    normal[2] /= normal_norm;
	    for (int j = 0; j < 3; j++)
                walls->facet[i].normal[j] = normal[j];
	}
	else
	    for (int j = 0; j < 3; j++)
                normal[j] = walls->facet[i].normal[j];
        #endif

	float absnormal[3] = {abs(normal[0]), abs(normal[1]), abs(normal[2])};
	unsigned j0 = 0;
	if (absnormal[1] > absnormal[0])
	    if (absnormal[2] > absnormal[1])
	        j0 = 2;
	    else
	        j0 = 1;
	unsigned j1 = (j0 + 1) % 3;
	unsigned j2 = (j0 + 2) % 3;

	// Sovle 1/2*a*t^2 + b*t + c using quadratic eqn.
	double a = dot(accel, normal);
	double b = dot(particle->velocity, normal);
	double c = dot(particle->position, normal) 
	         -(dot(V0, normal) + dot(V1, normal) + dot(V2, normal))/3;
	double discriminate = b*b - 2*a*c;
	if (discriminate >= 0)
	{ // test discriminate for any real solutions
	    double t_values[2];
	    int root_count;
	    //if (abs(a) > 2 * epsilon / (t_min * t_min))
	    if (a != 0)
	    { // found two real solutions
		root_count = 2;
	        double s = sqrt(discriminate);
	        t_values[0] = (-b - s) / a;
	        t_values[1] = (-b + s) / a;
	    }
	    else
	    { // found one real linear solution
		root_count = 1;
		t_values[0] = -c/b;
	    }
	    for (unsigned which_t = 0; which_t < root_count; which_t++)
	    {
		double t = t_values[which_t]; // distance to facet
		if (t < t_min && t > t_epsilon)
		{
		    // from "Graphic Gems" (pg. 393)
		    double u[3], v[3];
		    {
			double velocity = t * accel[j1];
			double position = t * (0.5 * velocity + particle->velocity[j1]);
			position += particle->position[j1];
			u[0] = position - V0[j1];
			u[1] = V1[j1] - V0[j1];
			u[2] = V2[j1] - V0[j1];
			velocity = t * accel[j2];
			position = t * (0.5 * velocity + particle->velocity[j2]);
			position += particle->position[j2];
			v[0] = position - V0[j2];
			v[1] = V1[j2] - V0[j2];
			v[2] = V2[j2] - V0[j2];
		    }

		    double alpha, beta;
		    if (u[1] == 0)
		    {
			beta = u[0]/u[2];
			if (-x_epsilon < beta and beta < 1 + x_epsilon)
			    alpha = (v[0] - beta*v[2]) / v[1];
		    }
		    else
		    {
			beta = (v[0]*u[1] - u[0]*v[1]) / (v[2]*u[1] - u[2]*v[1]);
			if (-x_epsilon < beta and beta < 1 + x_epsilon)
			    alpha = (u[0] - beta*u[2]) / u[1];
		    }
		    //if (alpha >= 0 and beta >= 0 and (alpha + beta) <= 1)
		    if (alpha > -x_epsilon and beta > -x_epsilon and (alpha + beta) < 1 + x_epsilon)
		    { //if (intersects inside barrycentric coords)
			t_min = t; // the best time
			//t_min_normal = normal; // stored normal = curr normal
			for (unsigned j = 0; j < 3; j++)
			    t_min_normal[j] = normal[j];
		    }
		}
	    }
	}
    }
#else
    // check_intersection();
#endif 

    particle->advance(accel, t_min); // Advance particle.
    if (t_min < delta_t) // found intersection
    	particle->reflect(t_min_normal);
}

#if 0
void Octree::check_intersection( ... )
{
    double t_min = delta_t;
    double t_min_normal[3];
    //for (each facet in cell)
    for (unsigned i = 0; i < walls->count; i++)
    {
	float *Vf0 = walls->facet[i].v[0];
	float *Vf1 = walls->facet[i].v[1];
	float *Vf2 = walls->facet[i].v[2];
	double V0[3] = {Vf0[0], Vf0[1], Vf0[2]};
	double V1[3] = {Vf1[0], Vf1[1], Vf1[2]};
	double V2[3] = {Vf2[0], Vf2[1], Vf2[2]};
		    
	#if 1
	//float *normalf = walls->facet[i].normal;
	//double normal[3] = {normalf[0], normalf[1], normalf[2]};
	//float *normal = walls->facet[i].normal;
	double normal[3] = 
	{-(V1[2]*V2[1]) + V0[2]*(-V1[1] + V2[1]) + V0[1]*(V1[2] - V2[2]) + V1[1]*V2[2], 
	   V0[2]*(V1[0] - V2[0]) + V1[2]*V2[0] - V1[0]*V2[2] + V0[0]*(-V1[2] + V2[2]), 
	 -(V1[1]*V2[0]) + V0[1]*(-V1[0] + V2[0]) + V0[0]*(V1[1] - V2[1]) + V1[0]*V2[1]};
	double normal_norm = sqrt(dot(normal,normal));
	normal[0] /= normal_norm;
	normal[1] /= normal_norm;
	normal[2] /= normal_norm;
        #else // the real way to do this is to compute the normals first in an outside function then run off cached
	double normal[3]; 
	if (facet is new)
	{
	    normal[0] = -(V1[2]*V2[1]) + V0[2]*(-V1[1] + V2[1]) + V0[1]*(V1[2] - V2[2]) + V1[1]*V2[2];
	    normal[1] =   V0[2]*(V1[0] - V2[0]) + V1[2]*V2[0] - V1[0]*V2[2] + V0[0]*(-V1[2] + V2[2]);
	    normal[2] = -(V1[1]*V2[0]) + V0[1]*(-V1[0] + V2[0]) + V0[0]*(V1[1] - V2[1]) + V1[0]*V2[1];
	    double normal_norm = sqrt(dot(normal,normal));
	    normal[0] /= normal_norm;
	    normal[1] /= normal_norm;
	    normal[2] /= normal_norm;
	    for (int j = 0; j < 3; j++)
                walls->facet[i].normal[j] = normal[j];
	}
	else
	    for (int j = 0; j < 3; j++)
                normal[j] = walls->facet[i].normal[j];
        #endif

	float absnormal[3] = {abs(normal[0]), abs(normal[1]), abs(normal[2])};
	unsigned j0 = 0;
	if (absnormal[1] > absnormal[0])
	    if (absnormal[2] > absnormal[1])
	        j0 = 2;
	    else
	        j0 = 1;
	unsigned j1 = (j0 + 1) % 3;
	unsigned j2 = (j0 + 2) % 3;

	// Sovle 1/2*a*t^2 + b*t + c using quadratic eqn.
	double a = dot(accel, normal);
	double b = dot(particle->velocity, normal);
	double c = dot(particle->position, normal) 
	         -(dot(V0, normal) + dot(V1, normal) + dot(V2, normal))/3;
	double discriminate = b*b - 2*a*c;
	if (discriminate >= 0)
	{ // test discriminate for any real solutions
	    double t_values[2];
	    int root_count;
	    //if (abs(a) > 2 * epsilon / (t_min * t_min))
	    if (a != 0)
	    { // found two real solutions
		root_count = 2;
	        double s = sqrt(discriminate);
	        t_values[0] = (-b - s) / a;
	        t_values[1] = (-b + s) / a;
	    }
	    else
	    { // found one real linear solution
		root_count = 1;
		t_values[0] = -c/b;
	    }
	    for (unsigned which_t = 0; which_t < root_count; which_t++)
	    {
		double t = t_values[which_t]; // distance to facet
		if (t < t_min && t > t_epsilon)
		{
		    // from "Graphic Gems" (pg. 393)
		    double u[3], v[3];
		    {
			double velocity = t * accel[j1];
			double position = t * (0.5 * velocity + particle->velocity[j1]);
			position += particle->position[j1];
			u[0] = position - V0[j1];
			u[1] = V1[j1] - V0[j1];
			u[2] = V2[j1] - V0[j1];
			velocity = t * accel[j2];
			position = t * (0.5 * velocity + particle->velocity[j2]);
			position += particle->position[j2];
			v[0] = position - V0[j2];
			v[1] = V1[j2] - V0[j2];
			v[2] = V2[j2] - V0[j2];
		    }

		    double alpha, beta;
		    if (u[1] == 0)
		    {
			beta = u[0]/u[2];
			if (-x_epsilon < beta and beta < 1 + x_epsilon)
			    alpha = (v[0] - beta*v[2]) / v[1];
		    }
		    else
		    {
			beta = (v[0]*u[1] - u[0]*v[1]) / (v[2]*u[1] - u[2]*v[1]);
			if (-x_epsilon < beta and beta < 1 + x_epsilon)
			    alpha = (u[0] - beta*u[2]) / u[1];
		    }
		    //if (alpha >= 0 and beta >= 0 and (alpha + beta) <= 1)
		    if (alpha > -x_epsilon and beta > -x_epsilon and (alpha + beta) < 1 + x_epsilon)
		    { //if (intersects inside barrycentric coords)
			t_min = t; // the best time
			//t_min_normal = normal; // stored normal = curr normal
			for (unsigned j = 0; j < 3; j++)
			    t_min_normal[j] = normal[j];
		    }
		}
	    }
	}
    }
}
#endif 

unsigned Octree::count_leaf_nodes_recursive(const OctreeNode *node) const
{
    if (node->is_leaf)
	return 1;
    else
    {
	unsigned rv = 0;
	for (unsigned x = 0; x < 2; x++)
	    for (unsigned y = 0; y < 2; y++)
		for (unsigned z = 0; z < 2; z++)
		    rv += count_leaf_nodes_recursive(node->nonleaf.children[x][y][z]);
	return rv;
    }
}

unsigned Octree::count_leaf_nodes() const
{
    return count_leaf_nodes_recursive(_root);
}

bool Octree::in_bounds(const double * position) const
{
    return 
	(position[0] > _x_min) &&
	(position[0] < _x_max) &&
	(position[1] > _y_min) &&
	(position[1] < _y_max) &&
	(position[2] > _z_min) &&
	(position[2] < _z_max); 
}
