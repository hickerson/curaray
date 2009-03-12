#include "UCNEvent.hh"


#if 0
{
	// make all the neutrons
	// TODO we really only need one neutron made each time
	Particle particle[neutron_count];
	for (unsigned i = 0; i < neutron_count; i++)
	{	
		double velocity[3];
		double position[3] = {0,0,0};
		//randomSphereVector(velocity, randomPowerLaw(7,2));
		//randomSphereVector(velocity, randomRange(6,7));
		randomSphereVector(velocity, ucn_speed);
		randomDiskVector(position, 0.0399);
		Particle neutron(position, velocity, 0, 1.0);
		particle[i] = neutron;
	}
}
#endif


// compute paths
void UCNEvent::run(const Particle & particle, double start_time, double stop_time)
{
#if 0
	// TODO path.show(start_time, stop_time);
        double last_time = start_time;
    	while (last_time < stop_time)
        {
            // copy over particle information to sample
            ParticlePathSample sample;
            sample.order = 3;
            for (int k = 0; k < 3; k++)
            {
                sample.coefficient[0][k] = particle.position[k];
                sample.coefficient[1][k] = particle.velocity[k];
                sample.coefficient[2][k] = gravity[k] / 2;
            }
            sample.start_time = last_time;
           
            // step forward
    	    // TODO octree.step_particle(&particle[i], &ucn_path[i], t_start, t_stop);
    	    octree.step_particle(&particle[i]);
            // XXX deal with this condition!!!!
            // XXX This is a know bug where the particle tunnels through walls
            if (not octree.in_bounds(particle.position))
            {
       	        cerr << "hide {" << particle.position[0] << ", " 
                                 << particle.position[2] << ", " 
                                 << particle.position[1] << "}" << endl;
                path.hide();
            }

            // look for the end of the path sample
            const double next_time = particle[i].time;
            sample.stop_time = next_time;
            last_time = next_time;
	    path.add(sample);
	}
        if (path.check(0.00000001) > 0)
        {
            cerr << "Detected errors in path." << endl
                 << "aborting..." << endl;
            exit(1);
        }
	#endif
}
