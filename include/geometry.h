#ifndef NCURSESPP_GEOMETRY_H__
#define NCURSESPP_GEOMETRY_H__

#include <cstddef>

namespace ncurses
{
struct Point
{
	int x;
	int y;
};

struct Size
{
	std::size_t w;
	std::size_t h;
};

struct Rect
{
	Point p;
	Size s;
};
}

#endif // NCURSESPP_GEOMETRY_H__
