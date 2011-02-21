#include "Simulation.hh"
#include "MonteCarlo.hh"
#include "CreationEvent.hh"
#include "AnnihilationEvent.hh"
#include "ContinuityEvent.hh"

#include <iomanip>
//Simulation::Simulation()
//{
//}


//Simulation::Simulation(const Volume &_volume)
//	: volume(_volume)
//{
    //unsigned max_depth = 1;
    //unsigned fields_count = 1;
//}


Simulation::Simulation(const Geometry *_volume) 
	: volume(_volume), earliest_time(0), latest_time(0)
{
	//addGeometry(volume);
    //unsigned max_depth = 1;
    //unsigned fields_count = 1;
}

Simulation::Simulation(const Geometry *_volume, 
					   double _earliest_time, 
					   double _latest_time)
	: volume(_volume), earliest_time(_earliest_time), latest_time(_latest_time)
{
}

Simulation::~Simulation() {}

// compute paths
//void Simulation::run(const Particle & particle, double start_time, double stop_time)
//{
	// ...
//}

	
// generate the next pathlet from the event using fields
Pathlet* Simulation::advance(ParticleEvent *event)
// TODO void Simulation::advance(Path *event)
{
	// TODO seperate polynomial solutions from Runge-Kutta
	//Pathlet* pathlet = 0;
	polynomial p[3];
	//Pathlet* pathlet = path.stop_event;
	
	for (int axis = 0; axis < 3; axis++)
    {
		int degree = 0;
		vector<Field*>::iterator f;
		for (f = fields.begin(); f != fields.end(); f++)
		{
			//cout << "checking field degree" << endl;
			Field* field = *f;
			int d = field->get_degree(event, axis); // TODO support time varying fields
			if (d > degree)
				degree = d + 1;	// TODO clarify what we mean by degree of a field
		}
		
		//p[axis] = new polynomial(degree);
		if (degree == 2) // TODO check non negative 
		{
			double c[3] = {
				event->get_position(axis), // TODO move outside
				event->get_velocity(axis), // TODO move outside
				0
			};
			vector<Field*>::iterator f;
			for (f = fields.begin(); f != fields.end(); f++)
			{
				Field* field = *f;
				c[2] += 0.5 * field->get_acceleration(event, axis); // TODO support time varying fields
				//cout << "c[2]: " << c[2] << endl;
			}
			
			p[axis] = polynomial(2,c);
			//cout << "advance[" << degree << "]: " << p[axis] << endl;
			// ...
		}
		else if (degree < 2) // TODO check non negative 
		{
			double c[2];
			c[0] = event->get_position(axis); // TODO move outside
			c[1] = event->get_velocity(axis); // TODO move outside
			//if (c[1] == 0 )
			//	exit(0);
			//pathlet->curve[axis] = polynomial(2, c);
			p[axis] = polynomial(1,c);
			//cout << "advance[" << degree << "]: " << p[axis] << endl;
			// ...
		}
		else
		{
			// TODO support polynomial fields with direct integration
			// TODO support 
			cerr << "higher degrees not supported yet" << endl;
			return 0;
		}
		// TODO look for any other solution type
	}
	
	return new Pathlet(p);
}
	
// compute many paths
//void Simulation::run(double start_time, double stop_time, int count, Path** paths)
int Simulation::run(double start_time, double stop_time, int count)
{
	int final_count = 0;
	for (int i = 0; i < count; i++)
	{
		//paths[i] = run(start_time, stop_time);	
		if (run(start_time, stop_time))
			final_count++;			
	}
	return final_count;
}

