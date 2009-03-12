#ifndef __GNUPLOT_H__
#define __GNUPLOT_H__

#define GNUPLOT_FORMAT "%.6f\t%.6f\t%.6f\n"
#define GNUPLOT_ARGS(pt)   ((pt)[0]),((pt)[2]),((pt)[1])

/*
struct GNUPlotfacet {
    float normal[3];
    float v[3][3];
};
*/

/*
struct GNUPlotfile {
    int count;
    //STLfacet * facet;

    //static STLfile*  readSTLfile(const char * filename);
    void writeGNUPlotFile(const char * filename);
};
*/

#endif //__GNUPLOT_H__
