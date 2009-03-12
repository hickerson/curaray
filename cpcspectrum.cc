#include "loadSTL.hh"
//#include "GNUPlot.hh"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fields.hh"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "MonteCarlo.hh"
#include "Visualization.hh"
#include "Histogram.hh"
#include "Volume.hh"
#include "Simulation.hh"

using namespace std;

// TODO make MathematicaStream
// TODO make ParticleSource

#define MULTIPLE_MATHEMATICA_FILES 0
#define SIMULATION_CLASS 0

/*
       	        cerr << "hide {" << particle[i].position[0] << ", " 
                                 << particle[i].position[2] << ", " 
                                 << particle[i].position[1] << "}" << endl;
*/

int
main (int argc, char **argv)
{
  assert (argv[1]);
  string stl_filename = argv[1];
  string base_filename = stl_filename;
#if !SIMULATION_CLASS
  STLfile *stl_file;
  stl_file = STLfile::readSTLfile (argv[1]);
  assert (stl_file);
#endif

  assert (argv[2]);
  const double cm_height = atof (argv[2]);
  cout << "using ucn height " << cm_height << " cm."  << endl;

  // TODO move gravity def somewhere nice
  const double g = 9.80665;	// m/s^2 at sea level
  const double gravity[3] = { 0, -g, 0 };	// define down
  VectorField *field = new ConstantGravityField (gravity);

  // TODO will be part of the Simulation class
  const unsigned experiment_count = 10;
  const unsigned neutron_count = 1000;
  const double max_bounce_count = 4;
  const double bounce_step_size = 1;

  // TODO add this to a Historgram Visulisation class
  const int histogram_size = 1000;
  const double histogram_start = 0.0;	// meters
  const double histogram_stop = 0.30;	// meters
  const unsigned histogram_height = experiment_count * neutron_count / 10;

  // TODO make ParticleSource
  //const double ucn_height = 0.07;     // meters
  const double ucn_height = cm_height / 100;	// meters
  const double ucn_speed = sqrt (2 * g * ucn_height);
  const double start_time = 0;	// sec
  const double stop_time = 1.2 * ucn_speed / g;

  /*
     // TODO will be part of the Animation Visulation class
     const unsigned frame_count = 10;
     const double frame_start_time = 0;
     const double frame_stop_time = 3;
   */

  // setup the simulation environment
#if SIMULATION_CLASS
  BoxVolume volume (-1, 4, -1, 4, -1, 4);
  STLSurface stl_surface (stl_filename);
  //Simulation simulation();
  //simulation.setSimulationVolume(volume);
  Simulation simulation (volume);
  simulation.addSurface (stl_surface);	// TODO UCNSimulation only
  simualtion.addVectorField (&field);
#else
  unsigned max_depth = 1;
  unsigned fields_count = 1;
  Octree octree (-1, 4, -1, 4, -1, 4, fields_count, max_depth);
  octree.setup_vector_fields (&field);
  octree.walls = stl_file;
#endif

  // TODO add to Simulation class 
  //Histogram *histogram[max_bounce_count + 1];
  vector < Histogram * >histogram;
  for (unsigned bounce_count = 0; bounce_count <= max_bounce_count;
       bounce_count++)
    {
      /*
         histogram[bounce_count] = new Histogram (histogram_size,
         histogram_start,
         histogram_stop);
       */
      histogram.push_back (new Histogram (histogram_size,
					  histogram_start, histogram_stop));
    }

  // TODO add to Simulation class 
  double path_hidden_count = 0;
  for (unsigned experiment = 0; experiment < experiment_count; experiment++)
    {
      // make all the neutrons
      // TODO we really only need one neutron made each time
      Particle particle[neutron_count];
      for (unsigned i = 0; i < neutron_count; i++)
	{
	  double velocity[3];
	  double position[3] = { 0, 0, 0 };
	  //randomSphereVector(velocity, randomPowerLaw(7,2));
	  //randomSphereVector(velocity, randomRange(6,7));
	  //randomSphereVector (velocity, ucn_speed);
	  randomHemiSphereVector (gravity, velocity, ucn_speed);
	  randomDiskVector (position, 0.0399);
	  Particle neutron (position, velocity, 0, 1.0);
	  particle[i] = neutron;
	  particle[i].time = start_time;
	}

      // compute paths
      ParticlePath ucn_path[neutron_count];
      for (unsigned i = 0; i < neutron_count; i++)
	{
	  // start path segments
	  ucn_path[i].start_time = start_time;
	  ucn_path[i].stop_time = stop_time;
	  ucn_path[i].show ();
	  double last_time = start_time;
	  while (last_time < stop_time)
	    {
	      // copy over particle information to sample
	      ParticlePathSample sample (particle[i], 0, gravity);
	      //sample.start_time = last_time;

	      // step forward
	      octree.step_particle (&particle[i], sample);
	      if (not octree.in_bounds (particle[i].position))
		{
		  // XXX This is a know bug where the particle tunnels through walls
		  cerr << "hiding path that is out of bounds." << endl;
		  ucn_path[i].hide ();
		}

	      // look for the end of the path sample
	      double next_time = min (particle[i].time, stop_time);
	      sample.stop_time = next_time;
	      last_time = next_time;
	      ucn_path[i].add (sample);
	    }
	  if (ucn_path[i].check (0.00000001) > 0)
	    {
	      cerr << "Detected errors in path " << i << "." << endl
		<< "aborting..." << endl;
	      exit (1);
	    }
	  //cout << "done." << endl;
	}

      // TODO Add to Histogram Visulazation class
      const double direction[3] = { 0, 1, 0 };
      for (unsigned bounce_count = 0; bounce_count <= max_bounce_count;
	   bounce_count++)
	{
	  for (unsigned i = 0; i < neutron_count; i++)
	    {
	      if (start_time != ucn_path[i].start_time)
		cerr << "mismatched start time" << endl;
	      if (not ucn_path[i].visable ()) {
		//cerr << "path hidden" << endl;
		path_hidden_count++;
	      }
	      if (ucn_path[i].visable ())
		{
		  if ((ucn_path[i].discontinuities () <= bounce_count)
		      or (bounce_count == max_bounce_count))
		    {
		      const double h =
			ucn_path[i].getMaximum (start_time, stop_time,
						direction);
		      histogram[bounce_count]->add (h);
		      //cout << "maximum height for path " << i << " is " << h << " meters." << endl;
		    }
		}
	      ucn_path[i].sample.clear ();
	    }
	}
      // cout << "Completed experiment " << experiment << "." << endl;
    }
    cerr << path_hidden_count << " paths hidden" << endl;

  // write the gnuplot file
  {
    ostringstream s;
    s << "cpc-bounce-" << 100 * ucn_height << "cm.gnuplot";
    string filename = s.str ();
    ofstream gf;
    gf.open (filename.c_str ());
    gf << "set term postscript eps color" << endl;
    gf << "set output \"cpc-bounce-" << 100 * ucn_height << "cm.ps\"" << endl;
    gf << "set style line 1 linetype 1" << endl;
    gf << "set style line 2 linetype 7" << endl;
    gf << "set multiplot" << endl;
    gf << "set yrange [ 0 : " << histogram_height << " ]" << endl;
    gf << "plot ";
    for (unsigned bounce_count = 0; bounce_count <= max_bounce_count;
	 bounce_count++)
      {
	if (bounce_count < max_bounce_count)
	  {
	    gf << "\"cpc-bounce-" << bounce_count << "-" << 100 *
	      ucn_height << "cm.dat\" title \"" << bounce_count <<
	      "\" with lines, \\" << endl;
	  }
	else
	  {
	    gf << "\"cpc-bounce-" << bounce_count << "-and-up-" << 100 *
	      ucn_height << "cm.dat\" ls 1 title \"> " << bounce_count -
	      1 << "\" with lines" << endl;
	  }
      }
    gf << "set nokey" << endl;
    gf << "set origin 0.1,0.3" << endl;
    gf << "set size 0.6,0.6" << endl;
    gf << "set xrange [ " << ucn_height - 0.04 
       << " : " << ucn_height << " ]" << endl;
    gf << "set yrange [ 0 : " << histogram_height / 10 << " ]" << endl;
    gf << "replot" << endl;
  }

  // also make a log plot
  {
    ostringstream s;
    s << "cpc-bounce-" << 100 * ucn_height << "cm-log.gnuplot";
    string filename = s.str ();
    ofstream gf;
    gf.open (filename.c_str ());
    gf << "set term postscript eps color" << endl;
    gf << "set output \"cpc-bounce-" << 100 * ucn_height << "cm-log.ps\"" << endl;
    gf << "set style line 1 linetype 1" << endl;
    gf << "set style line 2 linetype 7" << endl;
    gf << "set yrange [ 1 : " << histogram_height * 10 << " ]" << endl;
    gf << "set logscale y" << endl;
    gf << "set format y \"10^{\%L}\"" << endl;
    gf << "plot ";
    for (unsigned bounce_count = 0; bounce_count <= max_bounce_count;
	 bounce_count++)
      {
	if (bounce_count < max_bounce_count)
	  {
	    gf << "\"cpc-bounce-" << bounce_count << "-" << 100 *
	      ucn_height << "cm.dat\" title \"" << bounce_count <<
	      "\" with lines, \\" << endl;
	  }
	else
	  {
	    gf << "\"cpc-bounce-" << bounce_count << "-and-up-" << 100 *
	      ucn_height << "cm.dat\" ls 1 title \"> " << bounce_count -
	      1 << "\" with lines" << endl;
	  }
      }
  }

  // Now write the histograms
  for (unsigned bounce_count = 0; bounce_count <= max_bounce_count;
       bounce_count++)
    {
      ostringstream s;
      s << "cpc-bounce-" << bounce_count;
      if (bounce_count == max_bounce_count)
	s << "-and-up";
      s << "-" << 100 * ucn_height << "cm.dat";
      string filename = s.str ();
      histogram[bounce_count]->out (filename.c_str ());
      delete histogram[bounce_count];
    }


// TODO this will be part of a Mathematica Visulisation class
#if 0
  // open the Mathematica file
  string math_filename = base_filename + ".math";
  ofstream math_file;
  math_file.open (math_filename.c_str ());
  if (not math_file.is_open ())
    {
      cerr << "error opening file " << math_filename << endl;
      exit (1);
    }

  // write the header
  math_file << "SetOptions[Plot,DisplayFunction->Identity]" << endl;
  math_file << "graphics = Show[" << endl;

  // write the stl file first
  stl_file->writeMathematicaGraphics (math_file);
  // TODO math_file << stl_file; XXX no endl at the end
  math_file << "," << endl;

  // prep for drawing the paths
  math_file << "Graphics3D[{" << endl << "RGBColor[0,0,0]";

  // close Mathematica files
  math_file << " }], PlotRange -> {{-1, 6}, {0,1}, {-0.5, 3.5}}];" << endl;
  // TODO add range to Visulisation class
  //math_file << " }], PlotRange -> {{-.1, 4}, {0,1}, {-0.1, 3.1}}];" << endl;
  //math_file << " }], PlotRange -> {{4, 6}, {0,1}, {-0.5, 3.5}}];" << endl;
  math_file << "Export[\"" << base_filename << ".eps" << "\", graphics, "
    << "ImageSize->600, ImageResolution->75]" << endl;
  math_file << "Exit[]" << endl;
  math_file << "Quit[]" << endl;


  // Execute mathematica file
  cout << "serching in path " << getenv ("PATH") << endl;
  cout << "Mathematica:" << endl;
  string s = "math -noprompt -run \"<<" + base_filename + ".math" + "\"";
  cout << "Mathematica returned " << system (s.c_str ()) << endl;
  // TODO sys << "math -noprompt -run \"<<" << base_filename << "\"" << execute;
  // TODO if (sys.error())
  // TODO     cerr << "Mathematica returned " << sys.error() << endl;
#endif

  cout << "done" << endl;

  return 0;
}