// compute one path	
//Path* Simulation::run(double start_time, double stop_time)
bool Simulation::run(double start_time, double stop_time)
{
	Path* path = 0;
	Source* source = 0;	
	
	double sources_strength = 0;  // expected number of creation 
	                              // events in time (stop - start)
	vector<Source*>::iterator s;
	for (s = sources.begin(); s != sources.end(); s++)
	{
		// calculate source strengths for all times ...
		sources_strength += (*s)->get_strength(start_time, stop_time);
	}
	//double min_time = start_time;
	double random_strength = randomInterval();
	for (s = sources.begin(); s != sources.end(); s++)
	{
		// calculate source strengths for different times ...
		// ...
		// TODO pick a sources correctly
		source = *s; // TODO fix this hack (only work with one source)
	}
	
	//Particle* particle = source->get_new_particle(start_time, stop_time);
	CreationEvent* start_event = 0;
	if (not source) 
	{
		// TODO throw error ?
		cerr << "no sources found" << endl;
		return false;
	}

	start_event = source->create(start_time, stop_time);
	
	if (not start_event)
	{
		// TODO throw error ?
		cerr << "no creation event" << endl;
		return false;
	}

	ParticleEvent* event = start_event;
	path = new Path(event); // TODO add args
	cout << "setting path start time to " << event->get_time() << " sec" << endl;
	paths.push_back(path);
	
	// TODO Geometry* last_geormetry = source->getGeometry();
	Geometry* last_geormetry = source->geometry;
	
	// TODO while (start_time < t < stop_time)	
	int runs = 0;
	bool running = true;
	while (running)
	{
		runs++;
		cout << "runs " << runs << endl;
		if (runs > 100) 
			abort();
		Pathlet* pathlet = 0;
		Geometry* geometry = 0;
		InteractionEvent* best_interaction = 0;
		
		// ...
		
		// TODO? use solver: pathlet = solver->solve_path(prev_event);
		pathlet = advance(event);
		if (!pathlet)
		{
			// TODO throw error?
			cerr << "can't identify next event." << endl;
			return false;
		}

		//double max_time = pathlet->stop_time; // wrong! not set yet
		double min_time = event->get_time();
		double max_time = min_time + pathlet->get_relative_max_time();
		
		cout << "event->get_time() = " << event->get_time() << endl;
		cout << "pathlet->get_relative_max_time() = " << pathlet->get_relative_max_time() << endl;
		cout << "max_time = " << max_time << endl;
		cout << "stop_time = " << stop_time << endl;
		
		// check we are within the time interval
		event = 0;
		if (max_time >= stop_time)
		{
			// TODO EndSimulationEvent
			event = new ParticleEvent(stop_time);
			running = false;
			event->out_of_bounds = true;
			max_time = stop_time;
			cout << "found end time " << max_time << " sec." << endl;
		}
		
		// TODO handle decay events
		// TODO handle other loss events
		// ...
		
		// iterate through geometries and look for interaction events
		vector<Geometry*>::iterator g;
		for (g = geometries.begin(); g != geometries.end(); g++)
		{
			//cout << "found an interactable geometry" << endl;
			InteractionEvent* interaction = 0;
			Geometry* this_geometry = *g;
			//if (this_geometry == last_geormetry)
			//	interaction = this_geometry->selfinteract(pathlet, min_time, max_time);
			//else
				interaction = this_geometry->interact(pathlet, min_time, max_time);

			if (interaction)
			{
				double t = interaction->get_time(); // TODO make sure this is computed relatively
				cout << "Found interaction event at time " << t << " in window " << min_time << " to " << max_time << endl;
				if (t < max_time) // look for shortest time
				{
					cout << "found closest interaction" << endl;
					max_time = t;
					geometry = this_geometry;
					delete event;
					event = interaction;
					best_interaction = interaction;
				}
				else
					delete interaction;
			}
		}
		
		// TODO add volume to geometry list?
		// check bounding volume last 
		InteractionEvent* out_of_bounds = volume->interact(pathlet, min_time, max_time);
		if (out_of_bounds) 
		{
			cout << "out of bounds" << endl;
			delete event;
			event = out_of_bounds;
			event->out_of_bounds = true;
			max_time = event->get_time();
			running = false;
		}
		
		if (not event)
		{
			// no better intersection found? 
			cout << "continuity." << endl;
			event = new ContinuityEvent(max_time);
			// TODO compute new position and velocity in public function 
			for (int i = 0; i < 3; i++)
			{
				event->position[i] = pathlet->curve[i].evaluate(max_time - min_time);
				event->velocity[i] = pathlet->curve[i].derivative(max_time - min_time);
			}
			if (event->position[2] > 1.5)
			{
				cerr << "found odd continuity" << endl;
				abort();
			}
			running = true;
			delete best_interaction;
		}
		else if (event == best_interaction)
		{
			// TODO compute new position and velocity in public function 
			for (int i = 0; i < 3; i++)
			{
				event->position[i] = pathlet->curve[i].evaluate(max_time - min_time);
				event->velocity[i] = pathlet->curve[i].derivative(max_time - min_time);
			}
			//if (event->position[2] < 1.5 and event->position[2] > 0.5)
			if (event->position[2] > 0.0)
			{
				cerr << "found odd interaction" << endl;
				abort();
			}
			event->reflect_velocity(best_interaction->normal);
			running = true;
		}

		path->append(pathlet, event);
		int err_count = path->check(0.01);
		if (err_count)
		{
			// TODO throw error?
			cerr << "error appending new event to path" << endl;
			return false;
		}
	}
	return path;
}

