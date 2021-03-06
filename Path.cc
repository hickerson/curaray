#include "Path.hh"
#include "Vertex.hh"
#include "Event.hh"
#include <assert.h>
#include <math.h>


// TODO a vertex stuff
/*
Path::Path(Event* event)
{
	events.push_back(event);
	events.push_back(event);
	start_event = event;
	stop_event = event;
	//start_time = event->time;
	//stop_time = event->time;
}
*/

Path::Path(Vertex* vertex)
{
	assert(vertex);
	verticies.push_back(vertex);
	start = vertex;
	stop = vertex;
}

// TODO a vertex stuff
//void Path::append(Pathlet* pathlet, Event* event)
/*
void Path::append(polynomial p[3], Event* event)
{
	pathlets.push_back(pathlet);
	events.push_back(event);
	pathlet->start_event = stop_event;
	pathlet->stop_event = event;
	pathlet->start_time = stop_time;
	stop = new Vertex(... event ...);
	//stop_time = event->time;
	//pathlet->stop_time = stop_time;
	//cout << "pathlet->start_time = " << pathlet->start_time << endl;
	//cout << "pathlet->stop_time = " << pathlet->stop_time << endl;
	//cout << "path start_time = " << start_time << endl;
	//cout << "path stop_time = " << stop_time << endl;
}
*/

//void Path::append(polynomial p[3], Vertex* vertex)
void Path::append(Pathlet* pathlet, Vertex* new_stop)
{
	assert(pathlet);
	assert(new_stop);
	pathlets.push_back(pathlet);
	verticies.push_back(new_stop);

	pathlet->start = stop;
    stop->set_after(pathlet);

	pathlet->stop = new_stop;
	stop = new_stop;

    new_stop->set_before(pathlet);
    new_stop->set_after(0);
}

/*
Path::Path(Event* event)
{
	events.push_back(event);
	start_event = event;
	stop_event = event;
	start_time = event->time;
	stop_time = event->time;
}

void Path::append(Pathlet* pathlet, Event* event)
{
	pathlets.push_back(pathlet);
	events.push_back(event);
	pathlet->start_event = stop_event;
	pathlet->stop_event = event;
	pathlet->start_time = stop_time;
	stop_event = event;
	stop_time = event->time;
	pathlet->stop_time = stop_time;
	//cout << "pathlet->start_time = " << pathlet->start_time << endl;
	//cout << "pathlet->stop_time = " << pathlet->stop_time << endl;
	//cout << "path start_time = " << start_time << endl;
	//cout << "path stop_time = " << stop_time << endl;
}
*/

/*
void Path::append_continuity(Pathlet* pathlet, ContinuityEvent* event)
{
	double t = event->get_time() - stop_time;
	for (int i = 0; i < 3; i++)
	{
		event->position[i] = pathlet->curve[i].evaluate(t);
		event->velocity[i] = pathlet->curve[i].derivative(t);
	}
	append(pathlet,event);
}
	
void Path::append_interaction(Pathlet* pathlet, InteractionEvent* event)
{
	double t = event->get_time() - stop_time;
	for (int i = 0; i < 3; i++)
	{
		event->position[i] = pathlet->curve[i].evaluate(t);
		event->velocity[i] = pathlet->curve[i].derivative(t);
	}
	cout<<"interaction normal {"<<event->normal[0]<<", "<<event->normal[1]<<", "<<event->normal[2]<<"}"<<endl;
	event->reflect_velocity(event->normal);
	append(pathlet,event);
}
*/

/*
Path::Path(unsigned _count, double _start_time, double _stop_time)
{
    count = _count;
    start_time = _start_time;
    stop_time = _stop_time;
    //sample = new Pathlet[count];
    sample.resize
    _visable = true;
}


Path::Path()
{
    //count = 0;
    start_time = 0;
    stop_time = 0;

    _visable = false;
    _reflections = 0;
}

Path::~Path()
{
    //if (sample)
    //	delete[] sample;
    // TODO delete correctly 
	//sample.clear();
}
*/

