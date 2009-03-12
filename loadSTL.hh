#ifndef __LOADSTL_H__
#define __LOADSTL_H__

#include <string>
#include <stdlib.h>
using namespace std;



/*
 * 80 byte header
 *
 * 4 byte count
 */

//#define BIG_ENDIAN	0x04030201
//#define LITTLE_ENDIAN	0x01020304

#define SYSTEM_ENDIANNESS  LITTLE_ENDIAN
#define STL_ENDIANESS      LITTLE_ENDIAN

/*
 * 12 bytes - normal
 * 36 bytes - verticies
 * 2 bytes - unused padding
 */
struct STLfacet {
    float normal[3];
    float v[3][3];
    
    void writeMathematicaGraphicsNumber(ofstream &of);
    void writeMathematicaGraphicsPoint(ofstream &of);
    void writeMathematicaGraphics(ofstream &of);
};

struct STLfile {
    int count;
    STLfacet * facet;

    static STLfile*  readSTLfile(const char * filename);
    void writeGNUPlotFile(const char * filename);
    //void writeMathematicaGraphics(string filename);
    void writeMathematicaGraphics(const char * filename);
    void writeMathematicaGraphics(ofstream &of);
};

#endif //__LOADSTL_H__
