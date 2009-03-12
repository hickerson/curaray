#ifndef __GRAPHICS_HH__
#define __GRAPHICS_HH__

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

struct GraphicsPrimative
{
};

struct Line : public GraphicsPrimative
{
};

struct Point : public GraphicsPrimative
{
    double position[3];
};

struct Polygon : public GraphicsPrimative
{
};

struct Text : public GraphicsPrimative
{
    string text;
    double position[3];
};

struct Graphics3D 
{
    GraphicsPrimative *primative;
};

#endif
