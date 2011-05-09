#include "ParticleEvent.hh"

ParticleEvent::ParticleEvent(double t, const double x[3], const double v[3])
: Event(t)
{
    before = 0;
    after = 0;
    order = 1;
    for (unsigned k = 0; k < 3; k++)
    {
        position[k] = x[k];
        in[k] = v[k];
        out[k] = v[k];
    }
}

ParticleEvent::ParticleEvent(double t, Pathlet* path_in, Pathlet* path_out) 
: Event(t)
{
    before = path_in;
    after = path_out;
    order = 2;
    if (before)
    {
        before->getPosition(t, position);
        before->getVelocity(t, in);
    }
    if (order > 0)
        for (unsigned k = 0; k < 3; k++)
            out[k] = in[k];
}

void ParticleEvent::redirect_vertex(Vertex* vertex)
{
    double x[3]; // TODO
    double p[3];
    vertex->get_in(p);
    vertex->set_out(p);
    // ...
}

void ParticleEvent::writeMathematicaGraphics(ostream &math_file, double start_write_time, double stop_write_time)
{
    //if (get_time() >= start_write_time and get_time() < stop_write_time)
    {
        math_file << "Graphics3D[{Blue, Sphere [{"
            << get_position(0)<<","<<get_position(1)<<","<<get_position(2)<<"}, 0.1]}]";
    }
}

/*
	ParticleEvent::ParticleEvent(double t)
		: Event(t) 
	{
	}

	ParticleEvent::ParticleEvent(double t, double x[3]) 
		: Event(t) 
	{
		for (int i = 0; i < 3; i++)
			position[i] = x[i];
	}
*/	
	//ParticleEvent::~ParticleEvent() {};

	// XXX this copies the particle around for no reason
	//     most simulations have identical particles 
	//     so store somewhere else like the particle source
/*
	double ParticleEvent::get_velocity(int i)
	{
		return velocity[i];
	}

	void ParticleEvent::set_velocity(double v[3])
	{
		for (int i=0; i<3; i++)
			velocity[i] = v[i];
	}

	// TODO move to SurfaceMap?
	void ParticleEvent::reflect_velocity(const double normal[3])
	{ 
    	double vn = dot(velocity, normal);
    	for (unsigned i = 0; i < 3; i++)
    		velocity[i] -= 2*vn*normal[i];
	}
*/	
double ParticleEvent::get_position(int i)
{
    return position[i];
}

void ParticleEvent::set_position(double x[3])
{
    for (int i=0; i<3; i++)
        position[i] = x[i];
}