/*
Path::Path(const Path &copy)
{
    count = copy.count;
    start_time = copy.start_time;
    stop_time = copy.stop_time;
    //sample = new Pathlet[count];
    for(unsigned i = 0; i < count; i++)
    	sample[i] = copy.sample[i];
}
*/

/*
Pathlet::Pathlet(double _start_time,
				 double _stop_time,
				 const polynomial p[3])
: scale(1), start_time(_start_time), stop_time(_stop_time)
{
	for (int i = 0; i < 3; i++)
		curve[i] = p[i];
}
*/

/*
Pathlet::Pathlet(polynomial p[3], Vertex* _start)
: scale(1), start(_start), stop(0)
{
    assert(_start);
	double t = get_relative_max_time();
	double x[3], v[3];
	for (int i = 0; i < 3; i++)
	{
		curve[i] = p[i];
		x[i] = p[i].evaluate(t);
		v[i] = p[i].derivative(t);
	}
    Event* event = new Event(start->get_time() + t);
	stop = new Vertex(event, x ,v);
}
*/

Pathlet::Pathlet(polynomial p[3], Vertex* _start, Vertex* _stop)
  : start(_start), stop(_stop), 
    scale(1) // default for now
{
    cout << start << endl;
    cout << stop << endl;
	for (int i = 0; i < 3; i++)
		curve[i] = p[i];
}

/*
Pathlet::Pathlet(Event* start, polynomial p[3])
: scale(1), start_event(start), stop_event(NULL), start_time(start->get_time()), stop_time(start_time + 1)
{
	for (int i = 0; i < 3; i++)
		curve[i] = p[i];
}

Pathlet::Pathlet(Event* start, Event* stop, polynomial p[3])
: scale(1), start_event(start), stop_event(stop_event), start_time(start->get_time()), stop_time(stop->get_time())
{
	for (int i = 0; i < 3; i++)
		curve[i] = p[i];
}
*/

void Pathlet::set(int axis, const polynomial &p)
{
	assert (axis < 3);
	curve[axis] = p;
}

void Pathlet::get_position(double time, double position[3]) const
{
	assert(start);
    assert(time >= start->get_time());
    double s = (time - start->get_time())/scale;

    for (int i = 0; i < 3; i++)
		position[i] = curve[i].evaluate(s);
}

void Pathlet::get_velocity(double time, double velocity[3]) const
{
	assert(start);
    assert(time >= start->get_time());
    double s = (time - start->get_time())/scale;

    for (int i = 0; i < 3; i++)
		velocity[i] = curve[i].derivative(s);
}

Vertex* Pathlet::get_start_vertex()
{
	assert(start);
	return start;
}

Vertex* Pathlet::get_stop_vertex()
{
	assert(stop);
	return stop;
}

void Pathlet::set_start_vertex(Vertex* vertex)
{
	assert(vertex);
	start = vertex;
    start->set_after(this);
}

void Pathlet::set_stop_vertex(Vertex* vertex)
{
	assert(vertex);
	stop = vertex;
    stop->set_before(this);
}

double Pathlet::get_stable_time(int axis)
{
    return curve[axis % 3].get_stable_max();
}

double Pathlet::get_stable_time()
{
    double stable_time = get_stable_time(0);
    for (int axis = 1; axis < 3; axis++)
    {
        double t = get_stable_time(axis);
        if (stable_time > t)
            stable_time = t;
    }
    return stable_time;
}

double Pathlet::get_start_time()
{
    assert(start);
    return start->get_time();
}

double Pathlet::get_stop_time()
{
    assert(stop);
    return stop->get_time();
}

const polynomial & Pathlet::get_curve(int i) const
{
    return curve[i];
}

