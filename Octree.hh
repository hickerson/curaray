#ifndef __OCTREE__HH__
#define __OCTREE__HH__

#include <assert.h>
#include <math.h>
#include "loadSTL.hh"
#include "Particle.hh"

struct OctreeNode;
struct OctreeIterator;

/* 10 steps per cube */
#define DEFAULT_FINENESS		1

struct OctreeNode
{
    OctreeNode()
    {
	is_leaf = true;
	leaf.is_interior = true;
	leaf.fields = 0;
    }

    bool is_leaf;

    union {
	struct {
	    // the is_interior flag is only valid if is_leaf.
	    bool is_interior;

	    // an array of 3 numbers for each magnetic field.
	    double *fields;
	} leaf;

	struct {
	    // children, if !is_leaf
	    OctreeNode *children[2][2][2];
	} nonleaf;
    };
};

struct SolidObject
{
    virtual bool is_interior(const double *position) = 0;
};

/*
struct Particle
{
    double get_speed() const {
	double rv_squared;
	rv_squared = velocity[0] * velocity[0]
	           + velocity[1] * velocity[1]
	           + velocity[2] * velocity[2];
	return sqrt(rv_squared);
    }

    double pos[3];
    double velocity[3];
    double time;
    double mass;
    double charge;
    double magnetic_dipole;
};
*/

struct VectorField
{
    virtual bool should_subdivide(const double *center,
	                          double size) = 0;
    virtual void compute_field(const double *position,
	                       double *field_out) = 0;
    virtual void get_force (const Particle *particle,
			    const double *field_value,
			    double       *force_out) = 0;
};

struct Octree
{
    Octree(double x_min,double x_max,
           double y_min,double y_max,
           double z_min,double z_max,
	   unsigned n_fields,
	   unsigned max_depth);

    void deepen_octree_at_point (const double *xyz);

    void setup_vector_fields(VectorField **fields);
    void determine_interior(SolidObject *object);
    bool in_bounds(const double *xyz) const;

    double _x_min,_x_max;
    double _y_min,_y_max;
    double _z_min,_z_max;
    unsigned _n_fields;
    VectorField **_fields;
    unsigned _max_depth;
    OctreeNode *_root;
    STLfile *walls; // TODO: this needs to be changed

    void step_particle(Particle *particle,
	               const double *field_strengths,
		       double fineness = DEFAULT_FINENESS);
    void step_particle(Particle *particle,
                       ParticlePath *path);
    void step_particle(Particle *particle);

    void step_particle(Particle *particle, ParticlePathSample & sample);

    // debugging
    unsigned count_leaf_nodes() const;

private:
    void setup_vector_fields_recursive(OctreeIterator *iter);
    void determine_interior_recursive(SolidObject *object,
	                              OctreeIterator *iter);
    unsigned count_leaf_nodes_recursive(const OctreeNode *node) const;
};

struct OctreeIterator
{
    OctreeIterator(Octree *octree)
	: node(octree->_root),
	  depth(0),
	  x_min(octree->_x_min), x_max(octree->_x_max),
	  y_min(octree->_y_min), y_max(octree->_y_max),
	  z_min(octree->_z_min), z_max(octree->_z_max)
    {
    }

    void split()
    {
	unsigned x,y,z;
	assert(node->is_leaf);
	delete [] node->leaf.fields;
	node->is_leaf = false;
	for (x = 0; x < 2; x++)
	    for (y = 0; y < 2; y++)
		for (z = 0; z < 2; z++)
		    node->nonleaf.children[x][y][z] = new OctreeNode ();
    }

    void descend(unsigned x, unsigned y, unsigned z)
    {
	assert(!node->is_leaf);
	node = node->nonleaf.children[x][y][z];
	(x ? x_min : x_max) = (x_min + x_max) / 2;
	(y ? y_min : y_max) = (y_min + y_max) / 2;
	(z ? z_min : z_max) = (z_min + z_max) / 2;
	depth++;
    }

    void get_center(double *center_out)
    {
	center_out[0] = (x_min + x_max) * 0.5;
	center_out[1] = (y_min + y_max) * 0.5;
	center_out[2] = (z_min + z_max) * 0.5;
    }

    void find(const double *xyz)
    {
	while (!node->is_leaf)
	{
	    double center[3];
	    get_center(center);
	    descend(xyz[0] < center[0] ? 0 : 1,
	            xyz[1] < center[1] ? 0 : 1,
	            xyz[2] < center[2] ? 0 : 1);
	}
    }

    double get_range() const
    {
	// assuming that the octree is cubical
	return x_max - x_min;
    }

    OctreeNode *node;

    unsigned depth;
    double x_min,x_max;
    double y_min,y_max;
    double z_min,z_max;
};

#endif
