#ifndef __VISUALIZATION_HH__
#define __VISUALIZATION_HH__

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Graphics.hh"
#inlcude "Box.hh"

using namespace std;

class Visualization 
{
	const string    name;
	Box*    		region;
	
    unsigned  		frame_count;
    double    		start_time;
    double    		stop_time;
    
    ofstream 		math_file; 
    Graphics3D* 	frame;

	Visualization(string _name, Box* _region) 
	  : name(_name), 
		region(_region) {}
			
	
};


#endif