//const double[3] & Path::get_position(double time)
void Path::get_position(double time, double position[3])
{
    cout << "get_position()" << endl;
    assert(start);
    assert(stop);
    assert(time >= start->get_time());
    assert(time < stop->get_time());

    vector<Pathlet*>::iterator p;
    for (p = pathlets.begin(); p != pathlets.end(); p++)
    {
        Pathlet* pathlet = *p;
        double start_time = pathlet->start->get_time();
        double stop_time = pathlet->stop->get_time();

        if (time >= start_time and time <= stop_time)
        {
            cout << "get_position()" << endl;
            pathlet->get_position(time, position);
            return;
        }
    }

    /*
       for (int i = 0; i < count; i++)
       {
       if (time >= pathlets[i]->start_time
       and time <= pathlets[i]->stop_time)
       {
       pathlets[i]->get_position(time, position);
       return;
       }
       }
     */
    cerr << "request for range out of bound in get_position" << endl;
    assert(false);
}
/*
   double Path::get_position(double start, double stop, double position[3])
   {
   assert(start >= start_time);
   assert(start < stop_time);
   assert(stop > start_time);
   assert(stop <= stop_time);
   assert(start_time < stop_time);
   assert(start < stop);
   for (int i = 0; i < count; i++)
   {
   if (start >= sample[i].start_time 
   and start < sample[i].stop_time)
   {
   if (stop > sample[i].stop_time)
   stop = sample[i].stop_time;
   sample[i].get_position(stop, position);
   return stop;
   }
   }
   cerr << "ran out of samples." << endl;
   cerr << "start = " << start << " stop = " << stop << endl;
   cerr << "start_time = " << start_time << " stop_time = " << stop_time << endl;
   assert(false);
   }
 */

/*
   double Path::getMaximum(double start, double stop, const double direction[3])
   {
//if (start < start_time) 
if (not (start < stop_time)) 
{
cerr << start << " " << stop_time << endl;
cerr << visable() << endl;
cerr.flush();
}
assert(start >= start_time);
assert(start < stop_time);
assert(stop > start_time);
assert(stop <= stop_time);
assert(start_time < stop_time);
assert(start < stop);

// get first distance 
double maximum;
int i = 0;
while (i < count) {
if (start >= sample[i].start_time 
and start < sample[i].stop_time)
{
// the most extreme distance must at least as extreme as this point
maximum = sample[i].getMaximum(start, stop, direction);
break;
}
i++;
}

// we got the first point, now continue on looking for more extreme points
i++;
while (i < count)
{
if (stop >= sample[i].start_time)
{
// get maximum distance for this segment
double max = sample[i].getMaximum(start, stop, direction);

// see if this is more extreme than any other point so far
if (max > maximum)
maximum = max;
}
i++;
}
return maximum;
}
 */

int Path::compare_vectors(const double a[3], const double b[3], double c)
{
    double error_count = 0;
    for (int j = 0; j < 3; j++)
    {
        double d = fabs(a[j] - b[j]);
        if (d > c)
            error_count++;
    }
    return error_count;
}

