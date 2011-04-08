#include "Path.hh"
#include <assert.h>


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
void Path::append(Pathlet* pathlet, Vertex* vertex)
{
	//assert(vertex->time - stop->time == pathlet->); 
	assert(pathlet);
	assert(vertex);
	pathlets.push_back(pathlet);
	verticies.push_back(vertex);
	pathlet->start = stop;
	pathlet->stop = vertex;
	stop = vertex;
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

Pathlet::Pathlet(polynomial p[3], Vertex* _start)
: scale(1), start(_start), stop(0)
{
	double t = get_relative_max_time();
	double x[3], v[3];
	for (int i = 0; i < 3; i++)
	{
		curve[i] = p[i];
		x[i] = p[i].evaluate(t);
		v[i] = p[i].derivative(t);
	}
	stop = new Vertex(start->time + t, x ,v);
}

Pathlet::Pathlet(polynomial p[3], Vertex* _start, Vertex* _stop)
: scale(1), start(_start), stop(_stop)
{
	assert(start);
	assert(stop);
	for (int i = 0; i < 3; i++)
		curve[i] = p[i];
}

/*
Pathlet::Pathlet(Event* start, polynomial p[3])
: scale(1), start_event(start), stop_event(NULL), start_time(start->time), stop_time(start_time + 1)
{
	for (int i = 0; i < 3; i++)
		curve[i] = p[i];
}

Pathlet::Pathlet(Event* start, Event* stop, polynomial p[3])
: scale(1), start_event(start), stop_event(stop_event), start_time(start->time), stop_time(stop->time)
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

void Pathlet::getPosition(double time, double position[3]) const
{
	assert(start);
	assert(stop);
    assert(time >= start->time);
    assert(time <= stop->time);

    for (int i = 0; i < 3; i++)
		position[i] = curve[i].evaluate((time - start->time)/scale);
}

void Pathlet::getVelocity(double time, double velocity[3]) const
{
	assert(start);
	assert(stop);
    assert(time >= start->time);
    assert(time <= stop->time);

    for (int i = 0; i < 3; i++)
		velocity[i] = curve[i].derivative((time - start->time)/scale);
}


double Pathlet::get_start_time()
{
	assert(start);
	return start->time;
}

double Pathlet::get_stop_time()
{
	assert(stop);
	return stop->time;
}

void Vertex::writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time)
{
	event->writeMathematicaGraphics(math_file, start_write_time, stop_write_time);
}


//const double[3] & Path::getPosition(double time)
void Path::getPosition(double time, double position[3])
{
	cout << "getPosition()" << endl;
	assert(start);
	assert(stop);
    assert(time >= start->time);
    assert(time < stop->time);

	vector<Pathlet*>::iterator p;
	for (p = pathlets.begin(); p != pathlets.end(); p++)
    {
		Pathlet* pathlet = *p;
		double start_time = pathlet->start->time;
        double stop_time = pathlet->stop->time;

		if (time >= start_time and time <= stop_time)
        {
			cout << "getPosition()" << endl;
	    	pathlet->getPosition(time, position);
            return;
        }
	}
	/*
	for (int i = 0; i < count; i++)
    {
        if (time >= pathlets[i]->start_time
        and time <= pathlets[i]->stop_time)
        {
	    	pathlets[i]->getPosition(time, position);
            return;
        }
    }
	*/
	cerr << "request for range out of bound in getPosition" << endl;
    assert(false);
}
/*
double Path::getPosition(double start, double stop, double position[3])
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
	    sample[i].getPosition(stop, position);
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

// tests a particle paths continuity
// reports number of errors
int Path::check(double epsilon)
{
    int error_count = 0;
    double last_position[3];
    double last_velocity[3];
    double position[3];
    double last_time;
    //int i = 0;
	vector<Pathlet*>::iterator p;
	for (p = pathlets.begin(); p != pathlets.end(); p++)
    {
		Pathlet* pathlet = *p;
        double pathlet_start_time = pathlet->start->time;
        double pathlet_stop_time = pathlet->start->time;
		double start_time = start->time;
		double stop_time = stop->time;
        if (pathlet_start_time > pathlet_stop_time)
        {
            error_count++;
            cerr << "Pathlet start time is after stop time." << endl
			     << "Pathlet start time is " << start << " sec and "
                 << "Pathlet stop time is " << pathlet_stop_time << " sec." << endl
				 << "Can't continue." << endl;
			return error_count;
        }
		pathlet->getPosition(pathlet_start_time, position);
        //if (i == 0)
		if (p == pathlets.begin())
        {
            if (pathlet_start_time != start_time)
            {
                error_count++;
                cerr << "The first sample start time "
                     << "does not match the path start time." << endl
                     << "First Sample start time is " << start << " sec and "
                     << "Path start time is " << start_time << " sec." << endl;
            }
        }
        else
        {
            if (pathlet_start_time != last_time)
            {
                error_count++;
                cerr << "Sample " << /*i <<*/ " start time "
                     << "does not match the previous samples end time." << endl
                     << "Sample start time is " << start_time << " sec and "
                     << "previous sample stop time was " 
                     << last_time << " sec." << endl;
            }
            else
            {
                double position_error_count = 0;
                for (int j = 0; j < 3; j++)
                {
                    double d = position[j] - last_position[j];
                    //if (abs(d) > epsilon)
                    if (d > epsilon or -d > epsilon)
                        position_error_count++;
                }
                if (position_error_count)
                {
                    error_count++;
                    cerr << "Sample " << /*i <<*/ " start position did not match "
                         << "previous sample end position." << endl;
                    cerr << "Sample start position is " << "(" 
                         << position[0] << ", "
                         << position[1] << ", "
                         << position[2] << ")." << endl;
                    cerr << "Previous sample end position was " << "(" 
                         << last_position[0] << ", "
                         << last_position[1] << ", "
                         << last_position[2] << ")." << endl;
                    cerr << endl;
                }

				/*
                double velocity_error_count = 0;
                for (int j = 0; j < 3; j++)
                {
                    double d = velocity[j] - last_velocity[j];
                    if (d > epsilon or -d > epsilon)
                        velocity_error_count++;
                }
                if (velocity_error_cou)
                {
                    error_count++;
                    cerr << "Sample start velocity did not match "
                         << "previous sample end position." << endl;
                    cerr << "Sample start velocity is " << "(" 
                         << position[0] << ", "
                         << position[1] << ", "
                         << position[2] << ")." << endl;
                    cerr << "Previous sample end velocity was " << "(" 
                         << last_position[0] << ", "
                         << last_position[1] << ", "
                         << last_position[2] << ")." << endl;
                    cerr << endl;
                }
				*/
            }
        }

        //double stop = pathlet->stop->event->time;
		//sample[i].getPosition(stop, last_position);
        if (pathlet_stop_time < pathlet_start_time)
        {
            error_count++;
            cerr << "Pathlet stop time is before start time." << endl
			     << "Pathlet stop time is " << stop << " sec and "
                 << "Pathlet start time is " << pathlet_start_time << " sec." << endl
				 << "Can't continue." << endl;
			return error_count;
        }
		pathlet->getPosition(pathlet_stop_time, last_position);
		//pathlet->getVelocity(stop, last_velocity);
        //if (i == pathlets.size())
		if (p == pathlets.end())
        {
            if (pathlet_stop_time != stop_time)
            {
                error_count++;
                cerr << "the last sample stop time "
                     << "does not match the path stop time." << endl
                     << "Last sample stop time is " << pathlet_stop_time << " sec and "
                     << "Path stop time is " << stop_time << " sec." << endl;
            }
        }
        last_time = pathlet_stop_time;
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

