#include "Simulation.hh"
#include "MonteCarlo.hh"
//#include "CreationEvent.hh"
#include "AnnihilationEvent.hh"
//#include "ContinuityEvent.hh"

#include <iomanip>
Simulation::Simulation(const Geometry *_volume) 
: 	earliest_time(0), 
	latest_time(0),
	volume(_volume) 
{
}

Simulation::Simulation(const Geometry *_volume, 
					   double _earliest_time, 
					   double _latest_time)
: 	earliest_time(_earliest_time), 
	latest_time(_latest_time),
	volume(_volume)
{
}

int Simulation::get_field_degree(int axis)
// TODO int Simulation::get_field_degree(Vertex* vertex, int axis)
{
    int degree = 1;  // basic momentum

    vector<Field*>::iterator f;
    for (f = fields.begin(); f != fields.end(); f++)
    {
        Field* field = *f;
        int _degree = field->get_degree(axis); // TODO support time varying fields
        // TODO int _degree = field->get_degree(vertex, axis);
        if (degree < _degree)
            degree = _degree;	
    }

    return degree;
}

double Simulation::get_field_acceleration(Vertex* vertex, int axis)
{
    double c = 0;

    vector<Field*>::iterator f;
    for (f = fields.begin(); f != fields.end(); f++)
    {
        Field* field = *f; 
        c += 0.5 * field->get_acceleration(vertex, axis); 
    }

    return c;
}

// generate the next Pathlet from the event using fields
Pathlet* Simulation::solve_pathlet(Vertex *start)
{
    // TODO separate polynomial solutions from Runge-Kutta
    polynomial p[3]; // TODO make dimensionality a parameter
    for (int axis = 0; axis < 3; axis++) // TODO make dimensionality a parameter
    {
        int degree = get_field_degree(axis);

        if (degree == 2)
        {
            double c[3] = {
                start->get_position(axis), // TODO move outside
                start->get_out(axis), // TODO move outside
                get_field_acceleration(start, axis)
            };
            p[axis] = polynomial(2,c);
        }
        else if (degree == 1) // TODO check non-negative 
        {
            double c[2] = {
                start->get_position(axis), // TODO move outside
                start->get_out(axis)  // TODO move outside
            };
            if (c[1] == 0) exit(0); // not sure what the point of this is ...
            p[axis] = polynomial(1,c);
        }
        else
        { 	// TODO support polynomial fields with direct integration...
            cerr << "A polynomial path degree of " << degree << " not supported." << endl;
            abort();
        }
        // TODO look for any other solution type...
    }

    Pathlet* pathlet = new Pathlet(p, start, 0);
    assert(pathlet);
    return pathlet;
}

// compute many paths
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

Vertex* Simulation::get_first_vertex(double start_time, double stop_time)
{
    double sources_strength = 0;  // expected number of creation 
    vector<Source*>::iterator s;
    for (s = sources.begin(); s != sources.end(); s++)
    {
        // calculate source strengths for all times ...
        sources_strength += (*s)->get_strength(start_time, stop_time);
    }

    Source* source = 0;	
    double random_strength = randomInterval();
    for (s = sources.begin(); s != sources.end(); s++)
    {
        // TODO calculate source strengths for different times ...
        // TODO and pick a sources correctly.
        source = *s; // TODO fix this hack (only work with one source)
    }

    if (not source) 
    {
        cerr << "no sources found" << endl;
        abort(); // TODO throw error ?
    }

    Vertex* vertex = source->create_vertex(start_time, stop_time);
    if (not vertex)
    {
        cerr << "No vertex created by source." << endl;
        abort(); // TODO throw error ?
    }
    
    return vertex;
}