// tests a particle paths continuity
// reports number of errors
int Path::check(double epsilon)
{
    cout << "Checking path for error up to " << epsilon << "..." << endl;
    int error_count = 0;
    int i = 0;
    double start_position[3];
    double start_velocity[3];
    double stop_position[3];
    double stop_velocity[3];
    double last_position[3];
    double last_velocity[3];
    double start_time;
    double stop_time;
    double previous_time;

    if (start)
        start_time = start->get_time();
    else
    {
        error_count++;
        cerr << "There is no start vertex. Can't continue." << endl;
        return error_count;
    }

    if (stop)
        stop_time = stop->get_time();
    else
    {
        error_count++;
        cerr << "There is no stop vertex. Can't continue." << endl;
        return error_count;
    }

    previous_time = start_time;

    vector<Pathlet*>::iterator p;
    for (p = pathlets.begin(); p != pathlets.end(); p++)
    {
        Pathlet* pathlet = *p;
        Vertex* pathlet_start = pathlet->start;
        Vertex* pathlet_stop = pathlet->stop;
        double pathlet_start_time;
        double pathlet_stop_time;
        i++;

        if (pathlet_start)
            pathlet_start_time = pathlet_start->get_time();
        else
        {
            error_count++;
            cerr << "There is no start vertex for pathlet " << i << ". Can't continue." << endl;
            return error_count;
        }

        if (pathlet_stop)
            pathlet_stop_time = pathlet_stop->get_time();
        else
        {
            error_count++;
            cerr << "There is no stop vertex for pathlet " << i << ". Can't continue." << endl;
            return error_count;
        }

        if (pathlet_start_time > stop_time)
        {
            error_count++;
            cerr << "Pathlet start time is after stop time." << endl
                << "Pathlet start time is " << start << " sec and "
                << "Pathlet stop time is " << pathlet_stop_time << " sec." << endl
                << "Can't continue." << endl;
            return error_count;
        }

        if (pathlet_stop_time < start_time)
        {
            error_count++;
            cerr << "Pathlet stop time is before start time." << endl
                << "Pathlet stop time is " << stop << " sec and "
                << "Pathlet start time is " << pathlet_start_time << " sec." << endl
                << "Can't continue." << endl;
            return error_count;
        }

        if ((p == pathlets.begin()) and (pathlet_start_time != start_time))
        {
            error_count++;
            cerr << "The first sample start time "
                << "does not match the path start time." << endl
                << "First Sample start time is " << start << " sec and "
                << "Path start time is " << start_time << " sec." << endl;
        }

        if ((p == pathlets.end()) and (pathlet_stop_time != stop_time))
        {
            error_count++;
            cerr << "The last pathlet in the path stop time "
                << "does not match the path stop time." << endl
                << "The last pathlet in the path stop time is " << pathlet_stop_time << " sec and "
                << "the path stop time is " << stop_time << " sec." << endl;
        }

        if (pathlet_start_time != previous_time)
        {
            error_count++;
            cerr << "Sample " << /*i <<*/ " start time "
                << "does not match the previous samples end time." << endl
                << "Sample start time is " << pathlet_start_time << " sec and "
                << "previous sample stop time was " 
                << previous_time << " sec." << endl
                << "difference is " << pathlet_start_time - previous_time << endl;
        }
        else if (p != pathlets.begin())
        {
            pathlet->get_position(pathlet_start_time, start_position);
            pathlet->get_position(pathlet_stop_time, stop_position);

            if (compare_vectors(start_position, last_position, epsilon))
            {
                error_count++;
                cerr << "Pathlet "<<i<<" start position does not match "
                    << "previous pathlet stop position." << endl;
                cerr << "Current pathlet start position is " << "(" 
                    << start_position[0] << ", "
                    << start_position[1] << ", "
                    << start_position[2] << ")." << endl;
                cerr << "Previous pathlet stop position was " << "(" 
                    << last_position[0] << ", "
                    << last_position[1] << ", "
                    << last_position[2] << ")." << endl;
            }

            pathlet->get_velocity(pathlet_start_time, start_velocity);
            pathlet->get_velocity(pathlet_stop_time, stop_velocity);

            if (compare_vectors(start_velocity, last_velocity, epsilon))
            {
                error_count++;
                cerr << "Pathlet "<<i<<" start velocity does not match "
                    << "previous pathlet stop position." << endl;
                cerr << "Current pathlet start velocity is " << "(" 
                    << start_velocity[0] << ", "
                    << start_velocity[1] << ", "
                    << start_velocity[2] << ")." << endl;
                cerr << "Previous pathlet stop velocity was " << "(" 
                    << last_velocity[0] << ", "
                    << last_velocity[1] << ", "
                    << last_velocity[2] << ")." << endl;
            }



            // now check that the vectors match with the paths
            double vertex_start_position[3];
            double vertex_stop_position[3];
            double vertex_start_out[3];
            double vertex_stop_in[3];

            pathlet_start->get_position(vertex_start_position);
            if (compare_vectors(vertex_start_position, start_position, epsilon))
            {
                error_count++;
                cerr << "Pathlet "<<i<<" start position does not match "
                    << "start Vertex position." << endl;
            }

            pathlet_start->get_out(vertex_start_out);
            if (compare_vectors(vertex_start_out, start_velocity, epsilon))
            {
                error_count++;
                cerr << "Pathlet "<<i<<" start velocity does not match "
                    << "start Vertex velocity." << endl;
            }

            pathlet_stop->get_position(vertex_stop_position);
            if (compare_vectors(vertex_stop_position, stop_position, epsilon))
            {
                error_count++;
                cerr << "Pathlet "<<i<<" stop position does not match "
                    << "stop Vertex position." << endl;
            }

            pathlet_stop->get_in(vertex_stop_in);
            if (compare_vectors(vertex_stop_in, stop_velocity, epsilon))
            {
                error_count++;
                cerr << "Pathlet "<<i<<" stop velocity does not match "
                    << "stop Vertex velocity." << endl;
            }
        }

        pathlet->get_position(previous_time, last_position);
        pathlet->get_velocity(previous_time, last_velocity);
        previous_time = pathlet_stop_time;
    }

    if (error_count > 0)
    {
        cerr << "There were " << error_count << " errors with "
            << "the start and stop times." << endl
            << "No point in checking more. "
            << "Fix these first. " << endl;
    }
    return error_count;
}