void Path::writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time)
{
	// determine starting pathlet
	assert(stop_write_time > start_write_time);
	vector<Pathlet*>::iterator p;
	for (p = pathlets.begin(); p != pathlets.end(); p++)
	{
		Pathlet* pathlet = *p;
		//const double time = (stop_time - start_time)
		//                  * (frame + segment / (segment_count - 1)) 
		//                  / frame_count 
		//                  + start_time;
		//segment += 1.0;
		pathlet->writeMathematicaGraphics(math_file, start_write_time, stop_write_time);
		if (pathlet->stop)
		{
			math_file << ", " << endl;
			stop->writeMathematicaGraphics(math_file, start_write_time, stop_write_time);
		}
		if (p != --pathlets.end())
			math_file << ", " << endl;
	}
}

void Pathlet::writeMathematicaGraphics(ofstream &math_file, double start_write_time, double stop_write_time)
{
	assert(stop_write_time > start_write_time);
	assert(scale > 0);
	math_file << "ParametricPlot3D[{" << curve[0] << ", " << curve[1] << ", " << curve[2] << "}, ";
	math_file << "{x, " << 0 << ", " << (stop->time - start->time) / scale << "}]";
	cout << stop->time << " " << start->time << " " << scale << endl;
	cout << "{x, " << 0 << ", " << (stop->time - start->time) / scale << "}]";
}