//void Simulation::addVectorField(VectorField *field)
void Simulation::addField(Field *field)
{
    //octree->setup_vector_fields(&field);
	fields.push_back(field);
}

//void Simulation::addSurface(Surface * _surface)
//void Simulation::addSurface(STLSurface * stl_surface)
void Simulation::addGeometry(Geometry *geometry)
{
    //octree->walls = stl_surface->stl_file;
	geometries.push_back(geometry);
}

void Simulation::addSource(Source *source)
{
    //octree->walls = stl_surface->stl_file;
	sources.push_back(source);
}

void Simulation::writeMathematicaGraphics(ofstream &math_file)
{
	writeMathematicaGraphics(math_file, earliest_time, latest_time);
}

void Simulation::writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time)
{
	math_file << "Show[" << endl;

    vector<Source*>::iterator s;
	for	(s = sources.begin(); s != sources.end(); s++)
	{
        Geometry* geometry = (*s)->geometry;
		geometry->writeMathematicaGraphics(math_file, start_write_time, start_write_time);
		math_file << ", " << endl;
	}

    vector<Geometry*>::iterator g;
	for	(g = geometries.begin(); g != geometries.end(); g++)
	{
        Geometry* geometry = *g;
		geometry->writeMathematicaGraphics(math_file, start_write_time, start_write_time);
		math_file << ", " << endl;
	}

    vector<Path*>::iterator p;
	for	(p = paths.begin(); p != paths.end(); p++)
	{
        Path* path = *p;
		path->writeMathematicaGraphics(math_file, start_write_time, stop_write_time);
		math_file << ", " << endl;
	}
/*
*/
    math_file << "PlotRange -> {{-3, 3}, {-3,3}, {-3, 3}}" << endl;
	math_file << "]" << endl;
}
// TODO add range to Visulisation class?

#if 0
	const double frame_count = 1;
	int i = 0; //for (unsigned i = 0; i < neutron_count; i++)
    vector<Path*>::iterator p;
	for	(p = paths.begin(); p != paths.end(); p++)
	{
        cout << "ploting path " << i++ << "..."; 
        Path* path = *p;
		// start path segments
        double last_time = start_time;
        //if (path.visable())
        //{
		for (int frame = 0; frame < frame_count; frame++)
        {
    	    const double frame_start_time = (stop_time - start_time) * (double)frame / (double)frame_count + start_time;
    	    const double frame_stop_time = (stop_time - start_time) * ((double)frame + 1) / (double)frame_count + start_time;
            math_file << "," << endl 
                      << setiosflags(ios::fixed) 
                      << setprecision(8);
            math_file << "Line[{";
            // TODO write first point
            bool first_time = true;
    	    double segment = 0; 
    	    //for (double segment = 0; segment < segment_count; segment += 1.0)
			double segment_count = path->pathlets.size();
			vector<Pathlet*>::iterator s;
			for (s = path->pathlets.begin(); s != path->pathlets.end(); s++)
    	    {
				Pathlet* pathlet = *s;
    	        const double time = (stop_time - start_time)
                                  * (frame + segment / (segment_count - 1)) 
                                  / frame_count 
                                  + start_time;
				segment += 1.0;
                while (last_time < time or first_time)
                {
                    double p[3];
	    	    	if (first_time)
                    {
       		        	path->getPosition(time, p);
                        last_time = time;
                    }
                    else
                    {
            	        //math_file[frame] << "," << endl;
       		        	last_time = path->getPosition(last_time, time, p);
                    }
			
       		    	//math_file[frame] << "{" << p[0] << ", " << p[2] << ", " << p[1] << "}";
       		    	math_file << "{" << p[0] << ", " << p[2] << ", " << p[1] << "}";
                    first_time = false;
                }
	    	}
            //math_file[frame] << "}]";
            math_file << "}]";
        //} // if visable
        }
        cout << "done." << endl;
     }

    // end Show command Mathematica files
    //math_file << " }], PlotRange -> {{-.1, 4}, {0,1}, {-0.1, 3.1}}];" << endl;
    //math_file << " }], PlotRange -> {{4, 6}, {0,1}, {-0.5, 3.5}}];" << endl;
}
#endif
