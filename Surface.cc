#include "Surface.hh"
#include <assert.h>

//STLSurface::STLSurface(string filename) {
STLSurface::STLSurface(const char * filename) 
	: stl_file(NULL)
{
    stl_file = STLfile::readSTLfile(filename);
    assert(stl_file);
}

//STLSurface::~STLSurface() {
//}

//void STLSurface::member() {
//    octree.setup_vector_fields(&field);
//    octree.walls = stl_file;
//}
