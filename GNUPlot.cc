#include "GNUPlot.hh"
#include <stdio.h>

/*
STLfile*  STLfile::readSTLfile(const char * filename)
{
    unsigned char header[80];
    FILE *fp = fopen (filename, "rb");
    STLfile *rv = 0;
    unsigned len;
    if (fp == 0)
    {
	fprintf(stderr, "error opening %s\n", filename);
	return 0;
    }
    if (fread (header, sizeof (header), 1, fp) != 1)
	goto too_short;
    if (fread (header, 4, 1, fp) != 1)
	goto too_short;
#if STL_ENDIANESS == BIG_ENDIAN
    len = (header[0] << 24)
        | (header[1] << 16)
        | (header[2] << 8)
        | (header[3] << 0);
#else
    len = (header[0] << 0)
        | (header[1] << 8)
        | (header[2] << 16)
        | (header[3] << 24);
#endif
    //printf ("len=%u (%08x)\n",len,len);
    rv = new STLfile;
    rv->count = len;
    rv->facet = new STLfacet[len];
    for (unsigned i =0; i < len; i++)
    {
	union
	{
	    STLfacet facet;
	    unsigned char data[50];
	} u;
	if (fread (&u, 50, 1, fp) != 1)
	    goto too_short;
#if STL_ENDIANESS != SYSTEM_ENDIANNESS
	for (unsigned k = 0; k < 12; k++)
	{
	    unsigned dummy;
	    dummy = u.data[k*4+0];
	    u.data[k*4+0] = u.data[k*4+3];
	    u.data[k*4+3] = dummy;
	    dummy = u.data[k*4+1];
	    u.data[k*4+1] = u.data[k*4+2];
	    u.data[k*4+2] = dummy;
	}
#endif
	rv->facet[i] = u.facet;
    }
    fclose (fp);

    return rv;

too_short:
    fprintf(stderr, "too short in file %s\n",filename);
    delete rv;
    return 0;
}

void STLfile::writeGNUPlotFile(const char * filename)
{
    FILE *fp = fopen (filename, "w");
    if (fp == 0)
    {
	fprintf(stderr, "error opening %s\n", filename);
	return;
    }
#define GNUPLOT_FORMAT "%.6f\t%.6f\t%.6f\n"
#define GNUPLOT_ARGS(pt)   ((pt)[0]),((pt)[1]),((pt)[2])
    for (unsigned i = 0; i < count; i++)
    {
	fprintf (fp, "# facet %d\n", i);
	fprintf (fp, GNUPLOT_FORMAT, GNUPLOT_ARGS(facet[i].v[0]));
	fprintf (fp, GNUPLOT_FORMAT, GNUPLOT_ARGS(facet[i].v[1]));
	fprintf (fp, GNUPLOT_FORMAT, GNUPLOT_ARGS(facet[i].v[2]));
	fprintf (fp, "\n");
    }
}
*/