void Path::show()
{
    _visable = true;
}

void Path::hide()
{
    _visable = false;
}

bool Path::visable()
{
    return _visable;
}

//unsigned Path::add(const Pathlet &_sample)
//{
/*
   sample.push_back(_sample);
   count = sample.size();
   if (_sample.reflection)
   {
   _reflections++;
   double p[3];
   double floor_level = 0.000001;
   _sample.getStopPosition( p );
   if (p[1] < floor_level) {
   hide();
//cout << "hiding because reflection at ("
//     << p[0] << ", " << p[1] << ", " << p[2] 
//     << ") was below " << floor_level << endl;
}
//else
//cout << "not hiding because of reflection" << endl;
}
 */
//}

unsigned Path::discontinuities()
{
    return _reflections;
}

void Path::writeJSON(ostream &out, double start_write_time, double stop_write_time)
{
    // determine starting pathlet
    assert(stop_write_time > start_write_time);
    out << "{" << endl 
        << right << "\"pathlets\" : [" << endl << right;
    vector<Pathlet*>::iterator p;
    for (p = pathlets.begin(); p != pathlets.end(); p++)
    {
        Pathlet* pathlet = *p;
        pathlet->writeJSON(out, start_write_time, stop_write_time);
        if (p != --pathlets.end())
            out << ", " << endl;
    }
    out << left << "]" << endl;
    out << "\"verticies\" : [" << endl;
    vector<Vertex*>::iterator v;
    for (v = verticies.begin(); v != verticies.end(); v++)
    {
        Vertex* vertex = *v;
        vertex->writeJSON(out, start_write_time, stop_write_time);
        if (v != --verticies.end())
            out << ", " << endl;
    }
    out << "]" << endl << left  << "}";
}

void Path::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    // determine starting pathlet
    assert(stop_write_time > start_write_time);

    assert(start);
    start->writeMathematicaGraphics(out, start_write_time, stop_write_time);
    vector<Pathlet*>::iterator p;
    for (p = pathlets.begin(); p != pathlets.end(); p++)
    {
        Pathlet* pathlet = *p;
        //const double time = (stop_time - start_time)
        //                  * (frame + segment / (segment_count - 1)) 
        //                  / frame_count 
        //                  + start_time;
        //segment += 1.0;
        assert(pathlet);
        out << ", " << endl;
        pathlet->writeMathematicaGraphics(out, start_write_time, stop_write_time);

        assert (pathlet->stop);
        out << ", " << endl;
        pathlet->stop->writeMathematicaGraphics(out, start_write_time, stop_write_time);
    }
}

void Pathlet::writeJSON(ostream &out, double start_write_time, double stop_write_time)
{
    // TODO ...
    assert(stop_write_time > start_write_time);
    assert(scale > 0);
    out << "{" << endl 
        << "\"curve\" : [" << endl;
    for (int i = 0; i < 3; i++)
    {
        out << "\"" << curve[i] << "\"";
        if (i != 2) 
            out << ", ";
        out << endl;
    }
    out << "]" << endl;
    // TODO out << "\"start\" : ";
    // TODO stop - start->get_time()) / scale << endl 
    out << "}";
}

void Pathlet::writeMathematicaGraphics(ostream &out, double start_write_time, double stop_write_time)
{
    assert(stop_write_time > start_write_time);
    assert(scale > 0);
    out << "ParametricPlot3D[{" << curve[0] << ", " << curve[1] << ", " << curve[2] << "}, ";
    out << "{x, " << 0 << ", " << (stop->get_time() - start->get_time()) / scale << "}]";
}
