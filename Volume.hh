#ifndef __VOLUME_HH__
#define __VOLUME_HH__

#include <string>
#include <iostream>
#include <vector>
#include "Geometry.hh"

using namespace std;

class Volume : public Geometry
{
};
//typedef std::vector<Volume*> VolumeTable;

//typedef Volume UCNVolume;
//typedef std::vector<UCNVolume*> UCNVolumeTable;

/*
struct BoxVolume : Volume
{
	double x_min, x_max;
	double y_min, y_max;
	double z_min, z_max;
	
	BoxVolume(double _x_min, double _x_max,
		   	  double _y_min, double _y_max,
	          double _z_min, double _z_max)
		  : x_min(_x_min), x_max(_x_max),
		    y_min(_y_min), y_max(_y_max),
	        z_min(_z_min), z_max(_z_max) {}
	BoxVolume(const BoxVolume &copy)
		  : x_min(copy.x_min), x_max(copy.x_max),
		    y_min(copy.y_min), y_max(copy.y_max),
	            z_min(copy.z_min), z_max(copy.z_max) {}
};
*/
//typedef BoxVolume UCNBoxVolume;

//struct STLVolume : Volume
//{
//};
//typedef STLVolume UCNSTLVolume;

#endif