// compute one path	
bool Simulation::run(double start_time, double stop_time)
{
    cout << "Passed to run: { start_time = " << start_time << ", stop_time = " << stop_time << "}" << endl;

    Vertex* vertex = get_first_vertex(start_time, stop_time);
    Path* path = new Path(vertex); // TODO add args
    cout << "setting path start time to " << vertex->get_time() << " sec" << endl;
    paths.push_back(path);

    //Geometry* last_geometry = source->geometry;
    const Geometry* last_geometry = ((CreationEvent*)vertex->get_event())->geometry;

    // TODO while (start_time < t < stop_time)	
    int runs = 0;
    bool running = true;
    while (running)
    {
        runs++;
        cout << "runs " << runs << endl;
        if (runs >= 100)
        {    
            path->writeJSON(cerr, start_time, stop_time);
            assert(false);
        }
        Pathlet* pathlet = 0;
        Geometry* best_geometry = 0;
        ParticleEvent* best_event = 0;
        InteractionEvent* best_interaction = 0;

        pathlet = solve_pathlet(vertex); // TODO use solver
        if (!pathlet)
        {
            cerr << "No pathlet solved. Can't identify next event." << endl;
            abort();
        }
        double stable_time = pathlet->get_stable_time();  // yes! This is the way to do it!
        double min_time = vertex->get_time();
        double max_time = min_time + stable_time;  // yes! This is the way to do it!
        if (max_time > stop_time)
            max_time = stop_time;

        cout << "stable_time = " << stable_time << endl;
        cout << "min_time = " << min_time << endl;
        cout << "max_time = " << max_time << endl;
        cout << "stop_time = " << stop_time << endl;

            /*
        if (max_time > stop_time)
        //{
            max_time = stop_time;
            // TODO EndSimulationEvent
            //vertex->event->out_of_bounds = true;
            cout << "Found end time " << max_time << " sec." << endl;
            running = false;
            break;
        }
        */

        // TODO handle decay events by setting maximum stop time early		
        // TODO handle other loss events
        // ...

        // iterate through geometries and look for interaction events
        vector<Geometry*>::iterator g;
        for (g = geometries.begin(); g != geometries.end(); g++)
        {
            //cout << "found an interactable geometry" << endl;
            InteractionEvent* interaction = 0;
            Geometry* this_geometry = *g;
            if (this_geometry == last_geometry)
                interaction = this_geometry->selfinteract(pathlet, min_time, max_time);
            else
                interaction = this_geometry->interact(pathlet, min_time, max_time);

            if (interaction)
            {
                double t = interaction->time; // TODO make sure this is computed relatively
                cout << "Found interaction event at time " << t;
                cout << " in window " << min_time;
                cout << " to " << max_time << endl;
                if (t < max_time) // look for shortest time
                {
                    cout << "found closest interaction" << endl;
                    max_time = t;
                    best_interaction = interaction;
                    best_geometry = this_geometry;
                }
                else
                    delete interaction;
            }
        }

        // TODO add volume to geometry list? Last?
        assert(volume); // TODO change to "volume" to "boundary"
        InteractionEvent* out_of_bounds = volume->interact(pathlet, min_time, max_time); // TODO make out of bounds object
        if (out_of_bounds) 
        {   // terminate path since we didn't hit an object
            cout << "Path is out of bounds." << endl;
            best_event = out_of_bounds;
            //out_of_bounds->out_of_bounds = true; // TODO add to constructor
            max_time = out_of_bounds->time;
            running = false;
        }
        else
        {
            if (best_interaction)
            {
                cout << "Found best interaction." << endl;
                best_event = best_interaction;
                last_geometry = best_geometry;
            }
            else
            { 	
                if (max_time == stop_time)
                {
                    running = false;
                    best_event = new AnnihilationEvent(max_time);
                }
                else
                {
                    cout << "No interaction found. Creating continuity event at time " << max_time << " sec." << endl;
                    best_event = new ContinuityEvent(max_time);
                }
            }
        }

        // make new vertex and increment
        vertex = new Vertex(best_event, pathlet);
        best_event->set_position(pathlet);
        best_event->redirect_vertex(vertex);
        path->append(pathlet, vertex);

        int err_count = path->check(0.01);
        if (err_count)
        {
            cerr << "Error appending new event to path." << endl;
            path->writeJSON(cout, start_time, stop_time);
            abort();
        }
    } // end main running loop

    int err_count = path->check(0.01);
    if (err_count)
    {
        cerr << "There were errors with the path." << endl;
        //path->writeMathematicaGraphics(cout, start_time, stop_time);
        //path->writeJSON(cout, start_time, stop_time);
        abort();
    }

    return path;
}

void Simulation::addField(Field *field)
{
    fields.push_back(field);
}

void Simulation::addGeometry(Geometry *geometry)
{
    geometries.push_back(geometry);
}

void Simulation::addSource(Source *source)
{
    sources.push_back(source);
}

void Simulation::writeMathematicaGraphics(ostream &out)
{
    writeMathematicaGraphics(out, earliest_time, latest_time);
}

void Simulation::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    out << "Show[" << endl;

    vector<Source*>::iterator s;
    for	(s = sources.begin(); s != sources.end(); s++)
    {
        Geometry* geometry = (*s)->geometry;
        geometry->writeMathematicaGraphics(out, start_write_time, start_write_time);
        out << ", " << endl;
    }

    vector<Geometry*>::iterator g;
    for	(g = geometries.begin(); g != geometries.end(); g++)
    {
        Geometry* geometry = *g;
        geometry->writeMathematicaGraphics(out, start_write_time, start_write_time);
        out << ", " << endl;
    }

    vector<Path*>::iterator p;
    for	(p = paths.begin(); p != paths.end(); p++)
    {
        Path* path = *p;
        path->writeMathematicaGraphics(out, start_write_time, stop_write_time);
        //out << ", " << endl;
    }
    out << "PlotRange -> {{-6, 6}, {-6,6}, {-6, 6}}" << endl;
    out << "]" << endl;
}
// TODO add range to Visualization class?

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
